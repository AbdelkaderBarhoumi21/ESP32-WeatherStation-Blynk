# Weather Station – Blynk IoT 2.0

Ce projet permet de construire une mini-station météo connectée basée sur un ESP32, utilisant la plateforme Blynk IoT 2.0 pour la visualisation et le contrôle à distance. Les capteurs mesurés sont :  
- Température et pression (BMP280)  
- Température et humidité (DHT11)  
- Luminosité ambiante (LDR)  
- Présence de pluie (capteur analogique + digital)  

---

## 📋 Matériel requis

- **Carte** : ESP32 (DevKit)  
- **Capteurs** :  
  - Adafruit BMP280 (Température & Pression barométrique)  
  - DHT11 (Température & Humidité)  
  - LDR (résistance dépendante de la luminosité)  
  - Module de détection de pluie (sortie analogique & digital)  
- **Fils de connexion**, breadboard (facultatif)  
- **Alimentation** 5 V (via USB ou adaptateur secteur)  

---

## 📚 Bibliothèques Arduino

- `WiFi.h`  
- `BlynkSimpleEsp32.h` (Blynk IoT 2.0)  
- `Wire.h`  
- `Adafruit_BMP280.h`  
- `DHT.h`  

Installez-les via le **Library Manager** de l’IDE Arduino.

---

## ⚙️ Configuration du projet

1. **Cloner le dépôt**  
   ```bash
   git clone https://github.com/votre-utilisateur/weather-station-blynk.git
   cd weather-station-blynk
