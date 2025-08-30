

# IoT Dual-Mode Relay Control 🌐🔌

An **ESP-12F (ESP8266)** based home automation project with **dual control modes**:  
- **MQTT (HiveMQ broker / IoT apps)**  
- **HTTP (local web server access)**  

---

## 🔧 Features
- Control appliances remotely via MQTT broker
- Local control via HTTP server hosted on ESP12F
- Uses **GPIO D5** to drive relay
- Real-time Wi-Fi connectivity

---

## 🛠️ Hardware & Tools
- **Module:** ESP-12F (ESP8266)
- **Relay:** 5V Single-channel relay
- **IDE:** Arduino IDE
- **Libraries:** `ESP8266WiFi.h`, `PubSubClient.h`

---

## 🚀 How to Run
1. Install Arduino IDE and ESP8266 board support
2. Clone this repo  
   ```bash
   git clone https://github.com/prathameshsalunkhe/IoT-Relay.git
