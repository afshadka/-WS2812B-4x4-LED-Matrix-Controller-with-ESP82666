// ESP8266 WS2812B LED Controller with EEPROM, Custom Upload, and Color Picker
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>
#include <FastLED.h>

#define LED_PIN     13
#define NUM_LEDS    16
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

#ifndef EEPROM_SIZE
#define EEPROM_SIZE 10
#endif


const char *ssid = "LED_Controller";
const char *password = "";

AsyncWebServer server(80);
int currentPattern = 0;
int animationSpeed = 50;
CRGB userColor = CRGB::Red;
// Animation function declarations
void rainbow();
void colorWipe();
void scanner();
void twinkle();
void theaterChase();
void confetti();
void sinelon();
void bpm();
void juggle();
void rainbowWithGlitter();
void pulse();
void flash();
void waves();
void bouncingBalls();
void noise();
void matrix();
void snake();
void sparkles();
void lava();
void twinkleFox();
void fire();
void fireFly();
void ripple();
void plasma();
void blendwave();
void glitch();
void explode();
void meteorRain();
void lightning();
void animationPlaceholder(); // use this for any unimplemented ones


void saveSettings() {
  EEPROM.write(0, currentPattern);
  EEPROM.write(1, animationSpeed);
  EEPROM.write(2, userColor.r);
  EEPROM.write(3, userColor.g);
  EEPROM.write(4, userColor.b);
  EEPROM.commit();
}

void loadSettings() {
  currentPattern = EEPROM.read(0);
  animationSpeed = EEPROM.read(1);
  userColor.r = EEPROM.read(2);
  userColor.g = EEPROM.read(3);
  userColor.b = EEPROM.read(4);
}

void setup() {
  EEPROM.begin(EEPROM_SIZE);
  loadSettings();

  delay(1000);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  WiFi.softAP(ssid, password);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = R"rawliteral(
    <!DOCTYPE html><html><head><title>LED Controller</title>
    <style>
    body { font-family: sans-serif; background: #111; color: #fff; text-align: center; padding: 10px; }
    button { margin: 5px; padding: 10px 20px; font-size: 1rem; border: none; border-radius: 10px; background: #444; color: white; }
    button.active { background: #09f; color: #000; font-weight: bold; }
    .grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(100px, 1fr)); gap: 10px; }
    input[type=range] { width: 80%; }
    </style></head><body>
    <h2>LED Matrix Controller</h2>
    <div class="grid">
    )rawliteral";
    for (int i = 0; i < 30; i++) {
      html += "<button onclick=\"selectPattern(" + String(i) + ")\" id=\"btn" + String(i) + "\">Anim " + String(i) + "</button>";
    }
    html += R"rawliteral(
    </div><br>
    <label>Speed</label><br><input type="range" min="1" max="200" value=")rawliteral" + String(animationSpeed) + R"rawliteral(" onchange="setSpeed(this.value)"><br><br>
    <label>Color</label><br><input type="color" onchange="setColor(this.value)"><br><br>
    <script>
      function selectPattern(p) {
        fetch(`/set?pattern=${p}`);
        document.querySelectorAll('button').forEach(b => b.classList.remove('active'));
        document.getElementById(`btn${p}`).classList.add('active');
      }
      function setSpeed(v) { fetch(`/speed?value=${v}`); }
      function setColor(val) {
        const r = parseInt(val.substr(1,2),16);
        const g = parseInt(val.substr(3,2),16);
        const b = parseInt(val.substr(5,2),16);
        fetch(`/color?r=${r}&g=${g}&b=${b}`);
      }
    </script>
    </body></html>
    )rawliteral";
    request->send(200, "text/html", html);
  });

  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("pattern")) {
      currentPattern = request->getParam("pattern")->value().toInt();
      saveSettings();
    }
    request->send(200, "text/plain", "OK");
  });

  server.on("/speed", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("value")) {
      animationSpeed = request->getParam("value")->value().toInt();
      saveSettings();
    }
    request->send(200, "text/plain", "Speed set");
  });

  server.on("/color", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("r") && request->hasParam("g") && request->hasParam("b")) {
      userColor.r = request->getParam("r")->value().toInt();
      userColor.g = request->getParam("g")->value().toInt();
      userColor.b = request->getParam("b")->value().toInt();
      saveSettings();
    }
    request->send(200, "text/plain", "Color set");
  });

  server.begin();
}

void loop() {
  switch(currentPattern) {
    case 0: rainbow(); break;
    case 1: colorWipe(); break;
    case 2: scanner(); break;
    case 3: twinkle(); break;
    case 4: theaterChase(); break;
    case 5: confetti(); break;
    case 6: sinelon(); break;
    case 7: bpm(); break;
    case 8: juggle(); break;
    case 9: rainbowWithGlitter(); break;
    case 10: pulse(); break;
    case 11: flash(); break;
    case 12: waves(); break;
    case 13: bouncingBalls(); break;
    case 14: noise(); break;
    case 15: matrix(); break;
    case 16: snake(); break;
    case 17: sparkles(); break;
    case 18: lava(); break;
    case 19: twinkleFox(); break;
    case 20: fire(); break;
    case 21: fireFly(); break;
    case 22: ripple(); break;
    case 23: plasma(); break;
    case 24: blendwave(); break;
    case 25: glitch(); break;
    case 26: explode(); break;
    case 27: meteorRain(); break;
    case 28: lightning(); break;
    case 29: rainbow(); break;
    default: rainbow(); break;
  }
  FastLED.show();
  delay(animationSpeed);
}

