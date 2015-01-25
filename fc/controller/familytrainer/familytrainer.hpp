struct FamilyTrainer : Controller {
  uint5 data();
  uint2 data1();
  uint5 data2();
  void latch(bool data);
  FamilyTrainer(unsigned port);

private:
  bool latched;
  unsigned counter;

  bool b1, b2, b3, b4;
  bool b5, b6, b7, b8;
  bool b9, b10, b11, b12;
};
