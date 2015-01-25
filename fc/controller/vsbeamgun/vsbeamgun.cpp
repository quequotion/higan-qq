#ifdef CONTROLLER_CPP

void VSBeamGun::enter() {
  unsigned prev = 0;
  while(true) {
    unsigned next = ppu.status.ly * 341 + ppu.status.lx;

    if(light > 0) light -= 1;

    if(!offscreen) {
      unsigned target = y * 341 + x + 3;
      if(next >= target && prev < target) {
        //CRT raster detected
        //light remains in the gun for 10-25 scanlines
        if(read_light()) light = 341 * 16;
      }
    }

    if(next < prev) {
      if(triggertime > 0) triggertime -= 1;
      //Vcounter wrapped back to zero; update cursor coordinates for start of new frame
      int nx = interface->inputPoll(port, (unsigned)Input::Device::BeamGun, (unsigned)Input::BeamGunID::X);
      int ny = interface->inputPoll(port, (unsigned)Input::Device::BeamGun, (unsigned)Input::BeamGunID::Y);
      nx += x;
      ny += y;
      x = max(-16, min(256 + 16, nx));
      y = max(-16, min(240 + 16, ny));
      offscreen = (x < 0 || y < 0 || x >= 256 || y >= 240);
    }

    prev = next;
    step(2);
  }
}

uint5 VSBeamGun::data() {
  if(counter >= 8) return 1;
  if(latched == 1) return 0;

  switch(counter++) {
  case 0: return 0;
  case 1: return 0;
  case 2: return 0;
  case 3: return 0;
  case 4: return 1; // connected
  case 5: return 0;
  case 6: return light == 0;
  case 7:
    bool newtrigger = interface->inputPoll(port, (unsigned)Input::Device::BeamGun, (unsigned)Input::BeamGunID::Trigger);
    if(newtrigger && !triggerlock) {
      triggertime = 2;
      triggerlock = true;
    } else if(!newtrigger) {
      triggerlock = false;
    }
    return triggertime > 0;
  }
}

bool VSBeamGun::read_light() {
  if(offscreen) return false;
  uint32 color = ppu.buffer[y * 256 + x];
  return ((color & 0x20) && ((color & 0x0F) < 0x0D));
}

void VSBeamGun::latch(bool data) {
  if(latched == data) return;
  latched = data;
}

VSBeamGun::VSBeamGun(unsigned port) : Controller(port) {
  create(Controller::Enter, system.cpu_frequency());
  latched = 0;

  //center cursor onscreen
  x = 256 / 2;
  y = 240 / 2;
}

#endif
