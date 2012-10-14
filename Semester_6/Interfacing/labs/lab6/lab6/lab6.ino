
#include <math.h>

// Pin Assignments
int L_A = 15;
int L_B = 16;
int L_C = 7;
int L_D = 8;
int L_E = 9;
int L_F = 14;
int L_G = 13;
int L_DP = 6;

int L1_CA = 12;
int L2_CA = 10;

//Measuring Internals
int VR_COMMON = 20;
int R_220 = 5;
int R_1K = 4;
int R_10K = 3;

//Decimal Point LED
int LED = 18;
int VOM_OUT = 17;
int VOM_IN = 19;

// Voltage Per Segmant constant (255 / 8)
int VPS = 31;

// Modes
int HEX_MODE = 0;
int ALPHA_MODE = 1;
int GRADE_MODE = 2;

// Segment Masks
int MASK_A = 0x01;
int MASK_B = 0x02;
int MASK_C = 0x04;
int MASK_D = 0x08;
int MASK_E = 0x10;
int MASK_F = 0x20;
int MASK_G = 0x40;
int MASK_DP = 0x80;

// Hexidecimal Codes
int HEX_CODES[] = {
  0x3F,  // 0
  0x06,  // 1
  0x5B,  // 2
  0x4F,  // 3
  0x66,  // 4
  0x6D,  // 5
  0x7D,  // 6
  0x07,  // 7
  0x7F,  // 8
  0x67,  // 9
  0x77,  // A
  0x7F,  // B
  0x39,  // C
  0x3F,  // D
  0x79,  // E
  0x71   // F
};

int ALPHANUM_CODES[] = {
  // 0    1    2     3      4    5      6    7      8    9
  0x3F, 0x30, 0x5B, 0x79, 0x74, 0x6D, 0x6F, 0x38, 0x7F, 0x7D,
  // A    b    C      d    E      F    G     H     i      J    K      L    m      n    o
  0x7E, 0x67, 0x0F, 0x73, 0x4F, 0x4E, 0x6F, 0x76, 0x86, 0x33, 0x6E, 0x07, 0x6A, 0x62, 0x63, 
  // P    Q    R      S    T     U     v      W    x      Y    Z
  0x5E, 0x7C, 0x42, 0x6D, 0x47, 0x23, 0x15, 0x2B, 0x76, 0x75, 0x52
};

int LED_CODES[] = {
  0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01   
};

int NUM_BAR_LEDS = 14;

int counter = 0;

void setup() {
  pinMode( L_A, OUTPUT );
  pinMode( L_B, OUTPUT );
  pinMode( L_C, OUTPUT );
  pinMode( L_D, OUTPUT );
  pinMode( L_E, OUTPUT );
  pinMode( L_F, OUTPUT );
  pinMode( L_G, OUTPUT );
  pinMode( L_DP, OUTPUT );
 
  pinMode( L1_CA, OUTPUT );
  pinMode( L2_CA, OUTPUT );

  pinMode( LED, OUTPUT );  
  pinMode( VOM_OUT, OUTPUT );
  pinMode( VOM_IN, INPUT );
  
  //pinMode( VR_COMMON, OUTPUT );
  //pinMode( R_220, INPUT );
  //pinMode( R_1K, OUTPUT );
  //pinMode( R_10K, INPUT );
  
  Serial.begin( 9400 );

}

int MODE_CYLON = 0;
int MODE_GRAPH = 1;
int MODE_SENSE = 2;

void loop() {
  //digitalWrite( R_10K, LOW );
  //digitalWrite( R_1K, HIGH );
  //digitalWrite( R_220, HIGH );
  //digitalWrite( VR_COMMON, LOW );
  measureVoltage();
}

void measureVoltage() { 
  static int voltage;
  static int decimal;
  static int dig1;
  static int dig2;
  static int dig3;
  
  digitalWrite( VOM_OUT, HIGH );
  voltage = (analogRead( VOM_IN ) * 500L) / 1023;
  Serial.println( voltage, DEC ); 
  Serial.println( decimalPlace(voltage), DEC );
 
  decimal = decimalPlace( voltage );
  if ( decimal == 1 ) voltage = intRound(voltage);
  dig1 = voltage / 100;
  dig2 = (voltage % 100) / 10;
  dig3 = voltage % 10;
  
  //Red LED is the decimal
  if ( decimal == 0 ){
    digitalWrite( LED, HIGH );
    writeTo7Segment( L1_CA, HEX_CODES[dig2], false );
    writeTo7Segment( L2_CA, HEX_CODES[dig3], false ); 
  } 
  //Decimal in the middle
  if ( decimal == 1 ) {
    digitalWrite( LED, LOW );
    writeTo7Segment( L1_CA, HEX_CODES[dig1], true );
    writeTo7Segment( L2_CA, HEX_CODES[dig2], false );     
  }
}

int intRound( int voltage ) {
  if ( (voltage % 10) >= 5 ) {
    voltage -= voltage % 10; 
    voltage += 10; 
  }
  return voltage;
}

int decimalPlace( int voltage ) {
  if ( (voltage / 100) > 0 ) {
    return 1; 
  }
  else {
    return 0; 
  }
}

void writeTo7Segment( int pin, int hex, boolean dec ) {
  static int state;
  int numSegments;

  state = hex & MASK_A ? LOW: HIGH;
  digitalWrite( L_A, state );
  state = hex & MASK_B ? LOW: HIGH;
  digitalWrite( L_B, state );
  state = hex & MASK_C ? LOW: HIGH;
  digitalWrite( L_C, state );
  state = hex & MASK_D ? LOW: HIGH;
  digitalWrite( L_D, state );
  state = hex & MASK_E ? LOW: HIGH;
  digitalWrite( L_E, state );
  state = hex & MASK_F ? LOW: HIGH;
  digitalWrite( L_F, state );
  state = hex & MASK_G ? LOW: HIGH;
  digitalWrite( L_G, state );
  state = dec ? LOW: HIGH;
  digitalWrite( L_DP, state );
  
  for ( hex; hex != 0; hex >>= 1 ) {
    if ( hex & 0x01 ) 
      numSegments++;
  }  
  analogWrite( pin, VPS * numSegments );
  delay( 3 );
  analogWrite( pin, 0 );
  delay( 3 );    
}


