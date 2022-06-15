
#include <WiFi.h>

int a = 13;
int b = 12;
int e = 14;
int d = 27;

const char* ssid     = "B I S W A _ R X";
const char* password = "09871234";
bool ledFlag = true;
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(2, OUTPUT);      // set the LED pin mode

  delay(10);

  // We start by connecting to a WiFi network

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
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

int value = 0;

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            //            client.println("HTTP/1.1 200 OK");
            //            client.println("Content-type:text/html");
            //            client.println();
            //            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        if (currentLine.endsWith("GET /Tx00")) {
          digitalWrite(a, HIGH);
          digitalWrite(b, HIGH);

          digitalWrite(d, HIGH);
          digitalWrite(e, HIGH);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx00");
          client.println();
          Serial.println("Rx00");
        } else if (currentLine.endsWith("GET /Tx10")) {
          digitalWrite(a, LOW);
          digitalWrite(b, HIGH);

          digitalWrite(d, HIGH);
          digitalWrite(e, HIGH);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx10");
          client.println();
          Serial.println("Rx10");
        } else if (currentLine.endsWith("GET /Tx01")) {
          digitalWrite(a, HIGH);
          digitalWrite(b, HIGH);

          digitalWrite(d, HIGH);
          digitalWrite(e, LOW);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx01");
          client.println();
          Serial.println("Rx01");
        } else if (currentLine.endsWith("GET /Tx11")) {
          digitalWrite(a, LOW);
          digitalWrite(b, HIGH);

          digitalWrite(d, HIGH);
          digitalWrite(e, LOW);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx11");
          client.println();
          Serial.println("Rx11");
        } else if (currentLine.endsWith("GET /Tx22")) {
          digitalWrite(a, HIGH);
          digitalWrite(b, LOW);

          digitalWrite(d, LOW);
          digitalWrite(e, HIGH);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx22");
          client.println();
          Serial.println("Rx22");
        } else if (currentLine.endsWith("GET /Tx12")) {
          digitalWrite(a, LOW);
          digitalWrite(b, HIGH);

          digitalWrite(d, LOW);
          digitalWrite(e, HIGH);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx12");
          client.println();
          Serial.println("Rx12");
        } else if (currentLine.endsWith("GET /Tx21")) {
          digitalWrite(a, HIGH);
          digitalWrite(b, LOW);

          digitalWrite(d, HIGH);
          digitalWrite(e, LOW);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx21");
          client.println();
          Serial.println("Rx21");
        } else if (currentLine.endsWith("GET /Tx02")) {
          digitalWrite(a, HIGH);
          digitalWrite(b, HIGH);

          digitalWrite(d, LOW);
          digitalWrite(e, HIGH);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx02");
          client.println();
          Serial.println("Rx02");
        } else if (currentLine.endsWith("GET /Tx20")) {
          digitalWrite(a, HIGH);
          digitalWrite(b, HIGH);

          digitalWrite(d, LOW);
          digitalWrite(e, HIGH);
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.println("Rx20");
          client.println();
          Serial.println("Rx20");
        }  else if (currentLine.endsWith("GET /Ty")) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();
          client.print("Ry");
          client.print(analogRead(34));
          client.println();
          Serial.print("Ry");
          Serial.println(analogRead(34));
          if (ledFlag)
          {
            ledFlag = false;
            digitalWrite(2, HIGH);
          } else {
            ledFlag = true;
            digitalWrite(2, LOW);
          }
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
