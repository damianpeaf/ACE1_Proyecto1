
#ifndef CUSTOM_SERVO_H
#define CUSTOM_SERVO_H

#include <Arduino.h>
#include <Servo.h>

// Funciones
void calculate_movement_servo(Servo servo, int angle);

// Movimiento del servo
void calculate_movement_servo(Servo servo, int angle)
{
    // Mover 36 grados = 1 vuelta
    // Controlar que el ángulo no sea mayor a 36
    // Verificar la dirección
    // Si es positivo, girar en sentido horario
    // Si es negativo, girar en sentido antihorario

    int steps = 36; // 1 vuelta completa = 36 pasos
    if (angle > 0)
    {
        servo.write(angle); // girar en sentido horario
    }
    else
    {
        servo.write(angle); // girar en sentido antihorario
    }
}

#endif
