#include <sfc/sfc.hpp>

#define PPU_CPP
namespace SuperFamicom {

PPU ppu;

#include "background/background.cpp"
#include "mmio/mmio.cpp"
#include "screen/screen.cpp"
#include "sprite/sprite.cpp"
#include "window/window.cpp"
#include "serialization.cpp"

void PPU::step(unsigned clocks) {
  clock += clocks;
}

void PPU::synchronize_cpu() {
  if(CPU::Threaded == true) {
    if(clock >= 0 && scheduler.sync != Scheduler::SynchronizeMode::All) co_switch(cpu.thread);
  } else {
    while(clock >= 0) cpu.enter();
  }
}

void PPU::Enter() { ppu.enter(); }

void PPU::enter() {
  while(true) {
    if(scheduler.sync == Scheduler::SynchronizeMode::All) {
      scheduler.exit(Scheduler::ExitReason::SynchronizeEvent);
    }

    scanline();
    add_clocks(28);
    bg1.begin();
    bg2.begin();
    bg3.begin();
    bg4.begin();

    if(vcounter() <= 239) {
      for(signed pixel = -7; pixel <= 255; pixel++) {
        bg1.run(1);
        bg2.run(1);
        bg3.run(1);
        bg4.run(1);
        add_clocks(2);

        bg1.run(0);
        bg2.run(0);
        bg3.run(0);
        bg4.run(0);
        if(pixel >= 0) {
          sprite.run();
          window.run();
          screen.run();
        }
        add_clocks(2);
      }

      add_clocks(14);
      sprite.tilefetch();
    } else {
      add_clocks(1052 + 14 + 136);
    }

    add_clocks(lineclocks() - 28 - 1052 - 14 - 136);
  }
}

void PPU::add_clocks(unsigned clocks) {
  clocks >>= 1;
  while(clocks--) {
    tick(2);
    step(2);
    synchronize_cpu();
  }
}

void PPU::enable() {
  function<uint8 (unsigned)> reader = {&PPU::mmio_read, (PPU*)&ppu};
  function<void (unsigned, uint8)> writer = {&PPU::mmio_write, (PPU*)&ppu};

  bus.map(reader, writer, 0x00, 0x3f, 0x2100, 0x213f);
  bus.map(reader, writer, 0x80, 0xbf, 0x2100, 0x213f);
}

void PPU::power() {
  for(auto& n : vram) n = random(0x00);
  for(auto& n : oam) n = random(0x00);
  for(auto& n : cgram) n = random(0x00);
}

void PPU::reset() {
  create(Enter, system.cpu_frequency());
  PPUcounter::reset();
  memset(surface, 0, 512 * 512 * sizeof(uint32));

  mmio_reset();
  bg1.reset();
  bg2.reset();
  bg3.reset();
  bg4.reset();
  sprite.reset();
  window.reset();
  screen.reset();

  frame();
}

void PPU::exportRegisters(string &markup) {
  markup.append("ppu\n");
  // 2105
  markup.append("  bgmode:       ", regs.bgmode,       "\n");
  markup.append("  bg3-priority: ", regs.bg3_priority, "\n");
  // 2133
  markup.append("  pseudo-hires: ", regs.pseudo_hires, "\n");
  markup.append("  overscan:     ", regs.overscan,     "\n");
  // individual backgrounds
  auto bg = &bg1;
  for(unsigned bg_id = 1; bg_id <= 4; bg_id++) {
    switch(bg_id) {
      case 1: bg = &bg1; break;
      case 2: bg = &bg2; break;
      case 3: bg = &bg3; break;
      case 4: bg = &bg4; break;
    }
    markup.append("  bg\n");
    markup.append("    tile-size:     ",   bg->regs.tile_size,             "\n");
    markup.append("    mosaic:        ",   bg->regs.mosaic,                "\n");
    markup.append("    screen-addr:   0x", hex<4>(bg->regs.screen_addr),   "\n");
    markup.append("    screen-size:   ",   bg->regs.screen_size,           "\n");
    markup.append("    tiledata-addr: 0x", hex<4>(bg->regs.tiledata_addr), "\n");
    markup.append("    hoffset:       0x", hex<3>(bg->regs.hoffset),       "\n");
    markup.append("    voffset:       0x", hex<3>(bg->regs.voffset),       "\n");
    markup.append("    main-enable:   ",   bg->regs.main_enable,           "\n");
    markup.append("    sub-enable:    ",   bg->regs.sub_enable,            "\n");
  }
}

void PPU::scanline() {
  if(vcounter() == 0) {
    frame();
    bg1.frame();
    bg2.frame();
    bg3.frame();
    bg4.frame();
  }

  bg1.scanline();
  bg2.scanline();
  bg3.scanline();
  bg4.scanline();
  sprite.scanline();
  window.scanline();
  screen.scanline();
}

void PPU::frame() {
  system.frame();
  sprite.frame();

  display.interlace = regs.interlace;
  display.overscan = regs.overscan;
}

PPU::PPU() :
bg1(*this, Background::ID::BG1),
bg2(*this, Background::ID::BG2),
bg3(*this, Background::ID::BG3),
bg4(*this, Background::ID::BG4),
sprite(*this),
window(*this),
screen(*this) {
  surface = new uint32[512 * 512];
  output = surface + 16 * 512;
}

PPU::~PPU() {
  delete[] surface;
}

}
