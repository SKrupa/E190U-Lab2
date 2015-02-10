/*
  JoystickMouseControl
 
 Controls the mouse from a joystick on an Arduino Leonardo or Micro.
 Uses a pushbutton to turn on and off mouse control, and
 a second pushbutton to click the left mouse button
 
 Hardware:
 * 2-axis joystick connected to pins A0 and A1
 * pushbuttons connected to pin D2 and D3
 
 The mouse movement is always relative. This sketch reads 
 two analog inputs that range from 0 to 1023 (or less on either end)
 and translates them into ranges of -6 to 6. 
 The sketch assumes that the joystick resting values are around the 
 middle of the range, but that they vary within a threshold.
 
 WARNING:  When you use the Mouse.move() command, the Arduino takes
 over your mouse!  Make sure you have control before you use the command.
 This sketch includes a pushbutton to toggle the mouse control state, so
 you can turn on and off mouse control.
 
 created 15 Sept 2011
 updated 28 Mar 2012
 by Tom Igoe
 
 this code is in the public domain
 
 */

// set pin numbers for switch, joystick axes, and LED:
const int switchPin = 3;      // switch to turn on and off mouse control
const int start = 2;
const int upButton = 5;
const int downButton = 7;
const int leftButton = 6;
const int rightButton = 4;
const int aButton = 10;
const int bButton = 9;
const int xButton = 11;
const int yButton = 8;
const int r3 = 12;
const int l3 = 13;
const int xAxis = A2;         // joystick X axis  
const int yAxis = A3;         // joystick Y axis
const int xAxisL = A0;
const int yAxisL = A1;
const int analogButtons = A5;
const int ledPin = 5;         // Mouse control LED 

// parameters for reading the joystick:
int range = 32;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range/8;      // resting threshold
int center = range/2;         // resting position value
int acceleration = 0;

boolean mouseIsActive = false;    // whether or not to control the mouse
boolean controlState = 0;
boolean depressed = 1;
boolean depressed2 = 1;

int xMouseStateCurrent;
int xMouseStateOld;
double xMult = 1.0;

int yMouseStateCurrent;
int yMouseStateOld;
double yMult = 1.0;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);       // the switch pin
  pinMode(start, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(aButton, INPUT_PULLUP);
  pinMode(bButton, INPUT_PULLUP);
  pinMode(xButton, INPUT_PULLUP);
  pinMode(yButton, INPUT_PULLUP);
  pinMode(r3, INPUT_PULLUP);
  pinMode(l3, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);         // the LED pin  
  // take control of the mouse:
  Mouse.begin();
}

