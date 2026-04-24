#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// 🔐 Replace with your WiFi credentials
const char* ssid = "ESP32";
const char* password = "123456789";

ESP8266WebServer server(80);

bool deviceState = false;
int sensorValue = 0;

// 🌐 HTML Webpage
String getWebPage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP8266 Smart Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">

  <style>
    body {
      margin: 0;
      font-family: 'Segoe UI', sans-serif;
      background: linear-gradient(135deg, #1f4037, #99f2c8);
      color: white;
      text-align: center;
    }

    h1 {
      margin-top: 10px;
    }

    .profile {
      background: rgba(0,0,0,0.3);
      padding: 15px;
      margin: 15px;
      border-radius: 10px;
    }

    .container {
      display: flex;
      flex-direction: column;
      align-items: center;
      margin-top: 20px;
    }

    .card {
      background: rgba(255,255,255,0.1);
      backdrop-filter: blur(10px);
      border-radius: 15px;
      padding: 20px;
      margin: 10px;
      width: 260px;
      box-shadow: 0 4px 15px rgba(0,0,0,0.3);
    }

    .value {
      font-size: 26px;
      font-weight: bold;
    }

    .on { color: #00ff88; }
    .off { color: #ff4d4d; }

    button {
      border: none;
      padding: 12px 20px;
      margin: 10px;
      font-size: 16px;
      border-radius: 8px;
      cursor: pointer;
      transition: 0.3s;
    }

    .btn-on {
      background-color: #00c853;
      color: white;
    }

    .btn-off {
      background-color: #d50000;
      color: white;
    }

    footer {
      margin-top: 20px;
      font-size: 12px;
      opacity: 0.7;
    }
  </style>
</head>

<body>

  <h1> ESP8266 Smart IoT Dashboard</h1>

  <!--  PROFILE SECTION -->
  <div class="profile">
    <h2> Vignesh</h2>
    <p>ECE Graduate (2026) | Embedded Systems & IoT Engineer</p>
    <p> Skills: ESP8266, STM32, AWS IoT, Embedded C</p>
    <p> Seeking: Embedded / IoT Roles (Chennai Startups)</p>
  </div>

  <div class="container">

    <div class="card">
      <h3>Device Status</h3>
      <div id="device" class="value">--</div>
    </div>

    <div class="card">
      <h3>Sensor Value</h3>
      <div id="sensor" class="value">--</div>
    </div>

    <div>
      <button class="btn-on" onclick="control('on')">TURN ON</button>
      <button class="btn-off" onclick="control('off')">TURN OFF</button>
    </div>

  </div>

  <footer>Designed & Developed by Vignesh | Embedded IoT Project</footer>

  <script>
    function fetchData() {
      fetch('/status')
      .then(res => res.json())
      .then(data => {
        let deviceEl = document.getElementById('device');
        deviceEl.innerText = data.device;

        if (data.device === "ON") {
          deviceEl.className = "value on";
        } else {
          deviceEl.className = "value off";
        }

        document.getElementById('sensor').innerText = data.sensor;
      });
    }

    function control(state) {
      fetch('/control?state=' + state);
    }

    setInterval(fetchData, 2000);
    fetchData();
  </script>

</body>
</html>
)rawliteral";

  return html;
}

// 🏠 Root handler
void handleRoot() {
  server.send(200, "text/html", getWebPage());
}

// 🎛 Control handler
void handleControl() {
  String state = server.arg("state");

  if (state == "on") {
    deviceState = true;
    Serial.println("Device turned ON");
  } 
  else if (state == "off") {
    deviceState = false;
    Serial.println("Device turned OFF");
  }

  server.send(200, "text/plain", "OK");
}

// 📡 JSON Status API
void handleStatus() {
  // Simulated sensor data
  sensorValue = random(20, 100);

  String json = "{";
  json += "\"device\":\"" + String(deviceState ? "ON" : "OFF") + "\",";
  json += "\"sensor\":" + String(sensorValue);
  json += "}";

  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("\nConnecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Server routes
  server.on("/", handleRoot);
  server.on("/control", handleControl);
  server.on("/status", handleStatus);

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}