#include <sfc/sfc.hpp>

#define BSX_CPP
namespace SuperFamicom {

#include "serialization.cpp"
BSXCartridge bsxcartridge;

void BSXCartridge::init() {
}

void BSXCartridge::load() {
}

void BSXCartridge::unload() {
  rom.reset();
  ram.reset();
  psram.reset();
}

void BSXCartridge::power() {
}

void BSXCartridge::reset() {
  for(unsigned i = 0; i < 16; i++) r[i] = 0x00;
  r[0x02] = 0x80;
  r[0x03] = 0x80;
  r[0x05] = 0x80;
  r[0x06] = 0x80;
  r[0x07] = 0x80;
  r[0x08] = 0x80;
  r[0x09] = 0x80;
  r[0x0b] = 0x80;
  mmio_commit();
}

uint8 BSXCartridge::memory_access(bool write, Memory& memory, unsigned addr, uint8 data) {
  if(write == 0) return memory_read(memory, addr);
  memory_write(memory, addr, data);
}

uint8 BSXCartridge::memory_read(Memory& memory, unsigned addr) {
  addr = bus.mirror(addr, memory.size());
  return memory.read(addr);
}

void BSXCartridge::memory_write(Memory& memory, unsigned addr, uint8 data) {
  addr = bus.mirror(addr, memory.size());
  return memory.write(addr, data);
}

//mcu_access() allows mcu_read() and mcu_write() to share decoding logic
uint8 BSXCartridge::mcu_access(bool write, unsigned addr, uint8 data) {
//BIOS ROM Access
  if((addr & 0xe08000) == 0x008000) {  //$00-1f:8000-ffff
    if(r07 == 1) {
      addr = ((addr & 0x1f0000) >> 1) | (addr & 0x7fff);
      return memory_access(write, rom, addr, data);
    }
  }

  if((addr & 0xe08000) == 0x808000) {  //$80-9f:8000-ffff
    if(r08 == 1) {
      addr = ((addr & 0x1f0000) >> 1) | (addr & 0x7fff);
      return memory_access(write, rom, addr, data);
    }
  }

//PSRAM Access
//LoROM
  if(r02==0) {
    if((addr & 0xf28000) == 0x700000) { //$70-7d:0000-7fff
      if(r03==1) return memory_access(write, psram, addr & 0x07ffff, data);
    }
    if((addr & 0xf08000) == 0xf00000) { //$f0-ff:0000-7fff
      if(r04==1) return memory_access(write, psram, addr & 0x07ffff, data);
    }
    if((addr & 0xf08000) == 0x008000) { //$00-0f:8000-ffff
      if(r03==1 && r05==0 && r06==0) return memory_access(write, psram, ((addr & 0x7f0000) >> 1) | (addr & 0x7fff), data);
    }
    if((addr & 0xf08000) == 0x808000) { //$80-8f:8000-ffff
      if(r04==1 && r05==0 && r06==0) return memory_access(write, psram, ((addr & 0x7f0000) >> 1) | (addr & 0x7fff), data);
    }
    if((addr & 0xf08000) == 0x208000) { //$20-2f:8000-ffff
      if(r03==1 && r05==1 && r06==0) return memory_access(write, psram, ((addr & 0x7f0000) >> 1) | (addr & 0x7fff), data);
    }
    if((addr & 0xf08000) == 0xa08000) { //$a0-af:8000-ffff
      if(r04==1 && r05==1 && r06==0) return memory_access(write, psram, ((addr & 0x7f0000) >> 1) | (addr & 0x7fff), data);
    }
    if((addr & 0xf00000) == 0x400000) { //$40-4f:0000-ffff
      if(r03==1 && r05==0 && r06==1) return memory_access(write, psram, ((addr & 0x7f0000) >> 1) | (addr & 0x7fff), data);
    }
    if((addr & 0xf00000) == 0xc00000) { //$c0-cf:0000-ffff
      if(r04==1 && r05==0 && r06==1) return memory_access(write, psram, ((addr & 0x7f0000) >> 1) | (addr & 0x7fff), data);
    }
    if((addr & 0xf00000) == 0x600000) { //$60-6f:0000-ffff
      if(r03==1 && r05==1 && r06==1) return memory_access(write, psram, ((addr & 0x7f0000) >> 1) | (addr & 0x7fff), data);
    }
    if((addr & 0xf00000) == 0xe00000) { //$e0-ef:0000-ffff
      if(r04==1 && r05==1 && r06==1) return memory_access(write, psram, ((addr & 0x7f0000) >> 1) | (addr & 0x7fff), data);
    }
  } else {
//HiROM
    if((addr & 0xe0e000) == 0x206000) { //$20-3f:6000-7fff
      if(r03==1) return memory_access(write, psram, (addr&0x1fff)|0x6000, data);
    }
    if((addr & 0xe0e000) == 0xa06000) { //$a0-bf:6000-7fff
      if(r04==1) return memory_access(write, psram, (addr&0x1fff)|0x6000, data);
    }
    if((addr & 0xf80000) == 0x400000) { //$40-47:0000-ffff
      if(r03==1 && r05==0 && r06==0) return memory_access(write, psram, addr & 0x0fffff, data);
    }
    if((addr & 0xf80000) == 0x500000) { //$50-57:0000-ffff
      if(r03==1 && r05==1 && r06==0) return memory_access(write, psram, addr & 0x0fffff, data);
    }
    if((addr & 0xf80000) == 0x600000) { //$60-67:0000-ffff
      if(r03==1 && r05==0 && r06==1) return memory_access(write, psram, addr & 0x0fffff, data);
    }
    if((addr & 0xf80000) == 0x700000) { //$70-77:0000-ffff
      if(r03==1 && r05==1 && r06==1) return memory_access(write, psram, addr & 0x0fffff, data);
    }
    if((addr & 0xf80000) == 0xc0ffff) { //$c0-c7:0000-ffff
      if(r04==1 && r05==0 && r06==0) return memory_access(write, psram, addr & 0x0fffff, data);
    }
    if((addr & 0xf80000) == 0xd00000) { //$d0-d7:0000-ffff
      if(r04==1 && r05==1 && r06==0) return memory_access(write, psram, addr & 0x0fffff, data);
    }
    if((addr & 0xf80000) == 0xe00000) { //$e0-e7:0000-ffff
      if(r04==1 && r05==0 && r06==1) return memory_access(write, psram, addr & 0x0fffff, data);
    }
    if((addr & 0xf80000) == 0xf00000) { //$f0-f7:0000-ffff
      if(r04==1 && r05==1 && r06==1) return memory_access(write, psram, addr & 0x0fffff, data);
    }
  }

//Memory Pack Hole
  if(r02==0) {
    if((addr & 0xe08000) == 0x008000) { //$00-1f:8000-ffff
      if(r09==1 && r0b==0) return cpu.regs.mdr;
    }
    if((addr & 0xe00000) == 0x400000) { //$40-5f:0000-ffff
      if(r09==1 && r0b==1) return cpu.regs.mdr;
    }
    if((addr & 0xe08000) == 0x808000) { //$80-9f:8000-ffff
      if(r0a==1 && r0b==0) return cpu.regs.mdr;
    }
    if((addr & 0xe00000) == 0xc00000) { //$c0-df:0000-ffff
      if(r0a==1 && r0b==1) return cpu.regs.mdr;
    }
  } else {
    if((addr & 0xb08000) == 0x008000) { //$00-0f|$40-4f:0000-ffff
      if(r09==1 && r0b==0) return cpu.regs.mdr;
    }
    if((addr & 0xb08000) == 0x208000) { //$20-2f|$60-6f:0000-ffff
      if(r09==1 && r0b==1) return cpu.regs.mdr;
    }
    if((addr & 0xb08000) == 0x808000) { //$80-8f|$c0-cf:0000-ffff
      if(r0a==1 && r0b==0) return cpu.regs.mdr;
    }
    if((addr & 0xb08000) == 0xa08000) { //$a0-af|$e0-ef:0000-ffff
      if(r0a==1 && r0b==1) return cpu.regs.mdr;
    }
  }
// Memory Pack Acess
  if(((addr & 0x408000) == 0x008000)  //$00-3f|80-bf:8000-ffff
  || ((addr & 0x400000) == 0x400000)  //$40-7f|c0-ff:0000-ffff
  ) {
    if(r02 == 0) addr = ((addr & 0x7f0000) >> 1) | (addr & 0x7fff);
    Memory &memory = (Memory&)satellaviewcartridge;
    return memory_access(write, memory, addr & 0x7fffff, data);
  }

  return cpu.regs.mdr;
}

uint8 BSXCartridge::mcu_read(unsigned addr) {
  return mcu_access(0, addr);
}

void BSXCartridge::mcu_write(unsigned addr, uint8 data) {
  mcu_access(1, addr, data);
}

uint8 BSXCartridge::mmio_read(unsigned addr) {
  if((addr & 0xf0ffff) == 0x005000) {  //$00-0f:5000
    uint8 n = (addr >> 16) & 15;
    return r[n];
  }

  if((addr & 0xf8f000) == 0x105000) {  //$10-17:5000-5fff
    return memory_read(ram, ((addr >> 16) & 7) * 0x1000 + (addr & 0xfff));
  }

  return 0x00;
}

void BSXCartridge::mmio_write(unsigned addr, uint8 data) {
  if((addr & 0xf0ffff) == 0x005000) {  //$00-0f:5000
    uint8 n = (addr >> 16) & 15;
    r[n] = data;
    if(n == 0x0e && data & 0x80) mmio_commit();
    return;
  }

  if((addr & 0xf8f000) == 0x105000) {  //$10-17:5000-5fff
    return memory_write(ram, ((addr >> 16) & 7) * 0x1000 + (addr & 0xfff), data);
  }
}

void BSXCartridge::mmio_commit() {
  r00 = r[0x00] & 0x80;
  r01 = r[0x01] & 0x80;
  r02 = r[0x02] & 0x80;
  r03 = r[0x03] & 0x80;
  r04 = r[0x04] & 0x80;
  r05 = r[0x05] & 0x80;
  r06 = r[0x06] & 0x80;
  r07 = r[0x07] & 0x80;
  r08 = r[0x08] & 0x80;
  r09 = r[0x09] & 0x80;
  r0a = r[0x0a] & 0x80;
  r0b = r[0x0b] & 0x80;
  r0c = r[0x0c] & 0x80;
  r0d = r[0x0d] & 0x80;
  r0e = r[0x0e] & 0x80;
  r0f = r[0x0f] & 0x80;
}

}
