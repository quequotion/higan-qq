#include "bandai-fcg.cpp"
#include "konami-vrc1.cpp"
#include "konami-vrc2.cpp"
#include "konami-vrc3.cpp"
#include "konami-vrc4.cpp"
#include "konami-vrc6.cpp"
#include "konami-vrc7.cpp"
#include "namco-163.cpp"
#include "namco-34xx.cpp"
#include "nes-axrom.cpp"
#include "nes-bnrom.cpp"
#include "nes-cxrom.cpp"
#include "nes-exrom.cpp"
#include "nes-fxrom.cpp"
#include "nes-gxrom.cpp"
#include "nes-hkrom.cpp"
#include "nes-nrom.cpp"
#include "nes-pxrom.cpp"
#include "nes-sxrom.cpp"
#include "nes-txrom.cpp"
#include "nes-uxrom.cpp"
#include "sunsoft-4.cpp"
#include "sunsoft-5b.cpp"
#include "fds.cpp"
#include "vs.cpp"

// Unlicensed board definitions; feel free to remove
#include "unlicensed/camerica.cpp"
#include "unlicensed/colordreams-74377.cpp"
#include "unlicensed/mlt-action52.cpp"
#include "unlicensed/nina.cpp"
#include "unlicensed/noconflicts-cnrom.cpp"
#include "unlicensed/single-chip.cpp"

uint8 Board::Memory::read(unsigned addr) const {
  return data[mirror(addr, size)];
}

void Board::Memory::write(unsigned addr, uint8 byte) {
  if(writable) data[mirror(addr, size)] = byte;
}

unsigned Board::mirror(unsigned addr, unsigned size) {
  unsigned base = 0;
  if(size) {
    unsigned mask = 1 << 23;
    while(addr >= size) {
      while(!(addr & mask)) mask >>= 1;
      addr -= mask;
      if(size > mask) {
        size -= mask;
        base += mask;
      }
      mask >>= 1;
    }
    base += addr;
  }
  return base;
}

void Board::main() {
  while(true) {
    if(scheduler.sync == Scheduler::SynchronizeMode::All) {
      scheduler.exit(Scheduler::ExitReason::SynchronizeEvent);
    }

    cartridge.clock += (system.region() == System::Region::NTSC ? 12 : 16) * 4095;
    tick();
  }
}

void Board::tick() {
  cartridge.clock += (system.region() == System::Region::NTSC ? 12 : 16);
  if(cartridge.clock >= 0 && scheduler.sync != Scheduler::SynchronizeMode::All) co_switch(cpu.thread);
}

uint8 Board::chr_read(unsigned addr) {
  if(chrram.size) return chrram.data[mirror(addr, chrram.size)];
  if(chrrom.size) return chrrom.data[mirror(addr, chrrom.size)];
  return 0u;
}

void Board::chr_write(unsigned addr, uint8 data) {
  if(chrram.size) chrram.data[mirror(addr, chrram.size)] = data;
}

void Board::power() {
}

void Board::reset() {
}

void Board::serialize(serializer& s) {
  if(prgram.size) s.array(prgram.data, prgram.size);
  if(chrram.size) s.array(chrram.data, chrram.size);
}

Board::Board(Markup::Node& cartridge) {
  Famicom::cartridge.board = this;

  information.type = cartridge["board/type"].data;
  information.battery = cartridge["prg/ram/name"].exists();

  auto prom = cartridge["prg/rom"];
  auto pram = cartridge["prg/ram"];
  auto crom = cartridge["chr/rom"];
  auto cram = cartridge["chr/ram"];

  prgrom.size = numeral(prom["size"].data);
  prgram.size = numeral(pram["size"].data);
  chrrom.size = numeral(crom["size"].data);
  chrram.size = numeral(cram["size"].data);

  if(prgrom.size) prgrom.data = new uint8[prgrom.size]();
  if(prgram.size) prgram.data = new uint8[prgram.size]();
  if(chrrom.size) chrrom.data = new uint8[chrrom.size]();
  if(chrram.size) chrram.data = new uint8[chrram.size]();

  if(prom["name"].data) interface->loadRequest(ID::ProgramROM, prom["name"].data);
  if(pram["name"].data) interface->loadRequest(ID::ProgramRAM, pram["name"].data);
  if(crom["name"].data) interface->loadRequest(ID::CharacterROM, crom["name"].data);
  if(cram["name"].data) interface->loadRequest(ID::CharacterRAM, cram["name"].data);

  if(pram["name"].data) Famicom::cartridge.memory.append({ID::ProgramRAM, pram["name"].data});
  if(cram["name"].data) Famicom::cartridge.memory.append({ID::CharacterRAM, cram["name"].data});

  prgram.writable = true;
  chrram.writable = true;
}

