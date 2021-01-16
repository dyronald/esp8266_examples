#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient wifiClient; 
PubSubClient pubClient(
  "192.168.1.202",
  1883,
  wifiClient);

void connectWifi()
{
  String ssid;
  String password;
  
  Serial.println("");
  Serial.print("ssid: ");
  ssid = Serial.readStringUntil('\n');
  Serial.println(ssid);

  Serial.println("");
  Serial.print("password: ");
  password = Serial.readStringUntil('\n');
  Serial.println(password);

  ssid.trim();
  password.trim();
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print("x");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}

void setup(void)
{ 
  Serial.begin(115200);
  delay(2000);
  Serial.setTimeout(30000);

  connectWifi();

  if (pubClient.connect("Sub2"))
  {
    Serial.println("client connected");
  }
  else
  {
    Serial.println("client failed");
  }
}

int counter = 0;

void loop() {
  delay(1250);

  char payload[256];
  snprintf(payload, sizeof(payload), "arduino payload: %i", counter++);
  pubClient.publish("T1", payload);
  
  Serial.print(".");
  if (counter % 80 == 0)
  {
    Serial.println("");
  }
}
