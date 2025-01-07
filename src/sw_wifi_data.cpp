#include <WiFi.h>         // Gestione della connessione Wi-Fi
#include <WiFiClient.h>   // Gestione della comunicazione TCP
#include "lidar_data.h"   // Include il file per i dati simulati del LiDAR

// Impostazioni Wi-Fi

//LAB
// const char* ssid = "Sealab";         // Nome della rete Wi-Fi LAB
// const char* password = "Cyb3rS3cur1tyByD3s1gn1"; // Password della rete Wi-Fi LAB

//lavoro
// const char* ssid = "SL-Mobile";         // Nome della rete Wi-Fi 
// const char* password = "c4pykapigur!"; // Password della rete Wi-Fi 

//hotspot telefono
 const char* ssid = "Redmi Note 13 Pro";         // Nome della rete Wi-Fi 
 const char* password = "5qvkrf5djjerh9f"; // Password della rete Wi-Fi 

//casa 
// const char* ssid = "APUACOM_07E804";         // Nome della rete Wi-Fi 
// const char* password = "548e74c6"; // Password della rete Wi-Fi 

// Impostazioni server TCP con cui vuoi parlare
const char* server_ip = "192.168.204.165";   //  usare ip del pc: 192.168.204.165  con "ip addr" trovi l'ip dove far comunicare il client con il server, adesso l'ip è 172.28.215.14
const int server_port = 5169;

WiFiClient client;  // Oggetto client TCP

void setup() {
    Serial.begin(115200);  // Avvio della comunicazione seriale
    Serial.println("Inizio connessione Wi-Fi...");
    
    WiFi.mode(WIFI_STA);  // Modalità client
    WiFi.begin(ssid, password);  // Tentativo di connessione Wi-Fi

    // Timeout di 10 secondi per la connessione Wi-Fi
    int wifiTimeout = 10;
    while (WiFi.status() != WL_CONNECTED && wifiTimeout > 0) {
        delay(1000);  // Attendere un secondo
        Serial.print("Tentativo di connessione Wi-Fi... ");
        wifiTimeout--;  // Ridurre il timeout
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnesso al Wi-Fi!");
        Serial.print("IP ESP32: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nConnessione Wi-Fi fallita dopo 10 secondi.");
    }
}

void loop() {
    Serial.print("Tentativo di connessione a ");
    Serial.print(server_ip);
    Serial.print(":");
    Serial.println(server_port);
    // Connessione al server TCP
    if (!client.connected()) {
        Serial.println("Connessione al server TCP...");
        if (client.connect(server_ip, server_port)) {
            Serial.println("Connesso al server!");
        } else {
            Serial.println("Connessione fallita, riprovo...");
            delay(1000);
            return;  // Se la connessione non è riuscita, riprova
        }
    }

    // Ottieni i dati del LiDAR dal file dati_lidar.h
    String lidarData = getLidarData();

    // Stampa i dati simulati sulla seriale per il monitoraggio
    Serial.println("Dati simulati LiDAR:");
    Serial.println(lidarData);

    // Invia i dati al server TCP
    client.print(lidarData);
    Serial.println("Dati inviati al server");

    // Aspetta un secondo prima di inviare il prossimo pacchetto
    delay(1000);
}
