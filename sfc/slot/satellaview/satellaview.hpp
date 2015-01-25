#include <nall/file.hpp>
struct SatellaviewCartridge : Memory {
  MappedRAM memory;
  bool readonly;

  void init();
  void save();
  void load();
  void unload();
  void power();
  void reset();

  unsigned size() const;
  uint8 read(unsigned addr);
  void write(unsigned addr, uint8 data);

private:
  struct {
    unsigned command;
    unsigned command2;
    uint8 write_old;
    uint8 write_new;

    bool flash_enable;
    bool read_enable;
    bool write_enable;
    bool command_done; //Giving Flash Command is done.
    bool flash_stat_csr;
    bool flash_stat_gsr;
    bool flash_stat_bsr;
  } regs;
};

extern SatellaviewCartridge satellaviewcartridge;
