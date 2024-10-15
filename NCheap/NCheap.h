#include "Myservo.h"
#include "servoSetup.h"
#include "Display.h"
#include "Motor.h"
#include <MPU6050.h>

#define ma1 2
#define ma2 4
#define mb1 16
#define mb2 17

MPU6050 mpu6050(Wire);
int state_IMU = 0;

// General input function for digital read
int input(int pin) {
  return digitalRead(pin);  // Read digital input
}

// ADC read function for analog pins
int analog_read(int pin) {
  return analogRead(pin);  // Read analog input
}

// General output function
void output(int pin, int value) {
  pinMode(pin, OUTPUT);     // Set the pin mode
  digitalWrite(pin, value); // Write the output value
}

// Read the knob value from pin 36
int knob() {
  return analogRead(36); // Read knob (analog) value
}

// Function for buzzer beep with custom delay
void beep(int time_) {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(time_);
  digitalWrite(13, LOW);
  delay(10);
}

// Overloaded beep function with default 1-second beep
void beep() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(10);
}

// Read the state of switch 1 (pin 15)
int sw1() {
  pinMode(15, INPUT_PULLUP);  // Set pin 15 as input with pullup
  return digitalRead(15);     // Return the switch state
}

// Wait until switch 1 is pressed
void wait_sw1() {
  while (sw1() == HIGH) {  // Wait until the switch is pressed
    delay(10);
  }
}

// Helper function to display text on the screen
void displayText(const char* line1, const char* line2, int delayTime = 100) {
  clear();  // Clear the display
  display.setTextSize(3);
  display.setCursor(0, 0);
  display.print(line1);
  display.setTextSize(2);
  display.setCursor(80, 6);
  display.print(line2);
  display.setTextSize(1);
  display.display();
  delay(delayTime);
}

// Function to show the welcome message until the switch is pressed
void showPround() {
  while (sw1() == 1) {
    displayText("NAPS", "BOT", 100);
    displayText("NAPS", "BOT", 100);  // Alternate the display text
  }
}

// Robot setup function
void BotSetup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize I2C addr 0x3C
  clear();  // Clear the display and buffer

  // Set motor pins to output
  pinMode(ma1, OUTPUT);
  pinMode(ma2, OUTPUT);
  pinMode(mb1, OUTPUT);
  pinMode(mb2, OUTPUT);

  // Setup PWM channels for motors
  ledcSetup(6, 5000, 8);
  ledcSetup(7, 5000, 8);
  ledcSetup(4, 5000, 8);
  ledcSetup(5, 5000, 8);

  // Attach PWM channels to pins
  ledcAttachPin(ma1, 6);
  ledcAttachPin(ma2, 7);
  ledcAttachPin(mb1, 4);
  ledcAttachPin(mb2, 5);

  display.setTextColor(WHITE);
  display.display();

  //showPround();  // Show welcome message
}

// Setup and calibration for the IMU
void set_IMU() {
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);  // Calibrate gyro offsets
  mpu6050.update();

  // Ensure the IMU values are within a certain range
  auto isOutsideRange = [](float angle) {
    return (angle + 1000 > 1100 || angle + 1000 < 900);
  };

  if (isOutsideRange(mpu6050.getAngleX()) || 
      isOutsideRange(mpu6050.getAngleY()) || 
      isOutsideRange(mpu6050.getAngleZ())) {
    mpu6050.calcGyroOffsets(true);  // Recalibrate if outside the expected range
    mpu6050.update();
  }
  state_IMU = 1;
}

// Get the Z angle from the IMU
int angleZ() {
  mpu6050.update();
  return mpu6050.getAngleX() + 180;
}
int angleX() {
  mpu6050.update();
  return mpu6050.getAngleY() + 180;
}
int angleY() {
  mpu6050.update();
  return mpu6050.getAngleZ() + 180;
}

void NCheap_Setup()
{
  BotSetup();
  set_IMU();
}