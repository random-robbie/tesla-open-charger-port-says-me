#include <Arduino.h>
#include "signal_arrays.h"

// Configurable pins and timing
const int TX_PIN = 5;                         // Set to your 433 MHz transmitter data pin
const int REPEATS_PER_SIGNAL = 2;             // How many times to send each waveform
const unsigned long GAP_BETWEEN_REPEATS_MS = 500;
const unsigned long GAP_BETWEEN_SIGNALS_MS = 1500;

struct SignalDef {
  const char *name;
  const int16_t *data;
  size_t length;
};

// Add any additional signals here if you generate more arrays
SignalDef signals[] = {
  {"433.92MHz AM650 (Better)", signal_433_92MHz_AM650_Better_Tesla_Charge_Port_Opener, signal_433_92MHz_AM650_Better_Tesla_Charge_Port_OpenerLength},
  {"433.92MHz AM270 (Better)", signal_433_92MHz_AM270_Better_Tesla_Charge_Port_Opener, signal_433_92MHz_AM270_Better_Tesla_Charge_Port_OpenerLength},
  {"433 Long AM650 (EU/AUS)", signal_433_Tesla_Long_AM650_EU_AUS, signal_433_Tesla_Long_AM650_EU_AUSLength},
};

void sendRaw(const int16_t *timings, size_t length) {
  // The timings are +/- microseconds: positive = HIGH, negative = LOW.
  for (size_t i = 0; i < length; ++i) {
    int32_t duration = timings[i];
    bool level = duration > 0;
    if (duration < 0) {
      duration = -duration;
    }

    digitalWrite(TX_PIN, level ? HIGH : LOW);
    delayMicroseconds(duration);
  }

  digitalWrite(TX_PIN, LOW);  // Leave the line idle low between bursts
}

void setup() {
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, LOW);

  Serial.begin(115200);
  while (!Serial && millis() < 2000) {
    delay(10);
  }

  Serial.println();
  Serial.println("ESP32 Tesla charge-port sender");
  Serial.printf("Signals loaded: %u\n", (unsigned)(sizeof(signals) / sizeof(signals[0])));
  Serial.printf("Repeats per signal: %d\n", REPEATS_PER_SIGNAL);
}

void loop() {
  for (size_t i = 0; i < sizeof(signals) / sizeof(signals[0]); ++i) {
    const auto &sig = signals[i];
    for (int r = 1; r <= REPEATS_PER_SIGNAL; ++r) {
      Serial.printf("Sending %s (%u pulses) repeat %d/%d...\n",
                    sig.name, (unsigned)sig.length, r, REPEATS_PER_SIGNAL);
      sendRaw(sig.data, sig.length);
      delay(GAP_BETWEEN_REPEATS_MS);
    }
    Serial.println("Done with signal\n");
    delay(GAP_BETWEEN_SIGNALS_MS);
  }
}
