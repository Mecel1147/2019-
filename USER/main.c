#include "sys.h"
#include "stdio.h"

//#include "lcd.h"
#include "AD9833.h" 
#include "key.h"
#include "delay.h"
#include "wave.h"
#include "oled.h"
#include "iic.h"
extern u32 weep;
extern u8 _return;
extern u8 key_count;
extern u8 fuzhi;
u8 i=0;
u8 shape;
u8 s=11;
int main(void)
{
	char a[]="Hz";
	char b[]="V";
	char c[]=".";
	char d[]="Sinwave";
	char e[]="Square";
	char f[]="Triangle";
	u8 key;           //保存键值
	delay_init(168);	//初始化延时函数
	KEY_Init();
	delay_ms(300);
	AD9833_Init();
	IIC_Init();
	OLED_Init();//oled初始化
	//AD9833_SetFrequencyQuick(200000,AD9833_OUT_SINUS);//正弦波


while(1)
	{
						key=KEY_Scan(0);		//得到键值
			
			if(key==1)
			{				 
				AD9833_SetFrequencyQuick(weep,AD9833_OUT_MSB);
						switch(key_count)
						{
								case 0://正弦波
								{
									shape=AD9833_OUT_SINUS;
									delay_ms(100);
								}
									break;
								case 1:	//方波
								{
									shape=AD9833_OUT_MSB;
									delay_ms(100);
								}
									break;
								case 2:	//三角波	 
								{	
									shape=AD9833_OUT_TRIANGLE;
									delay_ms(100);
								}
								break;
						}
				}
			else if(key==2)
			{	
					weep_up();
			}
			else if(key==3)
				{
					weep_down();
				}
				else if(key==4)
				{
					fuzhi_up();
				}
				
				AD9833_SetFrequencyQuick(weep,shape);
				AD9833_AmpSet(fuzhi);
//								delay_ms(100); 
				for(i=0;i<2;i++)OLED_ShowCHinese(i*14,0,i);
				OLED_ShowNum(22,0,weep,6,12);
				OLED_ShowString(60,0,a,2);
				for(i=0;i<2;i++)OLED_ShowCHinese(i*14,2,i+2);
				OLED_ShowNum(22,2,fuzhi/5,6,12);
				OLED_ShowString(60,2,b,2);
				OLED_ShowString(48,3,c,0);
				for(i=0;i<2;i++)OLED_ShowCHinese(i*14,4,i+4);
				if(key_count==0)
					{
					OLED_ShowString(60,4,d,2);
          }
				else if(key_count==1)
				{
				OLED_ShowString(60,4,e,2);
				}
				if(key_count==2)
					{
					OLED_ShowString(60,4,f,2);
          }	
			}	
		}
