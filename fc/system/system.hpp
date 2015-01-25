struct Interface;

struct System : property<System> {
  enum class Region : unsigned { NTSC = 0, PAL = 1, Autodetect = 2 };
  enum class Revision : unsigned {
    Famicom,
    PlayChoice10,
    VSSystem,
  } revision;

  inline bool fc()   const { return revision == Revision::Famicom; }
  inline bool pc10() const { return revision == Revision::PlayChoice10; }
  inline bool vs()   const { return revision == Revision::VSSystem; }

  void run();
  void runtosave();

  void init();
  void term();
  void load(Revision);
  void unload();
  void power();
  void reset();

  void frame();
  void scanline();

  //return *active* system information (settings are cached upon power-on)
  readonly<Region> region;
  readonly<unsigned> cpu_frequency;
  readonly<unsigned> serialize_size;

  serializer serialize();
  bool unserialize(serializer&);

  System();

private:
  void runthreadtosave();

  void serialize(serializer&);
  void serialize_all(serializer&);
  void serialize_init();

  friend class Cartridge;
  friend class Video;
  friend class Input;
};

extern System system;

#include "video.hpp"
#include "input.hpp"

#include <fc/scheduler/scheduler.hpp>

struct Configuration {
  Input::Device controller_port1 = Input::Device::Joypad;
  Input::Device controller_port2 = Input::Device::Joypad;
  Input::Device expansion_port = Input::Device::Joypad;
  System::Region region = System::Region::Autodetect;
  bool random = true;
};

extern Configuration configuration;
