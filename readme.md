# ESP32 UART Ring Buffer with OLED Display

## Overview

This project demonstrates the implementation of a UART Ring Buffer (Circular Buffer) on an ESP32 using the Arduino framework. Incoming UART data is stored in a fixed-size circular buffer and then processed by the application. An SSD1306 OLED connected over I2C displays the latest received character along with the current head and tail indices of the ring buffer.

The project is intended to demonstrate common embedded firmware concepts such as UART communication, circular buffers, I2C communication, and basic display interfacing.

---

## Features

* UART data reception using the ESP32 Serial interface
* Circular (Ring) Buffer implementation
* Buffer full and empty detection
* OLED display using SSD1306 over I2C
* Displays:

  * Last received character
  * Head index
  * Tail index
* Serial Monitor debugging output

---

## Hardware Used

* ESP32 DevKit V4
* SSD1306 OLED Display (128 × 64, I2C)

## circuit simulation 
<img width="705" height="553" alt="image" src="https://github.com/user-attachments/assets/ce902672-71fd-433e-af0e-c62b76443a6d" />





---

## Software Used

* Visual Studio Code
* PlatformIO / Arduino Framework
* Wokwi Simulator
* Git & GitHub

---

## Libraries

* Wire
* Adafruit GFX Library
* Adafruit SSD1306

---

## Circuit Connections

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO21    |
| SCL      | GPIO22    |

---

## Project Structure

```text
ESP32_UART_RingBuffer/

├── src/
│   └── main.cpp
├── include/
├── lib/
├── platformio.ini
├── README.md
├── diagram.json
└── wokwi.toml
```

---

## Ring Buffer Working

The project uses a fixed-size circular buffer with two indices:

* **Head** – Points to the next location where incoming data will be stored.
* **Tail** – Points to the next element to be read.

When a character is received through UART:

1. The character is pushed into the ring buffer.
2. The head index advances.
3. The application pops data from the buffer.
4. The tail index advances.
5. The OLED displays the latest received character and buffer status.

---

## Serial Monitor Output

Example:

```text
UART Ring Buffer Ready
Type in Serial Monitor...

UART RX : H
Push : H
POP : H

UART RX : E
Push : E
POP : E

UART RX : L
Push : L
POP : L

UART RX : L
Push : L
POP : L

UART RX : O
Push : O
POP : O
```

---

## OLED Output

```text
UART Ring Buffer

Last RX : O

Head : 5
Tail : 5
```

---

## Concepts Demonstrated

* Embedded C/C++
* UART Communication
* Ring Buffer (Circular Buffer)
* FIFO Data Handling
* I2C Communication
* OLED Display Interface
* ESP32 Firmware Development
* Buffer Management

---

## Future Improvements

* UART Receive Interrupt (ISR)
* FreeRTOS task-based implementation
* Display complete buffer contents on the OLED
* Configurable buffer size
* Overflow and underflow counters
* UART transmit ring buffer
* Multiple UART support

---

## How to Run

1. Open the project in Visual Studio Code with PlatformIO or open it in Wokwi.
2. Build and upload the firmware to the ESP32 (or start the simulation).
3. Open the Serial Monitor at **115200 baud**.
4. Type characters into the Serial Monitor.
5. Observe the Serial Monitor logs and OLED updates.

---

## Author

**Himanshu Pawar**

Electronics and Telecommunication Engineer

Embedded Systems | Firmware Development | ESP32 | STM32 | Embedded C
