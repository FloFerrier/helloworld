#include <stdint.h>

void serial_init(void);
uint16_t serial_receive(void);
void serial_send(uint16_t data);
