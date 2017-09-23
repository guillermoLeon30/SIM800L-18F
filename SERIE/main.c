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
	
	dato=getc();	//Lee el dato recibido
	lcd_putc('\f');
	printf(lcd_putc, "%c", dato);
}	

void main(){
	int cont=0;
	set_tris_c(0b10111111);	//RC7/Rx entrada, RC6/Tx salida	
	//setup_uart(uart_autodetect);	//Activa ciclo de auto detección de baudios
	lcd_init();
	enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
	enable_interrupts(global);		//Habilita interrupciones
	while(1)
	{	
		cont++;
		printf("%d", cont);
		//putc('A');		//Transmite el caracter
		delay_ms(1000);	//Temporiza 1 segundo
	}
}