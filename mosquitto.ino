#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "GENIAL64";
const char* password = "EuMaAnCo_70";
const char* mqtt_server = "192.168.1.76";   // por ejemplo 192.168.1.15

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado");
  Serial.print("IP ESP32: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado");
    } else {
      Serial.print(" Error rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("Iniciando ESP32...");

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  client.publish("iot/mensaje", "Hola desde ESP32");
  Serial.println("Mensaje enviado");

  delay(5000);
}