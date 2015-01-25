#include <fc/fc.hpp>

#define SYSTEM_CPP
namespace Famicom {

System system;
Configuration configuration;

#include "video.cpp"
#include "input.cpp"
#include "serialization.cpp"

#include <fc/scheduler/scheduler.cpp>

void System::run() {
  scheduler.sync = Scheduler::SynchronizeMode::None;

  scheduler.enter();
  if(scheduler.exit_reason() == Scheduler::ExitReason::FrameEvent) {
    video.update();
  }
}

void System::runtosave() {
  scheduler.sync = Scheduler::SynchronizeMode::PPU;
  runthreadtosave();

  scheduler.sync = Scheduler::SynchronizeMode::All;
  scheduler.thread = cpu.thread;
  runthreadtosave();

  scheduler.sync = Scheduler::SynchronizeMode::All;
  scheduler.thread = apu.thread;
  runthreadtosave();

  scheduler.sync = Scheduler::SynchronizeMode::All;
  scheduler.thread = cartridge.thread;
  runthreadtosave();

  scheduler.sync = Scheduler::SynchronizeMode::None;
}

void System::runthreadtosave() {
  while(true) {
    scheduler.enter();
    if(scheduler.exit_reason() == Scheduler::ExitReason::SynchronizeEvent) break;
    if(scheduler.exit_reason() == Scheduler::ExitReason::FrameEvent) {
      video.update();
    }
  }
}

void System::init() {
  assert(interface != nullptr);

  vsarcadeboard.init();

  video.init();

  input.connect(0, configuration.controller_port1);
  input.connect(1, configuration.controller_port2);
  input.connect(2, configuration.expansion_port);
}

void System::term() {
}

void System::load(Revision revision) {
  this->revision = revision;
  string manifest = string::read({interface->path(ID::System), "manifest.bml"});
  auto document = Markup::Document(manifest);

  //if(revision == Revision::PlayChoice10) {
  //  interface->loadRequest(ID::PC10ROM, document["system/pc10/rom/name"].data);
  //  if(!file::exists({interface->path(ID::System), document["system/pc10/rom/name"].data})) {
  //    interface->notify("Error: required PlayChoice-10 firmware bios-dual.rom not found.\n");
  //  }
  //}

  region = configuration.region;
  if(region == Region::Autodetect) {
    region = (cartridge.region() == Cartridge::Region::NTSC ? Region::NTSC : Region::PAL);
  }

  cpu_frequency = region() == Region::NTSC ? 21477272 : 26601712;

  switch(revision) {
  case Revision::Famicom:
    // most Famicoms use a PPU with open bus OAMDATA (read).
    // For now, we use an NES PPU where OAMDATA (read) is defined.
    if(region == Region::NTSC) ppu.revision = PPU::Revision::RP2C02G;
    if(region == Region::PAL)  ppu.revision = PPU::Revision::RP2C07;
    break;
  case Revision::PlayChoice10:
    ppu.revision = PPU::Revision::RP2C03B;
    break;
  case Revision::VSSystem:
    vsarcadeboard.load();
    input.connect(2, Input::Device::VSPanel);
    // PPU revision is set within cartridge.load().
    break;
  }

  serialize_init();
}

void System::unload() {
  switch(revision) {
  case Revision::VSSystem:
    vsarcadeboard.unload();
    break;
  }
}

void System::power() {
  cartridge.power();
  cpu.power();
  apu.power();
  ppu.power();

  switch(revision) {
  case Revision::VSSystem:
    vsarcadeboard.power();
    break;
  }

  reset();
}

void System::reset() {
  cartridge.reset();
  cpu.reset();
  apu.reset();
  // Only the Famicom's PPU will reset. The NES's PPU will not.
  ppu.reset();

  switch(revision) {
  case Revision::VSSystem:
    vsarcadeboard.reset();
    break;
  }

  scheduler.init();
  input.connect(0, configuration.controller_port1);
  input.connect(1, configuration.controller_port2);
  input.connect(2, configuration.expansion_port);
}

void System::scanline() {
  video.scanline();
  if(ppu.status.ly == 241) scheduler.exit(Scheduler::ExitReason::FrameEvent);
}

void System::frame() {
}

System::System() {
  region = Region::Autodetect;
}

}
