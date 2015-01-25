void add_clocks(unsigned clocks);
uint8 op_read(uint16 addr);
void op_write(uint16 addr, uint8 data);
void last_cycle();
void nmi(uint16 &vector);

void oam_dma();

void set_nmi_line(bool);
void set_irq_line(bool);
void set_irq_apu_line(bool);

void set_rdy_line(bool);
void set_rdy_addr(bool valid, uint16 value = 0);
