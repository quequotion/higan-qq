#ifdef SYSTEM_CPP

serializer System::serialize() {
  serializer s(serialize_size);

  unsigned signature = 0x31545342, version = Info::SerializerVersion;
  char hash[64], description[512];
  memcpy(&hash, (const char*)cartridge.sha256(), 64);
  memset(&description, 0, sizeof description);

  s.integer(signature);
  s.integer(version);
  s.array(hash);
  s.array(description);

  serialize_all(s);
  return s;
}

bool System::unserialize(serializer& s) {
  unsigned signature, version;
  char hash[64], description[512];

  s.integer(signature);
  s.integer(version);
  s.array(hash);
  s.array(description);

  if(signature != 0x31545342) return false;
  if(version != Info::SerializerVersion) return false;

  power();
  serialize_all(s);
  return true;
}

//========
//internal
//========

void System::serialize(serializer& s) {
  s.integer((unsigned&)region);
}

void System::serialize_all(serializer& s) {
  cartridge.serialize(s);
  system.serialize(s);
  cpu.serialize(s);
  apu.serialize(s);
  ppu.serialize(s);

  if(revision == Revision::VSSystem) vsarcadeboard.serialize(s);
}

//perform dry-run state save:
//determines exactly how many bytes are needed to save state for this cartridge,
//as amount varies per game (eg different RAM sizes, etc.)
void System::serialize_init() {
  serializer s;

  unsigned signature = 0, version = 0;
  char hash[64], description[512];

  s.integer(signature);
  s.integer(version);
  s.array(hash);
  s.array(description);

  serialize_all(s);
  serialize_size = s.size();
}

#endif
