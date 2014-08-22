/*
 * This is the original mbed example
 */

#include "mbed.h"

DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);
CAN can(p30, p29);

int main() {
  int i = 0;

  can.frequency(125000);

  while(1) {
    myled = 1;
    wait(0.3);
    myled = 0;
    wait(0.3);
    pc.printf("i: %i\n\r", i);
    ++i;

    if (!can.write(CANMessage(1337, (char*)&i, 4))) {
      pc.printf("CAN send failed\n\r");
    }

    CANMessage msg;
    if(can.read(msg)) {
      pc.printf("CAN recv: 0x%02X\n\r", msg.data[0]);
    }
  }
}
