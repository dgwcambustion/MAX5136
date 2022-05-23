/*!
MAX5136: Quad 16-Bit Rail-to-Rail DACs in 16-Lead SSOP

@verbatim

*/

#include <stdint.h>
#include <math.h>
#include <Arduino.h>
//#include "Linduino.h"
//#include "LT_SPI.h"
#include "MAX5136.h"
#include <SPI.h>

// Write the 16-bit dac_code to the MAX5136
void MAX5136_write(uint8_t cs, uint8_t dac_command, uint8_t dac_address, uint16_t dac_code)
{
  uint8_t data_array[3], rx_array[3];
  //LT_union_int16_2bytes data;
  //data.LT_uint16 = dac_code;

  data_array[0] = dac_command | dac_address;
  data_array[1] = highByte(dac_code); //data.LT_byte[1];
  data_array[2] = lowByte(dac_code); //data.LT_byte[0];
  
  //modified
  
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs,LOW);
  SPI.transfer(data_array, 3);
  digitalWrite(cs,HIGH);
  SPI.endTransaction();

  //spi_transfer_block(cs, data_array, rx_array, (uint8_t) 3);
  //SPI.transfer(cs, data_array, 3);
  //rx_array[0] = SPI.transfer(cs, data_array[0], SPI_CONTINUE);
  //rx_array[1] = SPI.transfer(cs, data_array[1], SPI_CONTINUE);
  //rx_array[2] = SPI.transfer(cs, data_array[2]);
 
}

// Calculate a MAX5136 DAC code given the desired output voltage and DAC address (0-3)
uint16_t MAX5136_voltage_to_code(float dac_voltage, float MAX5136_lsb, int16_t MAX5136_offset)
{
  int32_t dac_code;
  float float_code;
  float_code = dac_voltage / MAX5136_lsb;                                                             //! 1) Calculate the DAC code
  float_code = (float_code > (floor(float_code) + 0.5)) ? ceil(float_code) : floor(float_code);       //! 2) Round
  dac_code = (int32_t)float_code - MAX5136_offset;                                                    //! 3) Subtract offset
  if (dac_code < 0)                                                                                   //! 4) If DAC code < 0, Then DAC code = 0
    dac_code = 0;
  return ((uint16_t)dac_code);                                                                        //! 5) Cast DAC code as uint16_t
}

// Calculate the MAX5136 DAC output voltage given the DAC code and DAC address (0-3)
float MAX5136_code_to_voltage(uint16_t dac_code, float MAX5136_lsb, int16_t MAX5136_offset)
{
  float dac_voltage;
  dac_voltage = ((float)(dac_code + MAX5136_offset)* MAX5136_lsb);                                    //! 1) Calculates the dac_voltage
  return (dac_voltage);
}

void MAX5136_begin(uint8_t cs){
			pinMode(cs, OUTPUT);
			digitalWrite(cs, HIGH);
		}