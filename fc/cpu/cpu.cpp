#include <fc/fc.hpp>

#define CPU_CPP
namespace Famicom {

CPU cpu;

#include "serialization.cpp"
#include "timing/timing.cpp"

void CPU::step(unsigned clocks) {
  apu.clock -= clocks;
  if(apu.clock < 0 && scheduler.sync != Scheduler::SynchronizeMode::All) co_switch(apu.thread);

  ppu.clock -= clocks;
  if(ppu.clock < 0 && scheduler.sync != Scheduler::SynchronizeMode::All) co_switch(ppu.thread);

  cartridge.clock -= clocks;
  if(cartridge.clock < 0 && scheduler.sync != Scheduler::SynchronizeMode::All) co_switch(cartridge.thread);

  input.port1->clock -= clocks * (uint64)input.port1->frequency;
  input.port2->clock -= clocks * (uint64)input.port2->frequency;
  input.expansion->clock -= clocks * (uint64)input.expansion->frequency;
  synchronize_controllers();
}

void CPU::synchronize_controllers() {
  if(input.port1->clock < 0) co_switch(input.port1->thread);
  if(input.port2->clock < 0) co_switch(input.port2->thread);
  if(input.expansion->clock < 0) co_switch(input.expansion->thread);
}

void CPU::Enter() { cpu.enter(); }

void CPU::enter() {
  while(true) {
    if(scheduler.sync == Scheduler::SynchronizeMode::All) {
      scheduler.exit(Scheduler::ExitReason::SynchronizeEvent);
    }

    cpu.main();
  }
}

void CPU::main() {
  if(status.interrupt_pending) {
    interrupt();
    return;
  }

  exec();
}

void CPU::power() {
  R6502::power();

  for(unsigned addr = 0; addr < 0x0800; addr++) ram[addr] = 0xff;
  ram[0x0008] = 0xf7;
  ram[0x0009] = 0xef;
  ram[0x000a] = 0xdf;
  ram[0x000f] = 0xbf;
}

void CPU::reset() {
  R6502::reset();
  create(CPU::Enter, system.cpu_frequency());

  regs.pc  = bus.read(0xfffc) << 0;
  regs.pc |= bus.read(0xfffd) << 8;

  status.interrupt_pending = false;
  status.nmi_pending = false;
  status.nmi_line = 0;
  status.irq_line = 0;
  status.irq_apu_line = 0;

  status.rdy_line = 1;
  status.rdy_addr_valid = false;
  status.rdy_addr_value = 0x0000;

  status.oam_dma_pending = false;
  status.oam_dma_page = 0x00;

  //status.controller_latch = false;
  //status.controller_port0 = 0;
  //status.controller_port1 = 0;
}

uint8 CPU::debugger_read(uint16 addr) {
  return bus.read(addr);
}

uint8 CPU::ram_read(uint16 addr) {
  return ram[addr & 0x07ff];
}

void CPU::ram_write(uint16 addr, uint8 data) {
  ram[addr & 0x07ff] = data;
}

uint8 CPU::read(uint16 addr) {
  if(system.revision != System::Revision::VSSystem) {
    if(addr == 0x4016) {
      return (mdr() & 0xe0) | input.port1->data() | input.expansion->data1();
    }

    if(addr == 0x4017) {
      return (mdr() & 0xe0) | input.port2->data() | input.expansion->data2();
    }
  } else { // if using VS. System
    if(addr >= 0x4016 && addr <= 0x5fff) return vsarcadeboard.read(addr);
  }

  return apu.read(addr);
}

void CPU::write(uint16 addr, uint8 data) {
  if(addr == 0x4014) {
    status.oam_dma_page = data;
    status.oam_dma_pending = true;
  }

  if(system.revision != System::Revision::VSSystem) {
    if(addr == 0x4016) {
      input.port1->latch(data & 1);
      input.port2->latch(data & 1);
      input.expansion->latch(data & 1);
    }
  } else { // if using VS. System
    if(addr >= 0x4016 && addr <= 0x5fff) vsarcadeboard.write(addr, data);
  }

  return apu.write(addr, data);
}

}
