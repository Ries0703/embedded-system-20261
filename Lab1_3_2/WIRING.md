# Wiring notes — exercise 3.2

Disconnect USB before changing wires. Use two 5161AS common-cathode displays, eight reused segment resistors (330 ohms intended by the lab circuit), two 10 kohm base resistors, and two P2N2222A NPN transistors. Confirm component values and transistor identity before assembly.

## Display orientation

Display 1: legs D5-D9 and H5-H9, decimal point nearest H5.
Display 2: legs D15-D19 and H15-H19, decimal point nearest H15.

| Row on display 1 / 2 | D side | H side |
|---|---|---|
| 5 / 15 | b | decimal point |
| 6 / 16 | a | c |
| 7 / 17 | common cathode | common cathode |
| 8 / 18 | f | d |
| 9 / 19 | g | e |

Join A7 to J7 and A17 to J17. Each display common is switched to ground by its own transistor, not grounded permanently.

## Digit switches

For the identified P2N2222A, flat marked face toward you and legs down: collector, base, emitter from left to right. Do not assume the same pinout for another 2222 variant.

| Connection | Digit 1 | Digit 2 |
|---|---|---|
| Collector leg | C24 | C30 |
| Base leg | C25 | C31 |
| Emitter leg | C26 | C32 |
| Collector jumper | A24 to B7 | A30 to B17 |
| Base resistor, 10 kohms | B25 to F25 | B31 to F31 |
| Control jumper | PG2 to J25 | PG3 to J31 |
| Ground jumper | A26 to shared GND | A32 to shared GND |

Connect board GND to the same ground rail section. Rail sections separated by a break require a bridge if both are used.

## Segment connections

Each table row means one resistor and three separate jumper wires. Only a, b and c were confirmed tested. The remaining entries are the proposed continuation, not completed wiring evidence.

| Segment | Resistor legs | Board jumper | Display 1 jumper | Display 2 jumper | Status |
|---|---|---|---|---|---|
| a | B35-F35 | PE8 to A35 | G35 to A6 | H35 to A16 | Tested |
| b | B36-F36 | PE9 to A36 | G36 to A5 | H36 to A15 | Tested |
| c | B37-F37 | PE10 to A37 | G37 to J6 | H37 to J16 | Tested |
| d | B38-F38 | PE11 to A38 | G38 to J8 | H38 to J18 | Not confirmed |
| e | B39-F39 | PE12 to A39 | G39 to J9 | H39 to J19 | Planned |
| f | B40-F40 | PE13 to A40 | G40 to A8 | H40 to A18 | Planned |
| g | B41-F41 | PE14 to A41 | G41 to A9 | H41 to A19 | Planned; one g segment faulty |
| dot | B42-F42 | PE15 to A42 | G42 to J5 | H42 to J15 | Planned |

With the board component side facing you and ST-LINK USB at the top, the right header outer PE8/10/12/14 pins are next to their printed labels; PE9/11/13/15 are the adjacent inner pins toward the LCD. PG2 is outer, PG3 is its inner neighbor.

Eight segment resistors were reused from exercise 3.1. The old PD8-PD15 LED signal wires must remain disconnected when their current-limiting resistors have been removed.
