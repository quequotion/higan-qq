#ifdef CARTRIDGE_CPP

void Cartridge::parse_markup(const char* markup) {
  auto document = Markup::Document(markup);
  information.title.cartridge = document["information/title"].text();

  auto cartridge = document["cartridge"];
  region = cartridge["region"].data != "PAL" ? Region::NTSC : Region::PAL;
  if(system.revision == System::Revision::VSSystem) {
    vsarcadeboard.swap_controllers = cartridge["vs/controller[0]/port"].integer() == 2;
    //string device1 = cartridge["vs/controller(port=1)/device"].text();
    //string device2 = cartridge["vs/controller(port=2)/device"].text();
    //if(device1 == "joypad") {
    //  input.connect(vsarcadeboard.swap_controllers, Input::Device::Joypad);
    //} else if(device1 == "none") {
    //  input.connect(vsarcadeboard.swap_controllers, Input::Device::None);
    //}
    //if(device2 == "joypad") {
    //  input.connect(!vsarcadeboard.swap_controllers, Input::Device::Joypad);
    //} else if(device2 == "beamgun") {
    //  input.connect(!vsarcadeboard.swap_controllers, Input::Device::BeamGun);
    //} else if(device2 == "none") {
    //  input.connect(!vsarcadeboard.swap_controllers, Input::Device::None);
    //}
    vsarcadeboard.set_dip(interface->dipSettings(cartridge["vs"]));
    string ppu_revision = cartridge["vs/ppu/revision"].data;
    if(ppu_revision == "RP2C02C")     ppu.revision = PPU::Revision::RP2C02C;
    if(ppu_revision == "RP2C02G")     ppu.revision = PPU::Revision::RP2C02G;
    if(ppu_revision == "RP2C03B")     ppu.revision = PPU::Revision::RP2C03B;
    if(ppu_revision == "RP2C03G")     ppu.revision = PPU::Revision::RP2C03G;
    if(ppu_revision == "RP2C04-0001") ppu.revision = PPU::Revision::RP2C04_0001;
    if(ppu_revision == "RP2C04-0002") ppu.revision = PPU::Revision::RP2C04_0002;
    if(ppu_revision == "RP2C04-0003") ppu.revision = PPU::Revision::RP2C04_0003;
    if(ppu_revision == "RP2C04-0004") ppu.revision = PPU::Revision::RP2C04_0004;
    if(ppu_revision == "RC2C03B")     ppu.revision = PPU::Revision::RC2C03B;
    if(ppu_revision == "RC2C03C")     ppu.revision = PPU::Revision::RC2C03C;
    if(ppu_revision == "RC2C05-01")   ppu.revision = PPU::Revision::RC2C05_01;
    if(ppu_revision == "RC2C05-02")   ppu.revision = PPU::Revision::RC2C05_02;
    if(ppu_revision == "RC2C05-03")   ppu.revision = PPU::Revision::RC2C05_03;
    if(ppu_revision == "RC2C05-04")   ppu.revision = PPU::Revision::RC2C05_04;
    if(ppu_revision == "RC2C05-05")   ppu.revision = PPU::Revision::RC2C05_05;
  }
  Board::load(cartridge);  //this call will set Cartridge::board if successful
}

#endif
