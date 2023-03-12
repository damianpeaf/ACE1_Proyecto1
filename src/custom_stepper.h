#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>
#include <Stepper.h>

// Funciones
void calculate_movement_stepper(Stepper stepper, bool clockwise);

// Movimiento del motor
void calculate_movement_stepper(Stepper stepper, bool clockwise)
{
    // Mover 36 grados = 1 vuelta
    // Controlar que el ángulo no sea mayor a 36
    // Verificar la dirección
    // Si es positivo, girar en sentido horario
    // Si es negativo, girar en sentido antihorario

    int steps = 36; // 1 vuelta completa = 36 pasos
    if (clockwise)
    {
        stepper.setSpeed(100); // velocidad en rpm
        stepper.step(steps);   // girar en sentido horario
    }
    else
    {
        stepper.setSpeed(-100); // velocidad en rpm
        stepper.step(-steps);   // girar en sentido antihorario
    }
}

#endif