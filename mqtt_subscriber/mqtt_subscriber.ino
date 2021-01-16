#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient wifiClient;
PubSubClient mqttClient(
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

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("x");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println(WiFi.localIP());
}

void subscribe()
{
    if (mqttClient.connect("Sub"))
    {
        Serial.println("client connected");
        mqttClient.subscribe("T1");
    }
    else
    {
        Serial.println("client connection failed");
    }
}

void messageCallback(char* topic, byte* payload, unsigned int length)
{
    Serial.println("MQTT message received callback");
    Serial.println(topic);

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s", reinterpret_cast<char*>(payload));
    Serial.println(buffer);

    Serial.println("------------");
}

void setup(void)
{
    Serial.begin(115200);
    delay(2000);
    Serial.setTimeout(30000);

    connectWifi();

    mqttClient.setCallback(messageCallback)
        .setBufferSize(1024);
    subscribe();
}

int counter = 0;

void loop()
{
    delay(250);

    if (!mqttClient.connected())
    {
        Serial.println("Reconnecting MQTT client");
        subscribe();
    }

    if (!mqttClient.loop())
    {
        Serial.println("MQTT client disconnected");
    }
}
