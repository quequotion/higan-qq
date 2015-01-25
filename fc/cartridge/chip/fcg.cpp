struct FCG : Chip {

enum class Revision : unsigned {
  FCG1,
  FCG2,
  LZ93D50,
} revision;

enum class EEPROM : unsigned {
  None,
  _24C01,
  _24C02
} eeprom;

uint8 chr_bank[8];
uint8 prg_bank;
uint2 mirror;
bool irq_counter_enable;
uint16 irq_counter;
uint16 irq_latch;
bool eeprom_i2c_scl; // When using SRAM, enables RAM chip
bool eeprom_enable_read;

void main() {
  while(true) {
    if(scheduler.sync == Scheduler::SynchronizeMode::All) {
      scheduler.exit(Scheduler::ExitReason::SynchronizeEvent);
    }

    if(irq_counter_enable) {
      if(--irq_counter == 0xffff) {
        cpu.set_irq_line(1);
        irq_counter_enable = false;
      }
    }

    tick();
  }
}

unsigned prg_addr(unsigned addr) const {
  bool region = addr & 0x4000;
  return ((region == 0 ? prg_bank : 15) << 14) | (addr & 0x3fff);
}

unsigned chr_addr(unsigned addr) const {
  return (chr_bank[addr >> 10] << 10) | (addr & 0x03ff);
}

unsigned ciram_addr(unsigned addr) const {
  switch(mirror) {
  case 0: return ((addr & 0x0400) >> 0) | (addr & 0x03ff);
  case 1: return ((addr & 0x0800) >> 1) | (addr & 0x03ff);
  case 2: return 0x0000 | (addr & 0x03ff);
  case 3: return 0x0400 | (addr & 0x03ff);
  }
}

uint8 ram_read(unsigned addr) {
  return board.prgram.data[addr & 0x1fff];
}

void ram_write(unsigned addr, uint8 data) {
  board.prgram.data[addr & 0x1fff] = data;
}

void reg_write(unsigned addr, uint8 data) {
  switch(addr & 0x0f) {
  case 0x00: case 0x01: case 0x02: case 0x03:
  case 0x04: case 0x05: case 0x06: case 0x07:
    chr_bank[addr & 7] = data;
    break;
  case 0x08:
    prg_bank = data & 0x0f;
    break;
  case 0x09:
    mirror = data & 0x03;
    break;
  case 0x0a:
    cpu.set_irq_line(0);
    irq_counter_enable = data & 0x01;
    irq_counter = irq_latch;
    break;
  case 0x0b:
    irq_latch = (irq_latch & 0xff00) | (data << 0);
    break;
  case 0x0c:
    irq_latch = (irq_latch & 0x00ff) | (data << 8);
    break;
  case 0x0d:
    //TODO: serial EEPROM support
    eeprom_i2c_scl = data & 0x20;
    eeprom_enable_read = data & 0x80;
    break;
  }
}

void power() {
  reset();
}

void reset() {
  for(auto &n : chr_bank) n = 0;
  prg_bank = 0;
  mirror = 0;
  irq_counter_enable = 0;
  irq_counter = 0;
  irq_latch = 0;
  eeprom_i2c_scl = 0;
  eeprom_enable_read = 0;
}

void serialize(serializer& s) {
  s.array(chr_bank);
  s.integer(prg_bank);
  s.integer(mirror);
  s.integer(irq_counter_enable);
  s.integer(irq_counter);
  s.integer(irq_latch);
  s.integer(eeprom_i2c_scl);
  s.integer(eeprom_enable_read);
}

FCG(Board& board, Markup::Node& cartridge) : Chip(board) {
  string type = cartridge["chip[0]/type"].data;
  if(type.match("*FCG-1*"  )) revision = Revision::FCG1;
  if(type.match("*FCG-2*"  )) revision = Revision::FCG2;
  if(type.match("*LZ93D50*")) revision = Revision::LZ93D50;

  eeprom = EEPROM::None;
  type = cartridge["chip[1]/type"].data;
  if(type.match("*24C01*"  )) eeprom = EEPROM::_24C01;
  if(type.match("*24C02*"  )) eeprom = EEPROM::_24C02;
}

};
