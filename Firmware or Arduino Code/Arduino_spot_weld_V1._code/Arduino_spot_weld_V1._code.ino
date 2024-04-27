/*
 * Libraries to download
 * 2. SSD1306 Splash Screen: https://javl.github.io/image2cpp/  settings: Horigontal, Plain byte
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OneButton.h" //we need the OneButton library to detect diffrent push functions.
#include <EEPROM.h>


#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

/******************************************************************/
// For measuring Voltage

#define Vref A0                   // Voltage sense for input wire.
int offset = 50;                  // To correct the voltage voltage loss in diode
unsigned long previousMillis = 0; // for volatage measuring every 5sec.
double voltage;                   // Variable that stores voltage value in Volts.

const unsigned char channel[] PROGMEM = {

    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x3d, 0xff, 0xc0, 0x3c, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x1c, 0xff, 0x80, 0x38, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x1c, 0xff, 0x80, 0x38, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x9c, 0xf8, 0x0f, 0x39, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x9c, 0xf8, 0x0f, 0x39, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9c, 0x3e, 0x33, 0xf9, 0xc0, 0x63, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9c, 0x3e, 0x73, 0xf9, 0xc0, 0x63, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9c, 0x1e, 0x73, 0xf9, 0xc0, 0x63, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9c, 0x07, 0xf3, 0x39, 0xc0, 0x63, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9c, 0x07, 0xf3, 0x39, 0xc0, 0x63, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9f, 0x06, 0x70, 0xf9, 0xc0, 0x63, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9f, 0x06, 0x70, 0xf9, 0xc0, 0x63, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x9c, 0x07, 0x8f, 0x39, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x9c, 0x07, 0x8f, 0x39, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x1c, 0x07, 0x8f, 0x38, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x1c, 0xc6, 0x73, 0x38, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x1c, 0xc4, 0x73, 0x38, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc1, 0xf0, 0x1f, 0xc6, 0x7f, 0xfe, 0x30, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc1, 0xf0, 0x1f, 0xee, 0x7f, 0xff, 0x30, 0x07, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x0f, 0xff, 0xff, 0xf0, 0x3f, 0xc1, 0x9f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe6, 0x0f, 0xff, 0xff, 0xf0, 0x3f, 0xc1, 0x9f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0x8e, 0x00, 0x03, 0xf0, 0x3c, 0x30, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0xcc, 0x00, 0x01, 0xf0, 0x38, 0x30, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0xde, 0x00, 0x01, 0xf0, 0x38, 0x30, 0x3f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xe0, 0x3e, 0x7f, 0x39, 0xce, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xe0, 0x3c, 0x3f, 0x99, 0xcc, 0x0f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0xcf, 0x9c, 0xf8, 0x1f, 0xc1, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf9, 0xcf, 0x9c, 0xf8, 0x0f, 0xc1, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe1, 0xfe, 0x7c, 0xe7, 0x80, 0x03, 0xef, 0x0f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc1, 0xfc, 0x7c, 0xc7, 0x80, 0x07, 0xcf, 0x9f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe1, 0xfc, 0x7c, 0xc7, 0x80, 0x07, 0x87, 0x9f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x9f, 0x38, 0x70, 0x1e, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x9f, 0x38, 0x70, 0x3e, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3c, 0x73, 0xfe, 0x0c, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3e, 0x73, 0xfe, 0x0e, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe1, 0xc0, 0x00, 0xce, 0x70, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc1, 0xc0, 0x00, 0xc6, 0x70, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x01, 0xff, 0x0f, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0x1f, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0x3f, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x1f, 0xc1, 0xff, 0x3d, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x1f, 0xc1, 0xff, 0x39, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x1d, 0xfe, 0x70, 0x3f, 0xc0, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x9c, 0xfe, 0x70, 0x3f, 0xc0, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x9c, 0xfc, 0x20, 0x1f, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9c, 0xc0, 0x0f, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9c, 0xc0, 0x0f, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9f, 0x07, 0x8c, 0xc0, 0x3c, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9f, 0x07, 0x8c, 0xc0, 0x3e, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9f, 0x07, 0xde, 0x40, 0x7c, 0x07, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9f, 0x39, 0xff, 0x39, 0xf1, 0x9f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc6, 0x03, 0x9f, 0x39, 0xff, 0x39, 0xf1, 0x9f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x9c, 0x00, 0x73, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0x9c, 0x00, 0x73, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x1c, 0xc0, 0x0c, 0xfd, 0xfc, 0x07, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x1c, 0xc0, 0x0c, 0xf9, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x1d, 0xe0, 0x1c, 0xfd, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

/******************************************************************/
// For Rotatory Encoder

volatile bool clk_State;  // For Rotatory Encoder
volatile bool Last_State; // For Rotatory Encoder
volatile bool dt_State;   // For Rotatory Encoder
#define clk 2             // Rotatory encoder clk pin to D2
#define dt 3              // Rotatory encoder dt pin to D3
#define push 4            // Push input of Rotatory Encoder

/******************************************************************/
// Declaring GPIOs of Input and Output Devices.

const int footSwitch = 5; // Input from Footswitch is attached to D5
const int ac_Switch = 6;  // Output at acSwitch(onboard Relay) is attached to D6
const int Ext_Relay = 7;  // Output at Ext_Relay is attached to D7
const int Mosfet = 8;     // Output at Mosfet is attached to D8
#define buzzer 9          // Output at Ext_Relay is attached to D9
int a = 0;

/******************************************************************/
// Declaring Variables for the code

int pulse;           // Saved variable to store how many times the weld will repeat.
int16_t counter;     // rotatory encoder adds increments to it.
int8_t pulsetime;    // saved Pulse set by user.
int8_t setpulsetime; // Unsaved variable to store the time value untill it is saved.
int footSwitchstate = LOW;
int8_t WeldMode;     // Set Mosfet Switch as default mode.
boolean LV_Shutdown; // To Enable/Disable low voltage shutdown.
bool Busy = false;
boolean failsafe = false;

double Alm_Volt; // To Set Low voltage.
int volt;

OneButton button(push, true); // attach a button on pin 4 to the library

/******************************************************************/
// Starting Setup

void setup()
{                     // [Starting Setup]
  Serial.begin(9600); // Wait Serial Monitor to start.
#define SSD1306_NO_SPLASH ;

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }     // Show initial display buffer contents on the screen --
        // the library initializes this with an Adafruit splash screen.

  display.display();
  delay(2000); // Pause for 2 seconds

  // Serial.println("Initialization Complete");

  /******************************************************************/
  // Declaring GPIOs as Inputs/Outputs

  pinMode(Vref, INPUT);       // Vref Pin is assigned as Input
  pinMode(push, INPUT);       // Define the pin as input
  pinMode(clk, INPUT);        // Define as input
  pinMode(dt, INPUT);         // Define as input
  pinMode(footSwitch, INPUT); // Define footSwitch as Input
  pinMode(ac_Switch, OUTPUT); // Define ac_Switch as Input
  pinMode(Ext_Relay, OUTPUT); // Define Ext_relay as Input
  pinMode(buzzer, OUTPUT);    // Define buzzer as output
  pinMode(Mosfet, OUTPUT);    // Define Ext_relay as Input

  // Call the interrupt when rotatory encoder is moved.
  attachInterrupt(digitalPinToInterrupt(clk), Rotatory, CHANGE);

  /******************************************************************/
  // Time Interrupt

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS11) | (1 << CS10);
  TIMSK1 = 0;
  TIMSK1 |= (1 << OCIE1A);

  Last_State = digitalRead(clk); // Scan Clk pin of Rotatory Encoder

  button.attachDoubleClick(doubleclick);  // link the function to be called on a doubleclick event.
  button.attachClick(singleclick);        // link the function to be called on a singleclick event.
  button.attachLongPressStart(longclick); // link the function to be called on a longpress event.

  pulsetime = EEPROM.read(1);
  pulse = EEPROM.read(2);
  WeldMode = EEPROM.read(3);
  LV_Shutdown = EEPROM.read(4);
  Alm_Volt = EEPROM.read(6); // to get the values in volt.
  Alm_Volt = Alm_Volt / 10;
  counter = pulsetime;
}

