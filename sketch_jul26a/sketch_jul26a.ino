// Import definitions
#include "DYPlayerArduino.h"

// Pin definitions
const int relayUp = 13; // Relay for movement in one direction
const int relayDown = 12; // Relay for movement in the opposite direction
const int relayMouth = 11; // Relay for moving the mouth

// Program states
bool movingToEnd = false;
bool movingToStart = false;

// Initialisation
DY::Player player;

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);
  Serial.println("System starting...");
  player.begin();
  player.setVolume(15); // 50% Volume

  // Initialize relay pins as outputs
  pinMode(relayUp, OUTPUT);
  pinMode(relayDown, OUTPUT);
  pinMode(relayMouth, OUTPUT);
  
  // Ensure relays are off at the start
  stopAllRelays();
}

void loop() {
  moveToEnd(); // Move up
  delay(5000); // Milliseconds
  player.playSpecified(1);
  startMoveMouth(); // Mouth movement
  delay(5000); // Milliseconds
  stopMoveMouth(); // Mouth movement
  player.playSpecified(3);
  delay(4000);
  moveToStart(); // Move down
  player.playSpecified(2);
  delay(700);
  delay(10000); // Milliseconds
}

void startMoveMouth() {
  digitalWrite(relayMouth, HIGH);
}

void stopMoveMouth() {
  digitalWrite(relayMouth, LOW);
}

void moveToEnd() {
  // Turn off relay2 and turn on relay1 to move to the end
  digitalWrite(relayUp, HIGH); // Relay 1 ON
  digitalWrite(relayDown, LOW);  // Relay 2 OFF
  movingToEnd = true;
  movingToStart = false;
  Serial.println("Relay 1 ON: Moving to end...");
}

void moveToStart() {
  // Turn off relay1 and turn on relay2 to move to the start
  digitalWrite(relayUp, LOW);  // Relay 1 OFF
  digitalWrite(relayDown, HIGH); // Relay 2 ON
  movingToEnd = false;
  movingToStart = true;
  Serial.println("Relay 2 ON: Moving to start...");
}

// Function to stop all relays (stops movement)
void stopAllRelays() {
  digitalWrite(relayUp, LOW);
  digitalWrite(relayDown, LOW);
  Serial.println("All relays OFF: Stopped movement.");
}
