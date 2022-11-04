/*
 * SPI.h
 *
 * Created: 11/2/2022 9:44:12 PM
 * Technical Manager: Carlos Almagro
 */ 


#ifndef SPI_H_
#define SPI_H


enum SPI_RESULTS {SUCCESS, UNKNOWN, FAILURE};

void SPI_INIT(void); // Initialize SPI Bus
uint8_t SPI_TRANSMIT(uint8_t data) // SPI Communication
uint8_t SPI_READ(unit8_t address);
void SPI_WRITE(uint8_t address, uint8_t data)





#endif /* SPI_H_ */