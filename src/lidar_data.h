#ifndef DATI_LIDAR_H
#define DATI_LIDAR_H

#include <WiFiClient.h> 
#include <WiFi.h>
#include <Arduino.h>

// Funzione per ottenere i dati simulati del LiDAR con distanza fissa a 5 metri
String getLidarData() {
    String data = "{ \"angle\": [";
    for (int angle = 0; angle < 360; angle++) {
        data += String(angle);
        if (angle < 359) data += ",";
    }
    data += "], \"distance\": [";
    for (int angle = 0; angle < 360; angle++) {
        float distance = 5.0; // Fissa la distanza a 5 metri
        data += String(distance);
        if (angle < 359) data += ",";
    }
    data += "] }";
    return data;
}

#endif

