#pragma once

#include "Array.h"

namespace digits
{

constexpr uint8_t point = 0b00000001;
constexpr uint8_t a = 0b11101110;
constexpr uint8_t b = 0b00111110;
constexpr uint8_t c = 0b10011100;
constexpr uint8_t d = 0b01111010;
constexpr uint8_t e = 0b10011110;
constexpr uint8_t f = 0b10001110;

constexpr uint8_t zero = 0b11111100;
constexpr uint8_t one = 0b01100000;
constexpr uint8_t two = 0b11011010;
constexpr uint8_t three = 0b11110010;
constexpr uint8_t four = 0b01100110;
constexpr uint8_t five = 0b10110110;
constexpr uint8_t six = 0b10111110;
constexpr uint8_t seven = 0b11100000;
constexpr uint8_t eight = 0b11111110;
constexpr uint8_t nine = 0b11110110;
constexpr uint8_t ten = a;
constexpr uint8_t eleven = b;
constexpr uint8_t twelve = c;
constexpr uint8_t thirteen = d;
constexpr uint8_t fourteen = e;
constexpr uint8_t fifteen = f;

constexpr Array<uint8_t, 16> digits {
    {zero, one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen}
};

inline uint8_t reverse(uint8_t input)
{
    input = (input & 0xF0) >> 4 | (input & 0x0F) << 4;
    input = (input & 0xCC) >> 2 | (input & 0x33) << 2;
    input = (input & 0xAA) >> 1 | (input & 0x55) << 1;
    return input;
}

constexpr uint8_t addPoint(uint8_t digit)
{
    return digit | point;
}
}
