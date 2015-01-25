#include <nall/file.hpp>

struct SatellaviewBaseUnit : Memory {
  void init();
  void load();
  void unload();
  void power();
  void reset();

  file BSXF;
  file BSXF2;

  void SatellaviewTuneInA(uint8 filenumber);
  void SatellaviewTuneInB(uint8 filenumber);

  uint8 GetTime(bool reset_count);


  uint8 read(unsigned addr);
  void write(unsigned addr, uint8 data);

private:
  struct {
    uint8 r2188, r2189, r218a, r218b;
    uint8 r218c, r218d, r218e, r218f;
    uint8 r2190, r2191, r2192, r2193;
    uint8 r2194, r2195, r2196, r2197;
    uint8 r2198, r2199, r219a, r219b;
    uint8 r219c, r219d, r219e, r219f;

    uint8 time_counter;
    uint8 time_hour, time_minute, time_second;
    uint8 time_weekday, time_day, time_month;
    uint8 time_yearL, time_yearH;

    bool r218b_port, r218c_port;
    bool r2191_port, r2192_port;

    bool BSX_access;
    uint8 BSXF_NUM;
    uint8 BSXF_Signal;

    uint8 BSXF_Queue;
    bool BSXF_1ST;

    bool BSX2_access;
    uint8 BSXF2_NUM;
    uint8 BSXF2_Signal;

    uint8 BSXF2_Queue;
    bool BSXF2_1ST;

    bool r218b_chk;
    bool r218c_chk;

    bool r2191_chk;
    bool r2192_chk;
  } regs;
};

extern SatellaviewBaseUnit satellaviewbaseunit;
