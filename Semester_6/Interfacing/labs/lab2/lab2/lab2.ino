void setup() {
  moveMouseToCorner();
  clickScreen();
  launchMari0();
  hitEnter(); 
  hitEnter();
  delay( 3000 );
  finishLevel1();
  
  cleanUp();
}

void loop() {
  
}

void moveMouseToCorner() {
  int i;
  
  //Move mouse to corner of screen
  for (i=0; i<130; i++) {
     Mouse.move(10, 5);
     delay(25);
  }
  delay(1000);
}

void clickScreen() {
  Mouse.click();
  delay(1000); 
}

void launchMari0() {
  Keyboard.set_modifier( MODIFIERKEY_CTRL );
  Keyboard.set_key1( KEY_M );
  Keyboard.send_now();
  Keyboard.set_modifier( 0 );
  Keyboard.set_key1( 0 );
  Keyboard.send_now();
  delay(10000);
}

void hitEnter() {
  Keyboard.println(); 
  delay(1000);
}

void finishLevel1() {
  setMoveRightFast( );
  delay( 1000 );
  jump( 1000 );
  delay( 700 );
  jump( 300 );
  delay( 500 );
  jump( 400 );
  delay( 500 );
  jump( 1000 );
  delay( 500 );
  jump( 1000 );
  delay( 700 );
  jump( 200 );
  delay( 1300 );
  jump( 300 );
  delay( 1000 );
  jump( 100 );
  delay( 800 );
  jump( 300 );
  delay( 800 );
  jump( 400 );
  delay( 900 );
  jump( 1000 );
  delay( 500 );
  jump( 1000 );
  delay( 500 );
  jump( 300 );
  delay( 400 );
  jump( 300 );
  delay( 600 );
  jump( 300 );
  delay( 600 );
  jump( 300 );
  delay( 700 );
  jump( 300 );
  delay( 700 );
  jump( 1000 );
  delay( 700 );
  jump( 400 );
  stopMovingRight();
  readyForJump();
  setMoveRightFast();
  delay( 400 );
  jump( 1000 );
}

void setMoveRightFast( ) {
  Keyboard.set_modifier( MODIFIERKEY_SHIFT );
  Keyboard.set_key6( KEY_D );
  Keyboard.send_now();
}

void stopMovingRight( ) {
  Keyboard.set_key6( 0 );
  Keyboard.send_now(); 
}

void jump(int time) {
  Keyboard.set_key1( KEY_SPACE );
  Keyboard.send_now();
  delay( time );
  Keyboard.set_key1( 0 );
  Keyboard.send_now(); 
}

void readyForJump() {
  int i; 
  for (i = 0; i < 4; i++) { 
    delay( 500 );
    Mouse.move( 0, 127);
    delay( 500 );
    Mouse.move( 0, -127);
  }
  
}

void cleanUp() {
  Keyboard.set_modifier( 0 );
  Keyboard.set_key1( 0 );
  Keyboard.set_key2( 0 );
  Keyboard.set_key3( 0 );
  Keyboard.set_key4( 0 );
  Keyboard.set_key5( 0 );
  Keyboard.set_key6( 0 );
  Keyboard.send_now();
}


