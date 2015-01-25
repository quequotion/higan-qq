struct FDS : Board {

uint16 irq_timer = 0x0000;
uint8 fds_control = 0x2E;
bool irq_enable = false;
uint2 io_enable = 0b00;

uint8 prg_read(unsigned addr) {
  switch(addr) {
  case 0x4032:
    // 0x01: 0=Disk inserted;       1=Disk ejected
    // 0x02: 0=Disk ready;          1=Disk not ready
    // 0x04: 0=Not write protected; 1=Write protected (on if disk ejected)
    return 0x07;
  case 0x4033: return 0x00; // 7-bit expansion input; 0x80 means low battery
  }
  switch(addr & 0xe000) {
  case 0x6000:
  case 0x8000:
  case 0xa000:
  case 0xc000: return prgram.read(addr);
  case 0xe000: return prgrom.read(addr);
  }
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  switch(addr) {
  case 0x4020: irq_timer &= 0xff00 | data;
  case 0x4021: irq_timer &= 0x00ff | (data << 8);
  case 0x4022: irq_enable = data & 0x02;
  case 0x4023: io_enable = data & 0x03;
  case 0x4025: fds_control = data;
  }
  switch(addr & 0xe000) {
  case 0x6000:
  case 0x8000:
  case 0xa000:
  case 0xc000: prgram.write(addr,data); break;
  }
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) {
    if(fds_control & 0x08) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_read(addr & 0x07ff);
  }
  if(chrram.size) return chrram.read(addr);
  return chrrom.read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) {
    if(fds_control & 0x08) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_write(addr & 0x07ff, data);
  }
  if(chrram.size) return chrram.write(addr, data);
}

void serialize(serializer& s) {
  Board::serialize(s);
}

FDS(Markup::Node& cartridge) : Board(cartridge) {
}

};
