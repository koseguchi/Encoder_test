#define pin_A 7
#define pin_B 8
#define resolution 512.0

double direction = 0;
bool Astate = LOW;
bool Bstate = LOW;
uint8_t cur_state = 0;
uint8_t prev_state = 0;

uint8_t getstate()
{
    Astate = !digitalRead(pin_A);
    Bstate = !digitalRead(pin_B);
    if (Astate == HIGH)
    {
        if(Bstate == HIGH)//A:HIGH, B:HIGH
        {
            return 2;
        }
        else//A:HIGH, B:LOW
        {
            return 1;
        }
    }
    else
    {
        if(Bstate == HIGH)//A:LOW, B:HIGH
        {
            return 3;
        }
        else//A:LOW, B:LOW
        {
            return 0;
        }
    }
}

void setup()
{
    pinMode(pin_A, INPUT_PULLUP);
    pinMode(pin_B, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{
    cur_state = getstate();
    Serial.print("STATE : ");
    Serial.println(cur_state);
    Serial.println("\0");
    if(cur_state != prev_state)
    {
        if((cur_state == prev_state -1) || (cur_state == 0 && prev_state == 3))
        {
            direction -= 360.0 / resolution / 2.0;
        }
        else
        {
            direction += 360.0 / resolution / 2.0;
        }
    }
    Serial.print("DIRECTION : ");
    Serial.println(direction);
    Serial.println("\0");
    prev_state = cur_state;
}