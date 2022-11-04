/*
 * SPI.c
 *
 * Created: 11/2/2022 9:47:40 PM
 * Technical Manager: Carlos Almagro
 */ 
//INCLUDE FILES
#include "SPI.h"
#include <avr/io.h>
#include <xc.h>
#include <ctype.h>
#include <avr/iom328pb.h>
//DEFINITIONS
#define DDR_SPI DDRE //DATA DIRECTION REGISTER PORT E
#define DDR_SPI_ONE DDRC  // DATA DIRECTION REGISTER PORT C
#define DD_MISO PE3 // PIN for MISO 
#define DD_SS PE2 // PIN for SS
#define DD_MISO PC0 // PIN for MISO
#define DD_SCK PC1 // PIN for SCK 
#define SPI_CMD_READ 0b11000000 //SPI Instruction for READ CMD
#define SPI_CMD_RX_READ 0b10010000 // SPI Instruction for READ RX BUFFER
#define SPI_CMD_WRITE 0b00000010 // SPI Instruction for WRITE CMD
#define SPI_CMD_READ_STATUS 0b10100000 // SPI Instruction for RX status



SPI_RESULTS SPI_INIT(void)//initialize SPI BUS 
{
	//SET MISO as an output
	DDR_SPI_ONE = (1 << DD_MISO) || (1 << DD_SCK);
	//Enable SPI, Master, Set clock rate fck/16
	SPCR1 = (1 << SPE) | (1 << MSTR) | (1 << SPR0);	
	return SUCCESS;
}
uint8_t SPI_TRANSMIT(uint8_t *data) //Transmit data 
{
	SPDR1 = data;
	while(!(SPSR1 & (1 << SPIF)));
	return SPDR1;
}
uint8_t SPI_READ(uint8_t *address) //read data from SPDR register
{
	uint8_t data;
	PORTE &= ~(1 << DD_SS);
	SPI_TRANSMIT(SPI_CMD_READ);
	SPI_TRANSMIT(address);
	uint8_t data = SPI_TRANSMIT(0xFF);
	PORTE |= (1<< DD_SS);
	return data;
}
SPI_RESULTS SPI_WRITE(uint8_t *address, uint8_t *data) // write address to slave address
{
	PORTE &= ~( 1<< DD_SS)
	SPI_TRANSMIT(SPI_CMD_WRITE); //Write Command 
	SPI_TRANSMIT(address); //Address location where to write the file to
	SPI_TRANSMIT(data); //Write data to the slave output
	SPI_TRANSMIT(0xFF);
	PORTE |= ( 1 << DD_SS);
	return SUCCESS;
}
SPI_RESULTS SPI_STATUS(void)
{
	uint8_t * status = (uint8_t)malloc(sizeof(uint8_t)); 
	PORTE &= ~(1 << DD_SS);// SS is pulled low 
	
	SPI_TRANSMIT(SPI_CMD_READ_STATUS); //Read Status Command
	status = SPI_TRANSMIT(0xFF); // receive and store status in a pointer for processing
	free(status); //free up the location of the status 
	PORTE |= (1 << DD_SS); //SS is pulled high
}


