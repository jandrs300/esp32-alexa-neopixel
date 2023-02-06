/**
 * Autor: Juan Sanmartín
 * Página: https://insani.academy/
 * YouTube: https://www.youtube.com/@InsaniAcademy
**/

/** Librerias para Alexa**/
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <Espalexa.h>

/** Librerias para NeoPixel**/
#include <Adafruit_NeoPixel.h>
#define PIN 22        // Pin NEOPIXEL
#define NUMPIXELS 12  // Cantidad NEOPIXEL

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


/** Variables Globales**/

// En caso de usar un LED
int LED = 5;        // Pin donde está conectado el LED


// Credenciales para la Red WiFi
const char* ssid = "Insani_Robotics";   // Nombre de la Red WiFi
const char* password = "1105651960_i";  // Contraseña de la Red Wifi

Espalexa asistente;                     // Nombre del Objeto de la libreria Espalexa
void onLuminaria(uint8_t brightness);         // Declaración de la función 1
void funcionDos(uint8_t brightness);    // Declaración de la función 2


void setup() {
  pixels.begin();                                 // Iniciamos el objeto del NeoPixel
  Serial.begin(115200);                           // Iniciamos la comunicación Serial
  pinMode(LED, OUTPUT);                           // Declaramos como salida el pin del LED
  ConectarWifi();                                 // Iniciamos la conexión WiFi
  asistente.addDevice("LED", onLuminaria);  // Añadimos el dispotivo
  asistente.addDevice("Lampara", funcionDos);       // Añadimos el dispotivo
  asistente.begin();                              // Iniciamos Alexa
}

void loop() {
  ConectarWifi();                                 // Revisar la conexión WiFi
  asistente.loop();                               // Ejecución infinita del asistente
  delay(1);                                       // Tiempo de espera
}

// Función para conectarse la red WiFi
void ConectarWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");
    Serial.println("Conectando a la Red WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      pixels.setPixelColor(1, pixels.Color(255, 0, 0)); //Encender NeoPixel color Rojo
      //digitalWrite(LED, 1);                           //Encender LED
      delay(500);
      Serial.print(".");
      pixels.show(); 
    }
    pixels.setPixelColor(1, pixels.Color(0, 255, 0)); //Encender NeoPixel color Verde
    pixels.show();                                      // Enciende NeoPixel
    Serial.print("Conectado a ");
    Serial.println(ssid);
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
  }
}

void onLuminaria(uint8_t brightness) {
  Serial.print("Funcion onLuminaria - ");
  if (brightness) {
    pixels.setPixelColor(4, pixels.Color(0, 255, 0)); // Enciende NeoPixel color Verde
    //digitalWrite(Foco, 1);
    Serial.println(" ON ");
  }
  else {
    pixels.setPixelColor(4, pixels.Color(0, 0, 0));   // Apagar NeoPixel
    //digitalWrite(Foco, 0);
    Serial.println(" OFF ");
  }
  pixels.show();    // Enciende NeoPixel                  
}



void funcionDos(uint8_t brightness) {
  Serial.print("Funcion Dos - ");

  if (brightness) {
    Serial.println(" True - Estamos en la Función Dos ");
  }
  else {
    Serial.println(" False - Estamos en la Función Dos ");
  }
}


