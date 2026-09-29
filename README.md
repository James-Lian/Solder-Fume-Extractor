# 💨 Solder-Fume-Extractor
A small solder fume extractor complete with an air quality sensor for hobbyist soldering applications. Soldering can get pretty fume-y (pun intended), irritating the eyes, nose, and throat. While this extractor won't be as good as a commercial-grade fume hood, the filter will at least mitigate some of solder smoke. 
<br>
<br>
Encompasses a control board with the air quality sensor, a 12V PC fan, activated carbon filter, and custom-designed 3d-printed casing to house everything. 
<br>
<br>
Stardance Project Tracker (Devlogs): [https://stardance.hackclub.com/projects/36238](https://stardance.hackclub.com/projects/36238)

<img width="3090" height="700" alt="image" src="https://github.com/user-attachments/assets/d30a4604-000d-4211-9f7b-7588938a2b77" />

## 💡 Features
- powered by a [12V DC power supply](https://www.amazon.ca/dp/B09W8S3FBV)
- 0.91inch OLED SSD1306
- LM2596-3.3 buck converter for 3V3 supply
- ENS160+AHT21 sensor to detect VOCs and eCO2
- ESP-01S microcontroller
- custom 3d-printed casing
- [12V desk fan](https://www.amazon.ca/dp/B0DPWWMNYM) which pulls solder fumes through an [activated carbon filter](https://www.amazon.ca/dp/B0DVX29MLH?ref=ppx_yo2ov_dt_b_fed_asin_title)
- flip flop switch circuit + MOSFET to control the fan, flyback diode to prevent MOSFET damage

## 📄 PCB & Schematic
<img width="1169" height="678" alt="image" src="https://github.com/user-attachments/assets/75b7060a-66ea-448b-95fd-68cacbc46d01" />
<img width="920" height="851" alt="image" src="https://github.com/user-attachments/assets/ea5f96dc-7a08-41b2-be17-d4a14f8644ec" />
<br>
<br>
Note: additional space is intentionally left empty at the bottom left of the PCB to leave space for the sensor components.

## 🧱 CAD Model
The casing for both the controller board and desk fan were designed in Fusion360. The casing for the controller board covers all the components apart from the air quality sensor, which, of course, needs ample exposure to the air to make an accurate reading. 

## ⚙️ Assembly
1. Download the production files from the production folder and upload them to a manufacturer like JLCPCB
2. Upload the code to the ESP-01S through something like the [CP2102 module](https://www.amazon.ca/dp/B07D6LLX19)
3. After acquiring the PCB, solder all the components to the board. Ensure you leave enough spacing between the PCB and the [right-angle male headers](https://www.amazon.ca/dp/B01461DQ6S?ref=ppx_yo2ov_dt_b_fed_asin_title) for the fan's female connectors to fit.
4. The fan's casing is in three parts. Add heatset inserts to the thickest part, and then sandwich your activated carbon filter between the two grill frames before assembling all three together with 4 M3 screws.
5. The PCB's controller casing comes with an optional screw hole for secure placement. In my experience, it's not needed.  

## ⌨️ Code + Sensors
The code comes with preventative measures to prevent OLED screen burn in, such as by inverting or scrolling the text, and turning off the screen at times. Do note that the ENS160+AHT21 sensor needs to be (unfortunately) powered on for at least 24 hours (ideally 48) to output accurate readings. 

## 📋 BOM
Here's a list of components for the build:
### PCB
| Designator | Footprint | Quantity |
| -------- | -------- | -------- |
| C1 680µF | CP_Radial_D10.0mm_P5.00mm | 1 |
| C2 220µF | CP_Radial_D6.3mm_P2.50mm | 1 |
| C3, C4 0.1µF | 0805 | 2 |
| C5 10nF | 0805 | 1 |
| C6 1µF | 0805 | 1 |
| D1 1N5822 | D_DO-201AD_P15.24mm_Horizontal | 1 |
| D2 1N4001 | D_DO-41_SOD81_P10.16mm_Horizontal | 1 |
| D3, D4 1N4148 | D_DO-35_SOD27_P7.62mm_Horizontal | 2 |
| J1 Barrel_Jack_Switch | XKB_DC-005-5A-2.0 | 1 |
| J2 [Fan](https://www.amazon.ca/dp/B0DPWWMNYM) | [PinHeader_1x03_P2.54mm_Horizontal](https://www.amazon.ca/dp/B01461DQ6S?ref=ppx_yo2ov_dt_b_fed_asin_title) | 1 |
| [Activated Carbon Filter](https://www.amazon.ca/dp/B0DVX29MLH?ref=ppx_yo2ov_dt_b_fed_asin_title) | | 1 |
| [12V DC Power Supply](https://www.amazon.ca/dp/B09W8S3FBV) | | 1 |
| L1 33µH | L_Bourns_SRU5016_5.2x5.2mm | 1 |
| Q1 STP55NF06L | TO-220-3_Vertical | 1 |
| Q2, Q3 PN2222 | TO-92_Inline | 2 |
| R1, R4, R5, R8 10kΩ | R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal | 4 |
| R2, R3 1kΩ | R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal | 2 |
| R6, R7 100kΩ | R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal | 2 |
| SW1 CherryMXSwitch | SW_Cherry_MX_1.00u_PCB | 1 |
| U1 LM2596S-3.3 | TO-263-5_TabPin3 | 1 |
| U2 ESP-01S | PinSocket_2x04_P2.54mm_Vertical | 1 |
| U3 ENS160+AHT21 | PinSocket_1x08_P2.54mm_Vertical | 1 |
| U4 0.91inch SSD1306 OLED | ER_OLEDM0.91_1x-I2C | 1 |

## 🖼️ Final Build Pictures
<img width="608" height="641" alt="image" src="https://github.com/user-attachments/assets/ea28f5a2-ad37-47b5-874e-6ae5f620ee08" />
<img width="604" height="716" alt="image" src="https://github.com/user-attachments/assets/57e251ee-1ac9-41ae-93cc-62ef1b975273" />
<img width="556" height="770" alt="image" src="https://github.com/user-attachments/assets/c1a65fdd-e628-4c5d-8664-708f604c2fc3" />

