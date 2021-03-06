/***************************************************************************//**
 *   @file   Communication.h
 *   @brief  Header file of Communication Driver for RENESAS RX62N Processor.
 *   @author DBogdan (dragos.bogdan@analog.com)
********************************************************************************
 * Copyright 2012(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************
 *   SVN Revision: 537
*******************************************************************************/
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "sys.h"

/******************************************************************************/
/* GPIO Definitions                                                           */
/******************************************************************************/
#define ADI_CS_PIN        // Add your code here
#define ADI_CS_PIN_OUT    // Add your code here
#define ADI_CS_LOW        // Add your code here
#define ADI_CS_HIGH       // Add your code here
#define ADI_RDY_PIN       // Add your code here
     
//#define AD9833_FSYNC 	GPIO_Pin_3    //A3
//#define AD9833_SCLK 	GPIO_Pin_4			//A4
//#define AD9833_SDATA  GPIO_Pin_5 		//A5
#define AD9833_FSYNC 	PAout(6)
#define AD9833_SCLK 	PAout(4)
#define AD9833_SDATA 	PAout(5)
	/*???????? */ 
	#define PORT_FSYNC	GPIOA
	#define PIN_FSYNC	GPIO_Pin_6

	#define PORT_SCK	GPIOA
	#define PIN_SCK		GPIO_Pin_4

	#define PORT_DAT	GPIOA
	#define PIN_DAT		GPIO_Pin_5

	#define PORT_CS		GPIOB
	#define PIN_CS		GPIO_Pin_12  //??????????????

//****************************************************************

	#define FSYNC_0()		GPIO_ResetBits(PORT_FSYNC, PIN_FSYNC)
	#define FSYNC_1()		GPIO_SetBits(PORT_FSYNC, PIN_FSYNC)

	#define SCK_0()		GPIO_ResetBits(PORT_SCK, PIN_SCK)
	#define SCK_1()		GPIO_SetBits(PORT_SCK, PIN_SCK)

	#define DAT_0()		GPIO_ResetBits(PORT_DAT, PIN_DAT)
	#define DAT_1()		GPIO_SetBits(PORT_DAT, PIN_DAT)	

	#define CS_0()		GPIO_ResetBits(PORT_DAT, PIN_CS)	
	#define CS_1()		GPIO_SetBits(PORT_DAT, PIN_CS)	

//??????AD9833 GPIO
/******************************************************************************/
/* Functions Prototypes                                                       */
/******************************************************************************/
/* Initializes the SPI communication peripheral. */
unsigned char AD9833_SPI_Init(unsigned char lsbFirst,
                       unsigned long clockFreq,
                       unsigned char clockPol,
                       unsigned char clockPha);
/* Writes data to SPI. */
unsigned char AD9833_SPI_Write(unsigned char* data,
                        unsigned char bytesNumber);
/* Reads data from SPI. */
unsigned char AD9833_SPI_Read(unsigned char* data,
                       unsigned char bytesNumber);
#endif	// _COMMUNICATION_H_
