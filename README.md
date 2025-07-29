Here’s a complete `README.md` for your WS2812B 4x4 LED Matrix Wi-Fi Controller project:

---

## 🧠 WS2812B 4x4 LED Matrix Controller with ESP8266

**Control 30 vibrant animations over Wi-Fi, hosted on your ESP8266 in AP mode — no internet required!**

---

### ✨ Features

* 🌈 30 dynamic LED animations (rainbow, fire, scanner, glitch, matrix, and more)
* 🎚️ Real-time speed control slider
* 🎨 Live color picker for custom hues
* 🖱️ Button-based instant animation switching (no "Apply" button needed!)
* 💾 EEPROM save/load for animation and speed
* 📡 Self-hosted web interface in AP mode — no router needed
* 📤 \[Planned] Upload custom animations via web UI

---

### ⚙️ Hardware Required

| Component          | Quantity     |
| ------------------ | ------------ |
| ESP8266 (NodeMCU)  | 1            |
| WS2812B 4x4 Matrix | 1            |
| Power Supply (5V)  | 1            |
| Resistor (330Ω)    | 1            |
| Capacitor (1000μF) | 1 (optional) |

📌 **Wiring Guide**

* `WS2812B DIN` → `GPIO13 (D7)`
* `5V` → Matrix VCC
* `GND` → Matrix GND and ESP8266 GND

---

### 🧰 Libraries Used

* [`FastLED`](https://github.com/FastLED/FastLED)
* [`ESPAsyncWebServer`](https://github.com/me-no-dev/ESPAsyncWebServer)
* [`ESPAsyncTCP`](https://github.com/me-no-dev/ESPAsyncTCP)
* `EEPROM` (standard)

Add these in `platformio.ini`:

```ini
lib_deps =
  ESPAsyncTCP
  ESPAsyncWebServer
  FastLED
  EEPROM
```

---

### 🚀 Getting Started (with PlatformIO)

1. Install [VS Code](https://code.visualstudio.com/) and [PlatformIO](https://platformio.org/)
2. Clone this repo:

   ```bash
   git clone (https://github.com/afshadka/-WS2812B-4x4-LED-Matrix-Controller-with-ESP82666/)
   ```
3. Open the folder in VS Code
4. Connect your NodeMCU
5. Modify `DATA_PIN`, `NUM_LEDS`, `SSID`, `PASSWORD` in `main.cpp` as needed
6. Upload the code:

   ```bash
   pio run --target upload
   ```

---

### 🌐 Access Web Interface

1. After boot, ESP8266 creates a Wi-Fi hotspot (e.g., `LED-Controller`)
2. Connect to it using your phone/laptop
3. Navigate to `192.168.4.1` in your browser
4. Control LEDs in real time!

---

### 🧪 Available Animations (30)

* Rainbow
* Color Wipe
* Scanner
* Twinkle
* Theater Chase
* Confetti
* Sinelon
* BPM
* Juggle
* Rainbow w/ Glitter
* Pulse
* Flash
* Waves
* Bouncing Balls
* Noise Field
* Matrix
* Snake
* Sparkles
* Lava
* TwinkleFox
* Fire
* Fireflies
* Ripple
* Plasma
* Blendwave
* Glitch
* Explosion
* Meteor Rain
* Lightning
* Aurora Rings

---

### 💾 EEPROM Saved Settings

* Last selected animation
* Speed value
* Preferred color

Settings are reloaded on boot!

---

### 🧱 Folder Structure

```
.
├── src/
│   └── main.cpp         ← Main code file
├── data/
│   └── index.html       ← Web interface (optional if embedded as string)
├── platformio.ini
├── README.md
```

---

### 🛠️ Troubleshooting

* ❗ **Upload Fails**: Set `upload_speed = 57600` in `platformio.ini` if 115200 fails
* ❗ **Serial Port Errors**: Close all serial monitors before upload
* ❗ **Not Connecting to Hotspot**: Try another USB cable or reboot the board

---

### 📦 To-Do / Future

* [x] Add 30 animations
* [x] Dynamic web UI
* [x] Save speed and pattern
* [ ] Add custom animation upload via browser
* [ ] OTA firmware updates
* [ ] Audio-reactive or mic-driven modes

---

### 📜 License

MIT © 2025 \Layrd.tech

---


