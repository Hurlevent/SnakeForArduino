#include "OutputManager.h"

OutputManager::OutputManager() : m_tft(TFT_CS, TFT_DC, TFT_RST) {
  m_tft.initR(INITR_BLACKTAB); // initialize a ST7735R chip, red tab
}

OutputManager::~OutputManager() {

}

void OutputManager::init(GameVariables * variables) {
  m_tft.fillScreen(ST7735_BLACK);
  m_tft.setTextColor(WHITE);
  m_variables = variables;

  setMenuScreen();
}

void OutputManager::update() {
  (this->*render)();
}


void OutputManager::menu_screen() {
  m_tft.setTextColor(GREEN);
  m_tft.setTextSize(2);
  m_tft.setCursor((DEVICE_RESOLUTION_X - TILE_SIZE_X*5*2) / 2, TILE_SIZE_Y * 2);
  m_tft.print("SNAKE");
  m_tft.setTextSize(1);
  
  m_tft.setTextColor(MAGENTA);
  m_tft.setCursor((DEVICE_RESOLUTION_X - TILE_SIZE_X*9) / 2, TILE_SIZE_Y * 5);
  m_tft.print("MAIN MENU");

  m_tft.setTextColor(WHITE);
  m_tft.setCursor((DEVICE_RESOLUTION_X - TILE_SIZE_X*16) / 2, TILE_SIZE_Y * 7);
  m_tft.print("Press the button");
  m_tft.setCursor((DEVICE_RESOLUTION_X - TILE_SIZE_X * 8) / 2, TILE_SIZE_Y * 8);
  m_tft.print("to start");
  m_tft.setCursor((DEVICE_RESOLUTION_X - TILE_SIZE_X * 9) / 2, TILE_SIZE_Y * 12);
  m_tft.print("HIGHSCORE");
  char hs_buffer[5];
  sprintf(hs_buffer, "%04d", m_variables->high_score);
  m_tft.setCursor((DEVICE_RESOLUTION_X - TILE_SIZE_X * 4) / 2, TILE_SIZE_Y * 13);
  m_tft.print(hs_buffer);
  m_tft.setCursor((DEVICE_RESOLUTION_X - TILE_SIZE_X * 11) / 2, TILE_SIZE_Y * 15);
  m_tft.print("DEATH COUNT");
  m_tft.setCursor((DEVICE_RESOLUTION_X - TILE_SIZE_X * 4) / 2, TILE_SIZE_Y * 16);
  char dc_buffer[5];
  sprintf(dc_buffer, "%04d", m_variables->death_count);
  m_tft.print(dc_buffer);
}

void OutputManager::game_screen() {
  remove_tail_trace();
  m_tft.drawChar(m_variables->apple_position.x, m_variables->apple_position.y, Apple, RED, BLACK, 1);
  m_tft.drawChar(m_variables->pos.x, m_variables->pos.y, SnakeHead, GREEN, BLACK, 1);
  for (int i = 0; i < m_variables->tail.size(); i++) {
    m_tft.drawChar(m_variables->tail.get(i).x, m_variables->tail.get(i).y, SnakeBody, GREEN, BLACK, 1);
  }
  paused_or_playing_status();
}

void OutputManager::remove_tail_trace() {
  if (!m_variables->paused) {
    Coordinate tip_of_tail = (m_variables->tail.size() == 0 ? m_variables->pos : m_variables->tail.dequeue());
    m_tft.drawChar(tip_of_tail.x, tip_of_tail.y, ' ', GREEN, BLACK, 1);
  }
}

void OutputManager::setGameScreen() {
  m_tft.fillScreen(ST7735_BLACK);
  m_tft.fillRect(0, 0, DEVICE_RESOLUTION_X, STATUSBAR_PIXELS_Y, WHITE);
  m_tft.setTextColor(BLACK);

  m_tft.setCursor(0, 0);
  m_tft.print("SCORE:"); // This string has length 6

  m_tft.setCursor(12 * TILE_SIZE_X, 0);

  m_tft.print("HIGH:");

  char buffer[5];
  sprintf(buffer, "%04d", m_variables->high_score);
  m_tft.setCursor(17 * TILE_SIZE_X, 0);
  m_tft.print(buffer);

  render = &OutputManager::game_screen;
}

void OutputManager::setMenuScreen() {
  render = &OutputManager::menu_screen;
}

void OutputManager::paused_or_playing_status() {
  if (m_variables->paused) {
    draw_paused();
  } else {
    draw_score();
  }
}

void OutputManager::draw_score() {
  char buffer[11];
  sprintf(buffer, "SCORE:%04d", m_variables->score);
  for (int i = 0; i < sizeof(buffer); ++i) {
    m_tft.drawChar(i * TILE_SIZE_X, 0, buffer[i], BLACK, WHITE, 1);
  }
}

void OutputManager::draw_paused() {
  char buffer[7];
  sprintf(buffer, "PAUSED");
  for (int i = 0; i < sizeof(buffer); ++i) {
    m_tft.drawChar(i * TILE_SIZE_X, 0, buffer[i], BLACK, WHITE, 1);
  }
}

