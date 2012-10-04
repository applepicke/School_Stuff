int LED_R = 15;
int LED_G = 14;
int LED_B = 12;

int BUTTON_R = 6; 
int BUTTON_G = 7;
int BUTTON_B = 8;

int BUTTON_MOD = 5;
int BUTTON_CHG_COL = 10;

int MAX_INTENSITY = 255;
int MIN_INTENSITY = 0;

void setup() {
  Serial.begin( 38400 );
  
  pinMode( LED_R, OUTPUT );
  pinMode( LED_G, OUTPUT );
  pinMode( LED_B, OUTPUT );
  pinMode( BUTTON_R, INPUT_PULLUP );
  pinMode( BUTTON_G, INPUT_PULLUP );
  pinMode( BUTTON_B, INPUT_PULLUP );
  pinMode( BUTTON_MOD, INPUT_PULLUP );
  pinMode( BUTTON_CHG_COL, INPUT_PULLUP );
}

int intensity_r = 0;
int intensity_g = 0;
int intensity_b = 0;
int increment = 1;


void loop() {
  
  digitalWrite( LED_R, !digitalRead(BUTTON_R) );
  digitalWrite( LED_G, !digitalRead(BUTTON_G) );
  digitalWrite( LED_B, !digitalRead(BUTTON_B) );
 
  if ( digitalRead( BUTTON_MOD ) == LOW ) {
    
    intensity_g = MAX_INTENSITY - intensity_r;
    intensity_b = MAX_INTENSITY - intensity_g;
    
    analogWrite( LED_R, intensity_r );
    analogWrite( LED_G, intensity_g );
    analogWrite( LED_B, intensity_b );  
  
    delay(10);  
    
    intensity_r += increment;
    if ( intensity_r == MAX_INTENSITY ) {
      increment = -1;
    } 
    if ( intensity_r == 0 ) {
      increment = 1; 
    }
  }
  
  if ( digitalRead( BUTTON_CHG_COL ) == LOW ) {
    randomColour();
    delay( 500 );
  }
}

void randomColour() {
  analogWrite( LED_R, random( MAX_INTENSITY ) );
  analogWrite( LED_G, random( MAX_INTENSITY ) );
  analogWrite( LED_B, random( MAX_INTENSITY ) );
}

