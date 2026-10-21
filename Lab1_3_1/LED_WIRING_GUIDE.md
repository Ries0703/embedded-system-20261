# Section 3.1: eight-LED wiring

Disconnect USB before changing wires. View the board from the component/LCD side, with the ST-LINK USB connector at the top. P2 is the right-hand two-column header.

The printed PD8, PD10, PD12 and PD14 labels identify the outer pins. The adjacent inner pins have different signals; PD9, PD11, PD13 and PD15 are not printed beside them on the front.

| Row identified by printed label | Inner pin (toward LCD) | Outer pin (toward board edge) |
|---|---|---|
| PD8 | PD9: P2 pin 53 | PD8: P2 pin 54 |
| PD10 | PD11: P2 pin 55 | PD10: P2 pin 56 |
| PD12 | PD13: P2 pin 57 | PD12: P2 pin 58 |
| PD14 | PD15: P2 pin 59 | PD14: P2 pin 60 |

Source: ST UM1670 Rev 6, Table 7, printed page 27: https://www.st.com/resource/en/user_manual/um1670-discovery-kit-with-stm32f429zi-mcu-stmicroelectronics.pdf

Each LED uses its own series resistor: GPIO -> resistor -> LED anode (+) -> LED cathode (-) -> GND. Preserve the polarity confirmed by the successful one-LED test.

| GPIO | LED + | LED - | Resistor | GPIO jumper destination |
|---|---|---|---|---|
| PD8 | E5 | E6 | C5-C10 | A10 |
| PD9 | E12 | E13 | C12-C17 | A17 |
| PD10 | E19 | E20 | C19-C24 | A24 |
| PD11 | E26 | E27 | C26-C31 | A31 |
| PD12 | E33 | E34 | C33-C38 | A38 |
| PD13 | E40 | E41 | C40-C45 | A45 |
| PD14 | E47 | E48 | C47-C52 | A52 |
| PD15 | E54 | E55 | C54-C59 | A59 |

Keep board GND connected to A6. Link B6 to A13, B13 to A20, B20 to A27, B27 to A34, B34 to A41, B41 to A48, and B48 to A55.

This layout needs 16 jumper wires total: eight GPIO wires, one board GND wire, and seven ground links. The working one-LED setup already has two, so add 14.
