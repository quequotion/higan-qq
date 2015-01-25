struct NES_TxROM : Board {

enum class Revision : unsigned {
  TBROM,
  TEROM,
  TFROM,
  TGROM,
  TKROM,
  TKSROM,
  TLROM,
  TL1ROM,
  TL2ROM,
  TLSROM,
  TNROM,
  TQROM,
  TR1ROM,
  TSROM,
  TVROM,
  MCACC,
} revision;

MMC3 mmc3;

void main() {
  mmc3.main();
}

uint8 prg_read(unsigned addr) {
  if((addr & 0xe000) == 0x6000 && prgram.size > 0) return mmc3.ram_read(addr);
  if(addr & 0x8000) return prgrom.read(mmc3.prg_addr(addr));
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if((addr & 0xe000) == 0x6000 && prgram.size > 0) return mmc3.ram_write(addr, data);
  if(addr & 0x8000) return mmc3.reg_write(addr, data);
}

uint8 chr_read(unsigned addr) {
  mmc3.irq_test(addr);
  if(revision == Revision::TR1ROM || revision == Revision::TVROM) {
    if(addr & 0x2000) return chrram.data[mirror(addr & 0x0FFF, chrram.size)];
    return chrrom.data[mirror(mmc3.chr_addr(addr), chrrom.size)];
  }
  if(addr & 0x2000) return ppu.ciram_read(ciram_addr(addr));
  if(revision == Revision::TQROM) {
    if(mmc3.chr_addr(addr) & (0x40 << 10))
      return chrram.data[mirror(mmc3.chr_addr(addr), chrram.size)];
    else
      return chrrom.data[mirror(mmc3.chr_addr(addr), chrrom.size)];
  }
  return Board::chr_read(mmc3.chr_addr(addr));
}

void chr_write(unsigned addr, uint8 data) {
  mmc3.irq_test(addr);
  if(revision == Revision::TR1ROM || revision == Revision::TVROM) {
    if(addr & 0x2000) chrram.data[mirror(addr & 0x0FFF, chrram.size)] = data;
    return;
  }
  if(addr & 0x2000) return ppu.ciram_write(ciram_addr(addr), data);
  return Board::chr_write(mmc3.chr_addr(addr), data);
}

unsigned ciram_addr(unsigned addr) {
  switch(revision) {
  default:
    return mmc3.ciram_addr(addr);
  case Revision::TKSROM:
  case Revision::TLSROM:
    return ((mmc3.chr_addr(addr & 0xfff) & 0x20000) >> 7) | (addr & 0x3ff);
  }
}

void power() {
  mmc3.power();
}

void reset() {
  mmc3.reset();
}

void serialize(serializer& s) {
  Board::serialize(s);
  mmc3.serialize(s);
}

NES_TxROM(Markup::Node& cartridge) : Board(cartridge), mmc3(*this, cartridge) {
  string type = cartridge["board/type"].data;
  if(type.match("*TBROM*" )) revision = Revision::TBROM;
  if(type.match("*TEROM*" )) revision = Revision::TEROM;
  if(type.match("*TFROM*" )) revision = Revision::TFROM;
  if(type.match("*TGROM*" )) revision = Revision::TGROM;
  if(type.match("*TKROM*" )) revision = Revision::TKROM;
  if(type.match("*TKSROM*")) revision = Revision::TKSROM;
  if(type.match("*TLROM*" )) revision = Revision::TLROM;
  if(type.match("*TL1ROM*")) revision = Revision::TL1ROM;
  if(type.match("*TL2ROM*")) revision = Revision::TL2ROM;
  if(type.match("*TLSROM*")) revision = Revision::TLSROM;
  if(type.match("*TNROM*" )) revision = Revision::TNROM;
  if(type.match("*TQROM*" )) revision = Revision::TQROM;
  if(type.match("*TR1ROM*")) revision = Revision::TR1ROM;
  if(type.match("*TSROM*" )) revision = Revision::TSROM;
  if(type.match("*TVROM*" )) revision = Revision::TVROM;
  if(type.match("*MC-ACC*")) revision = Revision::MCACC;
}

};
