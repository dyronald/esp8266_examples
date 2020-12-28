#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

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

void setup() 
{
  Serial.begin(115200);
  delay(2000);
  Serial.setTimeout(30000);
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    WiFiClient wifiClient;
    HTTPClient http;  //Declare an object of class HTTPClient

 
    String request_url("http://192.168.1.202/api/token");
    http.begin(wifiClient, request_url);
    int httpCode = http.POST("");

    Serial.println(httpCode);
    if (httpCode > 0) 
    {  
      String payload = http.getString();
      Serial.println(payload);
    }
 
    http.end();
  }
  else
  {
    Serial.println("connecting Wifi");
    connectWifi();
  }

  Serial.println("---");
  delay(5000);
}
