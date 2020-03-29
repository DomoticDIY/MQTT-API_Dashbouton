# MQTT-API_Dashbouton
DashButtons, ou action via un bouton poussoir

Dans la suite des créations d'objets connectés, nous allons voir comment créer un déclencheur vers Domoticz. L’objet connecté est présenté sous deux formes, l'une via MQTT, et l'autre via les API Domoticz.
L'intéret de cet exemple avec un bouton poussoir est de vous donner des idées de création, comme par exemple un détecteur d'ouverture de porte ou de fenêtre.

# Explications et Tuto vidéo
## Utilitaires à installer
- Driver USB CH340G : https://wiki.wemos.cc/downloads
- Logiciel Arduino IDE : https://www.arduino.cc/en/Main/Software
- URL à ajouter pour le Bord manager : http://arduino.esp8266.com/stable/package_esp8266com_index.json

Installer la prise en charge des cartes ESP8266

## Bibliothéques (pour MQTT) :
 - pubsubclient : https://github.com/knolleary/pubsubclient
 - ArduinoJson v5.13.3 : https://github.com/bblanchon/ArduinoJson
 
Dans IDE : Faire Croquis / inclure une bibliothéque / ajouter la bibliothèque ZIP.


### Adaptation pour reconnaissance dans Domoticz (pour MQTT) :
Dans le fichier PubSubClient.h : La valeur du paramètre doit être augmentée à 512 octets. Cette définition se trouve à la ligne 26 du fichier, sinon cela ne fonctionne pas avec Domoticz

## Tuto vidéo
Vidéo explicative sur YouTube :
