
#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>
#include <Stepper.h>

int stepsPerRevolution = 200; // Número de pasos por revolución

class Stepper
{
public:
    Stepper(int pin1, int pin2, int pin3, int pin4);
    void calculate_movement(bool clockwise);
    {
        // Movemos hacia adelante 36 grados (360/10)
        // Recibimos el clockwise para saber si es hacia adelante o hacia atrás
        // Si es hacia adelante, el stepper gira en sentido horario
        // Si es hacia atrás, el stepper gira en sentido antihorario

        if (clockwise)
        {
            for (int i = 0; i < 36; i++)
            {
                this->stepper->step(1);
                delay(10);
            }
        }
        else
        {
            for (int i = 0; i < 36; i++)
            {
                this->stepper->step(-1);
                delay(10);
            }
        }
    }

private:
    int currentStep = 0;
};

#endif