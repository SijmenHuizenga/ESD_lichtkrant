#include <Wire.h>
#include "Arduino.h"
#include "MatrixControl.h"
#include "font_8x8.h"

LedMatrix::LedMatrix(int adress) {
	this->adres = adress;
	Wire.begin();

	Wire.beginTransmission(this->adres);
	Wire.write(0x21);
	Wire.endTransmission();
}

/**
 * brightness between 0 and 15
 */
void LedMatrix::setBrightness(int brightness) {
	Wire.beginTransmission(this->adres);
	Wire.write(B11100000 + brightness);
	Wire.endTransmission();
}

/**
 * amount between 1 and 7
 */
void LedMatrix::setBlink(int amount) {
	Wire.beginTransmission(this->adres);
	Wire.write(B00100000 + amount);
	Wire.endTransmission();
}

/**
 * every one loves a smiley. So this function shows this smyle
 * to the display.
 */
void LedMatrix::drawSmiley() {
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);

	Wire.write(rightCycleShift(B00111100));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B01111110));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B11011011));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B11111111));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B10111101));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B11000011));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B01111110));
	Wire.write(0x00);
	Wire.write(rightCycleShift(B00111100));
	Wire.write(0x00);
	Wire.endTransmission();
}

/**
 * Draw a letter to the matrix.
 */
void LedMatrix::drawLetter(char asciiCode) {
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);
	for (int i = 0; i < 8; i++) {
		Wire.write(font8x8_basic[(int) asciiCode][i]);
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

/**
 * Draw the matrix with stuff.
 */
void LedMatrix::drawMatrix(byte bits[]) {
	Wire.beginTransmission(this->adres);
	Wire.write(0x00);
	for (int i = 0; i < 8; i++) {
		Wire.write(rightCycleShift(bits[i]));
		Wire.write(0x00);
	}
	Wire.endTransmission();
}

/**
 * get a unsigned char representing a row of a letter.
 */
unsigned char LedMatrix::getCharBock(int ascii, int row){
	return font8x8_basic[ascii][row];
}

/**
 * do a right cycle shift
 */
byte LedMatrix::rightCycleShift(byte in) {
	return (in >> 1 | in << 7);
}

/**
 * do a left cycle shift
 */
byte LedMatrix::leftCycleShift(byte in) {
	return (in << 1 | in >> 7);
}



