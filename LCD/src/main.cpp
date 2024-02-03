#include <Arduino.h>

#include "HD44780U.h"

HD44780U lcd {
    HD44780U::DataPins4Bit {4, 5, 6, 7},
     HD44780U::ControlPins {13, UINT8_MAX, 12}
};

void setup()
{
    lcd.reset(HD44780U::Function {HD44780U::BusMode::_4Bit, HD44780U::LineMode::_2, HD44780U::Font::_5x8});
    lcd.setDisplayControl({HD44780U::Activation::On});
    lcd.writeData('H');
    lcd.writeData('e');
    lcd.writeData('l');
    lcd.writeData('l');
    lcd.writeData('o');
    lcd.writeData(' ');
    lcd.writeData('W');
    lcd.writeData('o');
    lcd.writeData('r');
    lcd.writeData('l');
    lcd.writeData('d');
    lcd.writeData('!');
}

void loop() { }
