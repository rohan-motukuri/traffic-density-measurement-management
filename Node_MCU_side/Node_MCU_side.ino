#include <ESP8266WiFi.h>
#include <FS.h>
#include <SoftwareSerial.h>

const char* ssid = "Rohan's Galaxy M13";
const char* password = "qgiv5246";

SoftwareSerial mySerial(D7, D8);
WiFiServer server(80);

bool firstRender = true; // Variable to keep track of whether the div has been rendered

int laneDens[4] = {0, 0, 0, 0};

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  SPIFFS.begin();
  mySerial.begin(9600);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    while (client.connected()) {
      String msg = mySerial.readStringUntil('\r');

      if (msg.length()) {
        Serial.println(msg);

        // Parse the received message
        int commaIndex = msg.indexOf(',');
        if (commaIndex != -1) {
          int currLane = msg.substring(0, commaIndex).toInt();
          int currDensity = msg.substring(commaIndex + 1).toInt();
          int normalizedHeight = map(currDensity, 0, 20000, 10, 300);

          // Create the HTML response
          if (!laneDens[currLane]) {
            laneDens[currLane] += currDensity;

            String html = "<div id='myDiv" + String(currLane) + "' style='position:relative; bottom: 50% - 150px; background-color: #FF0000; width: 50px; height: " + String(normalizedHeight) + "px; transition: height 0.5s; margin: 10px;'>" + String(currLane + 1) + "</div>";

            if (firstRender) {
              String response = "HTTP/1.1 200 OK\r\n";
              response += "Content-Type: text/html\r\n";
              response += "\r\n";
              response += "<div id='parentDiv' style='position:absolute; left:50%; top:50%; transform: translate(-50%, -50%); display: flex; justify-content: center; align-items: center; width: 500px; height: 500px; border: 5px solid #000000;'>" + html + "</div>";
              client.print(response);
              firstRender = false;
            } else {
              String parentDivScript = "<script>document.getElementById('parentDiv').appendChild(html);</script>";

              client.print(parentDivScript);
            }
          } else {
            String script = "<script>document.getElementById('myDiv" + String(currLane) + "').style.height = '" + String(normalizedHeight) + "px';</script>";
            client.print(script);
          }
          delay(10);
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
