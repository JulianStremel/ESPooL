# ESPooL - ESP32 Boost Controller

An open-source boost controller for the ESP32, aimed at makers and car enthusiasts.

> **⚠️ RACE USE ONLY**
> This controller is intended **exclusively for closed-course / race use**.
> It is **not road legal** and must not be used on public roads.
> The software maintainer is **not liable** for any damage, injury, or loss caused by the use of this controller.

---

## Requirements

- [PlatformIO](https://platformio.org/) (CLI or IDE extension)
- ESP32 development board (e.g. ESP32 DevKitC)

## Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/JulianStremel/ESPooL.git
   cd ESPooL
   ```

2. Build and upload with PlatformIO:
   ```bash
   pio run --target upload
   ```

3. Monitor serial output:
   ```bash
   pio device monitor
   ```

## License

See [LICENSE](LICENSE) for details.