Board::~Board() {
}

Board* Board::load(Markup::Node cartridge) {
  string type = cartridge["board/type"].text();

  if(substr(type,0,4) == "HVC-" || substr(type,0,4) == "NES-") {
    type = substr(type,4);
    if(type == "AMROM"   ) return new NES_AxROM(cartridge);
    if(type == "ANROM"   ) return new NES_AxROM(cartridge);
    if(type == "AN1ROM"  ) return new NES_AxROM(cartridge);
    if(type == "AOROM"   ) return new NES_AxROM(cartridge);

    if(type == "BNROM"   ) return new NES_BNROM(cartridge);

    if(type == "BTR"     ) return new Sunsoft5B(cartridge);

    if(type == "CNROM"   ) return new NES_CxROM(cartridge);
    if(type == "CPROM"   ) return new NES_CxROM(cartridge);

    if(type == "DEROM"   ) return new Namco34xx(cartridge);
    if(type == "DE1ROM"  ) return new Namco34xx(cartridge);
    if(type == "DRROM"   ) return new Namco34xx(cartridge);

    if(type == "EKROM"   ) return new NES_ExROM(cartridge);
    if(type == "ELROM"   ) return new NES_ExROM(cartridge);
    if(type == "ETROM"   ) return new NES_ExROM(cartridge);
    if(type == "EWROM"   ) return new NES_ExROM(cartridge);

    if(type == "FJROM"   ) return new NES_FxROM(cartridge);
    if(type == "FKROM"   ) return new NES_FxROM(cartridge);

    if(type == "GNROM"   ) return new NES_GxROM(cartridge);
    if(type == "MHROM"   ) return new NES_GxROM(cartridge);

    if(type == "HKROM"   ) return new NES_HKROM(cartridge);

    if(type == "JLROM"   ) return new Sunsoft5B(cartridge);
    if(type == "JSROM"   ) return new Sunsoft5B(cartridge);

    if(type == "NROM"    ) return new NES_NROM(cartridge);
    if(type == "NROM-128") return new NES_NROM(cartridge);
    if(type == "NROM-256") return new NES_NROM(cartridge);
    if(type == "HROM"    ) return new NES_NROM(cartridge);
    if(type == "RROM"    ) return new NES_NROM(cartridge);
    if(type == "RROM-128") return new NES_NROM(cartridge);
    if(type == "RTROM"   ) return new NES_NROM(cartridge);
    if(type == "SROM"    ) return new NES_NROM(cartridge);
    if(type == "STROM"   ) return new NES_NROM(cartridge);

    if(type == "PEEOROM" ) return new NES_PxROM(cartridge);
    if(type == "PNROM"   ) return new NES_PxROM(cartridge);

    if(type == "SAROM"   ) return new NES_SxROM(cartridge);
    if(type == "SBROM"   ) return new NES_SxROM(cartridge);
    if(type == "SCROM"   ) return new NES_SxROM(cartridge);
    if(type == "SC1ROM"  ) return new NES_SxROM(cartridge);
    if(type == "SEROM"   ) return new NES_SxROM(cartridge);
    if(type == "SFROM"   ) return new NES_SxROM(cartridge);
    if(type == "SFEXPROM") return new NES_SxROM(cartridge);
    if(type == "SGROM"   ) return new NES_SxROM(cartridge);
    if(type == "SHROM"   ) return new NES_SxROM(cartridge);
    if(type == "SH1ROM"  ) return new NES_SxROM(cartridge);
    if(type == "SIROM"   ) return new NES_SxROM(cartridge);
    if(type == "SJROM"   ) return new NES_SxROM(cartridge);
    if(type == "SKROM"   ) return new NES_SxROM(cartridge);
    if(type == "SLROM"   ) return new NES_SxROM(cartridge);
    if(type == "SL1ROM"  ) return new NES_SxROM(cartridge);
    if(type == "SL2ROM"  ) return new NES_SxROM(cartridge);
    if(type == "SL3ROM"  ) return new NES_SxROM(cartridge);
    if(type == "SLRROM"  ) return new NES_SxROM(cartridge);
    if(type == "SMROM"   ) return new NES_SxROM(cartridge);
    if(type == "SNROM"   ) return new NES_SxROM(cartridge);
    if(type == "SNWEPROM") return new NES_SxROM(cartridge);
    if(type == "SOROM"   ) return new NES_SxROM(cartridge);
    if(type == "SUROM"   ) return new NES_SxROM(cartridge);
    if(type == "SXROM"   ) return new NES_SxROM(cartridge);

    if(type == "TBROM"   ) return new NES_TxROM(cartridge);
    if(type == "TEROM"   ) return new NES_TxROM(cartridge);
    if(type == "TFROM"   ) return new NES_TxROM(cartridge);
    if(type == "TGROM"   ) return new NES_TxROM(cartridge);
    if(type == "TKROM"   ) return new NES_TxROM(cartridge);
    if(type == "TKSROM"  ) return new NES_TxROM(cartridge);
    if(type == "TLROM"   ) return new NES_TxROM(cartridge);
    if(type == "TL1ROM"  ) return new NES_TxROM(cartridge);
    if(type == "TL2ROM"  ) return new NES_TxROM(cartridge);
    if(type == "TLSROM"  ) return new NES_TxROM(cartridge);
    if(type == "TNROM"   ) return new NES_TxROM(cartridge);
    if(type == "TQROM"   ) return new NES_TxROM(cartridge);
    if(type == "TR1ROM"  ) return new NES_TxROM(cartridge);
    if(type == "TSROM"   ) return new NES_TxROM(cartridge);
    if(type == "TVROM"   ) return new NES_TxROM(cartridge);

    if(type == "UNROM"   ) return new NES_UxROM(cartridge);
    if(type == "UOROM"   ) return new NES_UxROM(cartridge);
  }

  if(type == "ACCLAIM-MC-ACC") return new NES_TxROM(cartridge);

  if(type == "AVE-NINA-01") return new Nina(cartridge);
  if(type == "AVE-NINA-02") return new Nina(cartridge);
  if(type == "AVE-NINA-03") return new Nina(cartridge);
  if(type == "AVE-NINA-06") return new Nina(cartridge);

  if(type == "BANDAI-74*161/32") return new NES_CxROM(cartridge);
  if(type == "BANDAI-CNROM"    ) return new NES_CxROM(cartridge);
  if(type == "BANDAI-FCG"      ) return new BandaiFCG(cartridge);
  if(type == "BANDAI-FCG-1"    ) return new BandaiFCG(cartridge);
  if(type == "BANDAI-FCG-2"    ) return new BandaiFCG(cartridge);
  if(type == "BANDAI-GNROM"    ) return new NES_GxROM(cartridge);
  if(type == "BANDAI-JUMP2"    ) return new BandaiFCG(cartridge);
  if(type == "BANDAI-LZ93D50"  ) return new BandaiFCG(cartridge);
  if(type == "BANDAI-NROM-128" ) return new NES_NROM(cartridge);
  if(type == "BANDAI-NROM-256" ) return new NES_NROM(cartridge);
  if(type == "BANDAI-PT-544"   ) return new NES_CxROM(cartridge);

  if(type == "IREM-BNROM"   ) return new NES_BNROM(cartridge);
  if(type == "IREM-FCG-1"   ) return new BandaiFCG(cartridge);
  if(type == "IREM-NROM-128") return new NES_NROM(cartridge);
  if(type == "IREM-NROM-256") return new NES_NROM(cartridge);
  if(type == "IREM-UNROM"   ) return new NES_UxROM(cartridge);
  //TODO:
  //IREM-G101 (iNES 032)
  //IREM-H3001 (iNES 065)
  //IREM-74*161/161/21/138 (iNES 077)
  //IREM-HOLYDIVER (iNES 078)
  //IREM-TAM-S1 (iNES 097)

  if(type == "KONAMI-CNROM"   ) return new NES_CxROM(cartridge);
  if(type == "KONAMI-NROM-128") return new NES_NROM(cartridge);
  if(type == "KONAMI-SLROM"   ) return new NES_SxROM(cartridge);
  if(type == "KONAMI-TLROM"   ) return new NES_TxROM(cartridge);
  if(type == "KONAMI-UNROM"   ) return new NES_UxROM(cartridge);
  if(type == "KONAMI-VRC-1"   ) return new KonamiVRC1(cartridge);
  if(type == "KONAMI-VRC-2"   ) return new KonamiVRC2(cartridge);
  if(type == "KONAMI-VRC-3"   ) return new KonamiVRC3(cartridge);
  if(type == "KONAMI-VRC-4"   ) return new KonamiVRC4(cartridge);
  if(type == "KONAMI-VRC-6"   ) return new KonamiVRC6(cartridge);
  if(type == "KONAMI-VRC-7"   ) return new KonamiVRC7(cartridge);

  if(type == "NAMCOT-163" ) return new Namco163(cartridge);
  if(type == "NAMCOT-3301") return new NES_NROM(cartridge);
  if(type == "NAMCOT-3302") return new NES_NROM(cartridge);
  if(type == "NAMCOT-3305") return new NES_NROM(cartridge);
  if(type == "NAMCOT-3311") return new NES_NROM(cartridge);
  if(type == "NAMCOT-3312") return new NES_NROM(cartridge);
  if(type == "NAMCOT-3401") return new Namco34xx(cartridge);
  if(type == "NAMCOT-3406") return new Namco34xx(cartridge);
  if(type == "NAMCOT-3407") return new Namco34xx(cartridge);
  if(type == "NAMCOT-3416") return new Namco34xx(cartridge);
  if(type == "NAMCOT-3417") return new Namco34xx(cartridge);
  if(type == "NAMCOT-3443") return new Namco34xx(cartridge);
  if(type == "NAMCOT-3446") return new Namco34xx(cartridge);
  if(type == "NAMCOT-3453") return new Namco34xx(cartridge);

  if(type == "SUNSOFT-4" ) return new Sunsoft4(cartridge);
  if(type == "SUNSOFT-5B") return new Sunsoft5B(cartridge);

  if(type == "FDS") return new FDS(cartridge);
  if(type == "VS" ) return new VS(cartridge);

  // Unlicensed boards below; feel free to remove
  if(type == "CAMERICA-ALGN"     ) return new Camerica(cartridge);
  if(type == "CAMERICA-ALGQ"     ) return new Camerica(cartridge);
  if(type == "CAMERICA-BF9093"   ) return new Camerica(cartridge);
  if(type == "CAMERICA-BF9096"   ) return new Camerica(cartridge);
  if(type == "CAMERICA-BF9097"   ) return new Camerica(cartridge);
  if(type == "CODEMASTERS-NR8N"  ) return new Camerica(cartridge);
  if(type == "COLORDREAMS-74*377") return new ColorDreams74377(cartridge);
  if(type == "MLT-ACTION52"      ) return new MLT_Action52(cartridge);
  if(type == "TENGEN-800002"     ) return new Namco34xx(cartridge);
  if(type == "TENGEN-800003"     ) return new NES_NROM(cartridge);
  if(type == "TENGEN-800004"     ) return new Namco34xx(cartridge);
  if(type == "TENGEN-800008"     ) return new NES_CxROM(cartridge);
  if(type == "TENGEN-800030"     ) return new Namco34xx(cartridge);
  if(type == "TENGEN-800042"     ) return new Sunsoft4(cartridge);
  // Homebrew boards; feel free to remove
  if(type == "NoConflicts-CNROM") return new NoConflicts_CNROM(cartridge);
  if(type == "SingleChip") return new SingleChip(cartridge);

  return nullptr;
}
