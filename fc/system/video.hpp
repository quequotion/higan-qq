struct Video {
  uint32_t* palette;
  void generate_palette(Emulator::Interface::PaletteMode mode);
  Video();
  ~Video();

private:
  void update();
  void scanline();
  void init();

  uint32_t generate_color(unsigned, double, double, double, double, double);
  uint32_t retrieve_color(uint9_t, unsigned);
  static const uint8_t cursor[15 * 15];
  void draw_cursor(uint16_t color, int x, int y);

  friend class System;
};

extern Video video;
