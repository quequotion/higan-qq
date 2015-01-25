struct VSBeamGun : Controller {
  void enter();
  uint5 data();
  bool read_light();
  void latch(bool data);
  VSBeamGun(unsigned port);

//private:
  bool latched;
  unsigned counter;

  signed x, y;
  unsigned light;
  unsigned triggertime;

  bool offscreen;

  bool triggerlock;
};
