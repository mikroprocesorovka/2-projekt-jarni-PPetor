#include "stm8s.h"
#include "milis.h"
#include "stm8_hd44780.h"
#include "stdio.h"
#include "keypad.h"

void process_keypad(void);
void counter(void);
void Finalcountdown(void);
void kontrola_sekundy(void);
void kontrola_sekundy2(void);
void kontrola_minuty(void);
void kontrola_minuty2(void);
void menu(void);
char text[32];
static uint16_t posledni_cas=0;
const uint16_t period1 = 1000;
uint16_t sekundy = 0;
uint16_t minuty = 0;
uint16_t sekundy2 = 0;
uint16_t minuty2 = 0;
uint16_t stav=0;
uint16_t poradi = 1;
uint8_t pomocna = 0;
uint8_t pomocna2 = 0;
uint8_t pomocna3 = 0;
uint16_t stisknuto;
uint16_t minuty_celkem = 0;
uint16_t sekundy_celkem = 1;
void main(void){
CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
GPIO_Init(GPIOG,GPIO_PIN_2,GPIO_MODE_OUT_PP_HIGH_SLOW);
init_milis();
lcd_init();		
keypad_init();
menu();
stav=1;
  while (1){
		process_keypad();
		if(stav==1){
		if(poradi>4){
			poradi = 1;
			menu();
		}
		if(poradi<1){
			poradi = 4;
			menu();
		}
		
   }
		if(stav==2){
			if(pomocna2==1){
				counter();
				lcd_gotoxy(9,0);
				sprintf(text,"%2u",sekundy_celkem);
				lcd_puts(text);
				lcd_gotoxy(6,0);
				sprintf(text,"%2u",minuty_celkem);
				lcd_puts(text);
			}
			if(pomocna3==1){
				Finalcountdown();
			}	
	
		}
		
	}
}



void process_keypad(void){
static uint16_t last_time=0;
static uint8_t minule_stisknuto=0;
	if(milis()-last_time > 20){
		last_time = milis();
		stisknuto=keypad_scan();
		if(minule_stisknuto == 0 && stisknuto != 0){
			minule_stisknuto = stisknuto;
			if(stav==1){
			if(stisknuto==10){
				poradi = poradi + 1;
			}
			if(stisknuto==12){
				poradi = poradi - 1;
			}
			if(poradi==1){
				kontrola_minuty2();
			}
			if(poradi==2){
				kontrola_minuty();
			}	
			if(poradi==3){
				kontrola_sekundy2();
			}
			if(poradi==4){
				kontrola_sekundy();
				
			}
			menu();
				
			}
			if(stisknuto==13){
				sekundy_celkem = sekundy + sekundy2;
				minuty_celkem = minuty + minuty2;
				stav=2;
				lcd_clear();
				lcd_gotoxy(0,1);
				lcd_puts("MINUTKY BEZI");
				lcd_gotoxy(0,0);
				lcd_puts("ZBYVA 00:00");
				pomocna2 = 1;
	}

		
		}
		if(stisknuto == 0){minule_stisknuto=0;}
	}
}

void counter(void){
	static uint16_t last_time=0;
	if(milis()-last_time >= period1){
		last_time = milis();
	if(minuty_celkem == 0 && sekundy_celkem > 0){
	sekundy_celkem = sekundy_celkem - 1;
	}	
	if(minuty_celkem>0 && sekundy_celkem == 0){
		sekundy_celkem = 59;
		minuty_celkem = minuty_celkem - 1;
	}
	if(minuty_celkem>0 && sekundy_celkem > 0){
	sekundy_celkem = sekundy_celkem - 1;
	
	}
	if(sekundy_celkem == 0 && minuty_celkem == 0){
		pomocna3=1;
		pomocna2=0;
		
	}
}
}

