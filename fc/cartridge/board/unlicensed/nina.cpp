//AVE-NINA-01
//AVE-NINA-02
//AVE-NINA-03
//AVE-NINA-06

struct Nina : Board {

unsigned revision;

struct Settings {
  bool mirror;  //0 = vertical, 1 = horizontal
} settings;

bool prg_bank;
uint4 chr_bank[2];

uint8 prg_read(unsigned addr) {
  if(addr & 0x8000) return prgrom.read((prg_bank << 15) | (addr & 0x7fff));
  if((addr & 0xe000) == 0x6000) {
    if(prgram.size > 0) return prgram.read(addr);
  }
  return cpu.mdr();
}

void prg_write(unsigned addr, uint8 data) {
  switch(revision) {
  case  1:
  case  2:
    switch(addr) {
    case 0x7ffd: prg_bank    = data & 0x01; break;
    case 0x7ffe: chr_bank[0] = data & 0x0f; break;
    case 0x7fff: chr_bank[1] = data & 0x0f; break;
    }
    break;
  case  3:
  case  6:
    if((addr & 0xe100) == 0x4100) {
      prg_bank    = (data & 0x08) >> 3;
      chr_bank[0] = ((data & 0x07) << 1) | 0;
      chr_bank[1] = ((data & 0x07) << 1) | 1;
    }
    break;
  }
  if((addr & 0xe000) == 0x6000 && prgram.size > 0) prgram.write(addr, data);
}

uint8 chr_read(unsigned addr) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_read(addr);
  }
  return Board::chr_read((addr & 0x0fff) | (chr_bank[(addr & 0x1000) >> 12] << 12));
}

void chr_write(unsigned addr, uint8 data) {
  if(addr & 0x2000) {
    if(settings.mirror == 1) addr = ((addr & 0x0800) >> 1) | (addr & 0x03ff);
    return ppu.ciram_write(addr, data);
  }
  return Board::chr_write((addr & 0x0fff) | (chr_bank[(addr & 0x1000) >> 12] << 12), data);
}

void power() {
  reset();
}

void reset() {
  prg_bank = 0;
  chr_bank[0] = 0;
  chr_bank[1] = 0;
}

void serialize(serializer& s) {
  Board::serialize(s);
  s.integer(prg_bank);
  s.array(chr_bank);
}

Nina(Markup::Node& cartridge) : Board(cartridge) {
  string type = cartridge["board/type"].data;
  if(type.match("*NINA-01*")) revision =  1;
  if(type.match("*NINA-02*")) revision =  2;
  if(type.match("*NINA-03*")) revision =  3;
  if(type.match("*NINA-06*")) revision =  6;

  print("Revision: 0", revision, "\n");
  if(revision ==  1 || revision ==  2) {
    settings.mirror = 1;
  } else {
    settings.mirror = cartridge["mirror/mode"].data == "horizontal";
  }
}

};
