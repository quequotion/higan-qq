// This board is intended for homebrew games that do not account for bus
// conflicts. Many Sachen and Panesian games require this board, but they were
// not the reason for its inclusion.

struct NoConflicts_CNROM : Board {

struct Settings {
  bool mirror;  //0 = vertical, 1 = horizontal
} settings;

uint2 chr_bank;

uint8 prg_read(unsigned addr) {
  if(addr & 0x8000) return prgrom.read(addr & 0x7fff);
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if(addr & 0x8000) chr_bank = data & 0x03;
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_read(addr & 0x07ff);
  }
  addr = (chr_bank * 0x2000) + (addr & 0x1fff);
  return Board::chr_read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_write(addr & 0x07ff, data);
  }
  addr = (chr_bank * 0x2000) + (addr & 0x1fff);
  Board::chr_write(addr, data);
}

void power() {
}

void reset() {
  chr_bank = 0;
}

void serialize(serializer& s) {
  Board::serialize(s);
  s.integer(chr_bank);
}

NoConflicts_CNROM(Markup::Node& cartridge) : Board(cartridge) {
  settings.mirror = cartridge["mirror/mode"].data == "horizontal";
}

};
