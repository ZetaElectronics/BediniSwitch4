const uint8_t pA1 = 6, pA2 = 7;   // pair A → pins 6, 7
const uint8_t pB1 = 5, pB2 = 4;   // pair B → pins 5, 4

const uint16_t T_ON_US = 500;   // 500 µs = 0.5 ms

// ---- NEW: 3 LEDs for the 5-second sequencer ----
const uint8_t led1 = 8;
const uint8_t led2 = 9;
const uint8_t led3 = 10;
const uint32_t LED_STEP_MS = 5000;   // 5 seconds per LED

uint8_t  currentLed = 0;              // 0,1,2 → which LED is active
uint32_t lastLedChange = 0;           // timestamp of last switch

void setup() {
  pinMode(pA1, OUTPUT); pinMode(pA2, OUTPUT);
  pinMode(pB1, OUTPUT); pinMode(pB2, OUTPUT);

  // start safe: everything off
  digitalWrite(pA1, LOW); digitalWrite(pA2, LOW);
  digitalWrite(pB1, LOW); digitalWrite(pB2, LOW);

  // ---- NEW: LED setup ----
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void loop() {
  // ===== YOUR ORIGINAL OSCILLATOR CODE (unchanged) =====
  // Phase A: pins 6 & 7 HIGH, 5 & 4 LOW
  digitalWrite(pA1, HIGH); digitalWrite(pA2, HIGH);
  digitalWrite(pB1, LOW);  digitalWrite(pB2, LOW);
  delayMicroseconds(T_ON_US);

  // Phase B: pins 5 & 4 HIGH, 6 & 7 LOW
  digitalWrite(pA1, LOW);  digitalWrite(pA2, LOW);
  digitalWrite(pB1, HIGH); digitalWrite(pB2, HIGH);
  delayMicroseconds(T_ON_US);
  // =====================================================

  // ---- NEW: 5-second LED sequencer (non-blocking) ----
  uint32_t now = millis();
  if (now - lastLedChange >= LED_STEP_MS) {
    lastLedChange = now;

    // turn all off
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    // turn on the current one
    if (currentLed == 0)      digitalWrite(led1, HIGH);
    else if (currentLed == 1) digitalWrite(led2, HIGH);
    else                      digitalWrite(led3, HIGH);

    // advance to next LED (wraps 0→1→2→0…)
    currentLed = (currentLed + 1) % 3;
  }
}