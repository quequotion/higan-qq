#include <sfc/sfc.hpp>

#define SATELLAVIEW_BASE_UNIT_CPP
namespace SuperFamicom {

SatellaviewBaseUnit satellaviewbaseunit;

void SatellaviewBaseUnit::init() {
}

void SatellaviewBaseUnit::load() {
  bus.map(
    {&SatellaviewBaseUnit::read, &satellaviewbaseunit},
    {&SatellaviewBaseUnit::write, &satellaviewbaseunit},
    0x00, 0x3f, 0x2188, 0x219f
  );
  bus.map(
    {&SatellaviewBaseUnit::read, &satellaviewbaseunit},
    {&SatellaviewBaseUnit::write, &satellaviewbaseunit},
    0x80, 0xbf, 0x2188, 0x219f
  );
}

void SatellaviewBaseUnit::unload() {
}

void SatellaviewBaseUnit::power() {
}

void SatellaviewBaseUnit::reset() {
  BSXF.close();
  regs.BSXF_NUM = 0;
  memset(&regs, 0x00, sizeof regs);
}

void SatellaviewBaseUnit::SatellaviewTuneInA(uint8 filenumber) {
  BSXF.close();
  uint16 Signal_Nb=regs.r2188^(regs.r2189*256);
  string filenm;
  filenm.reserve(nall::configpath().length()+21+4+3);//configpath + bsxdat path + channel + program
  sprintf(filenm.data(), "%shigan/bsxdat/BSX%04.4hX-%d.bin", (const char*)nall::configpath(), Signal_Nb, filenumber);
  BSXF.open(filenm.data(), file::mode::read);
  if(BSXF.size()!= -1) {
    regs.BSX_access=true;
    regs.BSXF_Signal++;
    float QueueSize = BSXF.size() / 22.;
    regs.BSXF_Queue = (uint8)(ceil(QueueSize));
    regs.BSXF_1ST = true;
    }
  else {
    regs.BSX_access=false;
    regs.BSXF_Signal=0;
    }
}

void SatellaviewBaseUnit::SatellaviewTuneInB(uint8 filenumber) {
  BSXF2.close();
  uint16 Signal_Nb=regs.r218e^(regs.r218f*256);
  string filenm;
  filenm.reserve(nall::configpath().length()+21+4+3); //configpath + bsxdat path + channel + program
  sprintf(filenm.data(), "%shigan/bsxdat/BSX%04.4hX-%d.bin", (const char*)nall::configpath(), Signal_Nb, filenumber);
  BSXF2.open(filenm.data(), file::mode::read);
  if(BSXF2.size()!= -1) {
    regs.BSX2_access=true;
    regs.BSXF2_Signal++;
    float QueueSize = BSXF2.size() / 22.;
    regs.BSXF2_Queue = (uint8)(ceil(QueueSize));
    regs.BSXF2_1ST = true;
    }
  else {
    regs.BSX2_access=false;
    regs.BSXF2_Signal=0;
    }
}

uint8 SatellaviewBaseUnit::GetTime(bool reset_count) {
  if(reset_count == true) {
    regs.time_counter = 0;
    return 0xff;
  }
  unsigned counter = regs.time_counter;
  regs.time_counter++;
  if(regs.time_counter >= 22) regs.time_counter = 0;
  if(counter == 0) {
    time_t rawtime;
    time(&rawtime);
    tm *t = localtime(&rawtime);
    regs.time_hour   = t->tm_hour;
    regs.time_minute = t->tm_min;
    regs.time_second = t->tm_sec;
    regs.time_weekday = (t->tm_wday)++;
    regs.time_day = (t->tm_mday)++;
    regs.time_month = t->tm_mon;
    uint16 time_year = (t->tm_year) + 1900;
    regs.time_yearL = time_year & 0xFF;
    regs.time_yearH = time_year >> 8;
  }

  switch(counter) {
    case  0: return 0x00;  //???
    case  1: return 0x00;  //???
    case  2: return 0x00;  //???
    case  3: return 0x00;  //???
    case  4: return 0x03;  //???
    case  5: return 0x01;
    case  6: return 0x01;
    case  7: return 0x00;
    case  8: return 0x00;
    case  9: return 0x00;
    case 10: return regs.time_second;
    case 11: return regs.time_minute;
    case 12: return regs.time_hour;
    case 13: return regs.time_weekday;
    case 14: return regs.time_day;
    case 15: return regs.time_month;
    case 16: return regs.time_yearL;  //???
    case 17: return regs.time_yearH;  //???
  }
  return 0;
}

uint8 SatellaviewBaseUnit::read(unsigned addr) {
  addr &= 0xffff;

  switch(addr) {
    case 0x2188: return regs.r2188;
    case 0x2189: return regs.r2189;
    case 0x218a: {
      if(regs.r2188 == 0 && regs.r2189 == 0) {
        return 0x01;
      }
      if (regs.BSXF_Queue <= 0) {
        regs.BSXF_NUM++;
        SatellaviewTuneInA(regs.BSXF_NUM-1);
      }
      if(!regs.BSX_access && (regs.BSXF_NUM-1) > 0) {
        regs.BSXF_NUM=1;
        SatellaviewTuneInA(regs.BSXF_NUM-1);
      }
      if(regs.BSX_access) {
        regs.r218b_chk=true;
        regs.r218c_chk=true;
        return regs.BSXF_Queue;
      }
      else return 0;
    }
    case 0x218b: {
      if(regs.r218b_port) {
        if(regs.r2188 == 0 && regs.r2189 == 0) {
          regs.r218b = 0x90;
          return 0x90;
        }
        if(regs.BSX_access) {
          regs.r218b_chk=false;
          uint8 lol = 0;
          if (regs.BSXF_1ST) {
            lol = 0x10;
            regs.BSXF_1ST = false;
          }
          regs.BSXF_Queue--;
          if (regs.BSXF_Queue==0) { lol |= 0x80; }
          regs.r218d |= lol;
          return lol;
        }
      }
      else return 0x00;
    }
    case 0x218c: {
      if(regs.r218c_port) {
        if(regs.r2188 == 0 && regs.r2189 == 0) {
          return GetTime(false);
        }
        if(regs.BSX_access) {
          return BSXF.read();
        }
      }
      else return 0x00;
    }
    case 0x218d: {
      uint8 lol = regs.r218d;
    regs.r218d = 0;
    return lol;
    }
    case 0x218e: return regs.r218e;
    case 0x218f: return regs.r218f;
    case 0x2190: {
      if(regs.r218e == 0 && regs.r218f == 0) {
        return 0x01;
      }
      if (regs.BSXF2_Queue <= 0) {
        regs.BSXF2_NUM++;
        SatellaviewTuneInB(regs.BSXF2_NUM-1);
      }
      if(!regs.BSX2_access && (regs.BSXF2_NUM-1) > 0) {
        regs.BSXF2_NUM=1;
        SatellaviewTuneInB(regs.BSXF2_NUM-1);
      }
      if(regs.BSX2_access) {
        regs.r2191_chk=true;
        regs.r2192_chk=true;
        return regs.BSXF2_Queue;
      }
      else return 0;
    }
    case 0x2191: {
      if(regs.r2191_port) {
        if(regs.r218e == 0 && regs.r218f == 0) {
          regs.r2193 = 0x90;
          return 0x90;
        }
        if(regs.BSX2_access) {
          uint8 lol = 0;
          if (regs.BSXF2_1ST) {
            lol = 0x10;
            regs.BSXF2_1ST = false;
          }
          regs.BSXF2_Queue--;
          if (regs.BSXF2_Queue==0) { lol |= 0x80; }
          regs.r2193 |= lol;
          return lol;
        }
      }
      else return 0;
    }

    case 0x2192: {
      if(regs.r2192_port) {
        if(regs.r218e == 0 && regs.r218f == 0) {
          return GetTime(false);
        }
        if(regs.BSX2_access) {
          return BSXF2.read();
        }
        else return 0x00;
      } break;
    } //shouldn't this be here (instead of after this switch)?
    case 0x2193: {
      uint8 lol = regs.r2193;
      regs.r2193 = 0;
      return lol;
    }
    case 0x2194: return 0xff; //regs.r2194;
    case 0x2196: return regs.r2196;
    case 0x2197: return regs.r2197;
    case 0x2199: return regs.r2199;
  }

  return cpu.regs.mdr;
}

void SatellaviewBaseUnit::write(unsigned addr, uint8 data) {
  addr &= 0xffff;

  switch(addr) {
  case 0x2188: {
    if (regs.r2188 != data) {
      regs.BSXF_Signal = 0;
      regs.BSXF_NUM = 0;
    }
    else regs.BSXF_Signal++;
    regs.r2188 = data;
  } break;

  case 0x2189: {
    if (regs.r2189 != data) {
      regs.BSXF_Signal = 0;
      regs.BSXF_NUM = 0;
    }
    else regs.BSXF_Signal++;
    regs.r2189 = data;
  } break;

  case 0x218a: {
    regs.r218a = data;
  } break;

  case 0x218b: {
    if (data && 1 == 1) {
      regs.r218b_port=true;
      regs.r218b_chk=true;
    }
    else regs.r218b_port=false;
  } break;

  case 0x218c: {
    if (regs.r2188 == 0 && regs.r2189 == 0) { GetTime(true); }
    if (data && 1 == 1) {
      regs.r218c_port=true;
      regs.r218c_chk=true;
    }
    else regs.r218c_port=false;
  } break;

  case 0x218e: {
    if (regs.r218e != data) {
      regs.BSXF2_Signal = 0;
      regs.BSXF2_NUM = 0;
    }
    else regs.BSXF2_Signal++;
    regs.r218e = data;
  } break;

  case 0x218f: {
    if (regs.r218f != data) {
      regs.BSXF2_Signal = 0;
      regs.BSXF2_NUM = 0;
    }
    else regs.BSXF2_Signal++;
    regs.r218f = data;
  } break;

  case 0x2191: {
    if (data && 1 == 1) regs.r2191_port=true;
    else regs.r2191_port=false;
    regs.time_counter = 0;
  } break;

  case 0x2192: {
    if (regs.r218e == 0 && regs.r218f == 0) { GetTime(true); }
    if (data && 1 == 1) regs.r2192_port=true;
    else regs.r2192_port=false;
  } break;

  case 0x2193: {
    regs.r2193 = data;
  } break;

  case 0x2194: {
    regs.r2194 = data;
  } break;

  case 0x2197: {
    regs.r2197 = data;
  } break;

  case 0x2199: {
    regs.r2199 = data;
  } break;
  }
}

}
