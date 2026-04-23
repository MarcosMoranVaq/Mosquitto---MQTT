# MQTT IoT — Mosquitto Broker + ESP32 Publisher
 
Configuracion de un broker MQTT con Mosquitto en Raspberry Pi y un cliente Publisher programado en ESP32, comunicandose a traves de red local.
 
---
 
## Descripcion
 
El proyecto implementa una arquitectura IoT basada en el protocolo MQTT (Message Queuing Telemetry Transport). La Raspberry Pi funciona como servidor MQTT (broker) y la ESP32 como cliente publicador, enviando mensajes al broker cada 5 segundos. Cualquier cliente suscrito al topico recibe los mensajes en tiempo real.
 
```
ESP32 (Publisher) --> Broker Mosquitto (Raspberry Pi) --> Subscriber
      "Hola desde ESP32"           iot/mensaje
```
 
---
 
## Requisitos
 
**Hardware**
- Raspberry Pi (cualquier modelo con conectividad de red)
- ESP32 Dev Module
- Red Wi-Fi local
**Software**
- Raspberry Pi OS Bullseye o superior
- Arduino IDE 2.x o PlatformIO
- Libreria PubSubClient: https://github.com/knolleary/pubsubclient
---
 
## Instalacion y Configuracion
 
### 1. Instalar Mosquitto en Raspberry Pi
 
```bash
sudo apt update && sudo apt upgrade -y
sudo apt install mosquitto mosquitto-clients -y
sudo systemctl enable mosquitto
sudo systemctl start mosquitto
sudo systemctl status mosquitto
```
 
### 2. Configurar Mosquitto para conexiones externas
 
Editar el archivo de configuracion:
 
```bash
sudo nano /etc/mosquitto/mosquitto.conf
```
 
Agregar al final del archivo:
 
```
listener 1883
allow_anonymous true
```
 
Reiniciar el servicio:
 
```bash
sudo systemctl restart mosquitto
```
 
### 3. Obtener la IP de la Raspberry Pi
 
```bash
hostname -I
```
 
Esta IP se usara en la configuracion de la ESP32.
 
---
 
## Configuracion de la ESP32
 
### 1. Instalar la libreria PubSubClient
 
En Arduino IDE ir a Sketch > Include Library > Manage Libraries, buscar PubSubClient de Nick O'Leary e instalar la version mas reciente.
 
### 2. Modificar el sketch
 
Abrir `mosquitto.ino` y editar las siguientes lineas:
 
```cpp
const char* ssid = "NOMBRE_RED_WIFI";
const char* password = "CONTRASENA_WIFI";
const char* mqtt_server = "192.168.x.x";  // IP de la Raspberry Pi
```
 
### 3. Cargar el sketch
 
1. Conectar la ESP32 por USB.
2. Seleccionar la placa: ESP32 Dev Module.
3. Seleccionar el puerto COM correspondiente.
4. Cargar el sketch con Upload.
---
 
## Prueba del sistema
 
Ejecutar un Subscriber en la Raspberry Pi o en cualquier equipo con mosquitto-clients instalado:
 
```bash
mosquitto_sub -h 192.168.x.x -t iot/mensaje
```
 
Si la comunicacion es correcta, se recibiran mensajes cada 5 segundos:
 
```
Hola desde ESP32
Hola desde ESP32
Hola desde ESP32
```
 
Para publicar un mensaje de prueba de forma manual:
 
```bash
mosquitto_pub -h 192.168.x.x -t iot/mensaje -m "Mensaje de prueba"
```
 
Para monitorear el broker con log detallado:
 
```bash
mosquitto -c /etc/mosquitto/mosquitto.conf -v
```
 
---
 
## Estructura del repositorio
 
```
mqtt-esp32-mosquitto/
├── mosquitto.ino        # Codigo fuente de la ESP32
├── README.md            # Documentacion del proyecto
├── .gitignore           # Archivos excluidos del repositorio
└── evidencias/
    ├── broker_mosquitto.png
    ├── esp32_serial_monitor.png
    └── subscriber_recepcion.png
```
 
---
 
## Conceptos del protocolo MQTT
 
| Concepto   | Descripcion                                                         |
|------------|---------------------------------------------------------------------|
| Broker     | Servidor central que recibe y distribuye mensajes                   |
| Publisher  | Cliente que publica mensajes en un topico                           |
| Subscriber | Cliente que recibe mensajes de un topico al que esta suscrito       |
| Topico     | Canal de comunicacion, ej: iot/mensaje                              |
| QoS 0      | Entrega sin confirmacion (at most once)                             |
 
---
 
## Referencias
 
- Eclipse Mosquitto: https://mosquitto.org
- PubSubClient: https://github.com/knolleary/pubsubclient
- ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
- OASIS MQTT v5.0: https://docs.oasis-open.org/mqtt/mqtt/v5.0/mqtt-v5.0.html
