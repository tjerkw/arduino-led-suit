
// piezo buzzer
#define BUZZER 12

// Connect a 38KHz remote control sensor to the pin below
#define IR_PIN 2

// Led Strips Pins:

// left leg
#define PIN_STRIP_LEFT_BOTTOM 4
// right leg
#define PIN_STRIP_RIGHT_BOTTOM 5
// left torso and arm
#define PIN_STRIP_LEFT_TOP 6
// right torso and arm
#define PIN_STRIP_RIGHT_TOP 7


// buttons on the NEC ir remote
#define REPEAT_PREV 0xFFFFFFFF
#define VOL_DOWN 0
#define PLAY 0xFD807F
#define VOL_UP 2
#define SETUP 0xFD20DF
#define UP 0xFDA05F
#define STOP 6
#define LEFT 0xFD10EF
#define ENTER 0xFD906F
#define RIGHT 0xFD50AF
#define DOWN 0xFDB04F
#define BACK 0xFD30CF


// my samsung remote was giving these values
// nice to have a fallback to a samsung remote :-)
#define SAMSUNG_VOL_UP 0x68733A46
#define SAMSUNG_VOL_DOWN 0x83B19366
#define SAMSUNG_PROG_UP 0x5F12E8C4
#define SAMSUNG_PROG_DOWN 0x189D7928
