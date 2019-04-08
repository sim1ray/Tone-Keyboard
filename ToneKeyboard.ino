/*
 * 
 * Tone Keyboard:
 * 4 tone buttons: Plays four different notes(C, D, E, F) and lights corresponding LEDs
 * Replay button: As notes are played, device stores the notes and replays them (for as long as user pressed the note)
 * Reset button: Clears the stored notes
 * LCD displays notes as they are pressed and replayed
 * 
 * Circuit:
 * - Six buttons from +5V to analog in 0 through 5
 * - Six 10 kilohm resistors from analog in 0 through 5 to ground
 * - Four LEDS on digital pins 6, 7, 9, and 10
 * - Piezo buzzer on digital pin 8
 * - 16x2 LCD display:
 *   LCD RS pin to digital pin 12
 *   LCD Enable pin to digital pin 11
 *   LCD D4 pin to digital pin 5
 *   LCD D5 pin to digital pin 4
 *   LCD D6 pin to digital pin 3
 *   LCD D7 pin to digital pin 2
 *   LCD R/W pin to ground
 *   LCD VSS pin to ground
 *   LCD VCC pin to 5V
 *   10K resistor:
 *   ends to +5V and ground
 *   wiper to LCD VO pin (pin 3)
 */

#include <LiquidCrystal.h>

// INPUT 
const int noteC = A0;
const int noteD = A1;
const int noteE = A2;
const int noteF = A3;
const int reset = A4;
const int replay = A5;

// OUTPUT
const int ledC = 10;
const int ledD = 9;
const int ledE = 7;
const int ledF = 6;
const int speaker = 8;

// Note Frequencies
const int freqC = 262;
const int freqD = 294;
const int freqE = 330;
const int freqF = 349;

struct Tone {
  char note;
  int frequency;
  int ledPin;
};

// Initialize all possible tones
Tone c = {'C', freqC, ledC};
Tone d = {'D', freqD, ledD};
Tone e = {'E', freqE, ledE};
Tone f = {'F', freqF, ledF};

// Initialize arrays to store played tones and their durations
Tone replayArr[150];      //notes
int replayIndex = 0; 
long replayDuration[150]; //duration times for each note
int durationIndex = 0;
long firstTime;           //stores time when button is first pressed

// Initial state of tone buttons set to 0
int buttonState[4] = {LOW, LOW, LOW, LOW};

// LCD pin assignment and initialization
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Compare previous state of tone buttons with current state
bool stateCompare(int *current, int *previous) {
  for (int i = 0; i < 4; i++) {
    if (current[i] != previous[i]) return false;
  }
  return true;
}

// Play given note, print on LCD, turn on corresponding LED, and add tone to replay array
// Record time when button is first pressed to get duration of button click
void playNote(Tone t) {
  lcd.clear();
  lcd.print(t.note);
  tone(speaker, t.frequency);
  digitalWrite(t.ledPin, HIGH);
  replayArr[replayIndex++] = t;
  firstTime = millis();
}

// Replay given tone for given duration 
// Print note on LCD, and turn on corresponding LED
void replayNote(Tone t, int duration) {
  lcd.clear();
  lcd.print(t.note);
  tone(speaker, t.frequency, duration);
  digitalWrite(t.ledPin, HIGH);
  delay(duration);
  digitalWrite(t.ledPin, LOW);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(noteC, INPUT);    // Button C
  pinMode(noteD, INPUT);    // Button D
  pinMode(noteE, INPUT);    // Button E
  pinMode(noteF, INPUT);    // Button F
  pinMode(ledC, OUTPUT);    // C LED
  pinMode(ledD, OUTPUT);    // D LED
  pinMode(ledE, OUTPUT);    // E LED
  pinMode(ledF, OUTPUT);    // F LED
  pinMode(speaker, OUTPUT); //speaker

  // lcd setup
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}


void loop() {
  // put your main code here, to run repeatedly:
  int buttonCState = digitalRead(noteC);
  int buttonDState = digitalRead(noteD);
  int buttonEState = digitalRead(noteE);
  int buttonFState = digitalRead(noteF);
  int buttonResetState = digitalRead(reset);
  int buttonReplayState = digitalRead(replay);
  int currentButtonState[4] = {buttonCState, buttonDState, buttonEState, buttonFState};

  if (buttonReplayState == HIGH) {  // if replay button is pressed
    for (int i = 0; i < replayIndex; i++) {
      replayNote(replayArr[i], replayDuration[i]);
      delay(200);
    }
    lcd.clear();
    lcd.print("hello, world!");
  }

  if (buttonResetState == HIGH) {   // if reset button is pressed
    replayIndex = 0;
    durationIndex = 0;
  }

  if (!stateCompare(currentButtonState, buttonState)) { //if there is a change in the tone button pressed
    if (buttonCState == HIGH) {           // tone C is pressed
      playNote(c);
    } else if (buttonDState == HIGH) {    // tone D is pressed
      playNote(d);
    } else if (buttonEState == HIGH) {    // tone E is pressed
      playNote(e);
    } else if (buttonFState == HIGH) {    // tone F is pressed
      playNote(f);
    } else {                              // if no tone button is pressed (button is released), all LEDs and speaker are turned off
      lcd.clear();
      digitalWrite(ledC, LOW);
      digitalWrite(ledD, LOW);
      digitalWrite(ledE, LOW);
      digitalWrite(ledF, LOW);
      noTone(speaker);
      long millis_held = millis() - firstTime;    // get amount of time button was pushed
      replayDuration[durationIndex++] = millis_held;
    } 
  }

  // Update tone button states
  for (int i = 0; i < 4; i++) {
    buttonState[i] = currentButtonState[i];
  }
}