void loop() {
  // read the switch:
  mouseIsActive = !digitalRead(switchPin);
  
  //deadzone really messes up acceleration so we want to minize it
  //we still need a slight deadzone to prevent drift
  if(acceleration) 
    threshold = range/16;
  else
    threshold = range/8;      
  center = range/2; 
  
  // read and scale the two axes:
  int xReading = readAxis(xAxis);
  int yReading = -readAxis(yAxis);

  int xReadingL = readAxis(xAxisL);
  int yReadingL = readAxis(yAxisL);
  

  boolean aButton1 = 0;
  boolean aButton2 = 0;
  boolean aButton3 = 0;
  boolean aButton4 = 0;
  boolean aButton5 = 0;
  boolean aButton6 = 0;
  
  int aButtons = analogRead(analogButtons);
  int abuttons = aButtons;
  
  if(aButtons <= 100) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0;
  }else if (aButtons <= 120) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 1;
  }else if (aButtons <= 205) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 0;
  }else if (aButtons <= 280) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 1;
  }else if (aButtons <= 335) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 0;
  }else if (aButtons <= 385) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 1;
  }else if (aButtons <= 430) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 0;
  }else if(aButtons <= 475) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 1;
  }else if (aButtons <= 515) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0;
  }else if (aButtons <= 545) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 1;
  }else if (aButtons <= 570) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 0;
  } else if (aButtons <= 590) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 1;
  }else if (aButtons <= 615) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 0;   
  }else if (aButtons <= 630) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 1;
  }else if (aButtons <= 650) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 0;
  }else if (aButtons <= 659) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0;    
  }else if (aButtons <= 663) {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 1;
  }else if (aButtons <= 672) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 1;
  }else if (aButtons <= 688) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 0;
  }else if (aButtons <= 699) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 1;
  }else if (aButtons <= 712) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 0;
  }else if (aButtons <= 725) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 1;
  }else if (aButtons <= 735) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 745) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 755) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 765) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 773) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 779) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 784) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 792) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 798) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 805) {
    aButton1 = 0;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 814) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 819) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 824) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 829) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 833) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 838) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 842) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 846) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 850){
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 853) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 857) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 860) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 863) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 865) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 868) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 869) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 871) {
    aButton1 = 1;
    aButton2 = 0;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 873) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 875) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 880) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 882) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 885) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 886) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 888) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 889) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 891) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 893) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 895) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 0;
    aButton5 = 1;
    aButton6 = 1;
  } else if (abuttons <= 897) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 0;
  } else if (abuttons <= 898) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 0;
    aButton6 = 1;
  } else if (abuttons <= 900) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 0;
  } else if (abuttons <= 915) {
    aButton1 = 1;
    aButton2 = 1;
    aButton3 = 1;
    aButton4 = 1;
    aButton5 = 1;
    aButton6 = 1;
  } else {
    aButton1 = 0;
    aButton2 = 0;
    aButton3 = 0;
    aButton4 = 0;
    aButton5 = 0;
    aButton6 = 0; 
  }
  
          

  // if the mouse control state is active, move the mouse:
  if (mouseIsActive) {
    
    //control button was pressed
    if(aButton1) {
      if(depressed) {
        controlState = !controlState;
      }
      depressed = 0;
    } else {
      depressed = 1;
    }
    
    if(controlState) {
        if (digitalRead(upButton) == LOW) {
            if(depressed2) {
              range = range+8;
            }
            depressed2 = 0;
        } else if (digitalRead(downButton) == LOW) {
            if(depressed2) {
              if(range > 16){
                range= range-8;
              }
            }
            
            depressed2 = 0;
        } else if (digitalRead(leftButton) == LOW) {
            if(depressed2 && (acceleration > 0)) {
              acceleration = acceleration - 1;
            }
            depressed2 = 0;
        }else if (digitalRead(rightButton) == LOW) {
            if(depressed2){
              acceleration = acceleration + 1;
            }
            depressed2 = 0;
        } else {
         depressed2 = 1; 
        }
    } else {
      // use the pushbuttons to control the keyboard:
      if (digitalRead(upButton) == LOW) {
        Keyboard.press(KEY_UP_ARROW); 
      }
      else{
        Keyboard.release(KEY_UP_ARROW); 
      }
      if (digitalRead(downButton) == LOW) {
        Keyboard.press(KEY_DOWN_ARROW); 
      }
      else{
        Keyboard.release(KEY_DOWN_ARROW); 
      }
      if (digitalRead(leftButton) == LOW) {
        Keyboard.press(KEY_LEFT_ARROW); 
      }
      else{
        Keyboard.release(KEY_LEFT_ARROW); 
      }
      if (digitalRead(rightButton) == LOW) {
        Keyboard.press(KEY_RIGHT_ARROW); 
      }
      else{
        Keyboard.release(KEY_RIGHT_ARROW); 
      }
    }
    
    if (digitalRead(start) == LOW) {
      Keyboard.press(KEY_ESC); 
    }
    else{
      Keyboard.release(KEY_ESC); 
    }

    if(aButton2){
      Keyboard.press(KEY_RETURN);
    }else{
      Keyboard.release(KEY_RETURN); 
    }

    if(xReadingL < 0){
      Keyboard.press('a');
      Keyboard.release('d');
    } else if(xReadingL > 0){
      Keyboard.press('d');
      Keyboard.release('a');
    } else{
      Keyboard.release('a');
      Keyboard.release('d');
    }

    if(yReadingL < 0){
      Keyboard.press('s');
      Keyboard.release('w');
    }else if(yReadingL > 0){
      Keyboard.press('w');
      Keyboard.release('s');
    }else{
      Keyboard.release('w');
      Keyboard.release('s');
    }

    if(aButton3){
      Keyboard.press('y');
    }else{
      Keyboard.release('y'); 
    }
    
    if(aButton4){
      Keyboard.press('u');
    }else{
      Keyboard.release('u'); 
    }
    
    if(aButton5){
      Keyboard.press('i');
    }else{
      Keyboard.release('i'); 
    }
    
    if(aButton6){
      Keyboard.press('o');
    }else{
      Keyboard.release('o'); 
    }
        
    


    if (digitalRead(aButton) == LOW) {
      Keyboard.press('m'); 
    }
    else{
      Keyboard.release('m');
    }
    if (digitalRead(bButton) == LOW) {
      Keyboard.press('n'); 
    }
    else{
      Keyboard.release('n');
    }
    if (digitalRead(xButton) == LOW) {
      Keyboard.press('k'); 
    }
    else{
      Keyboard.release('k');
    }
    if (digitalRead(yButton) == LOW) {
      Keyboard.press('l'); 
    }
    else{
      Keyboard.release('l');
    }

    if (digitalRead(l3) == LOW) {
      Keyboard.press('j'); 
    }
    else{
      Keyboard.release('j');
    }
    if (digitalRead(r3) == LOW) {
      Keyboard.press('b'); 
    }
    else{
      Keyboard.release('b');
    }
    
    
    xMouseStateOld = xMouseStateCurrent;
    yMouseStateOld = yMouseStateCurrent;
    
    xMouseStateCurrent = xReading;
    yMouseStateCurrent = yReading;
    /*
    if(acceleration) {
      if(xMult > 1.0) {
        xMult = xMult-0.1*acceleration;
      } else {
        if(abs(xMouseStateOld)  < abs(xMouseStateCurrent)) {
           xMult = 3.5*acceleration; 
        } else if (abs(xMouseStateOld)  > abs(xMouseStateCurrent)) {
           xMult = 
           yuio0.5;
        } else {
          xMult = 1.0;
        }
      }
      if(yMult > 1.0) {
        yMult = yMult - 0.1*acceleration;
      } else {
        if(abs(yMouseStateOld)  < abs(yMouseStateCurrent)) {
           yMult = 3.5*acceleration;
        } else if (abs(yMouseStateOld)  > abs(yMouseStateCurrent)) {
           yMult = 0.5;
        } else {
          yMult = 1.0;
        }
      }
    }*/
	if(acceleration) {
		if((xMouseStateCurrent == xMouseStateOld) && ((xMouseStateCurrent == (range/2-1)) || (xMouseStateCurrent == -range/2) )) {
			xMult = xMult + 0.15*acceleration;
		} else if (xMult > (1 + acceleration)) {
			xMult = xMult - acceleration;
		} else {
			xMult = 1;
		}

		if((yMouseStateCurrent == yMouseStateOld) && (abs(yMouseStateCurrent) == range/2)) {
			yMult = yMult + 0.15*acceleration;
		} else if (yMult > (1 + acceleration)) {
			yMult = yMult -acceleration;
		} else {
			yMult = 1;
		}

	}	
      int xMove = xMult * xMouseStateCurrent;
      int yMove = yMult * yMouseStateCurrent;
      
      if(xMove > 127)
        xMove = 127;
      else if(xMove < -127)
        xMove = -127;
        
      if(yMove > 127)
        yMove = 127;
      else if(yMove < -127)
        yMove = -127;
      
      Serial.print(xMult);
      Serial.print("\n");
      Serial.print(xMouseStateCurrent);
      Serial.print("\n");
      Serial.print(xMove);
      Serial.print("\n");
      Serial.print("\n");
      
    Mouse.move(xMove, yMove, 0);
    
    delay(responseDelay);
    }  
  
}

/*
  reads an axis (0 or 1 for x or y) and scales the 
 analog input range to a range from 0 to <range>
 */

int readAxis(int thisAxis) { 
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  } 

  // return the distance for this axis:
  return distance;
}




