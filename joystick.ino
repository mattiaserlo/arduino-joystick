uint8_t buf[8] = { 0 }; // Keyboard report buffer
uint8_t old_buf[8] = { 0 }; 

#define BUTTON_FIRE_PIN   2
#define BUTTON_UP_PIN     3
#define BUTTON_LEFT_PIN   4
#define BUTTON_DOWN_PIN   5
#define BUTTON_RIGHT_PIN  6

#define BUTTON_FIRE_KEYCODE  0x1B
#define BUTTON_UP_KEYCODE    0x52
#define BUTTON_LEFT_KEYCODE  0x50
#define BUTTON_DOWN_KEYCODE  0x51
#define BUTTON_RIGHT_KEYCODE 0x4F

static int bufindex;

static int button_fire = 1;
static int button_up = 1;
static int button_left = 1;
static int button_down = 1;
static int button_right = 1;

static int button_fire_debounce_time = 0;
static int button_up_debounce_time = 0;
static int button_left_debounce_time = 0;
static int button_down_debounce_time = 0;
static int button_right_debounce_time = 0;

static int minimum_debounce_delta = 50; // millisec

void initPin(int pin)
{
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH); // connect internal pull-up
}

void setup()
{
  Serial.begin(9600);
  initPin(BUTTON_FIRE_PIN);
  initPin(BUTTON_UP_PIN);
  initPin(BUTTON_LEFT_PIN);
  initPin(BUTTON_DOWN_PIN);
  initPin(BUTTON_RIGHT_PIN);  
  pinMode(13, OUTPUT);
  delay(200);
}

void handleKey(int pin, int *button, int *last_debounce_time, unsigned char keyCode)
{
  int button_state;
  button_state = digitalRead(pin);
  
  if (button_state != *button)
  {
    int now = millis();
    if ((now - (*last_debounce_time)) > minimum_debounce_delta)
    {
      *last_debounce_time = now;
      *button = button_state;
      if (button_state == 0 && bufindex<8)
      {
        buf[bufindex++] = keyCode;
      }
    }
  }
}

void loop()
{
  buf[0] = 0x0;
  buf[1] = 0x0;
  buf[2] = 0x0;
  buf[3] = 0x0;
  buf[4] = 0x0;
  buf[5] = 0x0;
  buf[6] = 0x0;
  buf[7] = 0x0;
  
  bufindex = 2;
  
  handleKey(BUTTON_FIRE_PIN, &button_fire, &button_fire_debounce_time, BUTTON_FIRE_KEYCODE);
  handleKey(BUTTON_UP_PIN, &button_up, &button_up_debounce_time, BUTTON_UP_KEYCODE);
  handleKey(BUTTON_LEFT_PIN, &button_left, &button_left_debounce_time, BUTTON_LEFT_KEYCODE);
  handleKey(BUTTON_DOWN_PIN, &button_down, &button_down_debounce_time, BUTTON_DOWN_KEYCODE);
  handleKey(BUTTON_RIGHT_PIN, &button_right, &button_right_debounce_time, BUTTON_RIGHT_KEYCODE);

  if (buf[2] != old_buf[2] ||
      buf[3] != old_buf[3] ||
      buf[4] != old_buf[4] ||
      buf[5] != old_buf[5] ||
      buf[6] != old_buf[6] ||
      buf[7] != old_buf[7])
  {
        Serial.write(buf, 8);

        old_buf[2] = buf[2];
        old_buf[3] = buf[3];
        old_buf[4] = buf[4];
        old_buf[5] = buf[5];
        old_buf[6] = buf[6];
        old_buf[7] = buf[7];
  }
}
