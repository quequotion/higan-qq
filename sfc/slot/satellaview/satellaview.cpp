#include <sfc/sfc.hpp>

#define SATELLAVIEW_CARTRIDGE_CPP
namespace SuperFamicom {

SatellaviewCartridge satellaviewcartridge;

void SatellaviewCartridge::init() {
}

void SatellaviewCartridge::save() {
  if(memory.size() >= 1) {
    file MEMPAK;
    string mempakpath = {nall::configpath(), "higan/bsxmem/"}; //TODO: user configurable path
    directory::create(mempakpath.data());
    string filenm; //char filenm [25];
    filenm.reserve(mempakpath.length()+9); //mempakpath + filename
    bool writeisdone = false;
    sprintf(filenm.data(), "%smempak.bs", (const char*)mempakpath.data()); //TODO: user configurable name; foltainer?
    if (MEMPAK.open(filenm, file::mode::write)) {
      int x;
      for (x=0; x <= memory.size()-1; x++) {
          MEMPAK.write(memory.read(x));
      }
      MEMPAK.close();
    }
  }
}

void SatellaviewCartridge::load() {
  if(memory.size() == 0) {
    memory.map(allocate<uint8>(1024 * 1024, 0xff), 1024 * 1024);
  }
}

void SatellaviewCartridge::unload() {
  memory.reset();
}

void SatellaviewCartridge::power() {
}

void SatellaviewCartridge::reset() {
  regs.command   = 0;
  regs.write_old = 0x00;
  regs.write_new = 0x00;

  regs.flash_enable = false;
  regs.read_enable  = false;
  regs.write_enable = false;
  regs.command_done = false;
  memory.write_protect(!regs.write_enable);
}

unsigned SatellaviewCartridge::size() const {
  return memory.size();
}

uint8 SatellaviewCartridge::read(unsigned addr) {
  if(readonly) return memory.read(bus.mirror(addr, memory.size()));

  unsigned addr2 = addr&0xffff;

  if(addr2 == 0x5555 && regs.flash_enable) {
    return 0x80;
  }

  if(regs.flash_stat_bsr && addr2 == 0x0002) {
    return 0xc0;
  }

  if(regs.flash_stat_gsr && addr2 == 0x0004) {
    return 0x82;
  }

  if(regs.flash_stat_csr) {
    regs.flash_stat_csr = false;
    return 0x80;
  }

  if(regs.read_enable && addr2 >= 0xff00 && addr2 <= 0xff13) {
    //read flash cartridge vendor information
    switch(addr - 0xff00) {
    case 0x00: return 0x4d;
    case 0x01: return 0x50;
    case 0x02: return 0x50;
    case 0x03: return 0x00;
    case 0x04: return 0x00;
    case 0x05: return 0x00;
    case 0x06: return 0x1a;  //0x2a = 8mbit, 0x2b = 16mbit (not known to exist, though BIOS recognizes ID)
    case 0x07: return 0x00;
    default:   return 0x00;
    }
  }

  return memory.read(addr);
}

void SatellaviewCartridge::write(unsigned addr, uint8 data) {
  if(readonly) return;

  if((addr & 0xff0000) == 0) {
    regs.write_old = regs.write_new;
    regs.write_new = data;

    if(regs.write_enable && regs.write_old == regs.write_new) {
      regs.write_enable = false;
      return memory.write(addr, data);
    }
  } else {
    if(regs.write_enable) {
      regs.write_enable = false;
      return memory.write(addr, data);
    }
  }
  if(regs.write_enable) {
    regs.write_enable = false;
    return memory.write(addr, data);
  }

  if(true) {
    regs.command <<= 8;
    regs.command  |= data;

    switch(regs.command & 0xff) {
      case 0x00:
        regs.flash_enable = false;
        regs.read_enable  = false;
        regs.write_enable = false;
        regs.flash_stat_csr = false;
        regs.flash_stat_gsr = false;
        regs.flash_stat_bsr = false;
        regs.command_done = true;
        break;
      case 0x38:
        regs.flash_enable = true;
        regs.read_enable  = true;
        regs.flash_stat_csr = false;
        regs.flash_stat_gsr = false;
        regs.flash_stat_bsr = false;
        break;
      case 0x10:
        regs.write_enable = true;
        regs.flash_stat_csr = true;
        regs.flash_stat_gsr = false;
        regs.flash_stat_bsr = false;
        regs.command_done = true;
        break;
      case 0x40:
        regs.write_enable = true;
        regs.flash_stat_csr = true;
        regs.flash_stat_gsr = false;
        regs.flash_stat_bsr = false;
        regs.command_done = true;
        break;
      case 0x50:
        regs.flash_stat_csr = false;
        regs.flash_stat_gsr = false;
        regs.flash_stat_bsr = false;
        regs.command_done = true;
      case 0x70:
        regs.flash_stat_csr = true;
        regs.write_enable = false;
        regs.flash_stat_gsr = false;
        regs.flash_stat_bsr = false;
        regs.command_done = true;
        break;
      case 0x71:
        regs.flash_stat_gsr = true;
        regs.flash_stat_bsr = true;
        regs.flash_stat_csr = false;
        regs.flash_enable = true;
        regs.command_done = true;
      case 0x72:
        regs.command_done = true;
        break;
      case 0x75:
        regs.read_enable  = true;
        regs.flash_stat_csr = false;
        regs.command_done = true;
        break;
      case 0xd0:
        regs.command_done = true;
        break;
      case 0xff:
        regs.flash_enable = false;
        regs.read_enable  = false;
        regs.write_enable = false;
        regs.flash_stat_csr = false;
        regs.flash_stat_gsr = false;
        regs.flash_stat_bsr = false;
        regs.command_done = true;
        break;
    }
    if(regs.command_done) {
      memory.write_protect(!regs.write_enable);
      //Page Erase
      if (regs.command == 0x20d0) {
        memory.write_protect(false);
        int erase_addr = addr & 0xff0000;
        uint32 x;
        for (x=0; x < 0xffff; x++) {
          memory.write(erase_addr+x, 0xff);
        }
        memory.write_protect(true);
      }
      //Chip Erase
      if (regs.command == 0xa7d0) {
        memory.write_protect(false);
        unsigned x;
        for (x=0; x < satellaviewcartridge.size(); x++) {
          memory.write(x, 0xff);
        }
        memory.write_protect(true);
      }
      regs.command = 0;
      regs.command_done = false;
    }
  }

  if(addr == 0x2aaa) {
    regs.command <<= 8;
    regs.command  |= data;
  }

  if(addr == 0x5555) {
    regs.command <<= 8;
    regs.command  |= data;

    if((regs.command & 0xffffff) == 0xaa5570) {
      regs.write_enable = false;
      regs.flash_enable = true;
    }

    if((regs.command & 0xffffff) == 0xaa55a0) {
      regs.write_old = 0x00;
      regs.write_new = 0x00;
      regs.flash_enable = true;
      regs.write_enable = true;
    }

    if((regs.command & 0xffffff) == 0xaa55f0) {
      regs.flash_enable = false;
      regs.read_enable  = false;
      regs.write_enable = true;
      regs.flash_stat_csr = false;
      regs.flash_stat_gsr = false;
      regs.flash_stat_bsr = false;
    }

    memory.write_protect(!regs.write_enable);
  }
}

}
