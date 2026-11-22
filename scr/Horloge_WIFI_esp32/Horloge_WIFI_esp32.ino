// Horloge NTP sur ESP32 + LCD 1602 I2C
// SDA -> D21, SCL -> D22, VCC -> VIN (5 V), GND -> GND

#include "secret.h"          // contient SECRET_SSID et SECRET_PASS
#include <WiFi.h>
#include <time.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ntpServer = "pool.ntp.org";
const char* fuseauParis = "CET-1CEST,M3.5.0,M10.5.0/3"; // heure d'été / d'hiver automatique

unsigned long derniereMaJ = 0;

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.print("Connexion WiFi..");

  // 1) Connexion au WiFi
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  Serial.print("Connexion au reseau WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println("\nWiFi connecte");

  // 2) Configuration NTP (une seule fois : l'ESP32 se resynchronise ensuite tout seul)
  configTzTime(fuseauParis, ntpServer);
  lcd.clear();
  lcd.print("Attente NTP...");
  Serial.print("Attente date et heure");
  struct tm t;
  while (!getLocalTime(&t)) {   // attend jusqu'a 5 s par essai
    Serial.print('.');
  }
  Serial.println("\nHeure recue");
  lcd.clear();
}

void loop() {
  if (millis() - derniereMaJ >= 1000) {
    derniereMaJ = millis();
    afficheHeureDate();
  }
}

void afficheHeureDate() {
  struct tm t;
  if (!getLocalTime(&t, 0)) return;   // horloge pas encore valide

  char ligne[17];                     // 16 caracteres + fin de chaine
  strftime(ligne, sizeof(ligne), "heure : %H:%M:%S", &t);
  lcd.setCursor(0, 0);
  lcd.print(ligne);

  strftime(ligne, sizeof(ligne), "date :%d/%m/%Y", &t);
  lcd.setCursor(0, 1);
  lcd.print(ligne);
}
