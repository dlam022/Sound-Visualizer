 #include <arduinoFFT.h>


#include <MD_MAX72xx.h>


#include <SPI.h>


MD_MAX72XX disp = MD_MAX72XX(MD_MAX72XX::FC16_HW, 10, 4);


arduinoFFT FFT = arduinoFFT(); //first create FFT object


double realComponent[64]; //real parts of FFT output, use 64 samples to generate our time domain array


double imagComponent[64]; //imaginary parts of FFT output


int spectralHeight[] = {0b00000000,0b10000000,0b11000000,


                        0b11100000,0b11110000,0b11111000,


                        0b11111100,0b11111110,0b11111111};


int index, c, value;


void setup()


{


  disp.begin();


  Serial.begin(9600);


}


void loop()


{


  int sensitivity = map(analogRead(A0),0,1023,35,100); 


  Serial.println (analogRead(A0));


  for(int i=0; i<64; i++) 


  {


    realComponent[i] = analogRead(A0)/sensitivity;  //stores the 64 reading to realcomponenet


    imagComponent[i] = 0;


  }


  FFT.Windowing(realComponent, 64, FFT_WIN_TYP_HAMMING, FFT_FORWARD); //pass into FFT algoirthm


  FFT.Compute(realComponent, imagComponent, 64, FFT_FORWARD);


  FFT.ComplexToMagnitude(realComponent, imagComponent, 64);


  for(int i=0; i<32; i++)


  {


    realComponent[i] = constrain(realComponent[i],0,80);


    realComponent[i] = map(realComponent[i],0,80,0,8);


    index = realComponent[i];


    value = spectralHeight[index];


    c = 31 - i;


    disp.setColumn(c, value);


  }


}