/******************************************************************/

void loop()
{

  button.tick();          // check the status of the button
  setpulsetime = counter; //[Set Pulse time]

  if (setpulsetime < 5)
  { //[set Minimum Pulse time to 5ms]
    setpulsetime = 5;
  }
  if (setpulsetime >= 70)
  { //[set Maximum Pulse time to 5ms]
    setpulsetime = 70;
  }

  /******************************************************************/
  // Call singleclick(Weld) Function when footswitch is pressed.

  if (digitalRead(footSwitch) == HIGH)
  { // footSwitch becomes HIGH when the foot button is pressed.
    if (footSwitchstate != HIGH)
    {
      singleclick(); // Run the single click function
      // failsafe = false;
    }

    footSwitchstate = HIGH;
  }
  else
  {
    footSwitchstate = LOW;
  }
  // End

  /******************************************************************/
  // Measure Voltage Every Second using millis function.

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000)
  {                                 // [Measure Voltage Every Second]
    previousMillis = currentMillis; // save the last time you measured the voltage
    if (Busy == false)
    {               // Avoid checking voltage during welding
      check_Volt(); // Run the Check Volt function.
    }
  }

  if (WeldMode == 1 && voltage <= Alm_Volt && LV_Shutdown == true)
  { // Activate low voltage for mosfet Weld.
    failsafe = true;
  }

  if (failsafe == true && a != 8)
  {
    low_voltage(); // Call for Low_Voltage Function
  }

  if (a == 8 || failsafe != true)
  {
    printText(); // Print the values in the OLED if Batt Low Volt is On.
  }

} // End Loop

