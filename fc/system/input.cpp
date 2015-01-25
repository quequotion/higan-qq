#ifdef SYSTEM_CPP

Input input;

void Input::connect(uint2 port, Device id) {
  Controller*& controller = (
    port == Controller::Port1 ? port1 :
    port == Controller::Port2 ? port2 :
                                expansion
  );
  if(controller) {
    delete controller;
    controller = nullptr;
  }

  if(port < 2) {
    switch(id) { default:
    case Device::None: controller = new Controller(port); break;
    case Device::Joypad: controller = new Gamepad(port); break;
    case Device::FourScore: controller = new FourScore(port); break;
    case Device::BeamGun:
      if(!system.vs()) controller = new BeamGun(port);
      else             controller = new VSBeamGun(port);
      break;
    case Device::FamilyTrainer: controller = new FamilyTrainer(port); break;
    }
  } else {
    switch(id) { default:
    case Device::None: controller = new Controller(port); break;
    case Device::Joypad: controller = new Gamepad(port); break;
    case Device::FourPlayers: controller = new FourPlayers(port); break;
    case Device::BeamGun: controller = new BeamGun(port); break;
    case Device::FamilyTrainer: controller = new FamilyTrainer(port); break;
    case Device::VSPanel: controller = new VSPanel(port); break;
    }
  }

  switch(port) {
  case Controller::Port1: configuration.controller_port1 = id; break;
  case Controller::Port2: configuration.controller_port2 = id; break;
  case Controller::ExpansionPort: configuration.expansion_port = id; break;
  }

  /*switch(port) {
  case Controller::Port1:
    if(id == Device::FourScore && configuration.controller_port2 != Device::FourScore) {
      connect(Controller::Port2, Device::FourScore);
    } else if(id != Device::FourScore && configuration.controller_port2 == Device::FourScore) {
      connect(Controller::Port2, Device::None);
    }
    break;
  case Controller::Port2:
    if(id == Device::FourScore && configuration.controller_port1 != Device::FourScore) {
      connect(Controller::Port1, Device::FourScore);
    } else if(id != Device::FourScore && configuration.controller_port1 == Device::FourScore) {
      connect(Controller::Port1, Device::None);
    }
    break;
  }*/
}

Input::Input() {
  connect(Controller::Port1, Input::Device::Joypad);
  connect(Controller::Port2, Input::Device::Joypad);
  connect(Controller::ExpansionPort, Input::Device::Joypad);
}

Input::~Input() {
  if(port1) delete port1;
  if(port2) delete port2;
  if(expansion) delete expansion;
}

#endif
