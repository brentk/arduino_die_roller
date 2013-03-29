int buttonPin = 9;

//8-bit Shift Register Pins:
int dataPin   = 4;
int latchPin  = 5;
int clockPin  = 6;

byte leds = 0;

//Possible die configurations:
int dieConfigurations[6][6] = {
	{ 6, -1, -1, -1, -1, -1 },
	{ 0,  5, -1, -1, -1, -1 },
	{ 0,  5,  6, -1, -1, -1 },
	{ 0,  2,  3,  5, -1, -1 },
	{ 0,  2,  3,  5,  6, -1 },
	{ 0,  1,  2,  3,  4,  5 }
};

int state       = 0; //rolling or done.
int rolls       = 5; //random changes before landing on final result.
int currentRoll = 0; //track current roll count.

void setup() {
	pinMode( dataPin,   OUTPUT );
	pinMode( latchPin,  OUTPUT );
	pinMode( clockPin,  OUTPUT );
	pinMode( buttonPin, INPUT_PULLUP);  
}

void loop() {

	//If button is pushed, set state to "rolling"
	if ( digitalRead( buttonPin ) == LOW ) {
		state       = 1;
		currentRoll = 0;
		rollEm();

	} else {
		//Button is released, start roll process
		if( state == 1 ) {
			while( currentRoll <= rolls ) {
				rollEm();
				currentRoll++;
			}
		}
	state = 0;
	}
}

void lightUp() {

	digitalWrite( latchPin, LOW );
	shiftOut( dataPin, clockPin, MSBFIRST, leds );
	digitalWrite( latchPin, HIGH );
}

void rollEm() {

	//Blank out LEDs
	leds = 0;  
	lightUp();
	delay( 50 );

	//Display a random roll
	int cast = rand() % 6;
	for( int i = 0; i < 6; i++ ) {
		if( dieConfigurations[cast][i] != -1 ) {
			bitSet( leds, dieConfigurations[cast][i] );
		}
	}
	lightUp();
	delay( 100 );
}
