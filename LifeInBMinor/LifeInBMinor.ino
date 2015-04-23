#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=139,91
AudioMixer4              mixer1;         //xy=312,134
AudioOutputI2S           i2s2;           //xy=392,32
AudioAnalyzeFFT1024      fft1024;        //xy=467,147
AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
//AudioConnection          patchCord2(i2s1, 0, i2s2, 0);
AudioConnection          patchCord3(i2s1, 1, mixer1, 1);
//AudioConnection          patchCord4(i2s1, 1, i2s2, 1);
AudioConnection          patchCord5(mixer1, fft1024);
AudioControlSGTL5000     audioShield;    //xy=366,225
// GUItool: end automatically generated code

AudioSynthWaveformSine   sine2;          //xy=81,140
AudioSynthWaveformSine   sine4;          //xy=81,245
AudioSynthWaveformSine   sine1;          //xy=83,86
AudioSynthWaveformSine   sine3;          //xy=83,193
AudioMixer4              mixer2;         //xy=271,118

AudioEffectEnvelope env1;
AudioEffectEnvelope env2;
AudioEffectEnvelope env3;
AudioEffectEnvelope env4;

AudioConnection patchCordA(sine1,env1);
AudioConnection patchCordB(sine2,env2);
AudioConnection patchCordC(sine3,env3);
AudioConnection patchCordD(sine4,env4);

AudioConnection          patchCord8(env1, 0, mixer2, 0);
AudioConnection          patchCord6(env2, 0, mixer2, 1);
AudioConnection          patchCord9(env3, 0, mixer2, 2);
AudioConnection          patchCord7(env4, 0, mixer2, 3);

AudioConnection patchCord10(mixer2,0,i2s2,0);
AudioConnection patchCord11(mixer2,0,i2s2,1);


//const int myInput = AUDIO_INPUT_LINEIN;
const int myInput = AUDIO_INPUT_MIC;


// The scale sets how much sound is needed in each frequency range to
// show all 8 bars.  Higher numbers are more sensitive.
float scale = 60.0;

// An array to hold the 16 frequency bands
float level[16];

void setup() {
  // Audio requires memory to work.
  AudioMemory(20);

  // Enable the audio shield and set the output volume.
  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(0.8);

  // configure the mixer to equally add left & right
  mixer2.gain(0, 1);
  mixer2.gain(1, 1);
  mixer2.gain(2, 1);
  mixer2.gain(3, 1);
  
  sine1.frequency(220);
  sine1.amplitude(0.2);
  sine2.frequency(123);
  sine2.amplitude(0.2);
  sine3.frequency(146.8);
  sine3.amplitude(0.2);
  sine4.frequency(164.8);
  sine4.amplitude(0.2);
  
  env1.attack(9.2);
  env1.hold(0);
  env1.decay(31.4);
  env1.sustain(0.6);
  env1.release(84.5);
  
  env2.attack(9.2);
  env2.hold(0);
  env2.decay(31.4);
  env2.sustain(0.6);
  env2.release(84.5);
  
  env3.attack(9.2);
  env3.hold(0);
  env3.decay(31.4);
  env3.sustain(0.6);
  env3.release(84.5);
  
  env4.attack(9.2);
  env4.hold(0);
  env4.decay(31.4);
  env4.sustain(0.6);
  env4.release(84.5);
  
}


void loop() {
  if (fft1024.available()) {
    // read the 512 FFT frequencies into 16 levels
    // music is heard in octaves, but the FFT data
    // is linear, so for the higher octaves, read
    // many FFT bins together.
   /* level[0] =  fft1024.read(0);
    level[1] =  fft1024.read(1);
    level[2] =  fft1024.read(2, 3);
    level[3] =  fft1024.read(4, 6);
    level[4] =  fft1024.read(7, 10);
    level[5] =  fft1024.read(11, 15);
    level[6] =  fft1024.read(16, 22);
    level[7] =  fft1024.read(23, 32);
    level[8] =  fft1024.read(33, 46);
    level[9] =  fft1024.read(47, 66);
    level[10] = fft1024.read(67, 93);
    level[11] = fft1024.read(94, 131);
    level[12] = fft1024.read(132, 184);
    level[13] = fft1024.read(185, 257);
    level[14] = fft1024.read(258, 359);
    level[15] = fft1024.read(360, 511);*/
   
    level[0] =  fft1024.read(0);
    level[1] =  fft1024.read(1);
    level[2] =  fft1024.read(2);
    level[3] =  fft1024.read(3);
    level[4] =  fft1024.read(4);
    level[5] =  fft1024.read(5);
    level[6] =  fft1024.read(6);
    level[7] =  fft1024.read(7);
    level[8] =  fft1024.read(8);
    level[9] =  fft1024.read(9);
    level[10] = fft1024.read(10);
    level[11] = fft1024.read(11);
    level[12] = fft1024.read(12);
    level[13] = fft1024.read(13);
    level[14] = fft1024.read(14);
    level[15] = fft1024.read(15);
 
     if(level[2]<0.3){
       sine2.amplitude(0);
       env2.noteOff();
     }else{
       sine2.amplitude(level[3]);
       env2.sustain(level[3]);
       env2.noteOn();
     }
     
     if(level[4]<0.3){
       sine1.amplitude(0);
       env1.noteOff();
     }else{
       //sine1.amplitude(level[2]);
       env1.sustain(level[2]);
       env1.noteOff();
     }
     
     if(level[5]<0.3){
       sine3.amplitude(0);
       env3.noteOff();
     }else{
       sine3.amplitude(level[4]);
       env3.sustain(level[4]);
       env3.noteOff();
     }
     
     if(level[6]<0.3){
       sine4.amplitude(0);
       env4.noteOff();
     }else{
       sine4.amplitude(level[5]);
       env4.sustain(level[5]);
       env4.noteOff();
     }
     
    // sine3.amplitude(level[4]);
    // sine4.amplitude(level[5]);
 
    for (int i=0; i<16; i++) {
      Serial.print(level[i]);
      Serial.print(' ');
    }
    Serial.print(" cpu:");
    Serial.println(AudioProcessorUsageMax());
  }
}

//


