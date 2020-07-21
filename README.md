<div id="readme" class="Box-body readme blob js-code-block-container">
  <article class="markdown-body entry-content p-3 p-md-6" itemprop="text"><p><a href="https://www.microchip.com" rel="nofollow"><img src="https://camo.githubusercontent.com/5fb5505f69a28ff407841612dfe2b7004f210594/68747470733a2f2f636c6475702e636f6d2f553071684c7742696a462e706e67" alt="MCHP" data-canonical-src="https://cldup.com/U0qhLwBijF.png" style="max-width:100%;"></a></p>


# Introduction
The PIC16F184xx family has a new Analog to Digital Converter with Computation (ADCC) with a 12-bit resolution. This project shows how the PIC can internally measure its Vdd using the ADCC and FVR.

# Description
In this example we will be using the PIC16F18446 Sensor Board. Battery (Vdd) level measurement is performed while the display is turned on. The percentage level of the remaining charge in the batteries is shown as a battery icon with proportional filing in the top-right corner of the display. Additionally, the battery voltage in Volts and percentage graph are displayed.

![Battery Measurement](image/display.png)

To get the Vdd voltage, ADCC is used to measure the FVR (which is configured to 1.024V) with Vdd as positive reference. Then the Vdd is calculated using this formula: Vdd = 1.024V * 4096 / ADC_Reading.

# MCC Settings

Here are the settings used for MSSP, CLC, FVR, and ADCC. MSSP + CLC are used for the LCD control.
### MSSP Settings
![MSSP Settings](image/MSSP1.png)

### CCL Settings
![CCL1 Settings](image/CLC1.png)

![CCL2 Settings](image/CLC2.png)

### FVR Settings
![FVR Settings](image/FVR.png)

### ADCC settings
![ADCC Settings](image/ADCC1.png)
ADRPT register is set to 0x40, to average a burst of 64 samples.
![ADCC Registers](image/ADCC2.png)

### PIN Grid
![PIN Grid](image/PIN_Grid.png)

### PIN Module
![PIN Module](image/PIN_Module.png)
