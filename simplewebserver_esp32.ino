/*  
  Rui Santos & Sara Santos - Random Nerd Tutorials
  https://RandomNerdTutorials.com/learn-esp32-with-arduino-ide/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "HUAWEI Mate 10 lite";
const char* password = "georgia67";

// Assign output variables to GPIO pins
const int outputred = 12;
const int outputgreen = 27;
String outputredState = "off";
String outputgreenState = "off";

// Create a web server object
WebServer server(80);

// Function to handle turning GPIO 26 on
void handleGPIOredOn() {
  outputredState = "on";
  digitalWrite(outputred, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 26 off
void handleGPIOredOff() {
  outputredState = "off";
  digitalWrite(outputred, LOW);
  handleRoot();
}

// Function to handle turning GPIO 27 on
void handleGPIOgreenOn() {
  outputgreenState = "on";
  digitalWrite(outputgreen, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 27 off
void handleGPIOgreenOff() {
  outputgreenState = "off";
  digitalWrite(outputgreen, LOW);
  handleRoot();
}

// Function to handle the root URL and show the current states
void handleRoot() {
  // Start building a very simple HTML page
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>ESP32 Web Server</title>";
  html += "</head>";
  html += "<body>";
  
  html += "<h1>ESP32 Web Server</h1>";

  // GPIO red controls
  html += "<h2>GPIO red - State: " + outputredState + "</h2>";
  if (outputredState == "off") {
    html += "<a href='/red/on'>Turn ON</a><br><br>";
  } else {
    html += "<a href='/red/off'>Turn OFF</a><br><br>";
  }

  // GPIO green controls
  html += "<h2>GPIO green - State: " + outputgreenState + "</h2>";
  if (outputgreenState == "off") {
    html += "<a href='/green/on'>Turn ON</a><br><br>";
  } else {
    html += "<a href='/green/off'>Turn OFF</a><br><br>";
  }

  html += "</body>";
  html += "</html>";

  // Send the HTML page to the browser
  server.send(200, "text/html", html);
}


void setup() {
  Serial.begin(115200);

  // Initialize the output variables as outputs
  pinMode(outputred, OUTPUT);
  pinMode(outputgreen, OUTPUT);
  // Set outputs to LOW
  digitalWrite(outputred, LOW);
  digitalWrite(outputgreen, LOW);

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the web server to handle different routes
  server.on("/", handleRoot);
  server.on("/red/on", handleGPIOredOn);
  server.on("/red/off", handleGPIOredOff);
  server.on("/green/on", handleGPIOgreenOn);
  server.on("/green/off", handleGPIOgreenOff);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
