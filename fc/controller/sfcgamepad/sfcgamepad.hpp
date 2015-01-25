struct SFCGamepad : Controller {
  uint5 data();
  uint2 data1();
  uint5 data2();
  void latch(bool data);
  SFCGamepad(unsigned port);

private:
  bool latched;
  unsigned counter;

  bool b, y, select, start;
  bool up, down, left, right;
  bool a, x, l, r;
};
