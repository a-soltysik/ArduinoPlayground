#include "HD44780U.h"

#include "Arduino.h"

void HD44780U::clearDisplay()
{
    static constexpr uint8_t instruction = 0b00000001;
    sendCommandInstruction(instruction);
    delayMicroseconds(2000);
}

void HD44780U::returnHome()
{
    static constexpr uint8_t instruction = 0b00000010;
    sendCommandInstruction(instruction);
    delayMicroseconds(2000);
}

void HD44780U::setEntryMode(EntryMode entryMode)
{
    static constexpr uint8_t instruction = 0b00000100;
    static constexpr uint8_t idShift = 1;
    static constexpr uint8_t displayShift = 0;
    const uint8_t data = instruction |  //
                         (static_cast<uint8_t>(entryMode.cursor) << idShift) |
                         (entryMode.shouldShiftDisplay << displayShift);
    sendCommandInstruction(data);
}

void HD44780U::setDisplayControl(DisplayControl displayControl)
{
    static constexpr uint8_t instruction = 0b00001000;
    static constexpr uint8_t displayShift = 2;
    static constexpr uint8_t cursorShift = 1;
    static constexpr uint8_t blinkingShift = 0;
    const uint8_t data = instruction |  //
                         (static_cast<uint8_t>(displayControl.display) << displayShift) |
                         (static_cast<uint8_t>(displayControl.cursor) << cursorShift) |
                         (static_cast<uint8_t>(displayControl.blinking) << blinkingShift);

    sendCommandInstruction(data);
}

void HD44780U::shift(Shift shift)
{
    static constexpr uint8_t instruction = 0b00010000;
    static constexpr uint8_t typeShift = 3;
    static constexpr uint8_t directionShift = 2;

    const uint8_t data = instruction |  //
                         (static_cast<uint8_t>(shift.type) << typeShift) |
                         (static_cast<uint8_t>(shift.direction) << directionShift);

    sendCommandInstruction(data);
}

void HD44780U::setFunction(HD44780U::Function function)
{
    static constexpr uint8_t instruction = 0b00100000;
    static constexpr uint8_t busModeShift = 4;
    static constexpr uint8_t linesCountShift = 3;
    static constexpr uint8_t fontShift = 2;

    const uint8_t data = instruction |  //
                         (static_cast<uint8_t>(function.busMode) << busModeShift) |
                         (static_cast<uint8_t>(function.lineMode) << linesCountShift) |
                         (static_cast<uint8_t>(function.font) << fontShift);

    sendCommandInstruction(data);
}

void HD44780U::setCharGeneratorAddress(uint8_t address)
{
    static constexpr uint8_t instruction = 0b01000000;
    static constexpr uint8_t addressMask = 0b00000111;
    static constexpr uint8_t addressShift = 3;

    sendCommandInstruction(instruction | ((address << addressShift) & addressMask));
}

void HD44780U::setDisplayDataAddress(uint8_t address)
{
    static constexpr uint8_t instruction = 0b10000000;
    static constexpr uint8_t addressMask = 0b01111111;

    sendCommandInstruction(instruction | (address & addressMask));
}

HD44780U::State HD44780U::readBusyFlag()
{
    return {};
}

void HD44780U::writeData(uint8_t data)
{
    send(HIGH, LOW, data);
}

uint8_t HD44780U::readData()
{
    return {};
}

void HD44780U::sendCommandInstruction(uint8_t instruction)
{
    send(LOW, LOW, instruction);
}

void HD44780U::send(uint8_t registerSelect, uint8_t rw, uint8_t data)
{
    digitalWrite(_controlPins.registerSelect, registerSelect);

    if (_controlPins.rw != UINT8_MAX)
    {
        digitalWrite(_controlPins.rw, rw);
    }

    if (_function.busMode == BusMode::_8Bit)
    {
        write8Bits(data);
    }
    else
    {
        write4Bits(data >> 4);
        write4Bits(data);
    }
}

void HD44780U::write4Bits(uint8_t data)
{
    writeBits(data, 4);
}

void HD44780U::write8Bits(uint8_t data)
{
    writeBits(data, 8);
}

void HD44780U::writeBits(uint8_t data, uint8_t bitsCount)
{
    for (uint8_t i = 0; i < bitsCount; i++)
    {
        digitalWrite(_dataPins[i], (data >> i) & 1);
    }
    commit();
}

void HD44780U::commit() const
{
    digitalWrite(_controlPins.enable, LOW);
    delayMicroseconds(1);
    digitalWrite(_controlPins.enable, HIGH);
    delayMicroseconds(1);
    digitalWrite(_controlPins.enable, LOW);
    delayMicroseconds(100);
}

void HD44780U::initialize4BitMode()
{
    write4Bits(0b0011);
    delayMicroseconds(5000);

    write4Bits(0b0011);
    delayMicroseconds(5000);

    write4Bits(0b0011);
    delayMicroseconds(150);  // TMP

    write4Bits(0b0010);
}

void HD44780U::reset(Function function)
{
    _function = function;

    pinMode(_controlPins.registerSelect, OUTPUT);
    if (_controlPins.rw != UINT8_MAX)
    {
        pinMode(_controlPins.rw, OUTPUT);
    }
    pinMode(_controlPins.enable, OUTPUT);

    for (uint8_t i = 0; i < ((_function.busMode == BusMode::_8Bit) ? uint8_t {8} : uint8_t {4}); ++i)
    {
        pinMode(_dataPins[i], OUTPUT);
    }

    delay(50);
    digitalWrite(_controlPins.registerSelect, LOW);
    digitalWrite(_controlPins.enable, LOW);
    if (_controlPins.rw != UINT8_MAX)
    {
        digitalWrite(_controlPins.rw, LOW);
    }
    if (_function.busMode == BusMode::_4Bit)
    {
        initialize4BitMode();
    }

    setFunction(_function);

    setDisplayControl({Activation::Off, Activation::Off, Activation::Off});
    clearDisplay();
    setEntryMode({Move::Right, false});
}

HD44780U::HD44780U(const HD44780U::DataPins8Bit& dataPins, HD44780U::ControlPins controlPins)
    : _dataPins{{
          dataPins.db0,
          dataPins.db1,
          dataPins.db2,
          dataPins.db3,
          dataPins.db4,
          dataPins.db5,
          dataPins.db6,
          dataPins.db7,
      }},
      _controlPins{controlPins}
{
}

HD44780U::HD44780U(const HD44780U::DataPins4Bit& dataPins, HD44780U::ControlPins controlPins) : _dataPins{{
        dataPins.db4,
        dataPins.db5,
        dataPins.db6,
        dataPins.db7,
            0, 0, 0, 0
        }},
   _controlPins{controlPins}
{
}
