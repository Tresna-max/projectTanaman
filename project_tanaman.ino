#include "DHT.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>

#define DHTTYPE DHT11   // DHT 11 
#define DHTPIN4 D4     // Digital pin connected to the DHT sensor
#define DHTPIN5 D5     // Digital pin connected to the DHT sensor

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

DHT dht4(DHTPIN4, DHTTYPE);
DHT dht5(DHTPIN5, DHTTYPE);

const char* ssid = "ZTE_2.4G_UPyc5u"; 
const char* password = "tresna987";
//WiFiClient client;
byte server[] = {192, 168, 1, 11};   //eg: This is the IP address of your PC once XAMPP 

WiFiClient client;    

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  // Start the DS18B20 sensor
  sensors.begin();
  
  dht4.begin();
  dht5.begin();

  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Got IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  delay(1000);
}

static unsigned long lastMillis = 0;

void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  float humidity4 = dht4.readHumidity();
  float temperature4 = dht4.readTemperature();
  float humidity5 = dht5.readHumidity();
  float temperature5 = dht5.readTemperature();
  float soilMoisture = analogRead(A0);
  
    // TODO: Replace with your code here
  if (millis() - lastMillis > 5000)
  {
    lastMillis = millis();
    Sending_To_phpmyadmindatabase(soilMoisture, temperatureC, humidity4, temperature4, humidity5, temperature5); 
  }  
}


 void Sending_To_phpmyadmindatabase(float soilMoisture, float soilTemp, float windHumU, float windTempU, float windHumS, float windTempS)   //CONNECTING WITH MYSQL, pass the variables here to call the function correctly.
   {
   if (client.connect(server, 80)) {
    Serial.println("connected to local server");
    // Make a HTTP request:
    
    Serial.print("GET /arduino/projectTanaman.php?SoilMoist=");
    client.print("GET /arduino/projectTanaman.php?SoilMoist=");     //YOUR URL
    Serial.print(soilMoisture);
    client.print(soilMoisture);
    
    client.print("&SoilTemp=");    
    Serial.print("&SoilTemp=");
    client.print(soilTemp);
    Serial.print(soilTemp);

    client.print("&WindHumU=");    
    Serial.print("&WindHumU=");
    client.print(windHumU);
    Serial.println(windHumU);

    client.print("&WindTempU=");    
    Serial.print("&WindTempU=");
    client.print(windTempU);
    Serial.print(windTempU);

    client.print("&WindHumS=");    
    Serial.print("&WindHumS=");
    client.print(windHumS);
    Serial.print(windHumS);

    client.print("&WindTempS=");    
    Serial.print("&WindTempS=");
    client.print(windTempS);
    Serial.println(windTempS);

    
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
 
    client.println("Host: 192.168.1.11"); // Add your server IP address here. If you forgotten, please see XAMPP > Apached-access-logs for issues. If the IP address is not added or incorrectly added, Apache will give error 400 which is malformed HTTP Request
    client.println("Connection: close");
    client.println(); 
    
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
