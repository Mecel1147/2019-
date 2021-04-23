#include "AD9833.h"		// AD9833 definitions.
#include "delay.h"		// AD9833 definitions.
#include "Communication.h"

#define FCLK 25000000	//设置晶振频率
#define RealFreDat    268435456.0/FCLK//总的公式为 Fout=（Fclk/2的28次方）*28位寄存器的值

/***************************************************************************//**
 * @brief Initializes the SPI communication peripheral and resets the part.
 *
 * @return 1.
*******************************************************************************/
unsigned char AD9833_Init(void)
{
    AD9833_SPI_Init(0, 1000000, 1, 1);
    AD9833_SetRegisterValue(AD9833_REG_CMD | AD9833_RESET);
	
    return (1);
}

/***************************************************************************//**
 * @brief Sets the Reset bit of the AD9833.
 *
 * @return None.
*******************************************************************************/
void AD9833_Reset(void)
{
    AD9833_SetRegisterValue(AD9833_REG_CMD | AD9833_RESET);
	delay_ms(10);
}

/***************************************************************************//**
 * @brief Clears the Reset bit of the AD9833.
 *
 * @return None.
*******************************************************************************/
void AD9833_ClearReset(void)
{
	AD9833_SetRegisterValue(AD9833_REG_CMD);
}
/***************************************************************************//**
 * @brief Writes the value to a register.
 *
 * @param -  regValue - The value to write to the register.
 *
 * @return  None.    
*******************************************************************************/
void AD9833_SetRegisterValue(unsigned short regValue)
{
	unsigned char data[5] = {0x03, 0x00, 0x00};	
	
	data[1] = (unsigned char)((regValue & 0xFF00) >> 8);
	data[2] = (unsigned char)((regValue & 0x00FF) >> 0);
	ADI_CS_LOW;	    
	AD9833_SPI_Write(data,2);
	ADI_CS_HIGH;
}
void AD9833_SetFrequencyQuick(float fout,unsigned short type)
{
	static u8 Channel=0;

	if(Channel)
	{
			AD9833_SetFrequency(AD9833_REG_FREQ0, fout);// 400 kHz
			AD9833_Setup(AD9833_FSEL0, AD9833_PSEL0, type);
	}else
	{
			AD9833_SetFrequency(AD9833_REG_FREQ1, fout);// 400 kHz
			AD9833_Setup(AD9833_FSEL1, AD9833_PSEL0, type);
	}
	Channel=!Channel;
}

/***************************************************************************//**
 * @brief Writes to the frequency registers.
 *
 * @param -  reg - Frequence register to be written to.
 * @param -  val - The value to be written.
 *
 * @return  None.    
*******************************************************************************/
void AD9833_SetFrequency(unsigned short reg, float fout)
{
	unsigned short freqHi = reg;
	unsigned short freqLo = reg;
	unsigned long val=RealFreDat*fout;
	freqHi |= (val & 0xFFFC000) >> 14 ;
	freqLo |= (val & 0x3FFF);
	AD9833_SetRegisterValue(AD9833_B28);
	AD9833_SetRegisterValue(freqLo);
	AD9833_SetRegisterValue(freqHi);
}
/***************************************************************************//**
 * @brief Writes to the phase registers.
 *
 * @param -  reg - Phase register to be written to.
 * @param -  val - The value to be written.
 *
 * @return  None.    
*******************************************************************************/
void AD9833_SetPhase(unsigned short reg, unsigned short val)
{
	unsigned short phase = reg;
	phase |= val;
	AD9833_SetRegisterValue(phase);
}
/***************************************************************************//**
 * @brief Selects the Frequency,Phase and Waveform type.
 *
 * @param -  freq  - Frequency register used.
 * @param -  phase - Phase register used.
 * @param -  type  - Type of waveform to be output.
 *
 * @return  None.    AD9833_Setup(1000,0,AD9833_OUT_SINUS);
*******************************************************************************/
void AD9833_Setup(unsigned short freq,
				  unsigned short phase,
			 	  unsigned short type)
{
	unsigned short val = 0;
	
	val = freq | phase | type;
	AD9833_SetRegisterValue(val);
}
/***************************************************************************//**
 * @brief Sets the type of waveform to be output.
 *
 * @param -  type - type of waveform to be output.
 *
 * @return  None.    
*******************************************************************************/
/**********************************************************************************************************
*	函 数 名: AD9833_Delay
*	功能说明: 时钟延时
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void AD9833_Delay(void)
{
	uint16_t i;
	for (i = 0; i < 1; i++);
}

void AD9833_SetWave(unsigned short type)
{
	AD9833_SetRegisterValue(type);
}

void AD9833_AmpSet(unsigned char amp)
{
	unsigned char i;
	unsigned int temp;
   	
	CS_0();
	temp =0x1100|amp;
	for(i=0;i<16;i++)
	{
	    SCK_0();	
	   if(temp&0x8000)
	   	DAT_1();
	   else
		DAT_0();
		temp<<=1;
	    SCK_1();
	    AD9833_Delay();
	}
	
   	CS_1();
}
