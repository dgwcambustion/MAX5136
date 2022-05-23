/*!
MAX5136: Quad 16-Bit Rail-to-Rail DACs in 16-Lead SSOP

@verbatim


*/

/*! @file
  @ingroup MAX5136
  Header for MAX5136: Quad 16-Bit Rail-to-Rail DACs in 16-Lead SSOP
*/


#ifndef MAX5136_H
#define MAX5136_H

#include <SPI.h>

//! Define the SPI CS pin
#define MAX5136_CS 10

//! @name MAX5136 Command Codes
//!@{
#define  MAX5136_CMD_NO_OPERATION        0x00  //!< No operation
#define  MAX5136_CMD_UPDATE              0x01  //!< Move contents of input to DAC registers indicated by 1’s. No effect on registers indicated by 0’s.
#define  MAX5136_CMD_CLEAR               0x02  //!< Software clear.
#define  MAX5136_CMD_POWER_DOWN          0x03  //!< Power down n
#define  MAX5136_CMD_OPTIMIZE        	 0x05  //!< Optimize DAC linearity.
#define  MAX5136_CMD_WRITE		         0x10  //!< Write to selected input registers (DAC output not affected).
#define  MAX5136_CMD_WRITE_UPDATE        0x30  //!< Write to selected input and DAC registers, DAC outputs updated(writethrough).
//!@}

// Which DAC to operate on
#define  MAX5136_DAC_A     0x01
#define  MAX5136_DAC_B     0x02
#define  MAX5136_DAC_C     0x04
#define  MAX5136_DAC_D     0x08
#define  MAX5136_DAC_ALL   0x0F
//

//! Write the 16-bit dac_code to the MAX5136
//! @return Void
void MAX5136_write(uint8_t cs,                            //!< Chip Select Pin
                   uint8_t dac_command,                   //!< Command Nibble, left-justified, lower nibble set to zero
                   uint8_t dac_address,                   //!< DAC Address Nibble, right justified, upper nibble set to zero
                   uint16_t dac_code                      //!< 16-bit DAC code
                  );

//! Calculate a MAX5136 DAC code given the desired output voltage and DAC address (0-3)
//! @return The 16-bit code to send to the DAC
uint16_t MAX5136_voltage_to_code(float dac_voltage,       //!< Voltage to send to DAC
                                 float MAX5136_lsb,       //!< LSB value (volts)
                                 int16_t MAX5136_offset   //!< Offset (volts)
                                );

//! Calculate the MAX5136 DAC output voltage given the DAC code, offset, and LSB value
//! @return Calculated voltage
float MAX5136_code_to_voltage(uint16_t dac_code,          //!< DAC code
                              float MAX5136_lsb,          //!< LSB value (volts)
                              int16_t MAX5136_offset      //!< Offset (volts)
                             );

//! Configure SS pin MAX5136
//! @return Void
void MAX5136_begin(uint8_t cs                            //!< Chip Select Pin
                  );

#endif //MAX5136_H