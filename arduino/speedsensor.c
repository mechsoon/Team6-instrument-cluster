#include <mcp_can.h>
#include <SPI.h>
#include <stdint.h>

const int SPI_CS_PIN = 9;
int encoder_pin = 3;  // The pin the encoder is connected           
unsigned int rpm;     // rpm reading
unsigned int speed;
volatile byte pulses;  // number of pulses
unsigned long timeold; 
unsigned int pulsesperturn = 20;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void counter()
 {
    //Update count
      pulses++;    
 }

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ))
    //while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
    CAN.setMode(MCP_NORMAL);

    pinMode(encoder_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoder_pin), counter, FALLING);
    pulses = 0;
    rpm = 0;
    timeold = 0;

}



void loop() {
    if (millis() - timeold >= 300){  /*Uptade every one second, this will be equal to reading frecuency (Hz).*/
 
    //Don't process interrupts during calculations
    detachInterrupt(0);
    //Note that this would be 60*1000/(millis() - timeold)*pulses if the interrupt
    //happened once per revolution
    rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold) * pulses ;
    speed = rpm * 3.141592653589793238462643383279 * 2 * 3.3 /60; //cm 단위
    timeold = millis();
    pulses = 0;
   
    //Write it out to serial port
    Serial.print("speed = ");
    Serial.println(speed,DEC);
    //Restart the interrupt processing
    attachInterrupt(0, counter, FALLING);
    }

    //unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char stmp[8] = {0};  // CAN 메시지 데이터 배열 초기화
    // stmp[0] = (rpm >> 24) & 0xFF;  // 상위 8비트
    // stmp[1] = (rpm >> 16) & 0xFF;
    // stmp[2] = (rpm >> 8) & 0xFF;
    // stmp[3] = rpm & 0xFF; 
    stmp[0] = (speed>>8)  & 0xFF;  // 상위 8비트
    stmp[1] = speed  & 0xFF;  // 상위 8비트



    // CAN 메시지 전송: ID 0x100, 데이터 길이 8, stmp 데이터
    if (CAN_OK == CAN.sendMsgBuf(0x100, 0, 8, stmp)) {
        //Serial.println("Message Sent Successfully!");  // 성공 여부 확인
    } else {
        Serial.println("Error Sending Message");
    }

    delay(100);  // 100ms마다 전송
}
// END FILE