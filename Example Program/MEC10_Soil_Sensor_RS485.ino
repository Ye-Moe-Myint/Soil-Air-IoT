#include <ModbusMaster.h>

#define MAX485_DE      5
ModbusMaster node;
String mm = "";

void preTransmission(){
  digitalWrite(MAX485_DE, 1);
}

void postTransmission(){
  digitalWrite(MAX485_DE, 0);
}

void setup(){
  pinMode(MAX485_DE, OUTPUT);
  
  // Init in receive mode
  digitalWrite(MAX485_DE, 0);

  Serial.begin(9600);
  Serial1.begin(9600);

  Serial.println("Starting...");
  // Modbus slave ID 1
  node.begin(1, Serial1);
  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

}

void loop(){
  uint8_t result;
  uint8_t result2;
  uint8_t result3;
  /////////// RS485 ////////////       
  result = node.readHoldingRegisters(0x00, 1); // Small Probe
     
  if (result == node.ku8MBSuccess)  {
    long mm = (long)(node.getResponseBuffer(0x0000)); // Big Probe
    Serial.print("Soil Temp: ");
    Serial.print((float)mm/100,2);
    Serial.println(" C");
    Serial.println((float)mm/100);
    node.clearResponseBuffer();
  }
  delay(1);
  
  result2 = node.readHoldingRegisters(0x01, 1); // Small Probe
  if (result2 == node.ku8MBSuccess)
  {
    long mm = (long)(node.getResponseBuffer(0x0000)); // Big Probe
    Serial.print("Soil Humid: ");
    Serial.print((float)mm/100,2);
    Serial.println(" %");
    node.clearResponseBuffer();
  }
  
  result3 = node.readInputRegisters(0x02, 1); // Small Probe
    if (result3 == node.ku8MBSuccess)
  {
    long mm = (long)(node.getResponseBuffer(0x0000)); // Big Probe
    Serial.print("Soil EC: ");
    Serial.print((float)mm/100,2);
    Serial.println(" ms/cm");
    node.clearResponseBuffer();
  }
  node.clearResponseBuffer();
  delay(5000);
}
