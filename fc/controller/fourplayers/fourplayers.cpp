#ifdef CONTROLLER_CPP

uint2 FourPlayers::data1() {
  if(counter1 >= 8) return 2;
  if(latched) return interface->inputPoll(port, (unsigned)Input::Device::FourPlayers, 0) << 1;

  return interface->inputPoll(port, (unsigned)Input::Device::FourPlayers, counter1++) << 1;
}

uint5 FourPlayers::data2() {
  if(counter2 >= 8) return 2;
  if(latched) return interface->inputPoll(port, (unsigned)Input::Device::FourPlayers, 8) << 1;

  return interface->inputPoll(port, (unsigned)Input::Device::FourPlayers, (counter2++) + 8) << 1;
}

void FourPlayers::latch(bool data) {
  if(latched == data) return;
  latched = data;
  counter1 = 0;
  counter2 = 0;
}

FourPlayers::FourPlayers(unsigned port) : Controller(port) {
  latched = 0;
  counter1 = 0;
  counter2 = 0;
}

#endif
