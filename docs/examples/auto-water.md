--8<-- "examples/README.md"

Let's walk through the example code. 

Row 9 to 24; Define I/O pins, or in other words we could say we are _mapping_/_labeling_ them with words so it is easier for us to work with them later

```c++ linenums="7"
⋅⋅⋅
// set all moisture sensors PIN ID
int moisture1 = A0;
int moisture2 = A1;
int moisture3 = A2;
int moisture4 = A3;

// set water relays
int relay1 = 6;
int relay2 = 8;
int relay3 = 9;
int relay4 = 10;

// set water pump
int pump = 4;

// set button
int button = 12;
⋅⋅⋅
```

Rows 27 to 45; We are initializing variables which will hold sensor and other values which will be needed later when we start measuring and interacting with our devices

```c++ linenums="26"
// declare moisture values
int moisture1_value = 0; 
int moisture2_value = 0;
int moisture3_value = 0;
int moisture4_value = 0;

//pump state    1:open   0:close
int pump_state_flag = 0;

//relay1 state    1:open   0:close
int relay1_state_flag = 0;

//relay2 state   1:open   0:close
int relay2_state_flag = 0;

//relay3 state  1:open   0:close
int relay3_state_flag = 0;

//relay4 state   1:open   0:close
int relay4_state_flag = 0;
```
We will skip the parts in which we are drawing flowers and logos on the LCD screen for now.

Let's see out setup function. We are opening serial connection at baudrate of 9600 and we are setting the pins' modes as Inputs or Outputs 

```c++ linenums="140"
void setup()
{
	draw_elecrow();
	delay(2000);
	Wire.begin();
	RTC.begin();
	Serial.begin(9600);
	// declare relay as output
	pinMode(relay1, OUTPUT);
	pinMode(relay2, OUTPUT);
	pinMode(relay3, OUTPUT);
	pinMode(relay4, OUTPUT);
	// declare pump as output
	pinMode(pump, OUTPUT);
	// declare switch as input
	pinMode(button, INPUT);
	//pinMode(ROTARY_ANGLE_SENSOR, INPUT);
	// water_flower();
}
```

Also we have to define the function for reading sensors' values. It will be used in the loop, so it is important to mark that we have to set a little delay between readings, otherwise personally I experienced poor performance. 

```c++ linenums="189" hl_lines="16 22 28 34"
void read_value()
{
/**************These is for resistor moisture sensor***********
the code is reduced for clarity; if your project uses resistor sensors, refer to https://z.rootnode.duckdns.org/46265z/remote-watering/src/branch/master/examples
 **********************************************************/

/************These is for capacity moisture sensor*********/
 float value1 = analogRead(A0);
	moisture1_value =map(value1,590,360,0,100);
    delay(20);
	if(moisture1_value<0){
		moisture1_value=0;
	}
	float value2 = analogRead(A1);
	moisture2_value =map(value2,600,360,0,100);
    delay(20);
	if(moisture2_value<0) {
		moisture2_value=0;
	}
	float value3 = analogRead(A2);
	moisture3_value =map(value3,600,360,0,100);
    delay(20);
	if(moisture3_value<0){
		moisture3_value=0;
	}
	float value4 = analogRead(A3);
	moisture4_value =map(value4,600,360,0,100);
    delay(20);
	if(moisture4_value<0) {
		moisture4_value=0;
	}
}
```