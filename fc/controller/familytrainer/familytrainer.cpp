#ifdef CONTROLLER_CPP

uint5 FamilyTrainer::data() {
  if(counter >= 8) return 0x18;
  if(latched == 1) return (b2 << 3) | (b4 << 4);

  switch(counter++) {
  case  0: return (b2  << 3) | (b4  << 4);
  case  1: return (b1  << 3) | (b3  << 4);
  case  2: return (b5  << 3) | (b12 << 4);
  case  3: return (b9  << 3) | (b8  << 4);
  case  4: return (b6  << 3) | 0x10;
  case  5: return (b10 << 3) | 0x10;
  case  6: return (b11 << 3) | 0x10;
  case  7: return (b7  << 3) | 0x10;
  }
}

uint2 FamilyTrainer::data1() {
  return 0;
}

uint5 FamilyTrainer::data2() {
  return data();
}

void FamilyTrainer::latch(bool data) {
  if(latched == data) return;
  latched = data;
  counter = 0;

  if(latched == 0) {
    b1  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  0);
    b2  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  1);
    b3  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  2);
    b4  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  3);
    b5  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  4);
    b6  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  5);
    b7  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  6);
    b8  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  7);
    b9  = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  8);
    b10 = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer,  9);
    b11 = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer, 10);
    b12 = interface->inputPoll(port, (unsigned)Input::Device::FamilyTrainer, 11);
  }
}

FamilyTrainer::FamilyTrainer(unsigned port) : Controller(port) {
  latched = 0;
  counter = 0;

  b1 = b2 = b3 = b4 = 0;
  b5 = b6 = b7 = b8 = 0;
  b9 = b10 = b11 = b12 = 0;
}

#endif
