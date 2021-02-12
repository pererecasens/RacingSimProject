//Controller for 3 loadcell racing simulator pedals
//By Pere Recasens
//11-2-2021

//sck = verd/blanc = 10
//dt = verd = 11

#include <Arduino.h>
#include <HX711.h>
#include <Joystick.h>

//WIRING
const int LOADCELL_THROTTLE_DOUT_PIN = 11;
const int LOADCELL_THROTTLE_SCK_PIN = 10;

//ADJUSTMENT SETTINGS
const int SCALE = 124;


//values
int t_value = 0;

//JOYSTICK DECLARATION
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 
1, 			//Button count
0, 			//Switch hat count
false, 		//x axis
false, 		//y axis
false, 		//z axis
false, 		//Rx axis
false, 		//Ry axis
false, 		//Rz axis
false, 		//Rudder
true, 		//Throttle
false, 		//Accelerator
true, 		//Brake
false);		//Steering

//LOADCELL DECLARATIONS
HX711 throttle_lc;


//TESTING VARIABLES
int button_state = 0;
int button_pin = 8;
int led_pin = 12;


void setup() {
	
	//setup pin mode
	pinMode(led_pin, OUTPUT);
	pinMode(button_pin, INPUT);

	//initialize terminal
	Serial.begin(9600);
	
	//initialize loadcells
	throttle_lc.begin(LOADCELL_THROTTLE_DOUT_PIN, LOADCELL_THROTTLE_SCK_PIN);

	//initialize joystick
	Joystick.begin();
	

	//set loadcell scale
	throttle_lc.set_scale(124);
	throttle_lc.tare();

	//setup joystick
	Joystick.setThrottleRange(0, 20000);


}

void loop() {
	// put your main code here, to run repeatedly:

	//adquire reading
	t_value = throttle_lc.get_units();

	

	Serial.print("weight: ");
	Serial.println(t_value);

	Joystick.setThrottle(t_value);

	//TARA
	button_state = digitalRead(button_pin);

	if(button_state == LOW){
		throttle_lc.tare();
		digitalWrite(led_pin, HIGH);
	}
	else{
		digitalWrite(led_pin, LOW);
	
	}

}