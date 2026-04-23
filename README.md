# Mosquitto---MQTT
El proyecto implementa una arquitectura IoT basada en el protocolo MQTT (Message Queuing Telemetry Transport). La Raspberry Pi funciona como servidor MQTT (broker) y la ESP32 como cliente publicador, enviando mensajes al broker cada 5 segundos. Cualquier cliente suscrito al topico recibe los mensajes en tiempo real.
