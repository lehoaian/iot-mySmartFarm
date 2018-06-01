/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define DHTPIN 0
#define DHTTYPE DHT11

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "c34388c636924b0e963709b30e86f954";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AN AN";
char pass[] = "0977862555";

BlynkTimer timer; // Create a Timer object called "timer"! 
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  dht.begin(); // Start read from DHT sensor

  timer.setInterval(1000L, syncSensorData); //  Here you set interval (1sec) and which function to call 
}

void loop()
{
  Blynk.run();
  timer.run(); // BlynkTimer is working...
}

void syncSensorData()
{
  // This function sends Arduino up time every 1 second to Virtual Pin (V5)
  // In the app, Widget's reading frequency should be set to PUSH
  // You can send anything with any interval using this construction
  // Don't send more that 10 values per second

  syncDHTSensor();
}

void syncDHTSensor() {
  float h = dht.readHumidity();
  // readTemperature
  float t = dht.readTemperature();
  // readTemperature
  float f = dht.readTemperature(true);


  Serial.println("VBLUNO51 - DHT11\r\n");
  Serial.print("Temp(C): ");
  Serial.println(t);
  Serial.print("Humi(%): ");
  Serial.println(h);

  
  // Read OK ?!
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, h); // V0 : Humidity V1 : Temperature
  Blynk.virtualWrite(V1, t);
  
}

