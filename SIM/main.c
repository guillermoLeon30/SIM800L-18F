#include <18f2550.h>	//Tipo de procesador
#use delay(clock=4000000)			//Frecuencia de trabajo

#fuses 	EC_IO			//Oscilador externo, RA6=E/S,PLL OFF (CONFIG1H)	
#fuses 	CPUDIV1			//Postcaler OSC/1, Frec. CPU=4MHz/1=4MHz (CONFIG1L)
						//Ciclo de instrucción = 1uS (1/(4000000/4))

#fuses PUT,NOBROWNOUT,NOWDT,NOPBADEN,NOLVP

#define LCD_DATA_PORT getenv("SFR:PORTB") 
#include <lcd.c> //No se usa fast_io en la puerta

//Habilita las funciones RS232, velocidad a 9600 baudios
#use rs232(Baud=9600,xmit=PIN_C6, rcv=PIN_C7)

#use fast_io (C)

char dato;		//Variable para almacena el dato recibido
#int_rda			//Vector de interrupción al recibir por el UART
tratamiento()
{	
	dato = getc();	//Lee el dato recibido
	
	printf(lcd_putc, "%c", dato);
}	

void main(){
	set_tris_c(0b10111111);	//RC7/Rx entrada, RC6/Tx salida	
	//setup_uart(uart_autodetect);	//Activa ciclo de auto detección de baudios
	lcd_init();
	enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
	enable_interrupts(global);		//Habilita interrupciones
	lcd_gotoxy(1,1);
	//printf(lcd_putc, "AT2");
	//lcd_gotoxy(1,2);
	printf("AT+CMGS=?");

	//printf("AT+CMGF=1\r");
	//delay_ms(100);
	//printf("AT+CMGS=0959984110\r");
	//delay_ms(500);
	//printf("Esto es una prueba");
	//delay_ms(500);
	//putchar(0x1a);
	while(1)
	{	
		
	}
}