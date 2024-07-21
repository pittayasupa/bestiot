# Best IoT Solutions

## Integrating AIS NB-IoT with ESP32 and LPWA BC95-G NB-IoT Module

Welcome to this comprehensive example library for integrating the ESP32 microcontroller with the BC95-G NB-IoT module.

## Quectel BC95-G-GBC68 AT Command Manual v1.5

For detailed instructions on AT commands, you can download the manual from the following link: [Quectel BC95-G-GBC68 AT Commands Manual v1.5](https://www.quectel.com/download/quectel_bc95-gbc68_at_commands_manual_v1-5).

## Implementation Example

1. **Include the Library**  
   - Include the library `NB_BC95_G.h` in your project.

2. **Create an AISnb Instance**  
   - Instantiate the `AISnb` class from the `NB_BC95_G` library.

3. **Setup Serial Monitor**  
   - Configure your serial monitor with any baud rate suitable for your project.

4. **Initialize the Module**  
   - Use `AISnb.begin(baudrate, parity, rx_pin, tx_pin)` to initialize the module.
     - Set the baud rate to 9600.
     - Use `SERIAL_8N1` for 8 data bits and 1 stop bit. For more information, refer to the [Arduino Serial.begin() documentation](https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/).
     - Define `rx_pin` as the receiver pin connected to the BC95-G module.
     - Define `tx_pin` as the transmission pin connected to the BC95-G module.

5. **Test Commands**  
   - Verify the serial port functionality by sending test commands.

6. **Device Setup and UDP Socket Creation**  
   - Configure the device and create a UDP socket using the `serverPort` parameter.

7. **Retrieve Device IP**  
   - Obtain the device IP to check network connectivity.

8. **Test Server IP**  
   - Test communication with the server IP.

## NB-IoT Data Structures

1. **`nb_resp_t`**  
   - A structure for capturing response status and command responses (e.g., temperature).

2. **`nb_split_t`**  
   - A structure for parsing command responses, facilitating easier usage.

3. **`nb_socket_t`**  
   - A structure for managing socket creation.

## Recommended NB-IoT Functions

1. **`sendCommand`**  
   - Allows you to send test AT commands.

2. **`subFromData`**  
   - Retrieves command response results.

3. **`spiteFromData`**  
   - Splits command results for easier handling.

4. **`str2HexStr`**  
   - Converts text strings to hexadecimal strings for socket communication.

5. **`hex2Str`**  
   - Converts received hexadecimal strings to text strings using ASCII codes.

## Example Code
### Code Initialization

```c++
#include "NB_BC95_G.h"
NB_BC95_G AISnb;

const long interval = 10000;  // Interval in milliseconds
unsigned long previousMillis = 0;
```

**Include the Library:** NB_BC95_G.h is included to provide necessary functions and definitions for the NB-IoT module.

**Create AISnb Instance:** An instance of the NB_BC95_G class is created to interact with the NB-IoT module.

**Set Interval:** A constant interval of 10,000 milliseconds (10 seconds) is defined for timing operations.

**Previous Milliseconds:** A variable to store the last time a message was sent is initialized.

### Setup Function
```c++
void setup()
{
  AISnb.debug = true; // Enable debug mode
  AISnb.delayAfterCommand = 1000; // Set delay after each command to 1 second
  AISnb.begin(9600, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN); // Initialize the NB-IoT module
  Serial.println("Waiting for AIS NB test status!");
  
  // Loop until the test command is successful
  while(!AISnb.testCommand().status)
  {
    Serial.print('.');
  }
  Serial.println("AIS NB OK!"); // Indicate successful initialization
  delay(1000); // Wait for 1 second
  previousMillis = millis(); // Initialize the previousMillis with the current time
  
  // Setup the device with the specified port
  AISnb.setupDevice("enter your port");  
  nb_resp_t res_DeviceIP = AISnb.getDeviceIP(); // Get the device IP address
  nb_resp_t res_testPing = AISnb.testPing(serverIP); // Test ping to the server IP
}
```

**Enable Debug Mode:** Sets debug to true to enable debugging output.

**Set Command Delay:** Configures a delay of 1 second after each command.

**Initialize NB-IoT Module:** Calls begin to initialize the module with a baud rate of 9600 and appropriate serial settings.

**Wait for Initialization:** Continuously checks the module's status using testCommand and prints dots until the module is ready.

**Confirm Initialization:** Prints "AIS NB OK!" upon successful initialization.

**Delay and Timing:** Adds a 1-second delay and initializes the previousMillis variable.

**Setup Device:** Configures the device with the specified port and retrieves the device IP and ping response.

### Loop Function
```c++
void Loop()
{
  unsigned long currentMillis = millis(); // Get the current time in milliseconds
  
  // Check if the interval has passed
  if (abs(currentMillis - previousMillis) >= interval) 
  { 
    previousMillis = currentMillis; // Update the previousMillis variable
    
    // Attempt to send a UDP message to the server
    nb_resp_t res_send = AISnb.sendUDPMessage(socketId, "enter server ip", "enter server port", length, message, MODE_STRING_HEX);
    
    // If the command response is an error, create a new socket
    if(!res_send.status) 
    {
      AISnb.createUDPSocket(serverPort); 
    }
  }
  
  // Get and print the socket response
  String getResponse = AISnb.getSocketResponse();
  if(getResponse.length() > 0)
  {
    Serial.print("UDP response: ");
    Serial.println(getResponse);
  }
}
```

**Get Current Time:** Retrieves the current time in milliseconds using millis().

**Check Interval:** Compares the current time with the previousMillis to see if the defined interval has passed.

**Update Timing:** Updates **previousMillis** to the current time.

**Send UDP Message:** Attempts to send a UDP message to the specified server IP and port.

**Handle Errors:** If the send command fails, it creates a new UDP socket.

**Get Socket Response:** Retrieves any response from the socket and prints it to the serial monitor if available.
