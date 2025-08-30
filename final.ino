#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

String request, number;
int myInt, DelayTime = 0, flag = 0;

const int D5 = 14;  // GPIO14 corresponds to D5, declared globally

void setup() 
{
  pinMode(D5, OUTPUT);
  digitalWrite(D5, HIGH);  // Relay OFF initially
  Serial.begin(9600);

  WiFi.begin("OnePlus 11R 5G", "12345678");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() 
{
  client = server.available(); 
  
  if (client)  // changed from 'client == 1' to proper check
  {  
    request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();

    // ON commands
    if(request=="GET /1on HTTP/1.1") { digitalWrite(D5,HIGH); DelayTime = 60000; flag = 0; }
    else if(request=="GET /5on HTTP/1.1") { digitalWrite(D5,HIGH); DelayTime = 300000; flag = 0; }
    else if(request=="GET /10on HTTP/1.1") { digitalWrite(D5,HIGH); DelayTime = 600000; flag = 0; }
    else if(request=="GET /20on HTTP/1.1") { digitalWrite(D5,HIGH); DelayTime = 120000; flag = 0; }

    // OFF commands
    else if(request=="GET /1off HTTP/1.1") { digitalWrite(D5,LOW); DelayTime = 60000; flag = 1; }
    else if(request=="GET /5off HTTP/1.1") { digitalWrite(D5,LOW); DelayTime = 300000; flag = 1; }
    else if(request=="GET /10off HTTP/1.1") { digitalWrite(D5,LOW); DelayTime = 600000; flag = 1; }
    else if(request=="GET /20off HTTP/1.1") { digitalWrite(D5,LOW); DelayTime = 120000; flag = 1; }

    // Immediate commands
    else if(request=="GET /0off HTTP/1.1") { DelayTime = 0; digitalWrite(D5,HIGH); }
    else if(request=="GET /0on HTTP/1.1") { DelayTime = 0; digitalWrite(D5,LOW); }

    // Blocking delay (works but keeps Wi-Fi alive)
    if(DelayTime>0){
      unsigned long startTime = millis();
      while(millis() - startTime < DelayTime) {
        delay(100);
        yield();  // allows Wi-Fi stack to run
      }
      if(flag==0) digitalWrite(D5,LOW);
      else digitalWrite(D5,HIGH);

      Serial.println("done");
    }

    DelayTime = 0;
    flag = 0;

    // Send simple HTTP response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<html><body><h1>Command Received</h1></body></html>");
    client.stop();
  }
}
