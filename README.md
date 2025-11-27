# SnakeHandheld

An implementation of snake designed for the Wemos D1 R2

## Components

- Wemos D1 R2 (Based on ESP8266)
- Expansion Board (?) (TM1638)
- OLED display (SSD1306)
- Buzzer
- Wires

## Connections

### OLED (SSD1306)

| Wemos  | OLED |
|:------:|:----:|
| 3.3v   | VCC  |
| GND    | GND  |
| SCL/D1 | SCL  |
| SDA/D2 | SDA  |

### TM1638

| Wemos | TM1638 |
|:-----:|:------:|
| 3.3v  | VCC    |
| GND   | GND    |
| D3    | DIO    |
| D4    | CLK    |
| D5    | STB    |

### Buzzer

| Wemos | Buzzer |
|:-----:|:------:|
| 3.3v  | +      |
| D6    | -      |

## Case

While some parts were designed to hold the device together, the magority of the structure is ductape.

