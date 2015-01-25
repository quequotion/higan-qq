struct BeamGun : Controller {
  void enter();
  uint5 data();
  uint2 data1();
  uint5 data2();
  bool read_light();
  void latch(bool data);
  BeamGun(unsigned port);

//private:
  bool latched;

  signed x, y;
  unsigned light;
  unsigned triggertime;

  bool offscreen;

  bool triggerlock;
};
