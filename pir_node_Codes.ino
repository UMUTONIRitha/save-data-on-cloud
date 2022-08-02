
#include <ESP8266WiFi.h>

String apiKey = "Y6MPNVFIOKO2UA63";

const char *ssid =  "Rita";
const char *pass =  "123456789";
const char* server = "api.thingspeak.com";
WiFiClient client;
int bool1 = 300;
void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(A0, INPUT);
  Serial.println("Connecting to ");
  Serial.println(ssid);
 pinMode(A0,INPUT);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop()
{

  int pir = (analogRead(A0)-bool1);

  if (isnan(pir))
  {
    Serial.println("Failed to read from PIR sensor!");
    return;
  }

  if (client.connect(server, 80))
  {

    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(pir);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("PIR Value: ");
    Serial.print(pir);
    Serial.println(". Send to Thingspeak.");
  }
  client.stop();

  Serial.println("Waiting...");
  delay(100);
}
