# ESP32 Bare Metal Programming - Module 1: UART & Architecture

This repository documents the learning journey of building a non-blocking, CLI-driven embedded system on the ESP32 using the Arduino framework but focusing on C/C++ fundamentals.

## Project Structure

The project is evolved through iterative lessons, moving from basic blocking code to asynchronous architectures.

### 📂 src/ (Current Active Project)
- **main.cpp**: The final output of Module 1. A hybrid system that maintains a non-blocking LED blink task while listening for CLI commands.
  - **Feature**: Supports `period <ms>` command to dynamically change blink frequency without pausing execution.
  - **Technique**: Uses parsing (`strncmp`, `atoi`) and pointer arithmetic for command processing.

### 📂 completed_lessons/ (Archives)
These files represent the steps taken to reach the final architecture:

| Filename | Description |
| :--- | :--- |
| **led_blink.cpp** | Introduction to GPIO control using `millis()` for non-blocking delays (replacing `delay()`). |
| **UART_begin.cpp** | Basic Serial communication initialization and "Hello World". |
| **UART_1.cpp** | Implementation of a custom Ring Buffer logic (Head/Tail indices) to understand data flow manually. |
| **UART_ledControl.cpp** | Basic parser to toggle LED using specific string commands ("LED ON"). |
| **UART_ledControl2.cpp** | Advanced CLI parser with terminal emulation features (Echo, Backspace handling, Input Buffer management). |
| **MiniProject_1.cpp** | (Backup) The code for the dynamic period controller. |

## Key Concepts Covered
* **Non-Blocking Architecture:** `millis()` based state machines.
* **UART Polling:** Byte-by-byte data processing without `readString()`.
* **Buffer Management:** Handling overflows, null-termination (`\0`), and memory safety.
* **Parsing:** Using `strcmp`, `strncmp`, and `atoi` with pointer offsets.
* **Terminal UX:** Handling Backspace (`\b`), Carriage Return (`\r`), and Newline (`\n`) for a natural typing experience.

---
*Author: [Your Name/Handle]*
*Target Hardware: ESP32 Dev Module*