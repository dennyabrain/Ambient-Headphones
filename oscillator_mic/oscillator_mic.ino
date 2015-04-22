#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

const int myInput = AUDIO_INPUT_MIC;
int scale[]={196,233,261,277,293,349,392};

AudioInputI2S        audioInput;  
AudioAnalyzePeak     peak_L;
AudioAnalyzePeak     peak_R;
AudioSynthWaveformSine   sine1;          //xy=319,331
AudioOutputI2S           i2s2;           //xy=558,125
AudioConnection          patchCord1(sine1, 0, i2s2, 0);
AudioConnection          patchCord2(sine1, 0, i2s2, 1);
AudioConnection c1(audioInput,0,peak_L,0);
AudioConnection c2(audioInput,1,peak_R,0);
// GUItool: end automatically generated code

AudioControlSGTL5000 audioShield;

elapsedMillis fps;

void setup(){
  AudioMemory(6);
  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(0.5);
  
  sine1.amplitude(0.0);
  sine1.frequency(220);
}

void loop(){
  if(fps>200){
    if(peak_L.available() && peak_R.available()){
      fps = 0;
      uint8_t leftPeak = peak_L.read();
      //uint8_t rightPeak = peak_R.read();
      
      if(leftPeak>0.1){
        int i = int(random(0,6));
        sine1.frequency(scale[i]);
        sine1.amplitude(0.4);
      }else{
        sine1.amplitude(0.0);
      }
    }
  }
}
