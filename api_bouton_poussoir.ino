/*
 ESP8266 MQTT - DashBouton, Bouton poussoir ou détecteur d'ouverture de porte
 Création Dominique PAUL.
 Dépot Github : https://github.com/DomoticDIY/MQTT-API_Dashbouton
 Chaine YouTube du Tuto Vidéo : https://www.youtube.com/c/DomoticDIY
  
 Bibliothéques nécessaires :
  - pubsubclient : https://github.com/knolleary/pubsubclient
  - ArduinoJson : https://github.com/bblanchon/ArduinoJson
 Télécharger les bibliothèques, puis dans IDE : Faire Croquis / inclure une bibliothéque / ajouter la bibliothèque ZIP.
 Puis dans IDE : Faire Croquis / inclure une bibliothéque / Gérer les bibliothèques, et ajouter :
  - ESP8266Wifi.
 Installer le gestionnaire de carte ESP8266 version 2.5.0 
 Si besoin : URL à ajouter pour le Bord manager : http://arduino.esp8266.com/stable/package_esp8266com_index.json
 
 Adaptation pour reconnaissance dans Domoticz :
 Dans le fichier PubSubClient.h : La valeur du paramètre doit être augmentée à 512 octets. Cette définition se trouve à la ligne 26 du fichier.
 Sinon cela ne fonctionne pas avec Domoticz
 
 Pour prise en compte du matériel :
 Installer si besoin le Driver USB CH340G : https://wiki.wemos.cc/downloads
 dans Outils -> Type de carte : generic ESP8266 module
  Flash mode 'QIO' (régle générale, suivant votre ESP, si cela ne fonctionne pas, tester un autre mode.
  Flash size : 1M (no SPIFFS)
  Port : Le port COM de votre ESP vu par windows dans le gestionnaire de périphériques.
*/

// Inclure les librairies.
#include <ESP8266WiFi.h>


// Déclaration des constantes, données à adapter à votre réseau.
// ------------------------------------------------------------
const char* ssid = "_MON_SSID_";                  // SSID du réseau Wifi
const char* password = "_MOT_DE_PASSE_WIFI_";     // Mot de passe du réseau Wifi.
const char* ipDomoticz = "192.168.1.26";          // Adresse IP ou DNS du serveur Domoticz.
const int portDomoticz = 8080;                    // Port de connexion à Domoticz.
// ------------------------------------------------------------
// Variables et constantes utilisateur :
String nomModule = "DashBouton";                  // Nom usuel de ce module. Sera visible uniquement dans les Log Domoticz.
int idxDevice = 27;                               // Index du Device à actionner.
// ------------------------------------------------------------

WiFiClient client;


// SETUP
// *****
void setup() {
  Serial.begin(115200);                       // On initialise la vitesse de transmission de la console.
  setup_wifi();                               // Connexion au Wifi
  // Envoi de l'information via JSON et MQTT
  SendData();
  // On met le système en sommeil.
  Serial.println("Mise en veille prolongée de l'ESP !");
  ESP.deepSleep(0);
}

// BOUCLE DE TRAVAIL
// *****************
void loop() {
}


// CONNEXION WIFI
// **************
void setup_wifi() {
  // Connexion au réseau Wifi
  delay(10);
  Serial.println();
  Serial.print("Connection au réseau : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    // Tant que l'on est pas connecté, on boucle.
    delay(500);
    Serial.print(".");
  }
  // Initialise la séquence Random
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("Addresse IP : ");
  Serial.println(WiFi.localIP());
}


// ENVOI DES DATAS.
// ***************
void SendData () {
  // Création du lien qui sera envoyé à l'API.
  String messageOut = "/json.htm?type=command&param=switchlight&idx=" + String(idxDevice) + "&switchcmd=On";
  Serial.print("Message à envoyer : ");
  Serial.println(messageOut);
  
  // Envoi de la requete à Domoticz.
  if (client.connect(ipDomoticz, portDomoticz)) {    // On se connecte au serveur Domoticz
    client.println(String("GET ") + messageOut + " HTTP/1.1");
    client.println("Connection: close");             // On ferme la connexion.
    client.println();
  } 

  // Pause de 5 secondes
  delay(5000);
  Serial.println("Message envoyé à Domoticz");
}