

void motor(int pin, int speed)
{
    speed = speed * 2.55;
    if(speed > 255)
    {
        speed = 255;
    }
    else if(speed < -255)
    {
        speed = -255;
    }
    if (pin == 1)
    {
        if (speed >= 0)
        {
            ledcWrite(6, 255 - abs(speed));
            ledcWrite(7, 255);
        }
        else if (speed < 0)
        {
            ledcWrite(6, 255);
            ledcWrite(7, 255 - abs(speed));
        }
    }
    else if (pin == 2)
    {
        if (speed >= 0)
        {
            ledcWrite(4, 255 - abs(speed));
            ledcWrite(5, 255);
        }
        else if (speed < 0)
        {
            ledcWrite(4, 255);
            ledcWrite(5, 255 - abs(speed));
        }
    }
    delay(1);
}
void stop()
{
    ledcWrite(6, 255);
    ledcWrite(7, 255);
    ledcWrite(4, 255);
    ledcWrite(5, 255);
}
void fd(int speed)
{
    motor(1,speed);
    motor(2,speed);
}
void sl(int speed)
{
    motor(1, -speed);
    motor(2,speed);
}
void sr(int speed)
{
    motor(1,speed);
    motor(2,-speed);
}
void tl(int speed)
{
    motor(1, 0);
    motor(2,speed);
}
void tr(int speed)
{
    motor(1,speed);
    motor(2,0);
}
void ao()
{
    motor(1,0);
    motor(2,0);
}