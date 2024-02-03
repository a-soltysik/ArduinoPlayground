#pragma once

#include <inttypes.h>

#include "Array.h"

class HD44780U
{
public:
    struct DataPins8Bit
    {
        uint8_t db0;
        uint8_t db1;
        uint8_t db2;
        uint8_t db3;
        uint8_t db4;
        uint8_t db5;
        uint8_t db6;
        uint8_t db7;
    };

    struct DataPins4Bit
    {
        uint8_t db4;
        uint8_t db5;
        uint8_t db6;
        uint8_t db7;
    };

    struct ControlPins
    {
        uint8_t registerSelect;
        uint8_t rw;
        uint8_t enable;
    };

    enum class Activation : uint8_t
    {
        Off = 0,
        On = 1,
    };

    enum class Move : uint8_t
    {
        Left = 0,
        Right = 1,
    };

    enum class BusMode : uint8_t
    {
        _4Bit = 0,
        _8Bit = 1
    };

    enum class LineMode : uint8_t
    {
        _1 = 0,
        _2 = 1
    };

    enum class Font : uint8_t
    {
        _5x8 = 0,
        _5x10 = 1
    };

    struct EntryMode
    {
        Move cursor;
        bool shouldShiftDisplay;
    };

    struct DisplayControl
    {
        Activation display;
        Activation cursor;
        Activation blinking;
    };

    struct Shift
    {
        enum class Type : uint8_t
        {
            Cursor = 0,
            Display = 1
        };
        Type type;
        Move direction;
    };

    struct Function
    {
        BusMode busMode;
        LineMode lineMode;
        Font font;
    };

    struct State
    {
        bool isBusy;
        uint8_t addressCounter;
    };

    HD44780U(const DataPins8Bit& dataPins, ControlPins controlPins);
    HD44780U(const DataPins4Bit& dataPins, ControlPins controlPins);

    void reset(Function function);

    void clearDisplay();
    void returnHome();
    void setEntryMode(EntryMode entryMode);
    void setDisplayControl(DisplayControl displayControl);
    void shift(Shift shift);
    void setFunction(Function function);
    void setCharGeneratorAddress(uint8_t address);
    void setDisplayDataAddress(uint8_t address);
    State readBusyFlag();
    void writeData(uint8_t data);
    uint8_t readData();

private:
    void sendCommandInstruction(uint8_t instruction);
    void send(uint8_t registerSelect, uint8_t rw, uint8_t data);
    void commit() const;

    void write4Bits(uint8_t data);
    void write8Bits(uint8_t data);
    void writeBits(uint8_t data, uint8_t bitsCount);

    void initialize4BitMode();

    Array<uint8_t, 8> _dataPins;
    ControlPins _controlPins;
    Function _function {};
};
