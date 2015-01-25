struct SingleChip : Board {

struct Settings {
  uint4 va10;  //10 = vertical, 11 = horizontal, 12 = BLK0, 13 = BLK1
} settings;

uint8 prg_read(unsigned addr) {
  if(addr & 0x8000) return prgrom.read(addr);
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) {
    switch(settings.va10) {
    case 10: addr = (addr & 0x07ff);
    case 11: addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    case 12: addr = (addr & 0x03ff);
    case 13: addr = (addr & 0x03ff) | 0x0400;
    }
    return ppu.ciram_read(addr & 0x07ff);
  }
  return ppu.ciram_read(addr & 0x07ff);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) {
    switch(settings.va10) {
    case 10: addr = (addr & 0x07ff);
    case 11: addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    case 12: addr = (addr & 0x03ff);
    case 13: addr = (addr & 0x03ff) | 0x0400;
    }
    return ppu.ciram_write(addr & 0x07ff, data);
  }
  return ppu.ciram_write(addr & 0x07ff, data);
}

void serialize(serializer& s) {
  Board::serialize(s);
}

SingleChip(Markup::Node& cartridge) : Board(cartridge) {
  settings.va10 = numeral(cartridge["board/va10"].data);
}

};
