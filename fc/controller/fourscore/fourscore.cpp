#ifdef CONTROLLER_CPP

uint5 FourScore::data() {
  if(counter >= 24) return 1;
  if(latched) return interface->inputPoll(port, (unsigned)Input::Device::FourScore, 0);
  uint5 data = 0;

  if(counter >= 16) data = counter == (19 - port);
  else data = interface->inputPoll(port, (unsigned)Input::Device::FourScore, counter);
  counter++;

  return data;
}

void FourScore::latch(bool data) {
  if(latched == data) return;
  latched = data;
  counter = 0;
}

FourScore::FourScore(unsigned port) : Controller(port) {
  latched = 0;
  counter = 0;
}

#endif
