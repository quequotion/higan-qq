#ifndef NALL_EMULATION_FAMICOM_HPP
#define NALL_EMULATION_FAMICOM_HPP

#include <nall/sha256.hpp>
#include <nall/string.hpp>

namespace nall {

struct FamicomCartridge {
  string markup;
  inline FamicomCartridge(const uint8_t *data, unsigned size);

//private:
  unsigned mapper;
  unsigned mirror;
  unsigned prgrom;
  unsigned prgram;
  unsigned chrrom;
  unsigned chrram;
  bool     battery;
  bool     region;
  bool     vs;
  // NES 2.0
  bool     pc10;
  bool     nes2;
  unsigned submapper;
};

FamicomCartridge::FamicomCartridge(const uint8_t *data, unsigned size) {
  markup = "";
  if(size < 16) return;
  if(data[0] != 'N' ) return;
  if(data[1] != 'E' ) return;
  if(data[2] != 'S' ) return;
  if(data[3] != 0x1A) return;

  mapper  = ((data[7] >> 4) << 4) | (data[6] >> 4);
  prgrom  = data[4] * 0x4000;
  chrrom  = data[5] * 0x2000;
  prgram  = 0u;
  chrram  = chrrom == 0u ? 8192u : 0u;
  mirror  = ((data[6] & 0x08) >> 2) | (data[6] & 0x01);
  battery = data[6] & 0x02;
  vs      = data[7] & 0x01;
  nes2    = data[7] & 0x0c == 0x08;
  if(!nes2) {
    // ignore the last 9 bytes of headers that have "DiskDude!" or other
    // messages written there
    if(data[12] == 0 && data[13] == 0 && data[14] == 0 && data[15] == 0) {
      prgram = data[8] * 0x2000;
      region = data[9] & 0x01;
    } else {
      mapper &= 0x0f;
      vs = false;
      pc10 = false;
    }
  } else {
    pc10 = data[7] & 0x02;
    mapper |= (data[8] & 0x0f) << 8;
    submapper |= data[8] >> 4;
    prgrom += (data[9] & 0x0f) * 0x400000;
    chrrom += (data[9] >> 4) * 0x200000;
    prgram = (data[10] & 0x0f == 0 ? 0 : 64) << (data[10] & 0x0f); // no battery
    prgram += (data[10] >> 4 == 0 ? 0 : 64) << (data[10] >> 4); // battery
    chrram = (data[11] & 0x0f == 0 ? 0 : 64) << (data[11] & 0x0f); // no battery
    chrram += (data[11] >> 4 == 0 ? 0 : 64) << (data[11] >> 4); // battery
    region = data[12] & 0x01;
  }

  // Galaxian has its PRG ROM doubled to fit within iNES's constraints.
  if(prgrom == 0x4000 && (prgrom + chrrom + 0x10 == size + 0x2000)) prgrom = 0x2000;

  markup.append("cartridge region=", region == 0 ? "NTSC" : "PAL", "\n");

  switch(mapper) {
  default:
    if(prgrom <= 8192) {
      markup.append("  board type=NAMCOT-3301\n");
    } else if(prgrom <= 16384) {
      markup.append("  board type=NES-NROM-128\n");
    } else {
      markup.append("  board type=NES-NROM-256\n");
    }
    markup.append("  mirror mode=", mirror == 0 ? "horizontal" : "vertical", "\n");
    break;

  case   1:
  case 155:
    if(prgram <= 8192) {
      markup.append("  board type=NES-SUROM\n");
    } else {
      markup.append("  board type=NES-SXROM\n");
    }
    markup.append("  chip type=MMC1", mapper != 155 ? "B2" : "A", "\n");
    if(!nes2 && !prgram) prgram = 8192;
    break;

  case   2:
  case 180:
    if(prgrom <= 131072) markup.append("  board type=NES-UNROM\n");
    else                 markup.append("  board type=NES-UOROM\n");
    markup.append("  chip type=74HC", mapper != 180 ? "32" : "08", "\n");
    markup.append("  mirror mode=", mirror == 0 ? "horizontal" : "vertical", "\n");
    break;

  case   3:
  case 185:
    markup.append("  board type=NES-CNROM\n");
    if(mapper == 185) {
      markup.append("    security pass=0x", hex(submapper & 3), "\n");
    }
    markup.append("  mirror mode=", mirror == 0 ? "horizontal" : "vertical", "\n");
    break;

  case   4:
  case 118:
  case 119:
    if(prgram != 0x400) {
      switch(mapper) {
      case   4:
        if(mirror & 2) markup.append("  board type=NES-TR1ROM\n");
        else           markup.append("  board type=NES-TLROM\n");
        break;
      case 118: markup.append("  board type=NES-TLSROM\n"); break;
      case 119: markup.append("  board type=NES-TQROM\n"); break;
      }
      markup.append("  chip type=MMC3B\n");
    } else {
      markup.append("  board type=NES-HKROM\n");
      markup.append("  chip type=MMC6n");
    }
    if(!nes2 && !prgram) prgram = 8192;
    if(mapper == 119 && !nes2 && !chrram) chrram = 0x2000;
    break;

  case   5:
    markup.append("  board type=NES-ELROM\n");
    markup.append("  chip type=MMC5\n");
    if(!nes2 && !prgram) prgram = 32768;
    break;

  case   7:
    markup.append("  board type=NES-AOROM\n");
    break;

  case   9:
    markup.append("  board type=NES-PNROM\n");
    markup.append("  chip type=MMC2\n");
    if(!nes2 && !prgram) prgram = 8192;
    break;

  case  10:
    markup.append("  board type=NES-FKROM\n");
    markup.append("  chip type=MMC4\n");
    if(!nes2 && !prgram) prgram = 8192;
    break;

  case  13:
    markup.append("  board type=NES-CPROM\n");
    markup.append("  mirror mode=", mirror == 0 ? "horizontal" : "vertical", "\n");
    break;

  case  16:
  case 153:
  case 159:
    switch(mapper) {
    case  16:
      markup.append("  board type=BANDAI-FCG\n");
      markup.append("  chip type=LZ93D50\n");
      markup.append("  chip type=24C02\n");
      break;
    case 153:
      markup.append("  board type=BANDAI-JUMP2\n");
      markup.append("  chip type=LZ93D50\n");
      if(!nes2 && !prgram) prgram = 8192;
      break;
    case 159:
      markup.append("  board type=BANDAI-LZ93D50\n");
      markup.append("  chip type=LZ93D50\n");
      markup.append("  chip type=24C01\n");
      break;
    }
    break;

  case  21: //VRC4a,VRC4c
  case  23: //VRC4e,VRC4f,VRC2b
  case  25: //VRC4b,VRC4d,VRC2c
    markup.append("  board type=KONAMI-VRC-4\n");
    markup.append("  chip type=", submapper == 15 ? "VRC2" : "VRC4", "\n");
    if(submapper == 0) {
      switch(mapper) {
      case 21: markup.append("    pinout a0=1 a1=2\n"); break;
      case 23: markup.append("    pinout a0=0 a1=1\n"); break;
      case 25: markup.append("    pinout a0=1 a1=0\n"); break;
      }
    } else if(submapper == 15) {
      markup.append("    pinout",
        " a0=", submapper == 25,
        " a1=", submapper == 23,
      "\n");
    } else {
      markup.append("    pinout",
        " a0=", submapper & 7,
        " a1=", (submapper & 7) + (((submapper & 8) >> 2) - 1),
      "\n");
    }
    if(!nes2 && !prgram) prgram = 8192;
    break;

  case  22:
    //VRC2a
    markup.append("  board type=KONAMI-VRC-2\n");
    markup.append("  chip type=VRC2\n");
    markup.append("    pinout a0=1 a1=0\n");
    break;

  case  24:
  case  26:
    markup.append("  board type=KONAMI-VRC-6\n");
    markup.append("  chip type=VRC6\n");
    switch(mapper) {
    case 24: markup.append("    pinout a0=0 a1=1\n"); break;
    case 26: markup.append("    pinout a0=1 a1=0\n"); break;
    }
    if(!nes2 && !prgram) prgram = 8192;
    break;

  case  34:
    markup.append("  board type=NES-BNROM\n");
    markup.append("  mirror mode=", mirror == 0 ? "horizontal" : "vertical", "\n");
    break;

  case  66:
    markup.append("  board type=NES-GNROM\n");
    markup.append("  mirror mode=", mirror == 0 ? "horizontal" : "vertical", "\n");
    break;

  case  69:
    markup.append("  board type=SUNSOFT-5B\n");
    markup.append("  chip type=5B\n");
    if(!nes2 && !prgram) prgram = 8192;
    break;

  case  73:
    markup.append("  board type=KONAMI-VRC-3\n");
    markup.append("  chip type=VRC3\n");
    markup.append("  mirror mode=", mirror == 0 ? "horizontal" : "vertical", "\n");
    if(!nes2 && !prgram) prgram = 8192;
    break;

  case  75:
    markup.append("  board type=KONAMI-VRC-1\n");
    markup.append("  chip type=VRC1\n");
    break;

  case  85:
    markup.append("  board type=KONAMI-VRC-7\n");
    markup.append("  chip type=VRC7\n");
    if(!nes2 && !prgram) prgram = 8192;
    break;

  case  76:
  case  88:
  case  95:
  case 154:
  case 206:
    switch(mapper) {
    case  76: markup.append("  board type=NAMCOT-3446\n"); break;
    case  88: markup.append("  board type=NAMCOT-3443\n"); break;
    case  95: markup.append("  board type=NAMCOT-3425\n"); break;
    case 154: markup.append("  board type=NAMCOT-3453\n"); break;
    case 206: markup.append("  board type=NAMCOT-3401\n"); break;
    // Normally 3416, but バベルの塔 (Babel no Tou) uses bankswitching despite
    // fitting entirely in the memory map, and other 32KB programs are not
    // broken by having it enabled.
    }
    markup.append("  chip type=Namcot108\n");
    markup.append("  mirror mode=", mirror == 0 ? "horizontal" : "vertical", "\n");
    break;
  }

  markup.append("  prg\n");
  if(prgrom) markup.append("    rom name=program.rom size=0x", hex(prgrom), "\n");
  if(prgram) {
    if(battery) markup.append("    ram name=save.ram size=0x", hex(prgram), "\n");
    else        markup.append("    ram size=0x", hex(prgram), "\n");
  }

  markup.append("  chr\n");
  if(chrrom) markup.append("    rom name=character.rom size=0x", hex(chrrom), "\n");
  if(chrram) markup.append("    ram size=0x", hex(chrram), "\n");
}

}

#endif
