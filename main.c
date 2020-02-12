/*
 * UART.c
 *
 * Created: 12-Jun-19 8:18:03 PM
 * Author : Elmogy
 */ 

#include "LSTD_Types.h"
#include "LUTILS.h"
#include "LDELAY_Interface.h"
#include "MDIO_Interface.h"
#include "MUART_Interface.h"
#include "HLCD_Interface.h"
#include "HKPD_Interface.h"

int main(void)
{
	u8 character  =  0;
	u8 Data[8]	  = {0};
    u8 PressedKey =  0;
	
	MUART_voidInitializeUART();
	HLCD_voidInitializeLCD();
	HKPD_voidInitializeKeypad();
	
	HLCD_voidCursorDisplayOnOff(HLCD_OFF);
	HLCD_voidCursorBlinkOnOff(HLCD_OFF);
	HLCD_voidDisplayString("Received Char",HLCD_STRING);
	while (1) 
    {
		
		/*
		for (u8 i = 0; i < 8 ; i++)
		{
			character = MUART_voidRecieveByte(4000);
			if ( 0 == character )
			{
				Data[i] = '\0';
				break;
			}
			
			Data[i] = character;
			
		}
		*/
		character = MUART_voidRecieveByteSynch(4000);
		PressedKey = HKPD_u8GetPressedKey();
		
		if ( (PressedKey >= 0) && (PressedKey < 10) )
		{
			PressedKey += '0'; 
		}
		
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayString("                ",HLCD_STRING);
		HLCD_voidSelectLine(HLCD_LINE2);
		HLCD_voidDisplayChar(character);
		MUART_voidSendByteSynch(PressedKey);
		LDelay_voidDelay_ms(1000);	
    }
}

