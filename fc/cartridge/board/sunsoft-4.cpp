//SUNSOFT-4

struct Sunsoft4 : Board {

uint8 chr_bank[4];
uint7 ntrom_bank[2];
uint2 mirror;
bool nametable_mode;
uint8 prg_bank;

uint8 prg_read(unsigned addr) {
  if((addr & 0xc000) == 0x8000) return prgrom.read((prg_bank << 14) | (addr & 0x3fff));
  if((addr & 0xc000) == 0xc000) return prgrom.read((    0xff << 14) | (addr & 0x3fff));
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  switch(addr & 0xf000) {
  case 0x8000: chr_bank[0] = data; break;
  case 0x9000: chr_bank[1] = data; break;
  case 0xa000: chr_bank[2] = data; break;
  case 0xb000: chr_bank[3] = data; break;
  case 0xc000: ntrom_bank[0] = data | 0x80; break;
  case 0xd000: ntrom_bank[1] = data | 0x80; break;
  case 0xe000:
    mirror = data & 0x03;
    nametable_mode = data & 0x10;
    break;
  case 0xf000: prg_bank = data; break;
  }
}

unsigned ciram_addr(unsigned addr) {
  switch(mirror) {
  case 0: return ((addr & 0x0400) >> 0) | (addr & 0x03ff);
  case 1: return ((addr & 0x0800) >> 1) | (addr & 0x03ff);
  case 2: return 0x0000 | (addr & 0x03ff);
  case 3: return 0x0400 | (addr & 0x03ff);
  }
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) {
    addr = ciram_addr(addr);
    if(nametable_mode) return Board::chr_read(((ntrom_bank[(addr & 0x0400) >> 10] | 0x80) << 10) | (addr & 0x03FF));
    else               return ppu.ciram_read(addr);
  }
  addr = (chr_bank[(addr & 0x1800) >> 11] << 11) | (addr & 0x07ff);
  return Board::chr_read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) {
    if(nametable_mode == 0) return ppu.ciram_write(ciram_addr(addr), data);
  } else {
    return Board::chr_write(addr, data);
  }
}

void power() {
}

void reset() {
  chr_bank[0] = 0;
  chr_bank[1] = 0;
  chr_bank[2] = 0;
  chr_bank[3] = 0;
  ntrom_bank[0] = 0;
  ntrom_bank[1] = 0;
  mirror = 0;
  nametable_mode = 0;
  prg_bank = 0;
}

void serialize(serializer& s) {
  Board::serialize(s);
  s.array(chr_bank);
  s.array(ntrom_bank);
  s.integer(mirror);
  s.integer(nametable_mode);
  s.integer(prg_bank);
}

Sunsoft4(Markup::Node& cartridge) : Board(cartridge) {
}

};
