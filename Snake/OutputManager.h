#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "Constants.h"
#include "Direction.h"
#include "QueueList.h"
#include "GameVariables.h"

const char SnakeHead = '@';
const char SnakeBody = '*';
const char Apple = 'o';

class OutputManager{
  
    public:

   /*
   *  Constructor
   */
    OutputManager();

    /*
    * Destructor
    */
    ~OutputManager();

    /*
    * This function must be called before the program attempts to render the game. It initialises some core variables.
    */
    void init(GameVariables * variables);

    /*
    * This function updates the screen, and should be called in every iteration of the game loop.
    */
    void update();

    /*
    * This function makes the update() function render the gameplay screen.
    */
    void setGameScreen();

    /*
    * This function make the update() function render the menu screen.
    */
    void setMenuScreen();

    
    private:
    
    Adafruit_ST7735 m_tft;

    GameVariables * m_variables;

    void (OutputManager::*render)();

    void menu_screen();
    
    void game_screen();
    
    void remove_tail_trace();

    void draw_score();

    void draw_paused();

    void paused_or_playing_status();
};

#endif //OUTPUTMANAGER_H
