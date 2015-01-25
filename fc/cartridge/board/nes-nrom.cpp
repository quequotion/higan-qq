//NES-FAMILYBASIC
//NES-HROM
//NES-NROM-128
//NES-NROM-256
//NES-RROM
//NES-RROM-128
//NES-RTROM
//NES-SROM
//NES-STROM

struct NES_NROM : Board {

enum class Revision : unsigned {
  FAMILYBASIC,
  HROM,
  NROM,
  RROM,
  RTROM,
  SROM,
  STROM,
} revision;

struct Settings {
  bool mirror;  //0 = vertical, 1 = horizontal
} settings;

uint8 prg_read(unsigned addr) {
  if((addr & 0x8000) == 0x8000) return prgrom.read(addr);
  if(revision == Revision::FAMILYBASIC && (addr & 0xe000) == 0x6000)
    return prgram.read(addr);
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if(revision == Revision::FAMILYBASIC && (addr & 0xe000) == 0x6000)
    prgram.write(addr, data);
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_read(addr & 0x07ff);
  }
  if(chrram.size) return chrram.read(addr);
  return chrrom.read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_write(addr & 0x07ff, data);
  }
  if(chrram.size) return chrram.write(addr, data);
}

void serialize(serializer& s) {
  Board::serialize(s);
}

NES_NROM(Markup::Node& cartridge) : Board(cartridge) {
  string type = cartridge["board/type"].data;
  if(type.match("*FAMILYBASIC*")) revision = Revision::FAMILYBASIC;
  if(type.match("*HROM*"       )) revision = Revision::HROM;
  if(type.match("*RROM*"       )) revision = Revision::RROM;
  if(type.match("*SROM*"       )) revision = Revision::SROM;
  if(revision == Revision::HROM)
    settings.mirror = 0;
  else
    settings.mirror = cartridge["mirror/mode"].data == "horizontal";
}

};