/******************************************************************/

void singleclick()
{ // what happens when the button is clicked
  int i = 1;
  if (failsafe != true)
  {
    while (i <= pulse)
    { // If multiweld is activted, repeat welding process.
      if (Busy == false)
      {             // Continue only if device has finished welding
        delay(100); // Wait 100ms after previous weld to next weld.
        if (WeldMode == 1)
        {
          digitalWrite(Mosfet, HIGH);
        }
        if (WeldMode == 2)
        {
          digitalWrite(Ext_Relay, HIGH);
        }
        if (WeldMode == 3)
        {
          digitalWrite(ac_Switch, HIGH);
        }
        digitalWrite(13, HIGH);
        digitalWrite(buzzer, HIGH);

        TCNT1 = 0;
        OCR1A = pulsetime * 250;
        bool Busy = true; // Set Device to Busy
      }
      i++;
    }
    return;
  }
} // End Function

/******************************************************************/
void doubleclick()
{
  Settings(); //[Call settings function to display Setting options]
}

void longclick()
{ // what happens when buton is long-pressed

  pulsetime = setpulsetime; // Save the Changed Vaalue in multiweld.
  save_data();              // Call Save data function which stores values on eeprom.
  // Serial.println("Values Saved");
}

/******************************************************************/
// Voltage Measuring Function
void check_Volt()
{
  int volt = analogRead(Vref);
  voltage = map(volt, 0, 1023, 0, 2628) + offset; // 1V = 100increments
  voltage = voltage / 100;                        // divide  by 100 to get the decimal values.
}

ISR(TIMER1_COMPA_vect)
{ //[Deactivate the All Weldig Outputs after Set pulse Time]
  digitalWrite(Mosfet, LOW);
  digitalWrite(Ext_Relay, LOW);
  digitalWrite(ac_Switch, LOW);
  digitalWrite(13, LOW);
  digitalWrite(buzzer, LOW);
  Busy = false;
}

/******************************************************************/
// Rotatory Encoder Function Using hardware Interrupt.
// It's value can be accessed at any function.

void Rotatory()
{
  clk_State = digitalRead(clk);
  dt_State = digitalRead(dt);
  if (clk_State != Last_State)
  {
    /* If the data state is different to the clock state,
    that means the encoder is rotating clockwise */

    if (dt_State != clk_State)
    {
      // up=true;
      counter++; // Increase Counter by 1 increment.
    }
    else
    {
      //  down=true;
      counter--;
    }
  }
  Last_State = clk_State; // Updates the previous state of the data with the current state
  if (counter <= 0)
  {
    counter = 0;
  }

  if (counter >= 250)
  {
    counter = 250;
  }
}

/******************************************************************/
// Menu Item

