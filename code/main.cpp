#include <Arduino.h>
#include <Wire.h> // enables I2C communication
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h> // AHT21 library

#include "ScioSense_ENS160.h"  // ENS160 library

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// AHT21 = temperature and humidity sensor
#define AHT21_ADDRESS 0x38
Adafruit_AHTX0 aht; 
#define separatorStr "--------------------------------------------------"
// AHT21 variables
float tempC; 
float tempF; 
float humidity;

// ENS160 = digital gas sensor
#define ENS160_ADDRESS 0x53
ScioSense_ENS160 ens160(ENS160_ADDRESS);
// ENS160 variables
int aqi = 0; // air quality index (1 to 5)
int tvoc = 0; // total VOCs (Volatile Organic Compounds) concentation in ppb (0 - 65000 ppb)
int eco2 = 0; // estimated CO2 equivalent (400 to 65000 ppm)

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("\nI2C Air Quality Sensor + OLED Display");

	Serial.println("Initializing I2C SSD1306 OLED...");
    // SDA = GPIO0, SCL = GPIO2
    Wire.begin(0, 2);
	Serial.println("SSD1306 initialized.");
	Serial.println(separatorStr);
	Serial.println();

	Serial.println("ENS160...");
	ens160.begin();
	delay(100);
	Serial.println(ens160.available() ? "ENS160 initialized." : "ENS160 initialization failed.");
	if (ens160.available()) {
		ens160.setMode(ENS160_OPMODE_STD); // begin() leaves the chip in IDLE; switch to Standard mode so it senses
	}
	Serial.println(separatorStr);

	if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
		Serial.println(F("SSD1306 allocation failed"));
		for(;;); // Don't proceed, loop forever
	}

	bool okAht = aht.begin();
	if (!okAht) {
		Serial.println("AHT21 initialization failed.");
	}

	display.dim(true);
	display.setTextWrap(false); // clip at the panel edge instead of wrapping overflow onto a new line

	// clear buffer and show initial graphics
	display.clearDisplay();
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.println(F("Starting AQI sensor...")); // keeps strings in flash instead of dynamic RAM
	display.display();

	// scroll entire display to the right
	display.startscrollleft(0x00, 0x0F);
	delay(1500);
	display.stopscroll();
	display.setTextSize(1);
}

void loop() {
	uint32_t now = millis();
	static uint32_t lastSensor = 0;
	static uint32_t lastScroll = 0;
	static int scrollOffset = 0;

	// --- Sample sensors once per second ---
	if (now - lastSensor >= 1000) {
		lastSensor = now;

		sensors_event_t humidity1, temp;
		aht.getEvent(&humidity1, &temp);
		tempC = temp.temperature;
		tempF = temp.temperature * 9.0f / 5.0f + 32.0f;
		humidity = humidity1.relative_humidity;

		Serial.print("Temperature: ");
		Serial.print(tempC);
		Serial.print(" degrees C; ");
		Serial.print(tempF);
		Serial.println(" degrees F");

		Serial.print("Humidity: ");
		Serial.print(humidity);
		Serial.println("% rH");

		if (ens160.available()) {
			// Non-blocking: read whatever the ENS160 produced in its 1s cycle.
			// (measure(true) would block ~1s each call and stall the scroll.)
			ens160.set_envdata(tempC, humidity);
			ens160.measure(false);
			ens160.measureRaw(false);

			aqi  = ens160.getAQI();
			tvoc = ens160.getTVOC();
			eco2 = ens160.geteCO2();

			Serial.print("AQI: ");
			Serial.println(aqi);
			Serial.print("TVOC: ");
			Serial.print(tvoc);
			Serial.println("ppb");
			Serial.print("eCO2: ");
			Serial.print(eco2);
			Serial.println("ppm");
		}
	}

	// --- Build the two lines of text ---
	// NOTE: ESP8266 printf doesn't support %f, so format the floats first with dtostrf and stitch them into the line with integer %s
	char tmp1[8], tmp2[8], tmp3[8];
	dtostrf(tempC, 4, 1, tmp1);
	dtostrf(tempF, 6, 1, tmp2);
	dtostrf(humidity, 5, 1, tmp3);

	char line1[40];
	char line2[64];
	snprintf_P(line1, sizeof(line1), PSTR("%s C  %s F  %s %%rH"),
	           tmp1, tmp2, tmp3);
	if (ens160.available()) {
		snprintf_P(line2, sizeof(line2),
		           PSTR("AQI:%d | TVOC:%d ppb | eCO2:%d ppm"), aqi, tvoc, eco2);
	} else {
		snprintf_P(line2, sizeof(line2), PSTR("ENS160 not available"));
	}

	// Measure the wider line once and keep that scroll distance fixed so the
	// marquee doesn't jerk around when the digit widths change.
	static uint16_t scrollLimit = 0;
	if (scrollLimit == 0) {
		int16_t x1, y1, x2, y2;
		uint16_t w1 = 0, h1 = 0, w2 = 0, h2 = 0;
		display.getTextBounds(line1, 0, 0, &x1, &y1, &w1, &h1);
		display.getTextBounds(line2, 0, 0, &x2, &y2, &w2, &h2);
		// drawX starts at 128 (off the right edge) and must reach -maxW
		// (off the left edge), so the total travel is SCREEN_WIDTH + maxW,
		// plus a trailing gap for a blank pause before the loop restarts.
		const uint8_t scrollGap = 40;
		scrollLimit = SCREEN_WIDTH + (uint16_t)(w1 > w2 ? w1 : w2) + scrollGap;
	}

	//-----------------------------------------------------------------------------
	// Preventing OLED burn-in cycles
	// - phase 0: normal text
	// - phase 1: inverted text
	// - phase 2: all-black (fixed 7s)
	static uint32_t phaseStart = 0;
	static uint8_t phase = 0;

	// redraw further left every ~100 ms ---
	if (now - lastScroll >= 100) {
		lastScroll = now;
		if (phase == 2) {
			// Rest period
			display.invertDisplay(false);
			display.clearDisplay();
			display.display();
			// Phase 2 is 7s rest
			if (now - phaseStart >= 10000) {
				phase = 0;
				phaseStart = now;
			}
		} else {
			int16_t drawX = 128 - scrollOffset;

			display.clearDisplay();
			display.invertDisplay(phase == 1);
			display.setCursor(drawX, 4);
			display.print(line1);
			display.setCursor(drawX, 20);
			display.print(line2);
			display.display();

			// Advance one step toward the left edge.
			scrollOffset += 5;
			// When the text has finished a full pass across the panel,
			// move on to the next phase and restart the scroll.
			if (scrollOffset >= scrollLimit) {
				scrollOffset = 0;
				phase = (uint8_t)(phase + 1); // 0 -> 1 -> 2
				phaseStart = now;
			}
		}
	}
}
