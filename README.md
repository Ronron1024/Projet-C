# Projet µC

//structure BTN
typedef struct {
  
    uint8_t id;
    int status;           //1 pressed - 0 not pressed
    uint32_t count;      //count of button is pressed and relaxed

} BTN;

//buttons.h
//Init structure BTN
void initButtons(BTN* btn1, BTN* btn2, BTN* btn3, BTN* btn4 );
void initButton(BTN* btn, int num);

//Interruption ext btn1,2,3 et 4
void enable_interrupt_ext_buttons(void);

//structure LCD
typedef struct {
  
  uint8_t id;           //id digit, 1 to 4
  uint8_t val;          //for display

} DIGIT;

typedef struct {
  
  int mode;            //status ON/OFF
  int intensity;        //Between 0, 15
  DIGIT digit[4];         
  
} DISPLAYLCD;

//displayLcd.h
//Init structure DISPLAYLCD et init configuration SPI
void initLCD(DISPLAYLCD* DisplayLcd);
void GPIO_init(void);
void Set_CS();
void Reset_CS();
void SPI_Config(void);
void SendData_SPI(uint8_t data);
void SPI_write(uint8_t add, uint8_t data);
void Delay(uint32_t);

//mode ON/OFF pour le lcd
void statusLCD(DISPLAYLCD* DisplayLcd, Mode mode);

//Reglage de l' intensité du lcd, entre 0 et 15
void IntensityLCD(DISPLAYLCD* DisplayLcd, uint8_t intensity);

//Affiche "val" sur le digit "id"
void DisplayDigit(DISPLAYLCD* DisplayLcd, uint8_t id, uint8_t val);

//creer la valeur current, equivalente au choix des segments à afficher (liste des segments dans le define.h)
void createDigit(uint8_t* current, int n, ...);

//Basculment de l' intensité du LCD de mini, à max et retour à mini, à intervalle de temps parametrable
void blinkingLCD(DISPLAYLCD* DisplayLcd, Speed speed);

//Affiche sur le LCD une chaine de caractere, avec une vitesse de defilement parametrable
void printfDigit(DISPLAYLCD* DisplayLcd,char* text, Speed speed);
////Affiche un caractere sur le digit id du LCD
void printDigit(DISPLAYLCD* DisplayLcd,int id, char c);
//Affiche sur le LCD une variable de type int, avec une vitesse de defilement parametrable
void printIntDigit(DISPLAYLCD* DisplayLcd,int number, Speed speed);
//Efface les 4 digits
void eraseLCD(DISPLAYLCD* DisplayLcd);
## Buzzer

### Example

```c
// Create a melody
uint8_t music_sheet_length = 3;
Note music_sheet = 
{
    {A5, crotchet},
    {B5, crotchet},
    {F4, quaver}
};

// Init a new Buzzer
    // Configure Timers & GPIOs
Buzzer buzzer = InitBuzzer();

// Set the active melody
buzzer.setSheetMusic(music_sheet, music_sheet_length);

// Start the buzzer
    // Call this function again to stop it
buzzer.toggleBuzzer();
```

### Reference

```c
Buzzer InitBuzzer(void);
```

You must call this function before using your buzzer. It returns the structure from which you can interact with the hardware.

```c
struct Buzzer
{
    void (*toggleBuzzer)(void);
    void (*setSheetMusic)(Note[] sheet_music, uint8_t sheet_music_length);
}
```

The buzzer structure, contains two functions :

- __toggleBuzzer__ : Play or pause the music
- __setSheetMusic__ : Set the music played by the buzzer (see [How to make a music sheet](###How-to-make-a-music-sheet)), you must specify the number of note

### How to make a music sheet

A music sheet is an array of __Note__ :

```c
struct Note
{
    NoteName name;
    NoteDuration duration;
}
```

_name_ is the note pitch, from __C0__ to __C8__, including a silent note : __SILENCE__.

_duration_ is the note duration, which is either :

- __semibreve__ = 2 seconds
- __minim__ = 1 second
- __crotchet__ = 1/2 second
- __quaver__ = 1/4 second

For example, you can define the A5, during 1 second :

```c
Note a5 = {A5, minim};
```

Then, you can write an entire melody using an array like this :

```c
Note moonlight[11] =
{ 
    {G4, crotchet},
    {G4, crotchet}, 
    {G4, crotchet},
    {A5, crotchet},
    {B5, mninim},
    {A5, minim},
    {G4, crotchet},
    {B5, crotchet},
    {A5, crotchet},
    {A5, crotchet},
    {G4  semibreve}
};
```

## LedStripe

### Examples

```c
// Init a new LedStripe
    // Configure Timers & GPIOs
LedStripe ledstripe = InitLedStripe();

// Set the animation (see Reference)
ledstripe.setAnim(K2000);

// Start the animation
    // Call this function again to stop it
ledstripe.toggleAnim();
```

```c
// Init a new LedStripe
    // Configure Timers & GPIOs
LedStripe ledstripe = InitLedStripe();

// Set LEDs 1, 3, 5 and 7 to ON
ledstripe.setLEDs(ON, 4, LED1, LED3, LED5, LED7);
```

### Reference

```c
LedStripe InitLedStripe(void);
```

You must call this function before using your ledstripe. It returns the structure from which you can interact with the hardware.

```c
struct LedStripe
{
	void (*setLED)(uint8_t LED_state, uint8_t LED_position);
	void (*setLEDs)(uint8_t LED_state, uint8_t LED_number, ...);
	void (*setAnim)(Animation anim);
	void (*toggleAnim)();
}
```

The LedStripe structure, contains four functions :

- __setLED__ : set LED at _LED_position_ to state _LED_state_ (ON or OFF)
- __setLED__ : set _LED_number_ LEDs to state _LED_state_ (ON or OFF)
- __setAnim__ : set the animation to be played (see below for further information)
- __toggleAnim__ : PLay or pause the animation

```c
enum Animation
{
    K2000, BLINK
}
```

A list of available animation for the ledstripe :

- __K2000__ : K2000
- __BLINK__ : BLINK