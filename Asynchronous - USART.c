#define F_CPU 8000000
#define BAUD 9600
#define MYUBRR F_CPU/16/(BAUD-1)
#include <xc.h>
#include <util/delay.h>
#include <avr/io.h>

void UART_init(unsigned int ubrr){
	//set baud rate:
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	//set frame format:
	
	UCSR0C = 0x06;
	//UCSR0C = (1<<USBS0) | (3<<UCSZ00);
	//enable receiver and transmitter:
	UCSR0B = (1<<RXEN0) | (1<<TXEN0); 
	
}
void Data_Tx(unsigned char data){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}


int main(void)
{
	UART_init(MYUBRR);
	while(1){
		for (unsigned char i = 97; i<122; i++){
			
			Data_Tx(i);
			_delay_ms(100);
		}
	}
}