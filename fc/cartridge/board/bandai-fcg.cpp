//BANDAI-FCG
//BANDAI-FCG-1
//BANDAI-FCG-2
//BANDAI-JUMP2
//BANDAI-LZ93D50

struct BandaiFCG : Board {

enum class Revision : unsigned {
  FCGAll,
  FCG1,
  FCG2,
  JUMP2,
  LZ93D50,
} revision;

FCG fcg;

uint2 last_chr_bank;

void main() {
  fcg.main();
}

uint8 prg_read(unsigned addr) {
  if((addr & 0xe000) == 0x6000) {
    switch(revision) {
    case Revision::LZ93D50:
      //TODO: serial EEPROM support
      return 0x00 | (cpu.mdr() & 0xef);
    case Revision::JUMP2:
      return fcg.eeprom_i2c_scl ? fcg.ram_read(addr) : cpu.mdr();
    }
  }
  if((addr & 0x8000) == 0x8000) {
    if(revision != Revision::JUMP2)
      return prgrom.read(fcg.prg_addr(addr));
    else
      return prgrom.read(fcg.prg_addr(addr) | ((fcg.chr_bank[last_chr_bank] & 1) << 18));
  }
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  if((addr & 0xe000) == 0x6000) {
    switch(revision) {
    case Revision::FCGAll:
    case Revision::FCG1:
    case Revision::FCG2:
      return fcg.reg_write(addr, data);
    case Revision::LZ93D50:
      //TODO: serial EEPROM support
      break;
    case Revision::JUMP2:
      if(fcg.eeprom_i2c_scl) return fcg.ram_write(addr, data);
      else                   break;
    }
  }
  if((addr & 0x8000) == 0x8000) {
    switch(revision) {
    case Revision::FCGAll:
    case Revision::LZ93D50:
    case Revision::JUMP2:
      return fcg.reg_write(addr, data);
    }
  }
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) return ppu.ciram_read(fcg.ciram_addr(addr));
  last_chr_bank = 0;(addr & 0x0c00) >> 10;
  if(chrrom.size) return Board::chr_read(fcg.chr_addr(addr));
  if(chrram.size) return Board::chr_read(addr);
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) return ppu.ciram_write(fcg.ciram_addr(addr), data);
  last_chr_bank = 0;(addr & 0x0c00) >> 10;
  if(chrram.size) Board::chr_write(addr, data);
}

void power() {
  fcg.power();
}

void reset() {
  fcg.reset();
}

void serialize(serializer& s) {
  Board::serialize(s);
  fcg.serialize(s);
  s.integer(last_chr_bank);
}

BandaiFCG(Markup::Node& cartridge) : Board(cartridge), fcg(*this, cartridge) {
  string type = cartridge["board/type"].data;
  revision = Revision::FCGAll;
  if(type.match("*FCG-1*"  )) revision = Revision::FCG1;
  if(type.match("*FCG-2*"  )) revision = Revision::FCG2;
  if(type.match("*JUMP2*"  )) revision = Revision::JUMP2;
  if(type.match("*LZ93D50*")) revision = Revision::LZ93D50;
}

};
