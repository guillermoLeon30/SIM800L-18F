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

char dato[10];		//Variable para almacena el dato recibido
char c;

#int_rda			//Vector de interrupción al recibir por el UART
tratamiento()
{	
	//gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	c = getc();
	lcd_gotoxy(1,2);
	//printf(lcd_putc, "%s", dato);
	printf(lcd_putc, "%d", c);
}	

void main(){
	int cont=0;
	set_tris_c(0b10111111);	//RC7/Rx entrada, RC6/Tx salida	
	//setup_uart(uart_autodetect);	//Activa ciclo de auto detección de baudios
	lcd_init();
	enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
	enable_interrupts(global);		//Habilita interrupciones
	
	lcd_gotoxy(1,1);
	printf(lcd_putc, "AT+CMGS=?");
	printf("AT+CMGS=?\r"); //Tiene que responder OK
	delay_ms(1000);

	lcd_gotoxy(1,1);
	printf(lcd_putc, "AT+CMGF=1");
	printf("AT+CMGF=1\r"); //Modo texto
	delay_ms(1000);

	lcd_gotoxy(1,1);
	printf(lcd_putc, "AT+CMGS=\"+593959984110\"");
	printf("AT+CMGS=\"+593959984110\"\r"); //Numero de telefono
	delay_ms(1000);

	lcd_gotoxy(1,1);
	printf(lcd_putc, "Prueba");
	printf("Prueba"); //Mensaje
	putc(26); // CTRL+Z
	putc('\r');
	delay_ms(1000);

	while(1)
	{	
		
	}
}