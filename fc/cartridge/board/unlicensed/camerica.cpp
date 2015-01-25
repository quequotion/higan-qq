struct Camerica : Board {

enum class Revision : unsigned {
  ALGN, // Aladdin Game Enhancer
  ALGQ, // Aladdin Game Enhancer (Quattro Multicarts)
  BF9093,
  BF9096,
  BF9097,
} revision;

struct Settings {
  bool mirror;    //0 = vertical, 1 = horizontal
} settings;

uint4 prg_bank;
uint2 prg_block; // for ALGQ and BF9096
bool nametable; // for BF9097

uint8 prg_read(unsigned addr) {
  if((addr & 0x8000) == 0x0000) return cpu.mdr();
  if((addr & 0xc000) == 0x8000) {
    return prgrom.read((prg_block << 16) | (prg_bank << 14) | (addr & 0x3fff));
  } else {
    if(revision != Revision::ALGQ && revision != Revision::BF9096)
      return prgrom.read((0x0f << 14) | (addr & 0x3fff));
    else
      return prgrom.read((prg_block << 16) | (0x03 << 14) | (addr & 0x3fff));
  }
}

void prg_write(unsigned addr, uint8 data) {
  switch(revision) {
  case Revision::ALGQ:
  case Revision::BF9096:
    if((addr & 0xc000) == 0x8000) {
      prg_block = (data & 0x18) >> 3;
    }
    break;
  case Revision::BF9097:
    if((addr & 0xe000) == 0x8000) {
      nametable = data & 0x10;
    }
    break;
  }
  if((addr & 0xc000) == 0xc000) {
    switch(revision) {
    case Revision::ALGN:
    case Revision::BF9093: prg_bank = data & 0x0f; break;
    case Revision::ALGQ:
    case Revision::BF9096: prg_bank = data & 0x03; break;
    case Revision::BF9097: prg_bank = data & 0x07; break;
    }
  }
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) return ppu.ciram_read(ciram_addr(addr));
  return Board::chr_read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) return ppu.ciram_write(ciram_addr(addr), data);
  return Board::chr_write(addr, data);
}

unsigned ciram_addr(unsigned addr) const {
  if(revision != Revision::BF9097) {
    switch(settings.mirror) {
    case 0: return ((addr & 0x0400) >> 0) | (addr & 0x03ff);
    case 1: return ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    }
  } else {
    return (addr & 0x03ff) | (nametable << 10);
  }
}

void power() {
}

void reset() {
  prg_bank = 0;
  prg_block = 0;
  nametable = 0;
}

void serialize(serializer& s) {
  Board::serialize(s);

  s.integer(prg_bank);
  s.integer(prg_block);
  s.integer(nametable);
}

Camerica(Markup::Node& cartridge) : Board(cartridge) {
  string type = cartridge["board/type"].data;
  if(type.match("*ALGN*"  )) revision = Revision::ALGN;
  if(type.match("*ALGQ*"  )) revision = Revision::ALGQ;
  if(type.match("*BF9093*")) revision = Revision::BF9093;
  if(type.match("*BF9096*")) revision = Revision::BF9096;
  if(type.match("*BF9097*")) revision = Revision::BF9097;

  settings.mirror = cartridge["mirror/mode"].data == "horizontal";
}

};
