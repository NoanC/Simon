/*
  This proyect is about doing the game Simon, but with 5 colours in order to 4,
  and using a servomotor for see the colour that must be pressed next.

  Created by Noan Cantabrana, Josep Aymerich.

*/


#include <Servo.h>

// create servo object to control a servo
Servo myservo;


// Declare the pins for output LED
const int led_red = 2;
const int led_blue = 3;
const int led_yellow = 4;
const int led_green = 5;
const int led_orange = 6;

// Declare the pins for output Buttons
const int button_red = 9;
const int button_blue = 10;
const int button_yellow = 11;
const int button_green = 12;
const int button_orange = 13;

// Declare some variables
long sequence[25];             // Array that includes the sequence
int counter = 0;               // Counter
long input = 5;                // Indicator for pushed button
int wait = 500;                // Delay for when the sequence increases
int max_points = 25;           // Max points where the game Ends
int val;                       // variable to read the value from the analog pin



void setup() {

  myservo.attach(8);           // attaches the servo on pin 8 to the servo object

  // Set up the pins for LEDs as outputs
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_orange, OUTPUT);

  // Set up the pins for buttons as inputs
  pinMode(button_red, INPUT);
  pinMode(button_green, INPUT);
  pinMode(button_yellow, INPUT);
  pinMode(button_blue, INPUT);
  pinMode(button_orange, INPUT);

  // Initialize the internal PullUp resistances for the buttons
  digitalWrite(button_red, HIGH);
  digitalWrite(button_green, HIGH);
  digitalWrite(button_yellow, HIGH);
  digitalWrite(button_blue, HIGH);
  digitalWrite(button_orange, HIGH);
}



void loop() {
  show_sequence();             // Plays sequence
  read_sequence();             // Reads sequence
  delay(1000);                 // Waits a second
}



// Function for, in case of error, show what button should have been pressed
void show_correct_button (long led) {
  switch (led) {
    case 0:
      digitalWrite(led_red, HIGH);
      myservo.write (18);
      delay (500);
      myservo.write (0);
      digitalWrite(led_red, LOW);
      break;

    case 1:
      digitalWrite(led_green, HIGH);
      myservo.write (54);
      delay (500);
      myservo.write (0);
      digitalWrite(led_green, LOW);
      break;

    case 2:
      digitalWrite(led_yellow, HIGH);
      myservo.write (90);
      delay (500);
      myservo.write (0);
      digitalWrite(led_yellow, LOW);
      break;

    case 3:
      digitalWrite(led_blue, HIGH);
      myservo.write (126);
      delay (500);
      myservo.write (0);
      digitalWrite(led_blue, LOW);
      break;

    case 4:
      digitalWrite(led_orange, HIGH);
      myservo.write (162);
      delay (500);
      myservo.write (0);
      digitalWrite(led_orange, LOW);
      break;
  } delay (150);
}


// Function for congratulate when you win
void congratulation () {
  digitalWrite(led_red, HIGH);
  digitalWrite(led_green, HIGH);
  digitalWrite(led_yellow, HIGH);
  digitalWrite(led_blue, HIGH);
  digitalWrite(led_orange, HIGH);

  delay(500);
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_blue, LOW);
  digitalWrite(led_orange, LOW);

  delay(500);
  digitalWrite(led_red, HIGH);
  digitalWrite(led_green, HIGH);
  digitalWrite(led_yellow, HIGH);
  digitalWrite(led_blue, HIGH);
  digitalWrite(led_orange, HIGH);

  delay(500);
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_blue, LOW);
  digitalWrite(led_orange, LOW);
  resetcounter();
}



// Reset counters
void resetcounter() {
  counter = 0;
  wait = 500;
}



// Function for create and reproduce patrons
void show_sequence() {

  // We make pseudo-random sequence
  randomSeed(analogRead(10));

  sequence[counter] = random(5);
  for (int i = 0; i < counter; i++) {
    show_correct_button (sequence[i]);
  }
  wait = 500 - (counter * 15);
  counter++;
}



// Function for read what buttons is pushing the player
void read_sequence() {
  for (int i = 1; i < counter; i++) {
    while (input == 6) {
      if (digitalRead(button_red) == LOW) {
        input = 0;
      } if (digitalRead(button_green) == LOW) {
        input = 1;
      } if (digitalRead(button_yellow) == LOW) {
        input = 2;
      } if (digitalRead(button_blue) == LOW) {
        input = 3;
      } if (digitalRead(button_orange) == LOW) {
        input = 4;
      }
    } if (sequence[i - 1] == input) {
      show_correct_button (input);
      if (i == max_points) {
        congratulation();
      }
    } else {
      delay(500);
      show_correct_button(sequence[i - 1]);
      show_correct_button(sequence[i - 1]);
      delay(1000);
      congratulation();
    }
    input = 6;
  }
}
