//NES-UNROM
//NES-UOROM

struct NES_UxROM : Board {

struct Settings {
  bool mirror;    //0 = vertical, 1 = horizontal
  bool chip_type; //0 = 74HC32, 1 = 74HC08
} settings;

uint4 prg_bank;

uint8 prg_read(unsigned addr) {
  if((addr & 0x8000) == 0x0000) return cpu.mdr();
  switch(settings.chip_type) {
  case 0:
    if((addr & 0xc000) == 0x8000) return prgrom.read((prg_bank << 14) | (addr & 0x3fff));
    else                          return prgrom.read((    0x0f << 14) | (addr & 0x3fff));
  case 1:
    if((addr & 0xc000) == 0x8000) return prgrom.read((    0x00 << 14) | (addr & 0x3fff));
    else                          return prgrom.read((prg_bank << 14) | (addr & 0x3fff));
  }
}

void prg_write(unsigned addr, uint8 data) {
  if(addr & 0x8000) {
    // Bus conflicts
    data &= prg_read(addr);
    prg_bank = data & 0x0f;
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

NES_UxROM(Markup::Node& cartridge) : Board(cartridge) {
  settings.mirror = cartridge["mirror/mode"].data == "horizontal";
  settings.chip_type = cartridge["chip/type"].data == "74HC08" ? 1 : 0;
}

};
