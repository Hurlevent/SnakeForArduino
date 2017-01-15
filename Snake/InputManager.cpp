#include "InputManager.h"

InputManager::InputManager() : m_buttonBufferSize(5) {

}

InputManager::~InputManager() {

}

void InputManager::readInput() {
  int readingsX = analogRead(PIN_INPUT_X_AXIS);
  int readingsY = analogRead(PIN_INPUT_Y_AXIS);
  int readingsButton = analogRead(PIN_INPUT_BUTTON);

  m_currentXvalue = map(readingsX, 0, 1023, 0, joystickMappingValue);
  m_currentYvalue = map(readingsY, 0, 1023, 0, joystickMappingValue);

  for (int i = 1; i < m_buttonBufferSize; i++) {
    m_buttonValues[i] = m_buttonValues[i - 1];
  }

  if (readingsButton <= buttonValueThreshold) {
    m_buttonValues[0] = true;
  } else {
    m_buttonValues[0] = false;
  }

}

Direction InputManager::movementDirection(Direction currentDirection) {

  // Horizontal will have priority over Vertical input
  int horizontal = 128 - m_currentXvalue;
  int vertical = 130 - m_currentYvalue;

  if (abs(horizontal) >= abs(vertical)) {
    if (abs(horizontal) > joystickValueThreshold) {
      return (horizontal >= 0 ? LEFT : RIGHT);
    }
  } else {
    if (abs(vertical) > joystickValueThreshold) {
      return (vertical >= 0 ? UP : DOWN);
    }
  }
  return currentDirection;
}

bool InputManager::buttonPressed() {
  bool found_true = false;
  for (int i = 0; i < m_buttonBufferSize; i++) {
    if (m_buttonValues[i]) {
      found_true = true;
    }  else if (found_true) {
      return true;
    }
  }
  return false;
}
