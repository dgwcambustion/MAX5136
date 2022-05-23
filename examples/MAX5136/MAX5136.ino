/*!
MAX5136: Quad 16-Bit Rail-to-Rail DACs in 16-Lead SSOP
@verbatim

*/


/*! @file
  @ingroup MAX5136
*/

#include "MAX5136.h"
#include <SPI.h>

//Pins
const int DAC_SS=8;
double DAC_val=0;
int i=0;

void setup()
// Setup the program
{
  Serial.begin(115200);         // Initialize the serial port to the PC
  Serial.println("setting up");
  SPI.begin();
  MAX5136_begin(DAC_SS);
  Serial.println("set up");
}


void loop()
{
  DAC_val=i*5;
  i++;
  if (DAC_val > 100){
    i=0; 
    DAC_val=0;
  }
  Serial.print("DAC val: ");
  Serial.println(DAC_val);
  Set_DAC_A(DAC_val);
  Set_DAC_B(DAC_val);
  Set_DAC_C(DAC_val);
  Set_DAC_D(DAC_val);
  Serial.println("DACs set");
  delay(2000);
}

void Set_DAC_A(double value){
  uint16_t dac_code = 65535.0*value/100.0;  //convert float to uint 
  MAX5136_write(DAC_SS, MAX5136_CMD_WRITE_UPDATE, MAX5136_DAC_A, dac_code); 
}

void Set_DAC_B(double value){
  uint16_t dac_code = 65535.0*value/100.0;  //convert float to uint 
  MAX5136_write(DAC_SS, MAX5136_CMD_WRITE_UPDATE, MAX5136_DAC_B, dac_code); 
}

void Set_DAC_C(double value){
  uint16_t dac_code = 65535.0*value/100.0;  //convert float to uint 
  MAX5136_write(DAC_SS, MAX5136_CMD_WRITE_UPDATE, MAX5136_DAC_C, dac_code); 
}

void Set_DAC_D(double value){
  uint16_t dac_code = 65535.0*value/100.0;  //convert float to uint 
  MAX5136_write(DAC_SS, MAX5136_CMD_WRITE_UPDATE, MAX5136_DAC_D, dac_code); 
