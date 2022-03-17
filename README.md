# bestiot
# AIS NB-IoT Library
AIS NB-IoT Library is designed for DEVIO NB-SHIELD I to connect with your own IoT Platform/ Server. 
The library is using Software Serial for communication with Arduino board.
# BC95-G Libary
# Example
Serial port COM3 opened
Serial port buadrate: 115200

=================================
### Set Begin NB_BC95_G library v1.0 ###
Waiting for AIS NB test status!
Send Command: AT
Received Command: 
OK

AIS NB OK!
=================================
Send Command: AT+CGSN=1
Received Command: 
+CGSN:867724031411710

OK

=================================
Send Command: AT+NCCID
Received Command: 
+NCCID:8966031840041733227

OK

=================================
Send Command: AT+CGMR
Received Command: 
SSB,V150R100C10B200SP1

SECURITY_A,V150R100C20B300SP5

PROTOCOL_A,V150R100C20B300SP5

APPLICATION_A,V150R100C20B300SP5

SECURITY_B,V150R100C20B300SP5

RADIO,Hi2115_RF0

OK

attachNB
=================================
Send Command: AT+CGATT?
Received Command: 
+CGATT:1

OK

=================================
Send Command: AT+NSOCR=DGRAM,17,19956,1
Received Command: 
ERROR

=================================
Send Command: AT+CGPADDR
Received Command: 
+CGPADDR:0,10.14.13.64
OK

=================================
Send Command: AT+NPING=147.50.151.130
Received Command: 
OK

attachNB
=================================
Send Command: AT+CGATT?
Received Command: 
+CGATT:1

OK

=================================
Send Command: AT+NSOST=1,147.50.151.130,19956,40,7B22546E223A2238393636303331383430303431373333323237222C2274656D70223A33342E337D

1,40

OK

Send Command: AT+NSORF=1,100
Received Command: 
OK

Send Command: AT+NSORF=1,100
Received Command: 
OK

Send Command: AT+NSORF=1,100
Received Command: 
OK

attachNB
=================================
Send Command: AT+CGATT?
Received Command: 
+CGATT:1

OK

=================================
Send Command: AT+NSOST=1,147.50.151.130,19956,40,7B22546E223A2238393636303331383430303431373333323237222C2274656D70223A33342E337D

1,40

OK

Send Command: AT+NSORF=1,100
Received Command: 
OK

Send Command: AT+NSORF=1,100
Received Command: 
OK

Send Command: AT+NSORF=1,100
Received Command: 
+NPINGERR:1

OK

