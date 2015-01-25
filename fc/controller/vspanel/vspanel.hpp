struct VSPanel : Controller {
  uint5 data();
  uint2 data1();
  uint5 data2();
  void latch(bool data);
  VSPanel(unsigned port);

private:
  bool latched;
  unsigned counter1;
  unsigned counter2;

  bool b1, b2, b3, b4;
};
