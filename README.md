[![MCHP](images/microchip.png)](https://www.microchip.com)


# PIC16F18446 Sensor Board Battery Measurement

The PIC16F184xx family has a new Analog to Digital Converter with Computation (ADCC) with a 12-bit resolution. This project shows how the PIC can internally measure its Vdd using the ADCC and FVR.

In this example we will be using the PIC16F18446 Sensor Board. Battery (Vdd) level measurement is performed while the display is turned on. The percentage level of the remaining charge in the batteries is shown as a battery icon with proportional filing in the top-right corner of the display. Additionally, the battery voltage in Volts and percentage graph are displayed.

## Related Documentation
- [PIC16F18446 Product Family Page](https://www.microchip.com/design-centers/8-bit/pic-mcus/device-selection/pic16f18446)
- [PIC16F18446 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40001985B.pdf) for more information or specifications.


## Software Used
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or a newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- MPLAB® Code Configurator (MCC) 3.95.0 or newer [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- MPLAB® Code Configurator (MCC) Device Libraries 8-bit AVR MCUs 2.3.0 or newer [(microchip.com/mplab/mplab-code-configurator)](https://www.microchip.com/mplab/mplab-code-configurator)
- PIC16F1xxxx DFP 1.2.99 or newer Device Pack

## Hardware Used
- [PIC16F18446 Sensor Board Demonstration](https://www.microchip.com/promo/pic16f18446-sensor-board-demonstration)


## Setup

To get the Vdd voltage, ADCC is used to measure the FVR (which is configured to 1.024V) with Vdd as positive reference. Then the Vdd is calculated using this formula: Vdd = 1.024V * 4096 / ADC_Reading.

### MCC Settings

Here are the settings used for MSSP, CLC, FVR, and ADCC. MSSP + CLC are used for the LCD control.
### MSSP Settings
<br><img src="images/MSSP1.png" width="600">

### CCL Settings
<br><img src="images/CLC1.png" width="600">

<br><img src="images/CLC2.png" width="600">

### FVR Settings
<br><img src="images/FVR.png" width="600">

### ADCC settings
<br><img src="images/ADCC1.png" width="600">
ADRPT register is set to 0x40, to average a burst of 64 samples.
<br><img src="images/ADCC2.png" width="600">

### PIN Grid
<br><img src="images/PIN_Grid.png" width="600">

### PIN Module
<br><img src="images/PIN_Module.png" width="600">

## Demo
<br><img src="images/display.png" width="600">
