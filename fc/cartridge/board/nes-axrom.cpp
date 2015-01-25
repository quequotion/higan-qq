//NES-AMROM
//NES-ANROM
//NES-AN1ROM
//NES-AOROM

struct NES_AxROM : Board {

enum class Revision : unsigned {
  AMROM,
  ANROM,
  AN1ROM,
  AOROM,
} revision;

uint4 prg_bank;
bool mirror_select;

uint8 prg_read(unsigned addr) {
  if(addr & 0x8000) return prgrom.read((prg_bank << 15) | (addr & 0x7fff));
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if(addr & 0x8000) {
    // Bus conflicts
    if(revision == Revision::AMROM) data &= prg_read(addr);
    prg_bank = data & 0x0f;
    mirror_select = data & 0x10;
  }
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) return ppu.ciram_read((mirror_select << 10) | (addr & 0x03ff));
  return Board::chr_read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) return ppu.ciram_write((mirror_select << 10) | (addr & 0x03ff), data);
  return Board::chr_write(addr, data);
}

void power() {
}

void reset() {
  prg_bank = 0x0f;
  mirror_select = 0;
}

void serialize(serializer& s) {
  Board::serialize(s);

  s.integer(prg_bank);
  s.integer(mirror_select);
}

NES_AxROM(Markup::Node& cartridge) : Board(cartridge) {
  string type = cartridge["board/type"].data;
  if(type.match("*AMROM*" )) revision = Revision::AMROM;
  if(type.match("*ANROM*" )) revision = Revision::ANROM;
  if(type.match("*AN1ROM*")) revision = Revision::AN1ROM;
  if(type.match("*AOROM*" )) revision = Revision::AOROM;
}

};
