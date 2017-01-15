#include "GameManager.h"

GameManager * gameManager;

void setup() {
  gameManager = new GameManager();
  
  gameManager->init();
}

void loop() {
  gameManager->update();
}


