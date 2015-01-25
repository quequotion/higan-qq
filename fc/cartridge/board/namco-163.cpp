struct Namco163 : Board {

uint6 prg_bank[3];
uint8 chr_bank[12];
uint15 irq_counter;
bool irq_enable;
uint2 mirror;
uint2 chrram_disable;

uint8 prg_read(unsigned addr) {
  switch(addr & 0xf800) {
  case 0x4800: break; // Audio
  case 0x5000: return irq_counter & 0xff;
  case 0x5800: return ((irq_counter >> 8) & 0x7f) | (irq_enable << 7);
  case 0x6000: case 0x6800: case 0x7000: case 0x7800:
    return prgram.read(addr & 0x1fff);
  case 0x8000: case 0x8800: case 0x9000: case 0x9800:
  case 0xa000: case 0xa800: case 0xb000: case 0xb800:
  case 0xc000: case 0xc800: case 0xd000: case 0xd800:
    return prgrom.read((prg_bank[(addr & 0x6000) >> 13] << 13) | (addr & 0x1fff));
  case 0xe000: case 0xe800: case 0xf000: case 0xf800:
    return prgrom.read((0x3f << 13) | (addr & 0x1fff));
  default: return cpu.mdr();
  }
}

void prg_write(unsigned addr, uint8 data) {
  switch(addr & 0xf800) {
  case 0x4800: break; // Audio
  case 0x5000: // IRQ Low
    irq_counter = (irq_counter & ~0xff) | data;
    break;
  case 0x5800: // IRQ High
    irq_counter = (irq_counter & 0xff) | ((data & 0x7f) << 8);
    irq_enable = data & 0x80;
    break;
  case 0x6000: case 0x6800: case 0x7000: case 0x7800:
    prgram.data[addr & 0x1fff] = data;
    break;
  case 0x8000: case 0x8800: case 0x9000: case 0x9800: // CHR Select
  case 0xa000: case 0xa800: case 0xb000: case 0xb800:
  case 0xc000: case 0xc800: case 0xd000: case 0xd800: // Nametable Select
    chr_bank[(addr & 0x7800) >> 11] = data;
    break;
  case 0xe000: // PRG Select 8000
    prg_bank[0] = data & 0x3f;
    mirror = (data & 0xc0) >> 6;
    break;
  case 0xe800: // PRG Select A000
    prg_bank[1] = data & 0x3f;
    chrram_disable = (data & 0xc0) >> 6;
    break;
  case 0xf000: // PRG Select C000
    prg_bank[2] = data & 0x3f;
    break;
  case 0xf800: // Write Protection for External RAM
    break;
  }
}

unsigned ciram_addr(unsigned addr) {
  bool nt;
  switch(mirror) {
  case 0: nt = 0; break;
  case 1: nt = addr & 0x400; break;
  case 2: nt = addr & 0x800; break;
  case 3: nt = 1; break;
  }
  return (addr & 0x03ff) | (nt << 10);
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) return ppu.ciram_read(ciram_addr(addr));
  uint8 bank = chr_bank[(addr & 0x1c00) >> 10];
  if(bank >= 0xe0 && chrram_disable & (1 << ((addr & 0x1000) >> 12))) {
    if(chrram.size) return chrram.read(addr);
    else            return ppu.ciram_read(ciram_addr(addr));
  } else return chrrom.read((bank << 10) | (addr & 0x3ff));
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) return ppu.ciram_write(ciram_addr(addr), data);
  uint8 bank = chr_bank[(addr & 0x1c00) >> 10];
  if(bank >= 0xe0 && chrram_disable & (1 << ((addr & 0x1000) >> 12))) {
    if(chrram.size) return chrram.write(addr, data);
    else            return ppu.ciram_write(ciram_addr(addr), data);
  }
}

void serialize(serializer& s) {
  Board::serialize(s);
}

void main() {
  while(true) {
    if(irq_enable && irq_counter != 0x7fff) {
      irq_counter++;
      if(irq_counter == 0x7fff) cpu.set_irq_line(1);
    }

    tick();
  }
}

void power() {
}

void reset() {
  prg_bank[0] = 0;
  prg_bank[1] = 0;
  prg_bank[2] = 0;
  chr_bank[0] = 0;
  chr_bank[1] = 0;
  chr_bank[2] = 0;
  chr_bank[3] = 0;
  chr_bank[4] = 0;
  chr_bank[5] = 0;
  chr_bank[6] = 0;
  chr_bank[7] = 0;
  chr_bank[8] = 0;
  chr_bank[9] = 0;
  chr_bank[10] = 0;
  chr_bank[11] = 0;
  irq_counter = 0;
  irq_enable = false;
  mirror = 0;
  chrram_disable = 0;
}

Namco163(Markup::Node& cartridge) : Board(cartridge) {
}

};
