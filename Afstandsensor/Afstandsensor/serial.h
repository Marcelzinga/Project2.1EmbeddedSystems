void ser_init();

void ser_transmit(uint8_t data);
uint8_t ser_receive();

void init_ports(void);
void init_timer(void);
void init_ext_int(void);
void ser_write(char* s);
void ser_writeln(char* s);
void ser_readln(char* buf, int maxlength, uint8_t echo);

