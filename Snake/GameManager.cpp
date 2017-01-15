#include "GameManager.h"

GameManager::GameManager() {
  m_variables = new GameVariables;
  play_scene = &GameManager::pause_scene;
  m_pause_time = 0;
}

GameManager::~GameManager() {
  delete m_variables;
}

void GameManager::init() {
  pinMode(SOUND_PIN, OUTPUT);
  restart();

  /*
  * I tried really hard to implement SD-card reading here
  */
  
  m_variables->high_score = 0;
  m_variables->death_count = 0;

}

void GameManager::update() {
start:
  m_input.readInput(); // read input

  (this->*play_scene)(); // execute game logic

  if (m_game_over) {
    check_for_new_high_score();
    restart();
    ++(m_variables->death_count);
    goto start;
  }

  m_output.update(); // update the screen

  delay(game_speed); // Wait a bit before updating the next "frame"
}

void GameManager::update_direction_and_movement() {
  Coordinate newHeadPos;
  newHeadPos = m_variables->pos;
  switch (m_direction) {
    case UP:
      if (m_variables->pos.y - TILE_SIZE_Y >= STATUSBAR_PIXELS_Y) {
        newHeadPos.y -= TILE_SIZE_Y;
        move_snake(newHeadPos);
      } else {
        m_game_over = true;
      }
      break;
    case DOWN:
      if (m_variables->pos.y + TILE_SIZE_Y < DEVICE_RESOLUTION_Y) {
        newHeadPos.y += TILE_SIZE_Y;
        move_snake(newHeadPos);
      } else {
        m_game_over = true;
      }
      break;
    case RIGHT:
      if (m_variables->pos.x + TILE_SIZE_X < DEVICE_RESOLUTION_X - TILE_SIZE_X) {
        newHeadPos.x += TILE_SIZE_X;
        move_snake(newHeadPos);
      } else {
        m_game_over = true;
      }
      break;
    case LEFT:
      if (m_variables->pos.x - TILE_SIZE_X >= 0) {
        newHeadPos.x -= TILE_SIZE_X;
        move_snake(newHeadPos);
      } else {
        m_game_over = true;
      }
      break;
  }
}

void GameManager::move_snake(Coordinate newHeadPos) {

  m_variables->tail.enqueue(m_variables->pos);

  check_if_snake_is_eating_himself(newHeadPos);
  check_if_snake_is_eating_apple(newHeadPos);

  m_variables->pos = newHeadPos;
}

void GameManager::restart() {

  m_variables->tail.reset();
  m_variables->pos.x = TILE_SIZE_X * (starting_tail_length + 1);
  m_variables->pos.y = (TILE_SIZE_Y * 2) + STATUSBAR_PIXELS_Y;

  for (int i = 0; i < starting_tail_length; ++i) {
    m_variables->tail.enqueue({m_variables->pos.x - TILE_SIZE_X * (i + 1), m_variables->pos.y});
  }

  m_variables->score = 0;
  m_variables->paused = false;

  m_direction = RIGHT;

  m_game_over = false;

  play_scene = &GameManager::pause_scene;

  m_output.init(m_variables);

  spawn_apple();
}

void GameManager::spawn_apple() {
spawnApple:
  int temp_x = random(STAGE_DIMENTION_X) * TILE_SIZE_X;
  int temp_y = random(STAGE_DIMENTION_Y) * TILE_SIZE_Y + STATUSBAR_PIXELS_Y;

  for (int i = 0; i < m_variables->tail.size(); ++i) {
    Coordinate snakeBodyPos = m_variables->tail.get(i);
    if (snakeBodyPos.x == temp_x && snakeBodyPos.y == temp_y) {
      goto spawnApple;
    }
  }
  m_variables->apple_position = {temp_x, temp_y};
}

void GameManager::check_if_snake_is_eating_himself(Coordinate newHeadPos) {
  for (int i = 0; i < m_variables->tail.size(); i++) {
    Coordinate tailCoord = m_variables->tail.get(i);
    if (newHeadPos.x == tailCoord.x && newHeadPos.y == tailCoord.y) {
      m_game_over = true;
    }
  }
}

void GameManager::check_if_snake_is_eating_apple(Coordinate newHeadPos) {
  Coordinate apple_pos = m_variables->apple_position;
  if (newHeadPos.x == apple_pos.x && newHeadPos.y == apple_pos.y) {

    // Increase the body length and spawn a new apple

    m_variables->tail.enqueue(m_variables->pos);
    ++(m_variables->score);

    tone(SOUND_PIN, 262, 4);
    tone(SOUND_PIN, 180, 8);
    tone(SOUND_PIN, 262, 4);

    spawn_apple();
  }
}

void GameManager::check_for_new_high_score() {
  if (m_variables->score > m_variables->high_score) {
    m_variables->high_score = m_variables->score; // Change later to make it read from SD card!
  }
}


void GameManager::snake_scene() {
  if (m_input.buttonPressed() && millis() - m_pause_time > pause_cooldown_millis) {
    play_scene = &GameManager::pause_scene;
    m_variables->paused = true;
  }

  Direction possible_new_direction = m_input.movementDirection(m_direction);

  if (abs(m_direction - possible_new_direction) != 1) {
    m_direction = possible_new_direction;
  }

  update_direction_and_movement();
}

void GameManager::pause_scene() {
  if (m_input.buttonPressed()) {
    m_pause_time = millis();
    m_output.setGameScreen();
    play_scene = &GameManager::snake_scene;
    m_variables->paused = false;
  }
}

