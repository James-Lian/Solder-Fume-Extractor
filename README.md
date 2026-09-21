# 💨 Solder-Fume-Extractor
A small hobbyist solder fume extractor complete with an air quality sensor for soldering applications. Encompasses a control board with the air quality sensor, a 12V PC fan, activated carbon filter, and custom-designed 3d-printed casing to house everything. 
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
- flip flop switch circuit to control the fan

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

## ⌨️ Code + Sensors
The code comes with preventative measures to prevent OLED screen burn in, such as by inverting or scrolling the text, and turning off the screen at times. Do note that the ENS160+AHT21 sensor needs to be (unfortunately) powered on for at least 24 hours (ideally 48) to output accurate readings. 

## 🖼️ Final Build Pictures
<img width="608" height="641" alt="image" src="https://github.com/user-attachments/assets/ea28f5a2-ad37-47b5-874e-6ae5f620ee08" />
<img width="604" height="716" alt="image" src="https://github.com/user-attachments/assets/57e251ee-1ac9-41ae-93cc-62ef1b975273" />
<img width="556" height="770" alt="image" src="https://github.com/user-attachments/assets/c1a65fdd-e628-4c5d-8664-708f604c2fc3" />

