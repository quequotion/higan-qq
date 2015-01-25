//VS

struct VS : Board {

bool bank;

uint8 prg_read(unsigned addr) {
  if((addr & 0xe000) == 0x6000) return prgram.read(addr);
  if(addr & 0x8000) {
    if(prgrom.size <= 0x8000 || (addr & 0xe000) > 0x8000 || bank == 0) {
      return prgrom.read(addr & 0x7fff);
    } else {
      return prgrom.read((addr & 0x1fff) | 0x8000);
    }
  }
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if(addr == 0x4016) bank = (data & 0x04) >> 2;
  if((addr & 0xe000) == 0x6000) prgram.write(addr, data);
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) return chrram.read(addr & 0x0fff);
  if(bank && chrrom.size < 0x2000) return ppu.status.mdr;
  return chrrom.read((bank * 0x2000) + (addr & 0x1fff));
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) return chrram.write(addr & 0x0fff, data);
}

void power() {
}

void reset() {
  bank = 0;
}

void serialize(serializer& s) {
  Board::serialize(s);
  s.integer(bank);
}

VS(Markup::Node& cartridge) : Board(cartridge) {
}

};
