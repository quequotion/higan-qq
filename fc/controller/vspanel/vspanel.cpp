#ifdef CONTROLLER_CPP

uint5 VSPanel::data() {
  unsigned data = 0x00;
  if(interface->inputPoll(port, (unsigned)Input::Device::VSPanel, 4)) data |= 0x01; // service button
  if(interface->inputPoll(port, (unsigned)Input::Device::VSPanel, 5)) data |= 0x08; // coin 1
  if(interface->inputPoll(port, (unsigned)Input::Device::VSPanel, 6)) data |= 0x10; // coin 2
  // data will be left-shifted twice and OR'd into $4016 in CPU
  return data;
}

uint2 VSPanel::data1() {
  if(counter1 >= 8) return 1;
  if(latched == 1) return 0;

  switch(counter1++) { default: return 0;
  case 2: return b1;
  case 3: return b3;
  }
}

uint5 VSPanel::data2() {
  if(counter2 >= 8) return 1;
  if(latched == 1) return 0;

  switch(counter2++) { default: return 0;
  case 2: return b2;
  case 3: return b4;
  }
}

void VSPanel::latch(bool data) {
  if(latched == data) return;
  latched = data;
  counter1 = 0;
  counter2 = 0;

  if(latched == 0) {
    b1 = interface->inputPoll(port, (unsigned)Input::Device::VSPanel, 0);
    b2 = interface->inputPoll(port, (unsigned)Input::Device::VSPanel, 1);
    b3 = interface->inputPoll(port, (unsigned)Input::Device::VSPanel, 2);
    b4 = interface->inputPoll(port, (unsigned)Input::Device::VSPanel, 3);
  }
}

VSPanel::VSPanel(unsigned port) : Controller(port) {
  latched = 0;
  counter1 = 0;
  counter2 = 0;

  b1 = b2 = b3 = b4 = 0;
}

#endif
