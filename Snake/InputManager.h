#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Direction.h"
#include <Arduino.h>
#include "Constants.h"

const int buttonValueThreshold = 3; // The threshold for what is considered a button press, if you are having trouble with the joystick button, try to tweek this value
const int joystickValueThreshold = 20; // The threshold for that is considered a joystick tilt.
const int joystickMappingValue = 255; 

class InputManager{
  public:
  
  /*
  * Constructor
  */
  InputManager();
  
  /*
  * Destructor
  */
  ~InputManager();
  
  /*
  * Reads the analog input from the Playstation Joystick.
  * Which is connected to A0, A1, and A2.
  */
  void readInput();
  
  /*
  * Calculates the new direction that the snake should be moving in.
  * @param the direction that the snake is currently moving in
  * @return the new direction that the snake will be moving in
  */
  Direction movementDirection(Direction currentDirection);

  /*
  * This function is used to determine if the joystick button has been pressed. 
  * @return true if button has been pressed within the last few iterations
  */
  bool buttonPressed();
  
  private:
  
  int m_currentXvalue;
  int m_currentYvalue;
  bool m_buttonValues[5];
  int m_buttonBufferSize;

  int m_x_pin;
  int m_y_pin;
  int m_btn_pin;
  
};

#endif // INPUTMANAGER_H
