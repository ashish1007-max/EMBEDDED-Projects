#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Keypad.h>

// ---------------- WiFi ----------------
const char* ssid = "Ashish";
const char* password = "12345678";

// ---------------- MQTT ----------------
const char* mqtt_server = "4f2be0c0826240d8bb2f0a450d294263.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "hivemq.webclient.1781867087902";
const char* mqtt_password = "D1V.Ok0lYqeE3@n?v#7A";

WiFiClientSecure espClient;
PubSubClient client(espClient);

// ---------------- KEYPAD ----------------
char keys[4][4] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};

byte rowPins[4] = {16,17,5,18};
byte colPins[4] = {19,21,22,23};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

// MQTT Topic
const char* calcTopic = "Calculator/Input";

// ---------------- WiFi Connect ----------------
void setup_wifi()
{
  Serial.println();
  Serial.print("Connecting to WiFi ");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ---------------- MQTT Connect ----------------
void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Connecting to MQTT...");

    if (client.connect("ESP32Calculator", mqtt_user, mqtt_password))
    {
      Serial.println(" Connected");
    }
    else
    {
      Serial.print(" Failed. State=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

// ---------------- Setup ----------------
void setup()
{
  Serial.begin(115200);

  setup_wifi();

  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);
}

// ---------------- Loop ----------------
void loop()
{
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  char key = keypad.getKey();

  if (key)
  {
    char payload[2];
    payload[0] = key;
    payload[1] = '\0';

    Serial.print("Key Pressed: ");
    Serial.println(payload);

    client.publish(calcTopic, payload);

    delay(200);
  }
}