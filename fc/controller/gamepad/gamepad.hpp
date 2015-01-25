struct Gamepad : Controller {
  uint5 data();
  uint2 data1();
  uint5 data2();
  void latch(bool data);
  Gamepad(unsigned port);

private:
  bool latched;
  unsigned counter;

  bool a, b, select, start;
  bool up, down, left, right;
};
