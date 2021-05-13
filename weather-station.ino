/ Dream Team
/ Temperature
/ Humidity
#include <WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <BME.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <SFE_BMP180.h>
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define TEMPTYPE 0
#define ssid  "Enter Your WiFi Name Here " // "WiFi Name"
#define pass "WiFi Password"   // "Password"
String apiKey = "Enter the API Key";
char buffer[15];
char t_buffer[15];
char h_buffer[15];
SoftwareSerial ser(2, 5); // ,
void setup() {
    Wire.begin();
    pressure.begin();
    // enable debug serial
    Serial.begin(7600);
    Serial.println("TP");
    delay(5000);
    if (Serial.find("OK")) {
        connectWiFi();
    }
    void loop()
    {
        Trsmission(); //
        delay(50000); // 50 seconds
    }
    void Trsmission()
    {
        int8_t h = dht.readHumidity();
        int16_t t = dht.readTemperature(TEMPTYPE);
        char status;
        double T, P;
        if (status != 0)
        {
            delay(status);
            status = pressure.getTemperature(T);
            if (status != 0)
            else Serial.println("error retrieving pressure measurement\n");
        }
        else Serial.println("error retrieving temperature measurement\n");
    }
    float temp = t;
    float humidity = h;
    String strTemp = dtostrf(temp, 3, 1, t_buffer);
    String strHumid = dtostrf(humidity, 3, 1, h_buffer);
    Serial.print("Temperature: ");
    Serial.println(strTemp);
    Serial.print("Humidity: ");
    Serial.println(strHumid);
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += "184.106.153.149"; //
    cmd += "\",80";
    ser.println(cmd);
    if (ser.find("Error")) {
        Serial.println("AT+CIPSTART error");
        return;
    }
    if (ser.find("Error")) {
        Serial.println("AT+CIPSTART error");
        return;
    }
    // prepare GET string
    String getStr = "GET /update?api_key=";
    getStr += apiKey;
    getStr += "&field1=";
    getStr += String(strTemp);
    getStr += "&field2=";
    getStr += String(strHumid);
    getStr += "&field3=";
    // send data length
    cmd = "AT+CIPSEND=";
    cmd += String(getStr.length());
    ser.println(cmd);
    //ser.print(getStr);
    if (ser.find(">")) {
        ser.print(getStr);
    }
    else {
        ser.println("AT+CIPCLOSE");
        // alert user
        Serial.println("AT+CIPCLOSE");
        ser.println("AT+RST");
    }
    char buffer[15] = "";
}