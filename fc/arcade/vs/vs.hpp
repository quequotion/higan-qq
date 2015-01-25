struct VSArcadeBoard {
  bool swap_controllers;
  uint16 dip; // 16-bit for DualSystem games

  void init();
  void load();
  void unload();
  void power();
  void reset();

  void set_dip(uint16 dip);
  uint8 read(uint16 addr);
  void write(uint16 addr, uint8 data);

  void serialize(serializer& s);

private:
  uint8 r4016();
  uint8 r4017();
  uint8 r4020();
  void w4016(uint8 data);
  void w4020(uint8 data);
};

extern VSArcadeBoard vsarcadeboard;
