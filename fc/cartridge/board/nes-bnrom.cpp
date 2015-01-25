//IREM-BNROM
//NES-BNROM

struct NES_BNROM : Board {

struct Settings {
  bool mirror;  //0 = vertical, 1 = horizontal
} settings;

uint2 prg_bank;

uint8 prg_read(unsigned addr) {
  if(addr & 0x8000) return prgrom.read((prg_bank << 15) | (addr & 0x7fff));
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if(addr & 0x8000) {
    // Bus conflicts
    data &= prg_read(addr);
    prg_bank = data & 0x03;
  }
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_read(addr);
  }
  return Board::chr_read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_write(addr, data);
  }
  return Board::chr_write(addr, data);
}

void power() {
}

void reset() {
  prg_bank = 0;
}

void serialize(serializer& s) {
  Board::serialize(s);
  s.integer(prg_bank);
}

NES_BNROM(Markup::Node& cartridge) : Board(cartridge) {
  settings.mirror = cartridge["mirror/mode"].data == "horizontal";
}

};
