# 🌐 ESP8266 Embedded Web Server Implementation

## 📌 Overview
This project includes an embedded HTTP web server implemented on the ESP8266 (NodeMCU). The server enables real-time device control and monitoring through a web browser without requiring external hosting.

## ⚙️ How It Works

1. The ESP8266 connects to a WiFi network.
2. It starts an HTTP server on port 80.
3. The server listens for incoming client requests.
4. Based on the requested URL, it performs actions and sends responses.

## 🔗 API Endpoints

### 1. Root Endpoint (`/`)
- Serves the main HTML dashboard page
- Displays device status and sensor values
- Includes UI controls and live updates

### 2. Control Endpoint (`/control`)
- Used to control device state (ON/OFF)
- Example:
/control?state=on
/control?state=off
- Updates internal device state

### 3. Status Endpoint (`/status`)
- Returns real-time data in JSON format
- Example response:
```json
{
  "device": "ON",
  "sensor": 45,
  "uptime": 120
  }
  ```

## 🔄 Data Flow

Browser (Client)
      ↓
HTTP Request
      ↓
ESP8266 Web Server
      ↓
Process Request (Control / Data)
      ↓
Send Response (HTML / JSON)

## 🧠 Key Concepts Demonstrated

- Embedded HTTP Server implementation
- REST API design in embedded systems
- JSON data communication
- Real-time client-server interaction
- WiFi-based device control

## ⚡ Why This Matters

This implementation shows how a microcontroller can act as a standalone web server, eliminating the need for external backend systems. It demonstrates core embedded networking skills required in IoT and firmware development.

## 🚀 Future Enhancements

- Add MQTT protocol for cloud communication
- Secure endpoints with authentication
- Integrate real hardware sensors
- Enable OTA firmware updates

## 👨‍💻 Author
Vignesh  
Embedded Systems & IoT Engineer
