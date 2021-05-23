#include <ESP8266WiFi.h>
#include <Servo.h>
Servo servo;

 
const char* ssid = "NEERAJ04";
const char* password = "Anusrini#1975";  

WiFiServer server(80);

int irPin = 16;
String sensorStatus;
 
void setup() {
  Serial.begin(115200);
  delay(10);
  servo.attach(2); 
  
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  server.begin();
  Serial.println("Server started");
 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

 int value = 0;

if (request.indexOf("/prox") != -1) {
  if(digitalRead(irPin)==0){
   sensorStatus = "Object Detected, Waiting for Servo Signal......";    
  }
  else{
    sensorStatus = "Object Not Detected, We are safe for now!"; 
  }
}
if (request.indexOf("/Req1=0") != -1)  {
  servo.write(0); //Moving servo to 0 degree
  value=0;
}
if (request.indexOf("/Req1=90") != -1)  {  
  servo.write(90); //Moving servo to 90 degree
  value=90;
}
  

  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1 align=center>Security System over WiFi</h1><br><br>");
  client.print("<h2>IR Sensor Status : ");
  client.print(sensorStatus);
  client.println("<br><br>");
  client.print("Current position servo = ");
  client.print(value); 
  client.println("<br><br>");
  client.println("<a href=\"/prox\"\"><button>Get the IR Sensor values</button></a>");
  client.println("<br><br>");
  client.println("<a href=\"/Req1=0\"\"><button>Move servo to 0 degree</button></a>");
  client.println("<a href=\"/Req1=90\"\"><button>Move servo to  90 degree</button></a>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
