#include <Arduino.h>
#include <pitches.h>

constexpr uint32_t NOTES[] = {
        NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
constexpr uint32_t DURATION = 500;
constexpr uint8_t BUZZER = 8;

void setup() {

}

void loop() {
    for (uint32_t note : NOTES) {
        tone(BUZZER, note, DURATION);
        delay(1000);
    }

    delay(2000);
}
