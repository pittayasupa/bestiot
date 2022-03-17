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
 
