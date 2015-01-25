//NAMCOT-3401
//NAMCOT-3406
//NAMCOT-3407
//NAMCOT-3416
//NAMCOT-3425
//NAMCOT-3443
//NAMCOT-3446
//NAMCOT-3453
//NES-DEROM
//NES-DE1ROM
//NES-DRROM

struct Namco34xx : Board {

enum class Revision : unsigned {
  Namco3401, // bankswitching used even if PRG is 32KB (バベルの塔/Tower of Babel)
  Namco3406,
  Namco3407,
  Namco3416,
  Namco3425,
  Namco3443,
  Namco3446,
  Namco3453,
  DEROM,
  DE1ROM,
  DRROM,
} revision;

struct Settings {
  bool mirror;  //0 = vertical, 1 = horizontal
} settings;

Namco108 namco108;

bool nametable; // for Namco3453, used only by Devil Man

unsigned prg_addr(unsigned addr) {
  if(revision == Revision::Namco3401 || prgrom.size > 0x8000) return namco108.prg_addr(addr);
  else return addr & 0x7fff;
}

uint8 prg_read(unsigned addr) {
  if(addr & 0x8000) return prgrom.read(prg_addr(addr));
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if(addr & 0x8000) {
    namco108.reg_write(addr, data);
    if(revision == Revision::Namco3453) nametable = data & 0x40;
  }
}

unsigned chr_addr(unsigned addr) {
  switch(revision) {
  case Revision::Namco3443:
  case Revision::Namco3453:
    return namco108.chr_addr(addr) | ((addr & 0x1000) << 4);
  case Revision::Namco3446:
    if(addr <= 0x07ff) return (namco108.chr_addr(0x1000) << 1) | (addr & 0x07ff);
    if(addr <= 0x0fff) return (namco108.chr_addr(0x1400) << 1) | (addr & 0x07ff);
    if(addr <= 0x17ff) return (namco108.chr_addr(0x1800) << 1) | (addr & 0x07ff);
    if(addr <= 0x1fff) return (namco108.chr_addr(0x1c00) << 1) | (addr & 0x07ff);
  default:
    return namco108.chr_addr(addr);
  }
}

uint8 chr_read(unsigned addr) {
  if(revision == Revision::DRROM) {
    if(addr & 0x2000) return chrram.data[mirror(addr & 0x0FFF, chrram.size)];
    return chrrom.data[mirror(namco108.chr_addr(addr), chrrom.size)];
  }
  if(addr & 0x2000) return ppu.ciram_read(ciram_addr(addr));
  return Board::chr_read(chr_addr(addr));
}

void chr_write(unsigned addr, uint8 data) {
  if(revision == Revision::DRROM) {
    if(addr & 0x2000) chrram.data[mirror(addr & 0x0FFF, chrram.size)] = data;
    return;
  }
  if(addr & 0x2000) return ppu.ciram_write(ciram_addr(addr), data);
  return Board::chr_write(chr_addr(addr), data);
}

unsigned ciram_addr(unsigned addr) const {
  switch(revision) {
  case Revision::Namco3425:
    return ((namco108.chr_addr(addr) & 0x8000) >> 5) | (addr & 0x03ff);
  case Revision::Namco3453:
    return (addr & 0x03ff) | (nametable ? 0x0400 : 0x0000);
  default:
    if(settings.mirror == 0) return ((addr & 0x0400) >> 0) | (addr & 0x03ff);
    if(settings.mirror == 1) return ((addr & 0x0800) >> 1) | (addr & 0x03ff);
  }
}

void reset() {
  nametable = 0;
}

void serialize(serializer& s) {
  Board::serialize(s);
}

Namco34xx(Markup::Node& cartridge) : Board(cartridge), namco108(*this, cartridge) {
  string type = cartridge["board/type"].data;
  if(type.match("*3401*")) revision = Revision::Namco3401;
  if(type.match("*3406*")) revision = Revision::Namco3406;
  if(type.match("*3407*")) revision = Revision::Namco3407;
  if(type.match("*3416*")) revision = Revision::Namco3416;
  if(type.match("*3425*")) revision = Revision::Namco3425;
  if(type.match("*3443*")) revision = Revision::Namco3443;
  if(type.match("*3446*")) revision = Revision::Namco3446;
  if(type.match("*3453*")) revision = Revision::Namco3453;
  if(type.match("*DEROM*")) revision = Revision::DEROM;
  if(type.match("*DE1ROM*")) revision = Revision::DE1ROM;
  if(type.match("*DRROM*")) revision = Revision::DRROM;
  if(type.match("*TENGEN-800002*")) revision = Revision::DEROM;
  if(type.match("*TENGEN-800030*")) revision = Revision::DE1ROM;
  if(type.match("*TENGEN-800004*")) revision = Revision::DRROM;

  if(revision != Revision::Namco3425 && revision != Revision::Namco3453)
    settings.mirror = cartridge["mirror/mode"].data == "horizontal";
}

};
