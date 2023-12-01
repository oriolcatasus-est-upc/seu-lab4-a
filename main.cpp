#include "mbed.h"

Serial pc(USBTX, USBRX);
CAN can(p30, p29);

CANMessage msg;


int main()
{
    pc.printf("Starting program...\r\n");
    can.mode(CAN::Normal);
    can.frequency(500*1000); // 500Kbps

    while (true) {
        if (can.read(msg)) {
            pc.printf("Message received!\r\n");
            pc.printf("ID: %d\r\n", msg.id);
            pc.printf("Data: ");
            for (int i = 0; i < sizeof(msg.data); ++i) {
                pc.printf("%d", msg.data[i]);
            }
            pc.printf("\r\n");
            /*char respText[] = "Hola";
            CANMessage resp;
            resp.id = 1337;
            resp.len = sizeof(respText);
            memcpy(resp.data, respText, resp.len);*/
            if (can.write(msg)) {
                pc.printf("Message resent!\r\n");
            }
        }
        thread_sleep_for(1);
    }
}
