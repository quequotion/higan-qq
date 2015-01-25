#include "chip/chip.hpp"
#include "board/board.hpp"

struct Cartridge : Thread, property<Cartridge> {
  enum class Region : unsigned {
    NTSC,
    PAL,
  };

  static void Main();
  void main();

  readonly<bool> loaded;
  readonly<string> sha256;

  readonly<Region> region;

  struct Memory {
    unsigned id;
    string name;
  };
  vector<Memory> memory;

  struct Information {
    struct Markup {
      string cartridge;
      //string famicomDiskSystem;
    } markup;

    struct Title {
      string cartridge;
      //string famicomDiskSystem;
    } title;
  } information;

  string title();

  void load(System::Revision revision);
  void unload();

  void power();
  void reset();

  void serialize(serializer&);
  Cartridge();
  ~Cartridge();

//privileged:
  Board *board;

  uint8 prg_read(unsigned addr);
  void prg_write(unsigned addr, uint8 data);

  uint8 chr_read(unsigned addr);
  void chr_write(unsigned addr, uint8 data);

  //scanline() is for debugging purposes only:
  //boards must detect scanline edges on their own
  void scanline(unsigned y);

private:
  void parse_markup(const char*);
};

extern Cartridge cartridge;
