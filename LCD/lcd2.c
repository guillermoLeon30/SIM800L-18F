//								LCD2.C
//						Autor: Mikel Etxebarria
//			(c) Ingeniería de Microsistemas Programados S.L.
//						www.microcontroladores.com
//								Bilbao 2007
//
// Funciones para la gestión del display LCD por un PIC18F, según las siguientes conexiones:
//
// RB0-RB7 se conetcan con las líneas D0_D7 de datos del LCD
// RA1 se conecta con RS, RA2 con R/W y RA3 con E
//
//	lcd_enviar(LCD_COMANDO/LCD_DATO,valor)
//
//				Permite enviar un comando (LCD_COMANDO) o un dato (LCD_DATO)
//				valor represeta el valor hex. a enviar
//
//  lcd_init()   Debe ser llamada antes que las otras funciones.
//
//  lcd_putc(c)  Visualiza c en la siguiente posición del display.
//               Caracteres especiales de control:
//                      \f  Borrar display
//                      \n  Saltar a la segunda linea
//                      \b  Retroceder una posición.
//
//  lcd_gotoxy(x,y) Selecciona la nueva posición de escritura en el display.
//                  (la esquina superior izquierda es 1,1)
//
//  lcd_getc(x,y)   Devuelve el caracter de la posición x,y del display.


#bit  lcd_enable = 0xf80.3	//RA3 --> Enable
#bit  lcd_rw     = 0xf80.2	//RA2 --> R/W
#bit  lcd_rs     = 0xf80.1	//RA1 --> RS
#byte lcd_a = 0xf80			//Puerta A
#byte lcd_b = 0xf81			//Puerta B

#define LCD_LINEA2 0x40    // Dirección de memoria para la segunda línea
#define LCD_DATO    1		// Modo dato
#define LCD_COMANDO 0		// Modo comando

//Definición de los códigos de los comandos mas frecuentes

#define LCD_CLEAR       0x01
#define LCD_HOME	 	0x02

#define LCD_DISPLAY_OFF  0x08
#define LCD_DISPLAY_ON   0x0C
#define LCD_CURSOR_ON    0x0E
#define LCD_CURSOR_BLINK 0x0F

#define LCD_CURSOR_SHIFT_RIGHT  0x10
#define LCD_CURSOR_SHIFT_LEFT   0x14
#define LCD_DISPLAY_SHIFT_RIGHT 0x18
#define LCD_DISPLAY_SHIFT_LEFT  0x1C

//Realiza un ciclo de lectura de la pantalla LCD

int lcd_leer()	
{
  int valor;

//  set_tris_a(0xf1);	//RA1-RA3 se configuran como salidas
  set_tris_b(0xFF);	//RB0-RB7 se configuran como entradas

  lcd_rw = 1;		//Modo lectura
  delay_cycles(1);
  lcd_enable = 1;	//Activación del LCD
  delay_cycles(1);
  valor = lcd_b;	//Lectura de datos procedentes de LCD
  lcd_enable = 0;	//Desactivación del LCD
  delay_cycles(1);

  set_tris_b(0x00);	//RB0-RB7 se configuran como salidas
  return valor;
}

//Envia a la pantalla un comando (dir=1) o un dato (dir=0)

void lcd_enviar(int dir, int valor)
{
  set_tris_a(0xf1);
  set_tris_b(0x00);	//Puerta A y B salidas

  lcd_rs = 0;		//Modo comando
  while( bit_test(lcd_leer(),7) );	// Lectura del biy bussy del LCD para saber si está libre
  lcd_rs = dir;		//Establece el modo (comando/dato)
  delay_cycles(1);

  lcd_rw = 0;		//Modo escritura
  delay_cycles(1);
  lcd_enable = 0;
  lcd_b = valor;	//Envia el valor del comando o del dato
  delay_cycles(1);
  lcd_enable = 1;	//Habilita el LCD
  delay_us(2);
  lcd_enable = 0;	//Desactiva el LCD
}

//Función para inicio de la pantalla LCD según especificaciones del fabricante

void lcd_init()
{
  int i;

  set_tris_a(0xF1);	//RA1-RA3 salidas
  set_tris_b(0x00);	//RB0-RB7 salidas

  lcd_enable = 0;	//Desactiva LCD
  lcd_rw = 0;		//Modo escritura
  lcd_rs = 0;		//Modo comando
  delay_ms(15);		//Temporiza 15mS

  for(i=0; i<3; i++)	//Envía 3 veces el comando 0x38 a intervalos de 5 mS
  {
    lcd_enviar(LCD_COMANDO,0x38);
    delay_ms(5);
  }
  lcd_enviar(LCD_COMANDO,LCD_DISPLAY_ON);	//Secuencia de comandos a enviar a la pantalla LCD
  lcd_enviar(LCD_COMANDO,0x06);
  lcd_enviar(LCD_COMANDO,LCD_CLEAR);
  lcd_enviar(LCD_COMANDO,LCD_HOME);
}

//Función para situar el cursor

void lcd_gotoxy( byte x, byte y) {
   byte dir;

   if(y!=1)
     dir=LCD_LINEA2;
   else
     dir=0;
   dir+=x-1;
   lcd_enviar(LCD_COMANDO,0x80|dir);
}

//Visualiza un caracter

void lcd_putc( char c) {
   switch (c) {
     case '\f'   : lcd_enviar(LCD_COMANDO,0x01);
                   delay_ms(2);
                   break;
     case '\n'   : lcd_gotoxy(1,2);               break;
     case '\b'   : lcd_enviar(LCD_COMANDO,0x10);  break;
     default     : lcd_enviar(LCD_DATO,c);        break;
   }
}

//Devuelve el caracter

char lcd_getc( int x, int y) {
   char valor;

    lcd_gotoxy(x,y);

    lcd_rs = 1;
    valor = lcd_leer();
    lcd_rs = 0;

    return valor;
}

