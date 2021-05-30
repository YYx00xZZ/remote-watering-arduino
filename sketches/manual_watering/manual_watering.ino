#include <Wire.h>
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);    // I2C
#include "Wire.h"
#include "RTClib.h"
RTC_DS1307 RTC;

// set all moisture sensors PIN ID
int moisture1 = A0;
int moisture2 = A1;
int moisture3 = A2;
int moisture4 = A3;

// declare moisture values
int moisture1_value = 0;
int moisture2_value = 0;
int moisture3_value = 0;
int moisture4_value = 0;

// declare moisture raw values
int moisture1_raw_value = 0;
int moisture2_raw_value = 0;
int moisture3_raw_value = 0;
int moisture4_raw_value = 0;

// set water relays
int relay1 = 6;
int relay2 = 8;
int relay3 = 9;
int relay4 = 10;

// set water pump
int pump = 4;

// set button
int button = 12;

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

static unsigned long currentMillis_send = 0;
static unsigned long  Lasttime_send = 0;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat",};
unsigned long nowtime;
unsigned long endtime;
unsigned long nowtimeNext;
unsigned long nowtime1;
unsigned long endtime1;
unsigned long nowtimeNext1;
unsigned long nowtime2;
unsigned long endtime2;
unsigned long nowtimeNext2;
unsigned long nowtime3;
unsigned long endtime3;
unsigned long nowtimeNext3;

String command;
int rawValues[4];
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
//   water_flowers();
}

void loop()
{
  // read the value from the moisture sensors:
  read_value(); // chete stoinostite na senzorite postoqnno v loop
  //  water_flower();
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    // komandi vkluch./izkluch. za vsqko rele
    if (command.equals("relay1_on")) {
      digitalWrite(relay1,HIGH);
      relay1_state_flag = 1;
    }
    else if (command.equals("relay1_off")) {
      digitalWrite(relay1,LOW);
      relay1_state_flag = 0;
    }
    else if (command.equals("relay2_on")) {
      digitalWrite(relay2,HIGH);
      relay2_state_flag = 1;
    }
    else if (command.equals("relay2_off")) {
      digitalWrite(relay2,LOW);
      relay2_state_flag = 0;
    }
    else if (command.equals("relay3_on")) {
      digitalWrite(relay3,HIGH);
      relay3_state_flag = 1;
    }
    else if (command.equals("relay3_off")) {
      digitalWrite(relay3,LOW);
      relay3_state_flag = 0;
    }
    else if (command.equals("relay4_on")) {
      digitalWrite(relay4,HIGH);
      relay4_state_flag = 1;
    }
    else if (command.equals("relay4_off")) {
      digitalWrite(relay4,LOW);
      relay4_state_flag = 0;
    }
    else if (command.equals("pump_on")) {
      digitalWrite(pump, HIGH);
    }
    else if (command.equals("pump_off")) {
      digitalWrite(pump, LOW);
      Serial.println("pump low");
    }
    else if (command.equals("read_values")) {
      Serial.println(moisture1_value);
      Serial.println(moisture2_value);
      Serial.println(moisture3_value);
      Serial.println(moisture4_value);
    }
    else if (command.equals("read_raw_values")) {
      Serial.println(moisture1_raw_value);
      Serial.println(moisture2_raw_value);
      Serial.println(moisture3_raw_value);
      Serial.println(moisture4_raw_value);
    }
    else if (command.equals("water")) {
      Serial.println("Input integer number representing how many seconds u want to water");
      while (Serial.available() == 0) {
        // Wait for User to Input Data
      }
      int seconds_to_water = Serial.parseInt();
      water_flowers(seconds_to_water);
    }
  }
  int button_state = digitalRead(button);
  if (button_state == 1)
  {
    read_value();
    u8g.firstPage();
    do
    {
      drawTH();
      drawflower();

    } while ( u8g.nextPage() );
  }
  else
  {
    u8g.firstPage();
    do
    {
      drawtime();
      u8g.drawStr(8, 55 , "www.elecrow.com");
    } while (u8g.nextPage());
  }
}

//Set moisture value
void read_value()
{
  /**************These is for resistor moisture sensor***********
    float value1 = analogRead(A0);
    moisture1_value = (value1 * 120) / 1023; delay(20);
    float value2 = analogRead(A1);
    moisture2_value = (value2 * 120) / 1023; delay(20);
    float value3 = analogRead(A2);
    moisture3_value = (value3 * 120) / 1023; delay(20);
    float value4 = analogRead(A3);
    moisture4_value = (value4 * 120) / 1023; delay(20);
   **********************************************************/
  /************These is for capacity moisture sensor*********/
  float value1 = analogRead(A0);
  moisture1_value = map(value1, 590, 360, 0, 100); delay(2); moisture1_raw_value = value1; delay(18);
  if (moisture1_value < 0) {
    moisture1_value = 0;
  }
  float value2 = analogRead(A1);
  moisture2_value = map(value2, 600, 360, 0, 100); delay(2); moisture2_raw_value = value2; delay(18);
  if (moisture2_value < 0) {
    moisture2_value = 0;
  }
  float value3 = analogRead(A2);
  moisture3_value = map(value3, 600, 360, 0, 100); delay(2); moisture3_raw_value = value3; delay(18);
  if (moisture3_value < 0) {
    moisture3_value = 0;
  }
  float value4 = analogRead(A3);
  moisture4_value = map(value4, 600, 360, 0, 100); delay(2); moisture4_raw_value = value4; delay(18);
  if (moisture4_value < 0) {
    moisture4_value = 0;
  }
}

void water_flowers(int seconds_to_water)
{
  if ((relay1_state_flag == 0) && (relay2_state_flag == 0) && (relay3_state_flag == 0) && (relay4_state_flag == 0)){
    Serial.println("Nothing set as needed for watering. Set minimum 1 plant for watering.");
    return;
  }
  digitalWrite(pump, HIGH);
  delay(seconds_to_water * 1000);
  digitalWrite(pump, LOW); delay(10);
  relays_off();
}
void relays_off() {
  relay1_state_flag = 0;
  digitalWrite(relay1, LOW); delay(2);
  relay2_state_flag = 0;
  digitalWrite(relay2, LOW); delay(2);
  relay3_state_flag = 0;
  digitalWrite(relay3, LOW); delay(2);
  relay4_state_flag = 0;
  digitalWrite(relay4, LOW); delay(2);
}
