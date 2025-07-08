/* === Blynk IoT 2.0 === */
#define BLYNK_TEMPLATE_ID        "TMPL2IvU7Y5GX"
#define BLYNK_TEMPLATE_NAME      "Weather Station"
#define BLYNK_AUTH_TOKEN         "6FutGNyW5YsIabjl620oOu0bB9mkLbq0"

/* === Librairies === */
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

/* === Wi-Fi === */
char ssid[] = "ooredoo_brh";
char pass[] = "RTX4060--MSI--2025--";

/* === Capteurs === */
#define LDRPIN       33
#define DHTPIN       27
#define DHTTYPE      DHT11
#define RAIN_DO_PIN  25
#define RAIN_AO_PIN  26

Adafruit_BMP280 bmp;
DHT            dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(100);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  if (!bmp.begin(0x76)) {
    Serial.println(F("Erreur BMP280 !"));
    while (1) delay(10);
  }
  bmp.setSampling(
    Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16,
    Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_500
  );

  dht.begin();
  pinMode(LDRPIN, INPUT);
  pinMode(RAIN_DO_PIN, INPUT);
  pinMode(RAIN_AO_PIN, INPUT);
}

void loop() {
  Blynk.run();

  // --- BMP280 ---
  float tempBMP      = bmp.readTemperature();
  float pressure_hPa = bmp.readPressure() / 100.0;
  float altitude     = bmp.readAltitude(1013.25);

  // --- DHT11 ---
  float hum  = dht.readHumidity();
  float tDHT = dht.readTemperature();
  if (isnan(hum) || isnan(tDHT)) {
    Serial.println(F("Erreur DHT11"));
  }

  // --- LDR ---
  int   ldrValue       = analogRead(LDRPIN);
  String lightCondition;
  if      (ldrValue == 0)       lightCondition = "Non câblé";
  else if (ldrValue < 1000)     lightCondition = "Nuit";
  else if (ldrValue < 2000)     lightCondition = "Lever soleil";
  else if (ldrValue < 3000)     lightCondition = "Matin";
  else if (ldrValue < 3500)     lightCondition = "Midi";
  else                           lightCondition = "Jour";

  // --- Pluie ---
  int   rainDO         = digitalRead(RAIN_DO_PIN);
  int   rainAO         = analogRead(RAIN_AO_PIN);
  String   = (rainDO == LOW && rainAO == 4095)
                          ? "Non câblé"
                          : (rainDO == LOW) ? "Il pleut" : "Clair";

  // --- Console ---
  Serial.printf("BMP T:%.1f°C P:%.1fhPa Alt:%.1fm\n",
                tempBMP, pressure_hPa, altitude);
  Serial.printf("DHT T:%.1f°C H:%.1f%%\n", tDHT, hum);
  Serial.printf("LDR:%d → %s\n", ldrValue, lightCondition.c_str());
  Serial.printf("Rain DO:%d AO:%d → %s\n\n",
                rainDO, rainAO, rainCondition.c_str());

  // --- Envoi à Blynk selon votre mapping ---
  Blynk.virtualWrite(V0, tDHT);            // DHT Temp
  Blynk.virtualWrite(V1, hum);             // DHT Hum
  Blynk.virtualWrite(V2, tempBMP);         // BMP Temp
  Blynk.virtualWrite(V3, pressure_hPa);    // Bmp Pression
  Blynk.virtualWrite(V4, altitude);        // Bmp Altitude
  Blynk.virtualWrite(V6, rainCondition);   // rainCondition
  Blynk.virtualWrite(V7, lightCondition);  // lightCondition

  delay(2000);
}
