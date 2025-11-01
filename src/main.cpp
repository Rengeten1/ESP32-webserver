/*
 * ESP32 WROOM - Simple Web Server with LED Control
 * Author: Rownak Deb Kabya
 */

#include <WiFi.h>
#include <WebServer.h>

// LED 
#define LED_BUILTIN 2

bool ledState = LOW;

// WiFi credentials
const char* ssid = "SSID"; 
const char* password = "PASS;

// Create web server on port 80
WebServer server(80);

// HTML webpage
const char* htmlPage = R"(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Status Server</title>
    <style>
        body { font-family: Arial; text-align: center; padding: 20px; background:rgb(114, 114, 114); }
        h1 { color: #333; }
        .info-box { background: white; padding: 20px; border-radius: 8px; display: inline-block; }
        .button { padding: 10px 20px; margin: 5px; font-size: 16px; cursor: pointer; background:rgb(65, 65, 65); color: white; border: none; border-radius: 4px; }
    </style>
</head>
<body>
    <h1>Options</h1>
    <div class="info-box">
        <p><strong>Status:</strong>ESP#" Running</p>
        <button class="button" onclick="location.href='/status'">Get Status</button>
        <button class="button" onclick="location.href='/led'">Toggle Builtin LED</button>
    </div>
</body>
</html>
)";

void handleRoot() {
    Serial.println("Client visited: /");
    server.send(200, "text/html", htmlPage);
}

void toggleLED() {
    ledState = !ledState;  // Toggle state
    digitalWrite(LED_BUILTIN, ledState);
    String ledStatus = "LED IS: " + String(ledState ? "ON" : "OFF");  // FIX: Fixed string creation
    server.send(200, "text/plain", ledStatus);
    Serial.println(ledStatus);  // FIX: Added serial output
}

void handleStatus() {
    Serial.println("Client visited: /status");
    String status = "ESP32 Status:\n";
    status += "IP: " + WiFi.localIP().toString() + "\n";
    status += "Signal: " + String(WiFi.RSSI()) + " dBm\n";
    status += "Uptime: " + String(millis() / 1000) + " sec\n";
    server.send(200, "text/plain", status);
}

void handleNotFound() {
    Serial.println("404 - Page not found");
    server.send(404, "text/plain", "404 Not Found");
}

void setup() {
    // Initialize LED 
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW); 

    // Initialize Serial with proper delays
    delay(1000);  // Wait for power stabilization
    Serial.begin(115200);
    delay(1000);  // Wait for Serial to initialize
    
    // Send test data to ensure Serial is working
    Serial.write("");  // Newline
    Serial.write("");  // Newline
    
    // Now print startup message
    Serial.println("------------------------------------------");
    Serial.println("Web Server Starting...");
    Serial.println("------------------------------------------");
    delay(500);
    
    // WiFi setup
    Serial.println("\nWifi Connecting to: " + String(ssid));
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
        Serial.print(".");
        delay(500);
        attempts++;
    }
    Serial.println();  // New line
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Wifi  Connected!");
        Serial.print("Wifi IP Address: ");
        Serial.println(WiFi.localIP());

    } else {
        Serial.println("WiFi Connection Failed!");
        Serial.println("Check SSID and Password");
        return;
    }

    // Setup web server routes
    Serial.println("\nServer Setting up routes...");
    server.on("/", HTTP_GET, handleRoot);
    server.on("/led", HTTP_GET, toggleLED);
    server.on("/status", HTTP_GET, handleStatus);
    server.onNotFound(handleNotFound);

    // Start server
    server.begin();
    Serial.println("[Server]  Started on port 80!");
    Serial.println("\n------------------------------------------");
    Serial.println("OPEN BROWSER: http://" + WiFi.localIP().toString());
    Serial.println("------------------------------------------\n");
}

void loop() {
    server.handleClient();
    delay(1);
}