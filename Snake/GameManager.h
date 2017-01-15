#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InputManager.h"
#include "OutputManager.h"
#include "Direction.h"
#include "Constants.h"

const int starting_tail_length = 2; // the length of the tail from the start, notice that it looks like the tail is one less than the actual number
const int pause_cooldown_millis = 2000; // prevents the player from pausing withing the last 2 seconds since the player unpaused.
const int game_speed = 100; // higher_value = slower game, lower_value = faster fame

class GameManager{
    
    public:
    
    /*
    * Constructor
    */
    GameManager();
    
    /*
    * Destructor
    */
    ~GameManager();

    /*
    * Will initialize everything! Should be called in the setup function
    */
    void init();
    
    /*
    * an update in our game-loop, should be called in the loop function
    */
    void update();
    
    private:
    
    InputManager m_input;
    OutputManager m_output;

    bool m_game_over;

    Direction m_direction;

    GameVariables * m_variables;

    int m_pause_time;

    void move_snake(Coordinate newHeadPos);

    void update_direction_and_movement();

    void restart();

    void spawn_apple();

    void check_if_snake_is_eating_himself(Coordinate newHeadPos);

    void check_if_snake_is_eating_apple(Coordinate newHeadPos);

    void check_for_new_high_score();

    void (GameManager::*play_scene)();

    void snake_scene();

    void pause_scene();

};

#endif // GAMEMANAGER_H
