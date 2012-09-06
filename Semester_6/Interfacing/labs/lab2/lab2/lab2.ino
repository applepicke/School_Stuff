void setup() {
  moveMouseToCorner();
  clickScreen();
  launchMari0();
  hitEnter(); 
  hitEnter();
}

void loop() {
  
}

void moveMouseToCorner() {
  int i;
  
  //Move mouse to corner of screen
  for (i=0; i<100; i++) {
     Mouse.move(-10, 5);
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
