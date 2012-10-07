
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

int BUTTON = 0;
int BUTTON_CYCLE = 1;

// Bit Shift Register
int SRCLK = 17;
int RCLK1 = 18;
int RCLK2 = 3;
int SER1 = 19;
int SER2 = 20;
int OE = 5;

// Voltage Per Segmant constant (255 / 8)
int VPS = 31;

// Light Sensor Pin
int LDR = 21;

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
 
  pinMode( BUTTON, INPUT_PULLUP );
  pinMode( BUTTON_CYCLE, INPUT_PULLUP );
  
  pinMode( SRCLK, OUTPUT );
  pinMode( RCLK1, OUTPUT );
  pinMode( RCLK2, OUTPUT );
  pinMode( SER1, OUTPUT );
  pinMode( SER2, OUTPUT );
  pinMode( OE, OUTPUT );  
  
  pinMode( LDR, INPUT ); 

}

int MODE_CYLON = 0;
int MODE_GRAPH = 1;
int MODE_SENSE = 2;

void loop() {
  static int mode = MODE_CYLON;
  
  if ( analogRead( LDR ) < 60 ) {
    mode = ( mode < 2 ) ? mode+1: 0;
    delay( 1000 ); 
  }
  
  if ( mode == MODE_CYLON ) {
    cylonEffect(); 
  }
  else if ( mode == MODE_GRAPH ) {
    pulseGraph();
    digitalGraph(); 
  }
  else if ( mode == MODE_SENSE ) {
    senseLight();
  }
}

void senseLight() {
  
  if ( hasTimeElapsed( 200 ) ) {
    counter = analogRead( LDR ) / 3;
  }
  graph( counter );
  digitalGraph();
}

void digitalGraph() {
  regulateCounter();
  writeTo7Segment( L1_CA, HEX_CODES[ counter/10 ] );
  writeTo7Segment( L2_CA, HEX_CODES[ counter%10 ] );
}

void regulateCounter() {
  if (counter > 99) counter = 99;
  if (counter < 0) counter = 0; 
}

void flushRegisters() {
  registerData( SER1, 0x00 );
  registerData( SER2, 0x00 );
  blastRegisters();
}

void pulseGraph() { 
  static int inc = 1;
 
  if ( counter == 0 ) {
    inc = 1;
  } 
  if ( counter == 99 ) {
    inc = -1;
  } 
    
  if ( hasTimeElapsed( 50 ) ) {
    counter += inc;  
  }
  
  graph( counter );

}

boolean hasTimeElapsed( int milliseconds ) {
  static int oldTime = millis();
  int newTime = millis();
  if ( (newTime - oldTime) >= milliseconds ) {
    oldTime = newTime;
    return true; 
  }
  return false;
}

void graph( int percent ) {
  if ( percent > 100 ) {
    percent = 99;
  } 
  if ( percent < 0 ) {
    percent = 0; 
  }
  
  float led_percent = ( 100.0f / (float) NUM_BAR_LEDS );
  int num_leds1 = percent / (int)led_percent ;
  int num_leds2 = (num_leds1 > 8) ? (num_leds1 - 8): 0;
  int barrel = 0;
  
  for ( int i = 0; i < (num_leds1 - num_leds2); i++ ) {
    barrel = barrel + LED_CODES[i] ;
  }  
  registerData( SER1, barrel );
  blastRegister( RCLK1 );
  
  barrel = 0;  
  for ( int j = 0; j < num_leds2; j++ ) {
    barrel = barrel + LED_CODES[j] ;
  }
  registerData( SER2, barrel );
  blastRegister( RCLK2 );
  delay(1);
  
}

void cylonEffect() {
  static int index = 0;
  static int reg = SER1;
  
  registerData( reg, LED_CODES[index] );
  blastRegisters();
  index++;
  
  if ( index == 8 ) {
    index = 0; 
    reg = (reg == SER1) ? SER2: SER1;
  }
  
  delay( 150 );
}

void loadAndBlast( int dataPin, int data ){
  registerData( dataPin, data );
  blastRegisters(); 
}

void registerData( int dataPin, int data ) {
  int output;
  for ( int i = 0; i < 8; i++ ) {
    output = (data & 1) ? HIGH: LOW; 
    data = data >> 1;
    registerNext( dataPin, output );
  }  
}

void registerNext( int dataPin, int output ) {
  digitalWrite( dataPin, output );
  digitalWrite( SRCLK, HIGH );
  digitalWrite( SRCLK, LOW );
}

void blastRegisters( ) {
  digitalWrite( RCLK1, HIGH );
  digitalWrite( RCLK1, LOW );
  digitalWrite( RCLK2, HIGH );
  digitalWrite( RCLK2, LOW );
  digitalWrite( OE, LOW );
}

void blastRegister( int pin ) {
  digitalWrite( pin, HIGH );
  digitalWrite( pin, LOW );
  digitalWrite( OE, LOW );
}

void writeTo7Segment( int pin, int hex ) {
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
  state = hex & MASK_DP ? LOW: HIGH;
  digitalWrite( L_DP, state );
  
  for ( hex; hex != 0; hex >>= 1 ) {
    if ( hex & 0x01 ) 
      numSegments++;
  }  
  analogWrite( pin, VPS * numSegments );
  delay( 2 );
  analogWrite( pin, 0 );
  delay( 3 );    
}


