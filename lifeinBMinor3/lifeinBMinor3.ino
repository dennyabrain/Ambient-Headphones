#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

const int myInput = AUDIO_INPUT_MIC;

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=163,132
AudioAnalyzeFFT1024      fft1024;      //xy=334,129
AudioConnection          inFft(i2s2, 0, fft1024, 0);

AudioSynthWaveformSine sine[8];
AudioEffectEnvelope envelope[8];
AudioMixer4              mixer2;         //xy=488,414
AudioMixer4              mixer1;         //xy=516,137
AudioOutputI2S           i2s1;           //xy=738,277
AudioConnection          patchCord5(sine[0], envelope[0]);
AudioConnection          patchCord1(sine[1], envelope[5]);
AudioConnection          patchCord2(sine[2], envelope[2]);
AudioConnection          patchCord3(sine[3], envelope[7]);
AudioConnection          patchCord6(sine[4], envelope[4]);
AudioConnection          patchCord7(sine[5], envelope[1]);
AudioConnection          patchCord4(sine[6], envelope[6]);
AudioConnection          patchCord8(sine[7], envelope[3]);
AudioConnection          patchCord9(envelope[6], 0, mixer2, 2);
AudioConnection          patchCord10(envelope[1], 0, mixer1, 1);
AudioConnection          patchCord11(envelope[3], 0, mixer1, 3);
AudioConnection          patchCord12(envelope[0], 0, mixer1, 0);
AudioConnection          patchCord13(envelope[2], 0, mixer1, 2);
AudioConnection          patchCord14(envelope[5], 0, mixer2, 1);
AudioConnection          patchCord15(envelope[7], 0, mixer2, 3);
AudioConnection          patchCord16(envelope[4], 0, mixer2, 0);
AudioConnection          patchCord17(mixer2, 0, i2s1, 1);
AudioConnection          patchCord18(mixer1, 0, i2s1, 0);

// GUItool: end automatically generated code

AudioControlSGTL5000 audioShield;

//float BMinScale[]={123,138.5,146.8,164.8,185,196,220,246.9};
float BMinScale[]={261,293,311,392,440,523,554,622};
float BMinSubScale[]={65,73,77.78,98,110,130,146.8,155};
float level[8];
bool isNoteOn[8];

void setup() {
  // put your setup code here, to run once:
  AudioMemory(30);
  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(0.8);
  
  fft1024.windowFunction(AudioWindowHanning1024);
  
  for(int i=0;i<8;i++){
    sine[i].amplitude(0.25);  
    sine[i].frequency(BMinScale[i]);
    envelope[i].attack(20);
    envelope[i].decay(50);
    envelope[i].release(100);
    isNoteOn[i]=false;
  }
  
  Serial.begin(9600);
 
}

void loop() {
  if(fft1024.available()){
    for(int i=0;i<8;i++){
      level[i]=fft1024.read(i);
      Serial.print(isNoteOn[i]);
     // Serial.print(' ');
    }
  }
  for(int i=0;i<8;i++){
    if(level[i]>0.2){
      //envelope[i].noteOn();
      //delay(500);
      if(isNoteOn[i]==false){
        //envelope[i].noteOn();
        isNoteOn[i]=true;
      }
    }else{
      //envelope[i].noteOff();
      //delay(1000);
      isNoteOn[i]=false;
    }
  }
  for(int i=0;i<8;i++){
    if(isNoteOn[i]==true){
      sine[i].amplitude(0.3);
      envelope[i].noteOn();
    }else{
      sine[i].frequency()
      sine[i].amplitude(0);
      //envelope[i].noteOff();      
    }
  }
  //delay(500);
  Serial.println();
}
