#ifndef CONSTANTS_H
#define CONSTANTS_H


// MicroSD CS    Connected to D4
// MicroSD MISO  Connected to D12

// TFT+MicroSD !SCL  Connected to D13
// TFT+MicroSD !SDA  Connected to D11
// TFT          DC   Connected to D9
// TFT          RES  Connected to D8
// TFT          CS   Connected to D10

#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   9  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT

#define SOUND_PIN 2 // Used for the buzzer

#define PIN_INPUT_X_AXIS A0
#define PIN_INPUT_Y_AXIS A1
#define PIN_INPUT_BUTTON A2

//This is BGR Color values
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#define TILE_SIZE_X 6 // The width in pixels for each character!
#define TILE_SIZE_Y 8 // the height in pixels for each character

// Stage boundries
#define STAGE_DIMENTION_X 21 
#define STAGE_DIMENTION_Y 19

#define DEVICE_RESOLUTION_X 128
#define DEVICE_RESOLUTION_Y 160

#define STATUSBAR_PIXELS_Y 8


#endif // CONSTANTS_H
