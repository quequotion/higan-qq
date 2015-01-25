struct Input {
  enum class Device : unsigned {
    Joypad        = 0,
    FourPlayers   = 1,
    FourScore     = 1,
    BeamGun       = 2,
    FamilyTrainer = 3,
    VSPanel       = 4,
    None          = 5,
  };

  enum class JoypadID : unsigned {
    A  =  0, B    =  1, Select =  2, Start =  3,
    Up =  4, Down =  5, Left   =  6, Right =  7,
  };

  enum class BeamGunID : unsigned {
    X = 0, Y = 1, Trigger = 2,
  };

  Controller* port1 = nullptr;
  Controller* port2 = nullptr;
  Controller* expansion = nullptr;

  void connect(uint2 port, Device device);
  Input();
  ~Input();
};

extern Input input;
