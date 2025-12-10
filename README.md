# Tesla Charge Port Opener - ESP32

Open your Tesla charge port remotely using an ESP32 and a 433 MHz transmitter.

## Overview

This project allows you to wirelessly open your Tesla's charge port using an ESP32 microcontroller and a 433 MHz RF transmitter. The code sends the appropriate RF signals that Tesla charge ports recognize, making it convenient to open the port without using the car's touchscreen or mobile app.

## Hardware Requirements

- **ESP32 Development Board** (any variant)
- **433 MHz RF Transmitter Module** (e.g., FS1000A or similar)
- **Jumper Wires**
- **Power Supply** (USB or battery for portable use)

## Wiring

Connect the 433 MHz transmitter to your ESP32:

- **VCC** → 3.3V or 5V (depending on your transmitter module)
- **GND** → GND
- **DATA** → GPIO 5 (default, configurable in code)

## Installation

1. Clone this repository:
   ```bash
   git clone git@github.com:random-robbie/tesla-open-charger-port-says-me.git
   cd tesla-open-charger-port-says-me
   ```

2. Open `esp32_tesla_sender.ino` in Arduino IDE

3. Install the ESP32 board support:
   - In Arduino IDE, go to **File → Preferences**
   - Add to Additional Board Manager URLs: `https://dl.espressif.com/dl/package_esp32_index.json`
   - Go to **Tools → Board → Board Manager**
   - Search for "ESP32" and install

4. Select your ESP32 board:
   - **Tools → Board → ESP32 Arduino → Your ESP32 Board**
   - **Tools → Port → Select your COM port**

5. Upload the sketch to your ESP32

## Configuration

You can modify the following parameters in `esp32_tesla_sender.ino`:

```cpp
const int TX_PIN = 5;                         // Transmitter data pin
const int REPEATS_PER_SIGNAL = 2;             // How many times to send each signal
const unsigned long GAP_BETWEEN_REPEATS_MS = 500;
const unsigned long GAP_BETWEEN_SIGNALS_MS = 1500;
```

## Included Signals

The code includes three different signal variants optimized for different regions:

- **433.92MHz AM650** - Best for most US Teslas
- **433.92MHz AM270** - Alternative US signal
- **433 Long AM650** - Optimized for EU/AUS Teslas

## Usage

1. Power on your ESP32
2. The device will automatically start transmitting all three signal variants
3. Monitor the Serial output at 115200 baud to see transmission status
4. Your Tesla charge port should open when in range (typically 10-30 feet depending on transmitter power)

## How It Works

The ESP32 sends precisely-timed RF pulses at 433 MHz that mimic the signal from Tesla's key fob or mobile charger button. The `signal_arrays.h` file contains the exact timing sequences captured from legitimate Tesla charge port openers.

## Legal & Safety

- **Only use this on your own Tesla vehicle**
- This project is for educational and personal convenience purposes
- Ensure you comply with local RF transmission regulations
- Do not use this to interfere with vehicles you don't own

## Troubleshooting

**Charge port doesn't open:**
- Check your wiring connections
- Verify the transmitter is getting power
- Try moving closer to your Tesla
- Ensure antenna is properly connected to the transmitter
- Some transmitters may need 5V instead of 3.3V for better range

**Serial monitor shows nothing:**
- Check your baud rate is set to 115200
- Verify USB connection
- Try pressing the reset button on ESP32

## Credits

Signal data captured and optimized for Tesla charge port opening.

## License

This project is provided as-is for personal use. Use responsibly and at your own risk.

## Contributing

Feel free to submit issues or pull requests if you have improvements or additional signal variants that work better for your region/Tesla model.
