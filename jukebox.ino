
/*

  LA Hacks 2014
  Project Name: JukeBox
  Description: A music visualization device, based on analog LED circuit that react to played music. Pattern of LED reaction, controlled digitally with
  Arduino micro-controller implementing the Fast Fourier Transform (FFT) Library
  
  By: Louis Lesmana (Software Specialist), Dean Mahdi (Hardware Specialist), Edrick Joe (Hardware Specialist) (UCSD)
  
  Author: Louis Lesmana

*/

#include <fix_fft.h>//fft library using 8 bit values

#define NUMLED 13 //Number of LEDS connected to pin
#define HWVLENGTH 128// half sinewave wavelength
#define NUM_OF_FREQ 14//number of frequency that the analog audio will be classified into by the fft
#define ANALOG_PIN 3 //Pin location where music is inserted
#define CHOSEN_FREQUENCY 0//chosen frequency to visualize

int led[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};//LED corresponding to their connected pins
int anaRead;//real analog signal read

char real[HWVLENGTH], imaginary[HWVLENGTH];//real and imaginary arrays to be used by the fft 
                                           //library based on half wavelength of the sinewave
                   
char frequencyBands[NUM_OF_FREQ]; //The fourteen frequency level classified by the fft

//Setting up pins for the LED
void setup(){
  
  
  for(int i = 0; i < NUMLED; i++)
      pinMode(led[i], OUTPUT);//Setting microcontroller to process LED based on pins
    
  Serial.begin(9600);
  
}


//Setting pattern based on analog audio from pc
void loop(){
  
  //setting input signal
  for(int i = 0; i< HWVLENGTH ; i++){
    
    anaRead = analogRead(ANALOG_PIN);
    real[i] = anaRead; //assignin to real values as we read set of input signal
    imaginary[i] = 0; //no imaginary part in input signal
    
  }  
   
  fix_fft(real, imaginary, NUM_OF_FREQ/2, 0);//processing input to obtain output using fourier transform
  
  //obtaining the magnitude of readings 
  for(int i = 0; i < (HWVLENGTH/2); i++)
     real[i] = sqrt(real[i]*real[i] + imaginary[i]*imaginary[i] );
     
  //classifying frequencies, based on the average of the magnitude
  for(int i = 0; i < NUM_OF_FREQ; i++){
     frequencyBands[i] = real[i*4] + real[i*4+1] + real[i*4+2] + real[i*4+3];//bands based on average on four sample points on the sine wave
     frequencyBands[i] = map(frequencyBands[i], 0, 30, 0 ,9);// mapping values to the transformation itself
  }
  
  //Launch for visualization
  int setter = frequencyBands[CHOSEN_FREQUENCY];
  ledManager(setter);
  
  
}


//Manage the visualization of Led based on the given audio
void ledManager(int signal){
 
    switch ( signal) { 
      
        case 1:
        digitalWrite(led[0], HIGH);
        for(int i = 1; i< NUMLED-1 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[12], HIGH);
        break;
        case 2:
        digitalWrite(led[0], LOW);
        digitalWrite(led[1], HIGH);
        for(int i = 2; i< NUMLED-2 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[11], HIGH);
        digitalWrite(led[12], LOW);
        break;
        case 3:
        digitalWrite(led[0], LOW);
        digitalWrite(led[1], LOW);
        digitalWrite(led[2], HIGH);
        for(int i = 3; i< NUMLED-3 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[10], HIGH);
        break;
        case 4:
        digitalWrite(led[3], HIGH);
        for(int i = 4; i< NUMLED-4 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[4], HIGH);
        break;
        case 5:
        digitalWrite(led[0], HIGH);
        for(int i = 5; i< NUMLED-1 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[12], HIGH);
        break;
        case 6:
        digitalWrite(led[0], HIGH);
        for(int i = 6; i< NUMLED-1 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[12], HIGH);
        break;
        case 7:
        digitalWrite(led[0], HIGH);
        for(int i = 7; i< NUMLED-1 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[12], HIGH);
        break;
        case 8:
        digitalWrite(led[0], HIGH);
        for(int i = 8; i< NUMLED-1 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[12], HIGH);
        break;
        case 9:
        digitalWrite(led[0], HIGH);
        for(int i = 9; i< NUMLED-1 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[12], HIGH);
        break;
        case 10:
        digitalWrite(led[0], HIGH);
        for(int i = 10; i< NUMLED-1 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[12], HIGH);
        break;
        case 11:
        digitalWrite(led[0], HIGH);
        for(int i = 11; i< NUMLED-1 ; i++)
            digitalWrite(led[i], LOW);
        digitalWrite(led[12], HIGH);
        break;
        case 12:
        for(int i = 12; i< NUMLED ; i++){
            digitalWrite(led[i], HIGH);
            delay(100);
        }
        break;
        case 13:
        for(int i =13; i< NUMLED ; i++)
            digitalWrite(led[i], HIGH);
        break;
        default: 
        for(int i = 0; i< NUMLED ; i++)
            digitalWrite(led[i], LOW);
        break;
        
   
    }

}

