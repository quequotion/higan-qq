struct Mouse : Controller {
  uint5 data();
  uint2 data1();
  uint5 data2();
  void latch(bool data);
  Mouse(unsigned port);

private:
  bool latched;
  unsigned counter;

  unsigned speed;  //0 = slow, 1 = normal, 2 = fast
  signed x;        //x-coordinate
  signed y;        //y-coordinate
  bool dx;         //x-direction
  bool dy;         //y-direction
  bool l;          //left button
  bool r;          //right button
};