void Settings()
{              // when rotatory is pressed two times, open this menu page.
  counter = 1; // To Always highlight 1st menu.
  int submenu = 0;
  int page = 1;
  boolean okay = false; // To detect button press in menu.
  boolean pushState = HIGH;

  //******************************************************************/
  while (true)
  { // run this code for infinity to display the settings menu

    // Read if button is pressed.
    if (digitalRead(push) == LOW)
    { // footSwitch becomes HIGH when the foot button is pressed.
      if (pushState != LOW)
      {
        okay = true; // Say button has pressed
      }

      pushState = LOW;
    }
    else
    {
      pushState = HIGH;
      okay = false;
    }

    // End
    //******************************************************************/

    // Draw Main Menu on top section of the display.

    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setCursor(37, 0);
    display.print("MAIN MENU");
    display.drawFastHLine(0, 10, 127, WHITE);
    // First Window of the menu (First Window Concists of 6 pages or options)  [Main Menu]

    if (submenu == 0) // First Option [Main Menu Screen]
    {

      if (counter >= 0 && counter <= 2)
      { //[Highlight Set Pulse Menu]
        display.setTextSize(1);
        display.setCursor(0, 13);
        display.setTextColor(BLACK, WHITE);
        display.print("> Set Pulse");
        display.setCursor(0, 23);
        display.setTextColor(WHITE, BLACK);
        display.print("> Set Mode");
        display.setCursor(0, 33);
        display.print("> Set Low Volt");
        display.setCursor(0, 43);
        if (LV_Shutdown == false)
        {
          display.print("> L-V Shutdown: OFF");
        }
        else
        {
          display.print("> L-V Shutdown: ON");
        }
        page = 1;
      }

      if (counter > 2 && counter <= 4)
      { //[Highlight Select Weldig Mode Menu]
        display.setTextSize(1);
        display.setCursor(0, 13);
        display.setTextColor(WHITE);
        display.print("> Set Pulse");
        display.setCursor(0, 23);
        display.setTextColor(BLACK, WHITE);
        display.print("> Set Mode");
        display.setTextColor(WHITE);
        display.setCursor(0, 33);
        display.print("> Set Low Volt");
        display.setCursor(0, 43);
        if (LV_Shutdown == false)
        {
          display.print("> L-V Shutdown: OFF");
        }
        else
        {
          display.print("> L-V Shutdown: ON");
        }
        page = 2;
      }

      if (counter > 4 && counter <= 6)
      { //[Highlight Set Low VOlt Menu]
        display.setTextSize(1);
        display.setCursor(0, 13);
        display.setTextColor(WHITE);
        display.print("> Set Pulse");
        display.setCursor(0, 23);
        display.print("> Set Mode");
        display.setTextColor(BLACK, WHITE);
        display.setCursor(0, 33);
        display.print("> Set Low Volt");
        display.setTextColor(WHITE);
        display.setCursor(0, 43);
        if (LV_Shutdown == false)
        {
          display.print("> L-V Shutdown: OFF");
        }
        else
        {
          display.print("> L-V Shutdown: ON");
        }
        page = 3;
      }

      if (counter > 6 && counter <= 8)
      { //[Highlight Low Voltage Shutdown Menu]
        display.setTextSize(1);
        display.setCursor(0, 13);
        display.setTextColor(WHITE);
        display.print("> Set Pulse");
        display.setCursor(0, 23);
        display.print("> Set Mode");
        display.setCursor(0, 33);
        display.print("> Set Low Volt");
        display.setTextColor(BLACK, WHITE);
        display.setCursor(0, 43);
        if (LV_Shutdown == false)
        {
          display.print("> L-V Shutdown: OFF");
        }
        else
        {
          display.print("> L-V Shutdown: ON");
        }
        page = 4;
      }

      if (counter > 8 && counter <= 10)
      { //[Highlight About Menu]
        display.setTextSize(1);
        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 13);
        display.print("> Set Mode");
        display.setCursor(0, 23);
        display.print("> Set Low Volt");
        display.setCursor(0, 33);
        if (LV_Shutdown == false)
        {
          display.print("> L-V Shutdown: OFF");
        }
        else
        {
          display.print("> L-V Shutdown: ON");
        }
        display.setTextColor(BLACK, WHITE);
        display.setCursor(0, 43);
        display.print("> About");
        page = 5;
      }

      if (counter > 10)
      { //[Highlight Back Menu]
        display.setTextSize(1);
        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 13);
        display.print("> Set Low Volt");
        display.setCursor(0, 23);
        if (LV_Shutdown == false)
        {
          display.print("> L-V Shutdown: OFF");
        }
        else
        {
          display.print("> L-V Shutdown: ON");
        }
        display.setCursor(0, 33);
        display.print("> About");
        display.setCursor(0, 43);
        display.setTextColor(BLACK, WHITE);
        display.print("> Back");
        page = 6;
      }

      display.display();
    } // End Submenu=1 [Main Menu]

    //**********************************************************************************/

    if (submenu == 1) //[Sub-Option Folder for SET PULSE]
    {
      display.setTextSize(1);
      display.clearDisplay();

      if (counter >= 0 && counter <= 2) //[First option of Set Pulse]
      {
        display.setCursor(0, 0);
        display.setTextColor(BLACK, WHITE);
        display.print("> 1 Pulse");
        display.setCursor(0, 10);
        display.setTextColor(WHITE, BLACK);
        display.print("> 2 Pulses");
        display.setCursor(0, 20);
        display.print("> 3 Pulses");
        display.setCursor(0, 30);
        display.print("> 4 Pulses");
        page = 1;
      }

      if (counter > 2 && counter <= 4) //[Second option of Set Pulse]
      {
        display.setCursor(0, 0);
        display.setTextColor(WHITE, BLACK);
        display.print("> 1 Pulse");
        display.setCursor(0, 10);
        display.setTextColor(BLACK, WHITE);
        display.print("> 2 Pulses");
        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 20);
        display.print("> 3 Pulses");
        display.setCursor(0, 30);
        display.print("> 4 Pulses");
        page = 2;
      }

      if (counter > 4 && counter <= 6) //[Third option of Set Pulse]
      {
        display.setCursor(0, 0);
        display.setTextColor(WHITE, BLACK);
        display.print("> 1 Pulse");
        display.setCursor(0, 10);
        display.print("> 2 Pulses");
        display.setTextColor(BLACK, WHITE);
        display.setCursor(0, 20);
        display.print("> 3 Pulses");
        display.setTextColor(WHITE, BLACK);
        display.setCursor(0, 30);
        display.print("> 4 Pulses");
        page = 3;
      }

      if (counter > 6) //[Forth option of Set Pulse]
      {
        display.setCursor(0, 0);
        display.setTextColor(WHITE, BLACK);
        display.print("> 1 Pulse");
        display.setCursor(0, 10);
        display.print("> 2 Pulses");
        display.setCursor(0, 20);
        display.print("> 3 Pulses");
        display.setTextColor(BLACK, WHITE);
        display.setCursor(0, 30);
        display.print("> 4 Pulses");
        page = 4;
      }
    }

    //**********************************************************************************/

    if (submenu == 2) //[Sub-Option Folder for Set Mode]
    {

      // Draw Set Weld Mode on top section of the display.
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(WHITE, BLACK);
      display.setCursor(25, 0); //[Center Aligned]
      display.print("Set Weld Mode");
      display.drawFastHLine(0, 10, 127, WHITE);

      if (counter >= 0 && counter <= 2) //[First option of Set Mode]
      {
        display.setCursor(0, 14);
        display.setTextColor(BLACK, WHITE);
        display.print("1. Batt Weld");
        display.setCursor(0, 24);
        display.setTextColor(WHITE, BLACK);
        display.print("2. Ext Relay");
        display.setCursor(0, 34);
        display.print("3. Ac Switch");
        page = 1;
      }

      if (counter > 2 && counter <= 4) //[Second option of Set Mode]
      {
        display.setCursor(0, 14);
        display.setTextColor(WHITE, BLACK);
        display.print("1. Batt Weld");
        display.setCursor(0, 24);
        display.setTextColor(BLACK, WHITE);
        display.print("2. Ext Relay");
        display.setCursor(0, 34);
        display.setTextColor(WHITE, BLACK);
        display.print("3. Ac Switch");
        page = 2;
        //   okay=false;
      }

      if (counter > 4) //[Third option of Set Mode]
      {
        display.setCursor(0, 14);
        display.setTextColor(WHITE, BLACK);
        display.print("1. Batt Weld");
        display.setCursor(0, 24);
        display.print("2. Ext Relay");
        display.setCursor(0, 34);
        display.setTextColor(BLACK, WHITE);
        display.print("3. Ac Switch");
        page = 3;
        //   okay=false;
      }
    } // End Submenu = 2

    //**********************************************************************************/

    if (submenu == 3) //[Sub-Option Folder for Low Voltage]
    {
      submenu = 0;
      counter = Alm_Volt * 10; // Sync rotary with previously set value
      bool n = false;
      pushState = LOW;

      while (true)
      { // run this loop for infinity untill the push button is pressed.

        display.setTextSize(1);
        display.clearDisplay();
        display.setTextColor(WHITE, BLACK);
        display.setCursor(31, 0);
        display.print("Set Low V");
        display.drawFastHLine(0, 10, 127, WHITE);

        Alm_Volt = map(counter, 0, 200, 0, 2000);
        Alm_Volt = Alm_Volt / 100;

        display.setTextSize(2);

        display.setCursor(0, 20);
        display.print("Volt:");
        display.println(Alm_Volt);

        if (digitalRead(push) == LOW)
        { //[Read if button is pressed]
          if (pushState != LOW)
          {
            n = true; // Break while loop.
          }
          pushState = LOW;
        }
        else
        {
          pushState = HIGH;
          n = false;
        }
        if (n == true)
        { // If button is pressed, end while loop.
          counter = 6;
          break;
        }

        display.display();
        delay(100);
      }
    } // End submenu=3

    //**********************************************************************************/

    if (submenu == 4)
    { //[Toggle Low Voltage Shutdown]
      okay = false;
      LV_Shutdown = !LV_Shutdown; // Inverse the Shutdown State.
      submenu = 0;
      counter = 8;
      if (LV_Shutdown == false)
      {
        failsafe = false;
      }
    } // End Submenu

    //**********************************************************************************/

    if (submenu == 5) //[Sub-Option Folder for About]
    {
      display.fillScreen(BLACK);
      submenu = 0;
      counter = 10;
      okay = false;

      display.drawBitmap(0, 0, channel, 128, 64, WHITE);
      display.display();
      delay(5000);

    } // End submenu=5

    if (submenu == 6)
    {                         //[Sub-Option Folder for Back]
      counter = setpulsetime; // Reset Counter
      break;                  //[Exit the loop and go back to home Screen]
    }                         // End submenu=6;

    display.display();

    //*********************************************************************/
    // Actions for the menu and Submenu

    //*********************************************************************/
    // From Main menu to secondary menu.
    if (okay == true)
    { // [Action for Set Pulse Menu]
      if (submenu == 0)
      {
        if (page == 1)
        {
          submenu = 1;
          counter = 0;
          okay = false;
          delay(100);
        }

        if (page == 2)
        {
          submenu = 2;
          counter = 0;
          okay = false;
          delay(100);
        }

        if (page == 3) //[Set Alarm VOltage]
        {
          submenu = 3;
          // counter=0; //Because we use counter to set VOltage value.
          okay = false;
          delay(100);
        }

        if (page == 4)
        {
          submenu = 4;
          counter = 0;
          okay = false;
          delay(100);
        }

        if (page == 5)
        {
          submenu = 5;
          counter = 1;
          okay = false;
          delay(100);
        }

        if (page == 6)
        {
          submenu = 6;
          counter = 1;
          okay = false;
          delay(100);
        }
      }
    }

    if (okay == true)
    {
      if (submenu == 1)
      { //[Send User back to main menu]
        if (page == 1)
        {
          submenu = 0;
          counter = 1;
          okay = false;
          pulse = 1; //[1 Pulse Mode]
          delay(100);
        }
        if (page == 2)
        {
          submenu = 0;
          counter = 1;
          okay = false;
          pulse = 2; //[2 Pulse Mode]
        }
        if (page == 3)
        {
          submenu = 0;
          counter = 1;
          okay = false;
          pulse = 3; //[3 Pulse Mode]
          break;
        }
        if (page == 4)
        {
          submenu = 0;
          counter = 1;
          okay = false;
          pulse = 4; //[4 Pulse Mode]
        }
      }

      //*************************************************************************************/

      if (submenu == 2)
      { // [Action for Set Set Mode]
        if (page == 1)
        {
          submenu = 0;
          counter = 6;
          okay = false;
          WeldMode = 1; //[Batt Weld]
          delay(100);
        }
        if (page == 2)
        {
          submenu = 0; // Main Menu
          counter = 2;
          okay = false;
          WeldMode = 2; //[Ext.relay]
          delay(100);
        }
        if (page == 3)
        {
          submenu = 0; // Main Menu
          counter = 2;
          okay = false;
          WeldMode = 3; //[Ac Switch]
          delay(100);
        }
      }

      if (submenu == 5)
      { // [Action for About]
        if (page == 1)
        {
          submenu = 0;
          counter = 2;
          okay = false;
          delay(100);
        }
      }

    } // End of all the menus

  }            // End While loop
  save_data(); //[Save the Updated data to EEPROM]
} // End Settings Void.

