
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
  
}

void loop() {
  static int index1 = 0;
  static int index2 = 0;
  static int oldTime = millis();
  int newTime;
  static int mode = HEX_MODE;
  boolean change = false;
  static boolean stopNumbers = false;
  
  newTime = millis();
  if ( (newTime - oldTime) >= 500 ) {
    oldTime = newTime;
    change = true;
  }
  
  if ( mode == ALPHA_MODE ) {
    if ( change ) {
      index1 = ( index1 == 35 ) ? 0: index1 + 1;
    }       
    writeTo7Segment( L1_CA, ALPHANUM_CODES[index1] );
    writeTo7Segment( L2_CA, 0 );
  }
  
  if ( mode == HEX_MODE ) {    
    if ( change )  {
      if ( index1 == 15 ) {
        index1 = -1;
        index2 = ( index2 == 15 ) ? 0: index2+1; 
      }    
      index1++;    
    }    
    writeTo7Segment( L1_CA, HEX_CODES[index2] );
    writeTo7Segment( L2_CA, HEX_CODES[index1] );
  }
  
  if ( mode == GRADE_MODE ) {    
    if ( digitalRead( BUTTON_CYCLE ) == LOW ) {
       stopNumbers = ( stopNumbers == false ) ? true: false;
       delay( 250 );
    }
    if ( !stopNumbers ) {
      if ( index1 == 9 ) {
        index1 = -1;
        index2 = ( index2 == 9 ) ? 0: index2+1;
      }    
      index1++;
    }
    writeTo7Segment( L1_CA, HEX_CODES[index2] );
    writeTo7Segment( L2_CA, HEX_CODES[index1] );
  }
  
  if ( digitalRead( BUTTON ) == LOW ) {
    mode = ( mode == 2 ) ? 0: mode + 1; 
    index1 = 0;
    index2 = 0;
    delay( 250 ); 
  }
   
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
  delay( 7 );
  analogWrite( pin, 0 );
  delay( 3 );    
}


