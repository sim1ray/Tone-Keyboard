# Tone-Keyboard
## DESCRIPTION
 4 tone buttons: Plays four different notes(C, D, E, F) and lights corresponding LEDs <br />
 Replay button: As notes are played, device stores the notes and replays them (for as long as user pressed the note) <br />
 Reset button: Clears the stored notes <br />
 LCD displays notes as they are pressed and replayed <br />
  
## CIRCUIT
* Six buttons from +5V to analog in 0 through 5
* Six 10 kilohm resistors from analog in 0 through 5 to ground
* Four LEDS on digital pins 6, 7, 9, and 10
* Piezo buzzer on digital pin 8
* 16x2 LCD display:
   * LCD RS pin to digital pin 12
   * LCD Enable pin to digital pin 11
   * LCD D4 pin to digital pin 5
   * LCD D5 pin to digital pin 4
   * LCD D6 pin to digital pin 3
   * LCD D7 pin to digital pin 2
   * LCD R/W pin to ground
   * LCD VSS pin to ground
   * LCD VCC pin to 5V
   * 10K resistor:
   * ends to +5V and ground
   * wiper to LCD VO pin (pin 3)