//*************************************************************************************/
// Print Values to OLED on Home Screeen.

void printText()
{
  display.clearDisplay();

  display.drawLine(0, 10, 127, 10, WHITE);
  display.drawLine(0, 50, 127, 50, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(128 - 36, 0);
  display.print(voltage); //[Display Input Voltage]
  display.setCursor(127 - 6, 0);
  display.println("V");

  display.setCursor(0, 0);
  display.print("Mode: ");
  display.println(WeldMode); //[Display Weld Mode]

  if (failsafe == false)
  {                         // show pulse time if failsafe is deactivated.
    display.setTextSize(4); //[Display Pulse Time]
    display.setCursor(3, 16);
    display.println(setpulsetime);
    display.setTextSize(2);

    if (setpulsetime < 10)
    {
      display.setTextColor(WHITE, BLACK);
      display.setCursor(25, 28);
      display.println("ms");
    }
    else
    {
      display.setTextColor(WHITE, BLACK);
      display.setCursor(50, 28);
      display.println("ms");
    }

    display.drawRoundRect(85, 14, 43, 33, 5, WHITE); //[Display Pulse Quantity in Round Rectangle.]
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(92, 19);
    display.print(pulse);
    display.setCursor(110, 28);
    display.setTextSize(2);
    display.print("P");
  }
  else
  {
    display.setCursor(10, 20);
    display.setTextSize(2);
    display.print("Batt Low!");
  }

  display.setCursor(5 + 20, 55); //[Display Set Low Voltage,]
  display.setTextSize(1);
  display.print("LV: ");
  display.print(Alm_Volt);
  display.print("V");

  display.drawRoundRect(65 + 20, 53, 16, 10, 3, WHITE); //[Indicator for Low Voltage Shutdown Enable/disable]
  if (LV_Shutdown == true)
  {
    //(x,y, length, bredth, Color)
    display.fillRect(65 + 4 + 20, 56, 16 - 8, 4, WHITE);
  }
  else
  {
    display.fillRect(65 + 4 + 20, 56, 16 - 8, 4, BLACK);
  }
  display.fillRect(105, 52, 22, 11, BLACK); // To supress Display Noise

  display.drawRoundRect(55, 0, 20, 8, 3, WHITE); //(x,y, length, bredth, radius, color)
  if (pulsetime == setpulsetime)
  {
    display.drawRect(55 + 4, 3, 20 - 8, 2, WHITE); //(x,y, length, bredth, Color)
  }
  else
  {
    display.drawRect(55 + 4, 3, 20 - 8, 2, BLACK);
  }
  display.display();
}

void low_voltage()
{
  while (a < 8)
  {
    display.clearDisplay();
    display.drawRoundRect(6, 20, 114, 24, 4, WHITE);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(10, 25); //[Display Set Low Voltage,]
    display.setTextSize(2);
    display.print("Batt Low!");

    display.display();
    digitalWrite(buzzer, HIGH);
    delay(400);

    display.drawRoundRect(6, 20, 114, 24, 4, WHITE);
    display.setTextColor(BLACK, WHITE);
    display.setCursor(10, 25); //[Display Set Low Voltage,]
    display.setTextSize(2);
    display.print("Batt Low!");
    display.display();
    digitalWrite(buzzer, LOW);
    delay(200);
    a++;
  }
}

void save_data()
{ //[Save data to Eeprom if Changed]
  if (EEPROM.read(1) != pulsetime)
  {
    EEPROM.write(1, pulsetime);
  }
  if (EEPROM.read(2) != pulse)
  {
    EEPROM.write(2, pulse);
  }
  if (EEPROM.read(3) != WeldMode)
  {
    EEPROM.write(3, WeldMode);
  }
  if (EEPROM.read(4) != LV_Shutdown)
  {
    EEPROM.write(4, LV_Shutdown);
  }
  volt = Alm_Volt * 10;

  if (EEPROM.read(6) != volt)
  {
    EEPROM.write(6, volt);
  }

  /*
  if (Alm_Volt != EEPROM_readAnything(6, Alm_Volt)){
   EEPROM_writeAnything(6, Alm_Volt);
  }
  */
}
