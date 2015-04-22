#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=319,331
AudioOutputI2S           i2s2;           //xy=558,125
AudioConnection          patchCord1(sine1, 0, i2s2, 0);
AudioConnection          patchCord2(sine1, 0, i2s2, 1);
// GUItool: end automatically generated code

AudioControlSGTL5000 audioShield;

void setup(){
  AudioMemory(6);
  audioShield.enable();
  //audioShield.inputSelect(myInput);
  audioShield.volume(0.5);
  
  sine1.amplitude(0.3);
  sine1.frequency(220);
}

void loop(){
  
}
