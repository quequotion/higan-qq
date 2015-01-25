struct FourScore : Controller {
  uint5 data();
  void latch(bool data);
  FourScore(unsigned port);

private:
  bool latched;
  unsigned counter;
};
