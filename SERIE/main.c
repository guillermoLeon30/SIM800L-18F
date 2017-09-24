#include <18f2550.h>	//Tipo de procesador
#include <string.h>

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
char ok[10]="OK\r";
char c;
int comp;

#int_rda			//Vector de interrupción al recibir por el UART
tratamiento(){	
	gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	//c = getc();
	lcd_gotoxy(1,2);
	printf(lcd_putc, "%s", dato);
	//printf(lcd_putc, "%d", c);
}	

void initSim800(){
	comp = strcmp(ok, dato);
	while(strcmp(ok, dato) != 0){
		printf("AT\r");
<<<<<<< HEAD
		gets(dato); //Lee el dato recibido hasta el enter<CR> (13)
=======
		gets(dato); //Lee hasta <CR>
>>>>>>> 7963a1185f8a5bede6fc63296692cdd1858e9afc
		comp = strcmp(ok, dato);
	}
	printf("AT+IPR\r");
	delay_ms(1000);
<<<<<<< HEAD
}

void init2Sim800(){
	printf("AT\r");
	gets(dato);
	printf(lcd_putc, "%s", dato);
	comp = strcmp(ok, dato);
	
=======
>>>>>>> 7963a1185f8a5bede6fc63296692cdd1858e9afc
}

void init3Sim800(){
	printf(lcd_putc, "\r");
}

void main(){
	int cont=0;
	set_tris_c(0b10111111);	//RC7/Rx entrada, RC6/Tx salida	
	//setup_uart(uart_autodetect);	//Activa ciclo de auto detección de baudios
	lcd_init();
<<<<<<< HEAD
	//init3Sim800();
	//enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
	//enable_interrupts(global);		//Habilita interrupciones
=======
	initSim800();
	enable_interrupts(INT_RDA);		//Activa interrupción en la recepción
	enable_interrupts(global);		//Habilita interrupciones
>>>>>>> 7963a1185f8a5bede6fc63296692cdd1858e9afc
	
	//lcd_gotoxy(1,1);
	//printf(lcd_putc, "AT+CMGS=?");
	//printf("AT+CMGS=?\r"); //Tiene que responder OK
<<<<<<< HEAD
	//gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	//lcd_gotoxy(1,2);
	//printf(lcd_putc, "%s", dato);
	//delay_ms(5000);
=======
	//delay_ms(1000);
>>>>>>> 7963a1185f8a5bede6fc63296692cdd1858e9afc

	lcd_gotoxy(1,1);
	printf(lcd_putc, "AT+CMGF=1");
	printf("AT+CMGF=1\r"); //Modo texto
	gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	lcd_gotoxy(1,2);
	printf(lcd_putc, "%s", dato);
	gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	lcd_gotoxy(1,2);
	printf(lcd_putc, "%s", dato);
	delay_ms(5000);

	lcd_gotoxy(1,1);
	printf(lcd_putc, "AT+CMGS=\"+593959984110\"");
	printf("AT+CMGS=\"+593959984110\"\r"); //Numero de telefono
	gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	lcd_gotoxy(1,2);
	printf(lcd_putc, "%s", dato);
	gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	lcd_gotoxy(1,2);
	printf(lcd_putc, "%s", dato);
	delay_ms(5000);

	lcd_gotoxy(1,1);
	printf(lcd_putc, "Prueba");
	printf("Prueba\r"); //Mensaje
	putc(26); // CTRL+Z
	//putc('\r');
	gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	lcd_gotoxy(1,2);
	printf(lcd_putc, "%s", dato);
	gets(dato);	//Lee el dato recibido hasta el enter<CR> (13)
	lcd_gotoxy(1,2);
	printf(lcd_putc, "%s", dato);
	delay_ms(5000);

	while(1)
	{	
		
	}
}