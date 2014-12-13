#include "MatrixControl.h"
#include "Controllers.h"

LedMatrix* matrix;
PotentioMeter* meter;
/**
 * What are we showing?
 */
String txt = " DFTBA P4A";
/**
 * What is the current thing on the screen?
 */
unsigned char beeldje[8];

/**
 * How fast should the letters go?
 */
unsigned int speed = 300;
/**
 * What column are we sowing?
 */
int counter = 0;
/**
 * When was the last update?
 */
unsigned long lastUpdate = 0;

/**
 * Just one please
 */
void setup() {
	matrix = new LedMatrix(0x70);
	matrix->setBlink(1);
	matrix->setBrightness(2);

	meter = new PotentioMeter(0);
	meter->setValueChangeCallback(potCallback);

	for (int i = 0; i < 8; i++) {
		beeldje[i] = 0x00;
	}
}

/**
 * round, round, round we go
 */
void loop() {
	meter->update();
	unsigned long mils = millis();
	if (mils - lastUpdate > speed) {
		lastUpdate = mils;
		for (int i = 0; i < 8; i++) {
			beeldje[i] = matrix->getCharBock(txt.charAt(counter / 8), i)
					>> (counter % 8);
			beeldje[i] += matrix->getCharBock(txt.charAt(counter / 8 + 1), i)
					<< (8 - counter % 8);
		}
		matrix->drawMatrix(beeldje);
		counter++;
		if (counter >= txt.length()*8)
			counter = 0;
	}
}

/**
 * This function the callback of the potmeter change.
 */
void potCallback(){
	speed = meter->getValuePersentage()*3;
}
