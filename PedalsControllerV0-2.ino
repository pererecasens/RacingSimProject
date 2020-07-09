//Controller for 3 loadcell pedals
//
// By Pere Recasens
// 30-06-2020
//------------------------------------------------------------


#include <HX711.h>

#include <HID-Project.h>



const int n_buttons = 6;


//HX711 Data pins

#define T_CLK 2
#define B_CLK 11
#define C_CLK 12

#define T_DOUT 3
#define B_DOUT 13
#define C_DOUT 5

#define TARE_TIMEOUT_SECONDS 4

#define BOOT_MESSAGE "3 Loadcell Pedal V0.1"

HX711 throttle_scale;
//HX711 brake_scale;


  long throttle_lc;
  long clutch_lc;
  long brake_lc;

  int calibration_factor = 35000;


void setup() {

  
  // Initialize Button Pins
  /*pinMode(10, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);*/
  pinMode(4, INPUT_PULLUP);

  throttle_scale.begin(T_DOUT, T_CLK);
  throttle_scale.set_scale(calibration_factor);
  throttle_scale.tare();

 /* brake_scale.begin(B_DOUT, B_CLK);
  brake_scale.set_scale(calibration_factor);
  brake_scale.tare();*/




  Gamepad.begin();

  //Serial for testing
  //Serial.begin(9600);
  //Serial.println(BOOT_MESSAGE);

  
  

}

//getting data from loadcells
void get_lc_data(){
  throttle_lc = throttle_scale.get_value();
  //brake_lc = brake_scale.get_value();

}

long scale_data(long scale_data, long inMax, long outMax){
  long valor = (outMax * scale_data)/inMax;

  return valor;
}

// Last state of the buttons
//int lastButtonState[n_buttons] = {0,0,0,0,0,0};

void loop() {

  // Read pin values
    if(!digitalRead(2)){
      static uint8_t count = 0;
        Gamepad.press(count);
    }


  /*for (int index = 0; index < n_buttons; index++)
  {
    int currentButtonState = !digitalRead(index + 5);
    if (currentButtonState != lastButtonState[index])
    {
      switch (index) {
        case 0: // RIGHT
          if (currentButtonState == 1) {
            //Joystick.setHatSwitch(0, 270);
          } else {
            //Joystick.setHatSwitch(0, -1);
          }
          break;
        case 1: // UP
          if (currentButtonState == 1) {
            //Joystick.setHatSwitch(0, 0);
          } else {
            //Joystick.setHatSwitch(0, -1);
          }
          break;
        case 2: // LEFT
          if (currentButtonState == 1) {
            //Joystick.setHatSwitch(0, 90);
          } else {
            //Joystick.setHatSwitch(0, -1);
          }
          break;
        case 3: // DOWN
          if (currentButtonState == 1) {
            //Joystick.setHatSwitch(0, 180);
          } else {
            //Joystick.setHatSwitch(0, -1);
          }
          break;
        case 4: // FIRE
          if (currentButtonState == 1) {
            //Joystick.pressButton(0);
          } else {
            //Joystick.releaseButton(0);
          }
          break;
        case 5: // FIRE2
          if (currentButtonState == 1) {
            //Joystick.pressButton(1);
          } else {
            //Joystick.releaseButton(1);
          }
          break;
      }
      lastButtonState[index] = currentButtonState;
    }
  }*/

  get_lc_data();

  //Serial.println(throttle_scale.get_value());
  //Serial.println("ei");
  //Serial.println(brake_scale.get_value());
  Gamepad.xAxis(scale_data(throttle_lc, 320000, 1023));
  //Joystick.setBrake(scale_data(brake_lc, 320000, 1023));

  Gamepad.write();

  delay(30);

}


long convert(long input, long minInput, long maxInput, long minOutput, long maxOutput) {
  float ratio = ((float)input - (float)minInput) / ((float)maxInput - (float)minInput);
  float result =  minOutput + (maxOutput - minOutput) * ratio;
  return result;
}