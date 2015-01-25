struct KonamiVRC6 : Board {

struct Settings {
  struct Pinout {
    unsigned a0;
    unsigned a1;
  } pinout;
} settings;

VRC6 vrc6;

uint8 prg_read(unsigned addr) {
  if(addr < 0x6000) return cpu.mdr();
  if(addr < 0x8000) return vrc6.ram_read(addr);
  return prgrom.read(vrc6.prg_addr(addr));
}

void prg_write(unsigned addr, uint8 data) {
  if(addr < 0x6000) return;
  if(addr < 0x8000) return vrc6.ram_write(addr, data);

  bool a0 = (addr & settings.pinout.a0);
  bool a1 = (addr & settings.pinout.a1);
  addr &= 0xf000;
  addr |= (a1 << 1) | (a0 << 0);
  return vrc6.reg_write(addr, data);
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) return ppu.ciram_read(vrc6.ciram_addr(addr));
  return Board::chr_read(vrc6.chr_addr(addr));
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) return ppu.ciram_write(vrc6.ciram_addr(addr), data);
  return Board::chr_write(vrc6.chr_addr(addr), data);
}

void serialize(serializer& s) {
  Board::serialize(s);
  vrc6.serialize(s);
}

void main() { vrc6.main(); }
void power() { vrc6.power(); }
void reset() { vrc6.reset(); }

KonamiVRC6(Markup::Node& cartridge) : Board(cartridge), vrc6(*this) {
  settings.pinout.a0 = 1 << decimal(cartridge["chip/pinout/a0"].data);
  settings.pinout.a1 = 1 << decimal(cartridge["chip/pinout/a1"].data);
}

};
