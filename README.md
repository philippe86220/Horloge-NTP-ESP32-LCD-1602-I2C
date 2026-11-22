# Horloge NTP – ESP32 + LCD 1602 I2C

Affiche l'heure et la date (heure de Paris, changement d'heure automatique) sur un écran LCD 1602, en récupérant l'heure sur `pool.ntp.org` via le WiFi.


## Matériel

- Carte ESP32 DevKit V1 (module ESP-WROOM-32, 30 broches)
- Écran LCD 1602 5 V avec module I2C (PCF8574) au dos
- 4 fils de liaison
- Câble micro-USB de bonne qualité + chargeur 5 V ≥ 1 A

## Câblage

| LCD (module I2C) | ESP32  |
|------------------|--------|
| GND              | GND    |
| VCC              | VIN (5 V) |
| SDA              | D21    |
| SCL              | D22    |

## Logiciel

- **IDE** : Arduino IDE 1.8.19
- **Gestionnaire de cartes** : ajouter l'URL
  `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
  puis installer **esp32 by Espressif Systems**
- **Type de carte** : ESP32 Dev Module
- **Bibliothèque** : LiquidCrystal I2C (Frank de Brabander), via le gestionnaire de bibliothèques

## Installation

1. `secret.h` doit être dans le même dossier que le `.ino`.
2. Renseigner le nom et le mot de passe du WiFi dans `secret.h`.
3. Téléverser. Si l'upload reste bloqué sur « Connecting… », maintenir le bouton **BOOT** enfoncé.


## Fonctionnement

- Au démarrage, l'écran affiche « Connexion WiFi.. » puis « Attente NTP... ».
- L'heure est configurée une seule fois avec `configTzTime()` ; l'ESP32 se resynchronise ensuite tout seul avec le serveur NTP.
- L'affichage est rafraîchi chaque seconde avec `getLocalTime()`.

## Dépannage

- **L'écran clignote / l'ESP32 redémarre en boucle** : ouvrir le moniteur série à 115200 bauds. « Brownout detector was triggered » = alimentation trop faible → câble USB plus court et chargeur plus puissant.
- **Rien ne s'affiche mais l'écran est allumé** : régler le contraste avec le potentiomètre bleu au dos du module I2C.
- **Toujours rien** : l'adresse I2C peut être `0x3F` au lieu de `0x27` (à changer dans le code).
- **Bloqué sur « Connexion WiFi.. »** : vérifier les identifiants dans `secret.h` (l'ESP32 ne fonctionne qu'en WiFi 2,4 GHz).

## Historique

- 2023-11-08 : création.
- 2026-11-22 : remise en service, code simplifié (NTP configuré une seule fois, lecture de l'heure avec `getLocalTime()`).
