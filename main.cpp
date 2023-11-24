#include "mbed.h"

Serial pc(USBTX, USBRX);
CAN can(p30, p29);

CANMessage msg;

// main() runs in its own thread in the OS
int main()
{
    pc.printf("Starting program...\r\n");
    can.mode(CAN::Normal);
    can.frequency(500*1000); // 500Kbps
    while (true) {
        if (can.read(msg)) {
            pc.printf("Message received: ");
            for (int i = 0; i < sizeof(msg.data); ++i) {
                pc.printf("%d", msg.data[i]);
            }
            pc.printf("\r\n");
            char test[] = "Hola";
            CANMessage resp;
            resp.id = 1337;
            resp.len = sizeof(test);
            memcpy(resp.data, test, resp.len);
            if (can.write(resp)) {
                pc.printf("Message sent!!\r\n");
            }
        }
        thread_sleep_for(1);
    }
}
