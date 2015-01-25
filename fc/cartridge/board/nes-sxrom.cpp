struct NES_SxROM : Board {

enum class Revision : unsigned {
  SAROM,
  SBROM,
  SCROM,
  SC1ROM,
  SEROM,
  SFROM,
  SFEXPROM,
  SGROM,
  SHROM,
  SH1ROM,
  SIROM,
  SJROM,
  SKROM,
  SLROM,
  SL1ROM,
  SL2ROM,
  SL3ROM,
  SLRROM,
  SMROM,
  SNROM,
  SNWEPROM,
  SOROM,
  SUROM,
  SXROM,
} revision;

MMC1 mmc1;

bool last_chr_bank;

void main() {
  mmc1.main();
}

unsigned ram_addr(unsigned addr) {
  unsigned bank = 0;
  if(revision == Revision::SOROM) bank = (mmc1.chr_bank[0] & 0x08) >> 3;
  if(revision == Revision::SUROM) bank = (mmc1.chr_bank[0] & 0x0c) >> 2;
  if(revision == Revision::SXROM) bank = (mmc1.chr_bank[0] & 0x0c) >> 2;
  return (bank << 13) | (addr & 0x1fff);
}

uint8 prg_read(unsigned addr) {
  if((addr & 0xe000) == 0x6000) {
    if(revision == Revision::SNROM) {
      if(mmc1.chr_bank[last_chr_bank] & 0x10) return cpu.mdr();
    }
    if(mmc1.ram_disable) return 0x00;
    if(prgram.size > 0) return prgram.read(ram_addr(addr));
  }

  if(addr & 0x8000) {
    switch(revision) {
      case Revision::SEROM:
      case Revision::SHROM:
      case Revision::SH1ROM:
        break;
      default:
        addr = mmc1.prg_addr(addr);
        if(revision == Revision::SUROM || revision == Revision::SXROM) {
          addr |= ((mmc1.chr_bank[last_chr_bank] & 0x10) >> 4) << 18;
        }
        break;
    }
    return prgrom.read(addr);
  }

  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if((addr & 0xe000) == 0x6000) {
    if(revision == Revision::SNROM) {
      if(mmc1.chr_bank[0] & 0x10) return;
    }
    if(mmc1.ram_disable) return;
    if(prgram.size > 0) return prgram.write(ram_addr(addr), data);
  }

  if(addr & 0x8000) return mmc1.mmio_write(addr, data);
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) return ppu.ciram_read(mmc1.ciram_addr(addr));
  last_chr_bank = mmc1.chr_mode ? ((addr & 0x1000) >> 12) : 0;
  return Board::chr_read(mmc1.chr_addr(addr));
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) return ppu.ciram_write(mmc1.ciram_addr(addr), data);
  last_chr_bank = mmc1.chr_mode ? ((addr & 0x1000) >> 12) : 0;
  return Board::chr_write(mmc1.chr_addr(addr), data);
}

void power() {
  mmc1.power();
}

void reset() {
  mmc1.reset();
}

void serialize(serializer& s) {
  Board::serialize(s);
  mmc1.serialize(s);
  s.integer(last_chr_bank);
}

NES_SxROM(Markup::Node& cartridge) : Board(cartridge), mmc1(*this, cartridge) {
  string type = cartridge["board/type"].data;
  if(type.match("*SAROM*"   )) revision = Revision::SAROM;
  if(type.match("*SBROM*"   )) revision = Revision::SBROM;
  if(type.match("*SCROM*"   )) revision = Revision::SCROM;
  if(type.match("*SC1ROM*"  )) revision = Revision::SC1ROM;
  if(type.match("*SEROM*"   )) revision = Revision::SEROM;
  if(type.match("*SFROM*"   )) revision = Revision::SFROM;
  if(type.match("*SFEXPROM*")) revision = Revision::SFEXPROM;
  if(type.match("*SGROM*"   )) revision = Revision::SGROM;
  if(type.match("*SHROM*"   )) revision = Revision::SHROM;
  if(type.match("*SH1ROM*"  )) revision = Revision::SH1ROM;
  if(type.match("*SIROM*"   )) revision = Revision::SIROM;
  if(type.match("*SJROM*"   )) revision = Revision::SJROM;
  if(type.match("*SKROM*"   )) revision = Revision::SKROM;
  if(type.match("*SLROM*"   )) revision = Revision::SLROM;
  if(type.match("*SL1ROM*"  )) revision = Revision::SL1ROM;
  if(type.match("*SL2ROM*"  )) revision = Revision::SL2ROM;
  if(type.match("*SL3ROM*"  )) revision = Revision::SL3ROM;
  if(type.match("*SLRROM*"  )) revision = Revision::SLRROM;
  if(type.match("*SMROM*"   )) revision = Revision::SMROM;
  if(type.match("*SNROM*"   )) revision = Revision::SNROM;
  if(type.match("*SNWEPROM*")) revision = Revision::SNWEPROM;
  if(type.match("*SOROM*"   )) revision = Revision::SOROM;
  if(type.match("*SUROM*"   )) revision = Revision::SUROM;
  if(type.match("*SXROM*"   )) revision = Revision::SXROM;
}

};
