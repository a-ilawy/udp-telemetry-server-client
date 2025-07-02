# 🌐 UDP IoT Telemetry System

A lightweight, real-time telemetry system for IoT devices using **UDP**:

- 📡 **C++ Client** – Sends JSON-formatted telemetry data (e.g., temperature, humidity).
- 🛠️ **Node.js Server** – Receives, parses, and logs telemetry messages over UDP.

---

## 📦 Project Structure
```
udp-telemetry-server-client/
├── client.cpp                  # C++ UDP client (IoT device simulator)
├── server.js                   # Node.js UDP server
└── README.md                   # Project documentation
```
### 🛰️ Sample Telemetry Packet

```
{
  "device_id": "sensor_01",
  "timestamp": 1727854237,
  "temperature": 23.5,
  "humidity": 45.2
}
```
### ▶️ [Demo video](https://youtu.be/ckj3uGowqQ4)
