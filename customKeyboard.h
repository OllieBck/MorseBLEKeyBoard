#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

void startAdv(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);

  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();

  /* Start Advertising
     - Enable auto advertising if disconnected
     - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
     - Timeout for fast mode is 30 seconds
     - Start(timeout) with timeout = 0 will advertise forever (until connected)

     For recommended advertising interval
     https://developer.apple.com/library/content/qa/qa1931/_index.html
  */
  /*
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  */
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

/****************************************************************************/

void blueToothSetup(void) {
  Bluefruit.begin();
  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("HelloMorse");

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52");
  bledis.begin();

  /* Start BLE HID
     Note: Apple requires BLE device must have min connection interval >= 20m
     ( The smaller the connection interval the faster we could send data).
     However for HID and MIDI device, Apple could accept min connection interval
     up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
     connection interval to 11.25  ms and 15 ms respectively for best performance.
  */
  blehid.begin();

  /* Set connection interval (min, max) to your perferred value.
     Note: It is already set by BLEHidAdafruit::begin() to 11.25ms - 15ms
     min = 9*1.25=11.25 ms, max = 12*1.25= 15 ms
  */
  /* Bluefruit.setConnInterval(9, 12); */

  // Set up and start advertising
  startAdv();
}

/****************************************************************************/

// 

class KeyboardKey
{
    int keyPin;      // the number of the button pin
    char keyUppercase;
    char keyLowercase;
    int pressSpeed;
    int keyFirstPress = true;

    // logs the last state of the button
    int change = 0;

    // current state
    int state = 0;

    unsigned long lastDebounceTime = 0;
    unsigned long heldTime = 0;
    unsigned long debounceDelay = 50;

  public:
    KeyboardKey (int pin, char valueLower, char valueUpper, int ditdahTimer)
    {
      keyPin = pin;
      keyLowercase = valueLower;
      keyUppercase = valueUpper;
      pressSpeed = ditdahTimer;
      pinMode(keyPin, INPUT);
    }

    void Press(boolean isShiftPressed)
    {
      int keyState = digitalRead(keyPin);
      boolean shiftCheck = isShiftPressed;
      int keyValue;
      pressSpeed = speedTyper;

      if (isShiftPressed){
        keyValue = keyUppercase;
      }
      else{
        keyValue = keyLowercase;
      }

      if (keyState == HIGH) {
        if (millis() - lastDebounceTime > debounceDelay) {
          if (keyFirstPress == true){
            blehid.keyPress(keyValue);
            blehid.keyRelease();
            keyFirstPress = false;
            lastDebounceTime = millis();
          }
          while (digitalRead(keyPin) == HIGH && millis() - lastDebounceTime > debounceDelay) {
            if (millis() - lastDebounceTime > pressSpeed) {
              blehid.keyPress(keyValue);
              blehid.keyRelease();
              lastDebounceTime = millis();
            }
          }
          lastDebounceTime = millis();
        }
      }
      else{
        keyFirstPress = true;
      }
    }
};


/****************************************************************************/

class ModifierKey
{
    // Class Member Variables
    // These are initialized at startup
    int keyPin;      // the number of the button pin

    // These maintain the current state
    int change = 0;
    int state = 0;

    boolean modifierState = false;

  public:
    ModifierKey (int pin)
    {
      keyPin = pin;
      pinMode(keyPin, INPUT);
    }

    boolean Check()
    {
      int keyState = digitalRead(keyPin);

      if (keyState)
      {
        state = 1;
      }

      else {
        state = 0;
      }

      if (state != change) {
        if (state == 1) {
          digitalWrite(LED_BUILTIN, HIGH);
          modifierState = !modifierState;
          delay(5);
        }
        else {
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
      change = state;
      return modifierState;
    }
};

/****************************************************************************/

void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here

  // Request CPU to enter low-power mode until an event/interrupt occurs
}
