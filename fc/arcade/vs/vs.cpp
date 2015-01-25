#include <fc/fc.hpp>

#define VS_ARCADE_BOARD_CPP
namespace Famicom {

VSArcadeBoard vsarcadeboard;

#include "serialization.cpp"

void VSArcadeBoard::init() {
}

void VSArcadeBoard::load() {
}

void VSArcadeBoard::unload() {
}

void VSArcadeBoard::power() {
}

void VSArcadeBoard::reset() {
}

void VSArcadeBoard::set_dip(uint16 dip) {
  this->dip = dip;
}

uint8 VSArcadeBoard::read(uint16 addr) {
  if(addr == 0x4016) return r4016();
  if(addr == 0x4017) return r4017();
  if(addr >= 0x4020 && addr <= 0x5fff) return r4020();
}

void VSArcadeBoard::write(uint16 addr, uint8 data) {
  if(addr == 0x4016) w4016(data);
  if(addr >= 0x4020 && addr <= 0x5fff) w4020(data);
}

uint8 VSArcadeBoard::r4016() {
  uint8 data = 0x80; // 0x00 for slave CPU, 0x80 for master CPU
  if(!swap_controllers) data |= input.port1->data() & 0x03;
  else                  data |= input.port2->data() & 0x03;
  data |= input.expansion->data1(); // buttons 1 and 3
  data |= (dip & 0x03) << 3;
  data |= input.expansion->data() << 2; // Service button and coins
  return data;
}

uint8 VSArcadeBoard::r4017() {
  uint8 data = 0x00;
  if(!swap_controllers) data |= input.port2->data() & 0x03;
  else                  data |= input.port1->data() & 0x03;
  data |= input.expansion->data2(); // buttons 2 and 4
  data |= dip & 0xfc;
  return data;
}

uint8 VSArcadeBoard::r4020() {
  write(0x4020, cpu.mdr());
  return cpu.mdr();
}

void VSArcadeBoard::w4016(uint8 data) {
  input.port1->latch(data & 1);
  input.port2->latch(data & 1);
  input.expansion->latch(data & 1);
}

void VSArcadeBoard::w4020(uint8 data) {
  // increment coin counter
}

}
