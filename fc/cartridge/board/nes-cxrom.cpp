//NES-CNROM
//NES-CPROM

struct NES_CxROM : Board {

enum class Revision : unsigned {
  CNROM,
  CPROM,
} revision;

struct Settings {
  bool mirror;  //0 = vertical, 1 = horizontal
  bool security;
  uint2 pass;
} settings;

uint2 chr_bank;

uint8 prg_read(unsigned addr) {
  if(addr & 0x8000) return prgrom.read(addr & 0x7fff);
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if(addr & 0x8000) {
    data &= prg_read(addr); // Bus conflicts
    chr_bank = data & 0x03;
  }
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_read(addr & 0x07ff);
  }
  if(settings.security) {
    if(chr_bank != settings.pass) return ppu.status.mdr;
  }
  switch(revision) {
  case Revision::CNROM:
    addr = (chr_bank * 0x2000) + (addr & 0x1fff);
    break;
  case Revision::CPROM:
    if(addr < 0x1000) addr = addr & 0x1fff;
    else              addr = (chr_bank * 0x1000) + (addr & 0x0fff);
    break;
  }
  return Board::chr_read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_write(addr & 0x07ff, data);
  }
  switch(revision) {
  case Revision::CNROM:
    addr = (chr_bank * 0x2000) + (addr & 0x1fff);
    break;
  case Revision::CPROM:
    if(addr < 0x1000) addr = addr & 0x1fff;
    else              addr = (chr_bank * 0x1000) + (addr & 0x0fff);
    break;
  }
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

NES_CxROM(Markup::Node& cartridge) : Board(cartridge) {
  string type = cartridge["board/type"].data;
  if(type.match("*CNROM*")) revision = Revision::CNROM;
  if(type.match("*CPROM*")) revision = Revision::CPROM;

  settings.mirror = cartridge["mirror/mode"].data == "horizontal";
  settings.security = cartridge["board/security"].exists();
  if(settings.security) {
    settings.pass = cartridge["board/security/pass"].integer();
  }
}

};