// Animation implementations
void rainbow() { static uint8_t hue = 0; fill_rainbow(leds, NUM_LEDS, hue++, 7); }
void colorWipe() { static int pos = 0; fill_solid(leds, NUM_LEDS, CRGB::Black); leds[pos++] = userColor; if (pos >= NUM_LEDS) pos = 0; }
void scanner() { static int pos = 0; static int dir = 1; fill_solid(leds, NUM_LEDS, CRGB::Black); leds[pos] = userColor; pos += dir; if (pos <= 0 || pos >= NUM_LEDS - 1) dir *= -1; }
void twinkle() { for (int i = 0; i < NUM_LEDS; i++) { leds[i] = random8() < 10 ? userColor : CRGB::Black; } }
void theaterChase() { static int offset = 0; fill_solid(leds, NUM_LEDS, CRGB::Black); for (int i = offset; i < NUM_LEDS; i += 3) leds[i] = userColor; offset = (offset + 1) % 3; }
void confetti() { fadeToBlackBy(leds, NUM_LEDS, 10); int pos = random16(NUM_LEDS); leds[pos] += userColor; }
void sinelon() { fadeToBlackBy(leds, NUM_LEDS, 20); int pos = beatsin16(13, 0, NUM_LEDS - 1); leds[pos] += userColor; }
void bpm() { uint8_t BeatsPerMinute = 62; CRGBPalette16 palette = PartyColors_p; uint8_t beat = beatsin8(BeatsPerMinute, 64, 255); for (int i = 0; i < NUM_LEDS; i++) { leds[i] = ColorFromPalette(palette, i * 2 + beat, 255); } }
void juggle() { fadeToBlackBy(leds, NUM_LEDS, 20); byte dothue = 0; for (int i = 0; i < 3; i++, dothue += 64) { leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255); } }
void rainbowWithGlitter() { rainbow(); if (random8() < 80) leds[random16(NUM_LEDS)] += CRGB::White; }
void pulse() { static uint8_t brightness = 0; static int8_t direction = 5; brightness += direction; if (brightness <= 0 || brightness >= 255) direction = -direction; fill_solid(leds, NUM_LEDS, userColor.nscale8(brightness)); }
void flash() { static bool on = false; fill_solid(leds, NUM_LEDS, on ? userColor : CRGB::Black); on = !on; }
void waves() { for (int i = 0; i < NUM_LEDS; i++) { leds[i] = CHSV(sin8(i * 10 + millis() / 5), 255, 255); } }
void bouncingBalls() { static int pos = 0; static int dir = 1; fill_solid(leds, NUM_LEDS, CRGB::Black); leds[pos] = userColor; pos += dir; if (pos <= 0 || pos >= NUM_LEDS - 1) dir = -dir; }
void noise() { for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(random8(), 255, 255); }
void matrix() { for (int i = 0; i < NUM_LEDS; i++) leds[i] = (random8() > 128) ? CRGB::Green : CRGB::Black; }
void snake() { static int head = 0; static int len = 4; fill_solid(leds, NUM_LEDS, CRGB::Black); for (int i = 0; i < len; i++) leds[(head - i + NUM_LEDS) % NUM_LEDS] = userColor; head = (head + 1) % NUM_LEDS; }
void sparkles() { fill_solid(leds, NUM_LEDS, CRGB::Black); for (int i = 0; i < NUM_LEDS / 4; i++) leds[random16(NUM_LEDS)] = userColor; }
void lava() { for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(i * 3 + millis() / 10, 255, 255); }
void twinkleFox() { fadeToBlackBy(leds, NUM_LEDS, 30); if (random8() < 128) leds[random16(NUM_LEDS)] = userColor; }
void fire() { for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(0, 255, random8(100, 255)); }
void fireFly() { static int pos = 0; fadeToBlackBy(leds, NUM_LEDS, 20); leds[random16(NUM_LEDS)] = userColor; }
void ripple() { static int center = NUM_LEDS / 2; static int step = 0; for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Black; leds[(center + step) % NUM_LEDS] = userColor; leds[(center - step + NUM_LEDS) % NUM_LEDS] = userColor; step = (step + 1) % (NUM_LEDS / 2); }
void plasma() { for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV((sin8(i * 8 + millis() / 4)), 255, 255); }
void blendwave() { for (int i = 0; i < NUM_LEDS; i++) leds[i] = blend(CRGB::Red, CRGB::Blue, sin8(i * 10 + millis() / 3)); }
void glitch() { for (int i = 0; i < NUM_LEDS; i++) leds[i] = random8() < 128 ? userColor : CRGB::Black; }
void explode() { static int center = NUM_LEDS / 2; static int radius = 0; fill_solid(leds, NUM_LEDS, CRGB::Black); if (center - radius >= 0) leds[center - radius] = userColor; if (center + radius < NUM_LEDS) leds[center + radius] = userColor; radius++; if (center - radius < 0 && center + radius >= NUM_LEDS) radius = 0; }
void meteorRain() { fadeToBlackBy(leds, NUM_LEDS, 64); int pos = random16(NUM_LEDS); leds[pos] = userColor; }
void lightning() { static bool flash = false; flash = !flash; fill_solid(leds, NUM_LEDS, flash ? CRGB::White : CRGB::Black); }