void Finalcountdown(void){
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("KONEC");
	GPIO_WriteLow(GPIOG,GPIO_PIN_2);
	delay_ms(1500);
	GPIO_WriteHigh(GPIOG,GPIO_PIN_2);
	delay_ms(1500);
	GPIO_WriteLow(GPIOG,GPIO_PIN_2);
	delay_ms(1500);
	GPIO_WriteHigh(GPIOG,GPIO_PIN_2);
	stav=1;
	pomocna3 = 0;
	sekundy = 0;
	minuty = 0;
	minuty2 = 0;
	sekundy2 = 0;
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("CAS>");
	lcd_gotoxy(6,0);
	lcd_puts(":");
	lcd_gotoxy(4,1);
	lcd_puts("|");
	lcd_gotoxy(4,0);
	sprintf(text,"%1u",minuty2);
	lcd_puts(text);
	lcd_gotoxy(5,0);
	sprintf(text,"%1u",minuty);
	lcd_puts(text);
	lcd_gotoxy(7,0);
	sprintf(text,"%1u",sekundy2);
	lcd_puts(text);
	lcd_gotoxy(8,0);
	sprintf(text,"%1u",sekundy);
	lcd_puts(text);

}
void kontrola_minuty(void){
	if (stisknuto == 1){
		minuty = 1;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 2){
		minuty = 2;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 3){
		minuty = 3;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 4){
		minuty = 4;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 5){
		minuty = 5;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 6){
		minuty = 6;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 7){
		minuty = 7;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 8){
		minuty = 8;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 9){
		minuty = 9;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 11){
		minuty = 0;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
		
	}
}
void kontrola_minuty2(void){
	if(stisknuto == 1){
		minuty2 = 10;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(4,0);
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 2){
		minuty2 = 20;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(4,0);
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 3){
		minuty2 = 30;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(4,0);
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 4){
		minuty2 = 40;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(4,0);
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 5){
		minuty2 = 50;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(4,0);
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 6){
		minuty2 = 60;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 7){
		minuty2 = 70;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(4,0);
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 8){
		minuty2 = 80;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(4,0);
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 9){
		minuty2 = 90;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(4,0);
		sprintf(text,"%1u",minuty2);
		lcd_puts(text);
		lcd_gotoxy(5,0);
		sprintf(text,"%1u",minuty);
		lcd_puts(text);
	}
	if (stisknuto == 11){
		minuty2 = 0;
		lcd_gotoxy(4,0);
		lcd_puts("0");
		
	}
}
void menu(void){
if(poradi==1){
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("CAS>");
	lcd_gotoxy(6,0);
	lcd_puts(":");
	lcd_gotoxy(4,1);
	lcd_puts("|");
	lcd_gotoxy(4,0);
	sprintf(text,"%1u",minuty2);
	lcd_puts(text);
	lcd_gotoxy(5,0);
	sprintf(text,"%1u",minuty);
	lcd_puts(text);
	lcd_gotoxy(7,0);
	sprintf(text,"%1u",sekundy2);
	lcd_puts(text);
	lcd_gotoxy(8,0);
	sprintf(text,"%1u",sekundy);
	lcd_puts(text);
}
if(poradi==2){
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("CAS>");
	lcd_gotoxy(6,0);
	lcd_puts(":");
	lcd_gotoxy(5,1);
	lcd_puts("|");
	lcd_gotoxy(4,0);
	sprintf(text,"%1u",minuty2);
	lcd_puts(text);
	lcd_gotoxy(5,0);
	sprintf(text,"%1u",minuty);
	lcd_puts(text);
	lcd_gotoxy(7,0);
	sprintf(text,"%1u",sekundy2);
	lcd_puts(text);
	lcd_gotoxy(8,0);
	sprintf(text,"%1u",sekundy);
	lcd_puts(text);
	
}
if(poradi==3){
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("CAS>");
	lcd_gotoxy(6,0);
	lcd_puts(":");
	lcd_gotoxy(7,1);
	lcd_puts("|");
	lcd_gotoxy(4,0);
	sprintf(text,"%1u",minuty2);
	lcd_puts(text);
	lcd_gotoxy(5,0);
	sprintf(text,"%1u",minuty);
	lcd_puts(text);
	lcd_gotoxy(7,0);
	sprintf(text,"%1u",sekundy2);
	lcd_puts(text);
	lcd_gotoxy(8,0);
	sprintf(text,"%1u",sekundy);
	lcd_puts(text);
	
}
if(poradi==4){
	lcd_clear();
	lcd_gotoxy(0,0);
	lcd_puts("CAS>");
	lcd_gotoxy(6,0);
	lcd_puts(":");
	lcd_gotoxy(8,1);
	lcd_puts("|");
	lcd_gotoxy(4,0);
	sprintf(text,"%1u",minuty2);
	lcd_puts(text);
	lcd_gotoxy(5,0);
	sprintf(text,"%1u",minuty);
	lcd_puts(text);
	lcd_gotoxy(7,0);
	sprintf(text,"%1u",sekundy2);
	lcd_puts(text);
	lcd_gotoxy(8,0);
	sprintf(text,"%1u",sekundy);
	lcd_puts(text);
	
	
}
}
void kontrola_sekundy(void){
	if (stisknuto == 1){
		sekundy = 1;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 2){
		sekundy = 2;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 3){
		sekundy = 3;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 4){
		sekundy = 4;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 5){
		sekundy = 5;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 6){
		sekundy = 6;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 7){
		sekundy = 7;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 8){
		sekundy = 8;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 9){
		sekundy = 9;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
	}
	if (stisknuto == 11){
		sekundy = 0;
		lcd_gotoxy(8,0);
		lcd_puts("0");
	}
}
void kontrola_sekundy2(void){
	if (stisknuto == 1){
		sekundy2 = 10;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
		lcd_gotoxy(7,0);
		sprintf(text,"%1u",sekundy2);
		lcd_puts(text);
	}
	if (stisknuto == 2){
		sekundy2 = 20;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
		lcd_gotoxy(7,0);
		sprintf(text,"%1u",sekundy2);
		lcd_puts(text);
	}
	if (stisknuto == 3){
		sekundy2 = 30;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
		lcd_gotoxy(7,0);
		sprintf(text,"%1u",sekundy2);
		lcd_puts(text);
	}
	if (stisknuto == 4){
		sekundy2 = 40;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
		lcd_gotoxy(7,0);
		sprintf(text,"%1u",sekundy2);
		lcd_puts(text);
	}
	if (stisknuto == 5){
		sekundy2 = 50;
		lcd_gotoxy(0,0);
		lcd_puts("CAS>");
		lcd_gotoxy(6,0);
		lcd_puts(":");
		lcd_gotoxy(8,0);
		sprintf(text,"%1u",sekundy);
		lcd_puts(text);
		lcd_gotoxy(7,0);
		sprintf(text,"%1u",sekundy2);
		lcd_puts(text);
	}	
	if (stisknuto == 11){
		sekundy2 = 0;
		lcd_gotoxy(7,0);
		lcd_puts("0");
	}
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/