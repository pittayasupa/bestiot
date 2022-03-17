#include "NB_BC95_G.h"
//#include <HardwareSerial.h>

//String serverIP = "45.91.135.37"; // Your Server IP;
//String serverPort = "20133"; // Your Server Port;
//String json = "";
//String udpData = "{\"Tn\":\"HFRvmpdTEDRBYdlCzCDn\",\"temp\":34.3}";
//String udpData = "{\"Tn\":\"8966031840041733227\",\"temp\":34.3}";

String serverIP = "147.50.151.130"; // Your Server IP;
String serverPort = "19956"; // Your Server Port;
String json = "";
String udpData = "{\"Tn\":\"8966031840041733227\",\"temp\":34.3}";


const long interval = 5000;  //millisecond
unsigned long previousMillis = 0;
 
//HardwareSerial myserial(1);
#define SERIAL1_RXPIN 14
#define SERIAL1_TXPIN 27
 
char buffer_receive[1000];
unsigned int count_buffer = 0;
String data_str = ""; 
int read_timeout = 0;

NB_BC95_G AISnb;

void setup() 
{
  Serial.begin(115200); 
  Serial.print("Serial port buadrate: ");
  Serial.println(115200); 
  Serial.println();
  
  AISnb.debug = true;
  AISnb.delayAfterCommand = 1000;
  AISnb.begin(9600, SERIAL_8N1, SERIAL1_RXPIN, SERIAL1_TXPIN);
  Serial.println("Waiting for AIS NB test status!");
  while(!AISnb.testCommand().status)
  {
    Serial.print('.');
  }
  Serial.println("AIS NB OK!"); 

  delay(1000); 
  previousMillis = millis(); 

  //nb_resp_t _res = AISnb.sendCommand("AT+NRB", 10000);
  //Serial.print("Received: ");
  //Serial.println(_res.data);

  //String hex = AISnb.str2HexStr("Welcome AIS NB!");
  //String ss = AISnb.hex2Str(hex);
  //Serial.print("TEST HEX: ");
  //Serial.println(hex);
  //Serial.print("TEST STRING: ");
  //Serial.println(ss);

  /*
  nb_split_t res_splite = AISnb.splitFromData("192.128.1.0..2", "..");
  if(res_splite.hasValue)
  {
    for(int i=0;i<20;i++){
      Serial.print("item[" + String(i) + "]=");
      Serial.println(res_splite.result[i]); 
    }
  }
  */
  AISnb.setupDevice(serverPort);  
  nb_resp_t res_DeviceIP = AISnb.getDeviceIP();  
  nb_resp_t res_testPing = AISnb.testPing(serverIP);  
  
  /*
  nb_resp_t res_Reboot = AISnb.rebootModule();
  delay(1000); 
  //nb_resp_t res_ConnectOn = AISnb.autoConnectOn();
  delay(1000); 

  nb_resp_t res_NetworkStatus = AISnb.getNetworkStatus();
  String result = AISnb.subFromData(res_NetworkStatus.temp,"+CEREG:");
  Serial.println("result:"+result);
  delay(1000); 
  nb_resp_t res_SetNetworkStatus = AISnb.setNetworkStatus(4);
  delay(1000); 
  nb_resp_t res_FuncMode = AISnb.setFuncMode(1);
  delay(1000); 
  nb_resp_t res_SetCGATT = AISnb.setCGATT(1);
  delay(1000); 
  
  nb_resp_t res_APN = AISnb.getAPN();
  delay(1000); 
  //nb_resp_t res_SetAPN = AISnb.setAPN("devkit.nb");
  //delay(1000);  
  
  nb_resp_t res_ModuleStatus = AISnb.getModuleStatus();
  delay(1000); 
  nb_resp_t res_FirmwareRevision = AISnb.getFirmwareRevision();
  delay(1000); 
  nb_resp_t res_Signal = AISnb.getSignal();
  delay(1000); 
  nb_resp_t res_IMEI = AISnb.getIMEI();
  delay(1000); 
  nb_resp_t res_IMSI = AISnb.getIMSI();
  delay(1000); 
  nb_resp_t res_NCCID = AISnb.getNCCID();
  delay(1000); 
  
  nb_resp_t res_CGATT = AISnb.getCGATT(); 
  delay(1000); 
  nb_resp_t res_DeviceIP = AISnb.getDeviceIP(); 
  delay(1000); 
  nb_resp_t res_TestPing = AISnb.testPing(serverIP);
  delay(1000); 
  
  */
}

void loop() 
{
  unsigned long currentMillis = millis();
  //Serial.print("currentMillis: ");
  //Serial.println(currentMillis);
  if (abs(currentMillis - previousMillis) >= interval)
  { 
    previousMillis = currentMillis;  
    
    nb_resp_t res_send = AISnb.sendUDPMessage(1, serverIP, serverPort, udpData.length(), udpData, MODE_STRING_HEX);
    if(!res_send.status)
    {
      AISnb.createUDPSocket(serverPort); 
    }
    /*if(myserial.available() > 0)
    {
      Serial.println();
      Serial.println("=================================");
      delay(10);
      Serial.print("Received from NB: "); 
      while(myserial.available())
      {
        char c = myserial.read();
        Serial.print(c); 
      }
      Serial.println(); 
    }*/

    /*
    if(Serial.available() > 0)
    {
      read_timeout = 1;
      Serial.println("================================="); 
      delay(10);
      Serial.print("Received from Serial: "); 
      while(Serial.available())
      {
         char c = Serial.read();
         buffer_receive[count_buffer] = c;
         count_buffer ++;
         Serial.print(c); 
      } 
      Serial.println();  
    } 
    if(read_timeout-- <= 0)
    {
      read_timeout = 1;
      if(count_buffer > 0)
      { 
        Serial.println("================================="); 
        data_str = ""; 
        for(unsigned int i = 0; i < count_buffer; i++)
        { 
           data_str += buffer_receive[i];
        }  
        data_str += '\n';  
        Serial.print("Send to NB: "); 
        Serial.println(data_str);
        count_buffer = 0;
        
        nb_resp_t res = AISnb.sendCommand(data_str, 10000);
        //Serial.print("Received from NB: "); 
        //Serial.println(res.temp); 
      }
   
       
    } 
     */
  }
  String getResponse = AISnb.getSocketResponse();
  if(getResponse.length() > 0){
    Serial.print("UDP response: ");
    Serial.println(getResponse);
  }

}
