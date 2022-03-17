# Best IoT
# Work AIS NB-IoT with ESP32 and LPWA BC95-G NB-IoT Module
  Hi Welcome this example library for ESP32 and BC95-G  

# Quectel BC95-G-GBC68 AT Command Manual v1.5
  you can download manual At command here: https://www.quectel.com/download/quectel_bc95-gbc68_at_commands_manual_v1-5
  
# For Example
  1. include library NB_BC95_G.h
  2. create class AISnb from NB_BC95_G
  3. set up your monitor serial port any buatrate
  4. set AISnb.begin(buadrate, parity, rx_pin, tx_pin) 
     - buadrate 9600
     - parity bit SERIAL_8N1 mean 8 data bits and 1 stop bit, see more: https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/
     - rx pin mean receiver pin from BC95-G Module
     - tx pin mean transmission pin to BC95-G Module
  5. test Command if you can use serial port
  6. set up device and create UDP socket from serverPort parameter
  7. get device ip for checking network
  8. test server ip for comunicate with server ip
 
# NB type
  1. nb_resp_t is type of structure for get response status, command response(temp) 
  2. nb_split_t is type of structure for split command response than easy to use
  3. nb_socket_t is type of structure for remember socket create 

# NB function recommend
  1. sendCommand your can send command for test AT Command
  2. subFromData for get command result response 
  3. spiteFromData for split command result easy to use
  4. str2HexStr when you want to send message to any socket you can convert text string to hex string
  5. hex2Str when you received message from socket you can convert hex string to string by ascii code

# Example Code

```c++
#include "NB_BC95_G.h"
NB_BC95_G AISnb;

const long interval = 10000;  //millisecond
unsigned long previousMillis = 0;
```

```c++
void setup()
{
  AISnb.debug = true;
  AISnb.delayAfterCommand = 1000;
  AISnb.begin(9600, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN);
  Serial.println("Waiting for AIS NB test status!");
  while(!AISnb.testCommand().status)
  {
    Serial.print('.');
  }
  Serial.println("AIS NB OK!"); 
  delay(1000);
  previousMillis = millis(); 
  AISnb.setupDevice("enter your port");  
  nb_resp_t res_DeviceIP = AISnb.getDeviceIP();  
  nb_resp_t res_testPing = AISnb.testPing(serverIP);
}
```

```c++
void Loop()
{
  unsigned long currentMillis = millis(); // millis() maximun about 4,294,967,295 or 49 days overflow reset
  if (abs(currentMillis - previousMillis) >= interval) // take abs
  { 
    previousMillis = currentMillis;   
    //try send UPD message to server
    nb_resp_t res_send = AISnb.sendUDPMessage(socketId, "enter server ip", "enter server port", length, message, MODE_STRING_HEX);
    if(!res_send.status) // if command response ERROR than create socket
    {
      AISnb.createUDPSocket(serverPort); 
    }
  }
  String getResponse = AISnb.getSocketResponse();
  if(getResponse.length() > 0){
    Serial.print("UDP response: ");
    Serial.println(getResponse);
  }
}
```
