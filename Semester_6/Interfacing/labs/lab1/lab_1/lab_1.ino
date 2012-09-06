#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Codes in the table are mapped as characters beginning
//at 65 of the ascii table. They are case insensitive. A is a.
//code_table['A' - 65] == code_table['a' - 97] == morse code of 'a'

//All values are binary masks. 0001 is one short. 0011 is one long.
// 0101 is two short. 1111 is two long.
unsigned int code_table[] = {  
   0x0D,       //A - 0000 1101
   0x57,       //B - 0101 0111
   0x77,       //C - 0111 0111
   0x17,       //D - 0001 0111
   0x01,       //E - 0000 0001 
   0x75,       //F - 0111 0101
   0x1F,       //G - 0001 1111
   0x55,       //H - 0101 0101
   0x05,       //I - 0000 0101
   0xFD,       //J - 1111 1101
   0x37,       //K - 0011 0111
   0x5D,       //L - 0101 1101
   0x0F,       //M - 0000 1111
   0x07,       //N - 0000 0111
   0x3F,       //O - 0011 1111
   0x7D,       //P - 0111 1101
   0xDF,       //Q - 1101 1111
   0x1D,       //R - 0001 1101
   0x15,       //S - 0001 0101
   0x03,       //T - 0000 0011
   0x35,       //U - 0011 0101
   0xD5,       //V - 1101 0101
   0x3D,       //W - 0011 1101
   0xD7,       //X - 1101 0111
   0xF7,       //Y - 1111 0111
   0x5F        //Z - 0101 1111
};

//These are the masks
unsigned int SHORT = 0x01;   //0000 0001
unsigned int LONG = 0x03;    //0000 0011

//How much will need to be subtracted to get the index
unsigned int LOWERCASE_ASCII = 97;
unsigned int UPPERCASE_ASCII = 65;

unsigned int MASK = 0x03;   //0000 0011

//Delay times
unsigned int short_delay = 500;
unsigned int long_delay = 1000;

void setup() {
  pinMode( 11, OUTPUT ); 
}

void loop() {
  blinkMessage( "b" );
  digitalWrite( 11, LOW );
  delay( 2000 );   
}

void blinkMessage( char* text ) {
  unsigned int len = strlen( text );
  unsigned int i;

  for (i = 0; i < len; i++) {
    blinkCharacter(text[i]);
  }

}

void blinkCharacter( char character ) {
  unsigned int index = islower(character) ? LOWERCASE_ASCII - character : UPPERCASE_ASCII - character;

  //Only blink alhabetic characters
  if (!isalpha(character)) {
    return;
  }

  blinkCode( code_table[index] );
}

void blinkCode( int code ) {
  unsigned int delay_amt = 0;

  while (code != 0) {
    digitalWrite( 11, HIGH );
    
    if ( (code & MASK) == SHORT) {
      delay_amt = short_delay;
    }
    else if ( (code & MASK) == LONG) {
      delay_amt = long_delay;
    }
    delay( delay_amt );
    code = code >> 2;

    digitalWrite( 11, LOW );
    delay( 100 );
  }

}

