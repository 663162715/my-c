



#include "isr.h"
#include "All_Init.h"
#include "Data.h"
#include "Balance.h"
#include "Speed.h"
#include "Direction.h"
#include "Motor.h"
#include "UART_CMD.h"

vuint32 Pin_Flag;            //?¡§¨°?¨¤¨¤D¨ª¡À?D??auint32 ¡ä?¡ä¡é2¨²¨¦¨²?D??¦Ì?¨°y??o?

void PIT_CH0_IRQHandler(void)      //PIT?D??  ,1o¨¢??
{
	static uint8	Balance_Task = 0;
	static uint8	Speed_Task = 0;
	static uint8	Direction_Task = 0;
    PIT_FLAG_CLR(pit0);
	
	  Balance_Task ++;
  	Speed_Task ++;
	  Direction_Task ++;
	
	if(Balance_Task == 5)  //5o¨¢??
	{
		Balance_Task = 0;
		Get_AccData();   //?¨®?¨´?¨¨
		Get_Gyro();       //¨ª¨®
		
		Get_Zero();
		Complementary_Filter();  //?£¤21
		Balance();        	 	 //PID         
		Motor();
	}
    
	if(Speed_Task ==7)  //7o¨¢??  70o¨¢??
    {
		Speed_Task = 0;
		Speed();
	  }
	
	if(Direction_Task == 11) //11o¨¢??
	{
		Direction_Task = 0;
		Direction();
	}


}

void PIT_CH1_IRQHandler(void)  //¨®??¨¨??¦Ì¨ª¨°?¦Ì?¡ê??¦Ì?¨º¦Ì¨ª¨°?¦Ì?¡ã¨¦¡ê?¡ê?2o¨¢??¨°?¡ä??D??	
{ 	
	static uint8 x,x1,x2,x3,x4,x5,x6;
	static uint8 key,key1;
	static uint8 Rank_Flag = 1;
	static uint8 keyaddage1;
	static uint8 keyaddage2;
	
	PIT_FLAG_CLR(pit1);
	
	x   = (1-gpio_get(D1))*1
		+ (1-gpio_get(C5))*2
		+ (1-gpio_get(H2))*4
		+ (1-gpio_get(H5))*8
		+ (1-gpio_get(H6))*16
		+ (1-gpio_get(H7))*32;

	x6=x5;
	x5=x4;
	x4=x3;
	x3=x2;
	x2=x1;
	x1=x;
	if (x==x2 && x==x3 && x==x4  && x==x5  && x==x6)
	 {
     key1=key;	 
		 key=x;
	 
	if ((key&0x01)==0x01  &&  (key1&0x01)==0)  //D1,S7
	   {
			Save_Data();                               //¡ä?¨ºy
		 }
 

	if ((key&0x02)==0x02  &&  (key1&0x02)==0)  //C5,S6
	   {
		  (*g_Line) ++;
		 }
 if ((key&0x04)==0x04  &&  (key1&0x04)==0)//H2,S5???¦Ì??¡ê????¨®¨°?¡ä?
	   {
		*g_Add_Flag = 1;//¨¢??¨®
		 }
 if ((key&0x04)==0x04  &&  (key1&0x04)==0x04)//H2,S5¡ê?¨¢??¨®
	   { static uint8 count=0;
			
      if(++count==4)			                     //??¡ä??D???¨®¨°?¡ä?
      {
				keyaddage1++;                          //?¨¹¨¢??¨®1
			  if (keyaddage1>60)	
			 	 { 
					 *g_Add_Flag = 1;//¨¢??¨®	                //?¨¹¨¢?3?60¡ê?¨¢??¨®
			   	keyaddage1=61;
			  }
				count=0;
			}
		 }	
		 
if ((key&0x04)==0  &&  (key1&0x04)==0)//H2,S5
	   {
      keyaddage1=0;                           //¨¬¡ì?e¡ê??¨¹¨¢???¨¢?
		 }		 
		
 
		 
 if ((key&0x08)==0x08  &&  (key1&0x08)==0)//H5,S4
	   {
			Rank_Flag ++;
		 }
 if ((key&0x10)==0x10  &&  (key1&0x10)==0)//H6,S3  //???¦Ì??
	   {
		*g_Minus_Flag = 1; //¨¢???
		 }
 if ((key&0x10)==0x10  &&  (key1&0x10)==0x10)//H6,S3 //3?D?¡ã¡ä??
	   { static uint8 count=0;
			
      if(++count==4)			 
      {
			keyaddage2++;
			  if (keyaddage2>60)	
        {
					*g_Minus_Flag = 1; //¨¢???	
				  keyaddage2=60;
				}
			 count=0;
			}
		 }	
		 
if ((key&0x10)==0  &&  (key1&0x10)==0)//H6,S3   ?¨¦?a
	   {
      keyaddage2=0; 
		 }		 
		
	 
		 
		 
 if ((key&0x20)==0x20  &&  (key1&0x20)==0)//H7,S2
	   {
		(*g_Line) -- ;		
		 }
		 
		 if(Rank_Flag == 9)
	{
		Rank_Flag = 1;
	}
	
	
	switch(Rank_Flag)
	{
		case 1:*g_Rank = 1.0f;		  	break;
		case 2:*g_Rank = 0.1f;		 	break;
		case 3:*g_Rank = 0.01f;		  	break;
		case 4:*g_Rank = 0.001f;	  	break;
		case 5:*g_Rank = 0.0001f;	  	break;
		case 6:*g_Rank = 0.00001f;		break;
		case 7:*g_Rank = 0.000001f;		break;
		case 8:*g_Rank = 10;	    	break;
		default:					    break;
	}


}

}


void IRQ_IRQHandler(void)   //I0-I7
{
    CLEAR_IRQ_FLAG;
	
}


/**
*@function		¡ä??¨²?¨®¨º??D??
*@param			?T2?¨ºy
*@return		?T¡¤¦Ì???¦Ì
*@date			2018-06-29
*@version		V1.0
*@author		Liu Shifu
*/
void UART1_IRQHandler(void)
{
    static uint8 	i;
	UART1_S1;	//??3y?D??¡À¨º??
	UART_Receive_Data[i] = UART1_D;	//?¨¢¨ºy?Y¡ã¨¹
	i ++;		//¨ºy?Y¨°???
	if(UART_Receive_Data[i-1] == 'z')	//?D??¨ºy?Y¡ã¨¹¦Ì?¡ã¨¹?2
	{
		i = 0;	//¡À¡ê?¡è??¨°?¡ä??¨®¨º?¦Ì?¨ºy?Y¡ã¨¹¨ª¡¤?¨¹¡¤??¨²¦Ì¨²¨°???
	}
	Alter_Parameters_Flag = 0;		//¡ä¨°?a¡ä??¨²¦Ì¡Â2?
}


