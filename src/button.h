#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
    public:
        
        Button(int pin){
            this->pin = pin;
        }

        void setup(){
            pinMode(this->pin, INPUT);
        }

        bool is_pressed(){
            if(state == false && digitalRead(pin) == HIGH){
                state = true;
                return true;
            }else if(state == true && digitalRead(pin) == LOW){
                state = false;
                return false;
            }else{
                return false;
            }
        }

    private:
        int pin;
        bool state = false;
};

#endif