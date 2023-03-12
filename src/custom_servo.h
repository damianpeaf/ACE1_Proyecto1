
#ifndef CUSTOM_SERVO_H
#define CUSTOM_SERVO_H

#include <Arduino.h>
#include <Servo.h>

class Servo
{
public:
    Servo();
    void attach(int pin);
    void write(int angle);
    void detach();
    void calculateMovement(int angle)
    {
        int steps = 0;
        if (angle > this->angle)
        {
            steps = angle - this->angle;
            for (int i = 0; i < steps; i++)
            {
                this->write(this->angle + i);
                delay(10);
            }
        }
        else if (angle < this->angle)
        {
            steps = this->angle - angle;
            for (int i = 0; i < steps; i++)
            {
                this->write(this->angle - i);
                delay(10);
            }
        }
    }
};

#endif
