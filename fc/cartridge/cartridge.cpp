#include <fc/fc.hpp>

#define CARTRIDGE_CPP
namespace Famicom {

#include "markup.cpp"
#include "chip/chip.cpp"
#include "board/board.cpp"
Cartridge cartridge;

string Cartridge::title() {
  //if(information.title.famicomDiskSystem.empty() == false) {
  //  return {information.title.cartridge, " + ", information.title.famicomDiskSystem};
  //}

  return information.title.cartridge;
}

void Cartridge::Main() {
  cartridge.main();
}

void Cartridge::main() {
  board->main();
}

void Cartridge::load(System::Revision revision) {
  region = Region::NTSC;
  system.revision = revision;

  information.markup.cartridge         = "";
  //information.markup.famicomDiskSystem = "";

  information.title.cartridge         = "";
  //information.title.famicomDiskSystem = "";

  interface->loadRequest(ID::Manifest, "manifest.bml");
  parse_markup(information.markup.cartridge);

  if(board == nullptr) return;

  sha256_ctx sha;
  uint8 hash[32];
  sha256_init(&sha);
  //hash each ROM image that exists; any with size() == 0 is ignored by sha256_chunk()
  sha256_chunk(&sha, board->prgrom.data, board->prgrom.size);
  sha256_chunk(&sha, board->chrrom.data, board->chrrom.size);
  //finalize hash
  sha256_final(&sha);
  sha256_hash(&sha, hash);
  string result;
  for(auto& byte : hash) result.append(hex<2>(byte));
  sha256 = result;

  system.load(system.revision);
  loaded = true;
}

void Cartridge::unload() {
  if(loaded == false) return;

  system.unload();

  loaded = false;
  memory.reset();
}

void Cartridge::power() {
  board->power();
}

void Cartridge::reset() {
  create(Cartridge::Main, system.cpu_frequency());
  board->reset();
}

Cartridge::Cartridge() {
  loaded = false;
}

Cartridge::~Cartridge() {
  unload();
}

uint8 Cartridge::prg_read(unsigned addr) {
  return board->prg_read(addr);
}

void Cartridge::prg_write(unsigned addr, uint8 data) {
  return board->prg_write(addr, data);
}

uint8 Cartridge::chr_read(unsigned addr) {
  return board->chr_read(addr);
}

void Cartridge::chr_write(unsigned addr, uint8 data) {
  return board->chr_write(addr, data);
}

void Cartridge::scanline(unsigned y) {
  return board->scanline(y);
}

void Cartridge::serialize(serializer& s) {
  Thread::serialize(s);
  return board->serialize(s);
}

}
