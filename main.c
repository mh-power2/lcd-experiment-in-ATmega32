#include <avr/io.h> // Include AVR I/O header file for microcontroller's ports and pins
#include <avr/delay.h> // Include delay header file for creating delays

// Define macros for bit manipulation
#define CLR_BIT(REG,OFFSET) REG&=~(1<<OFFSET) // Clear a bit in a register
#define SET_BIT(REG,OFFSET) REG|=(1<<OFFSET) // Set a bit in a register
#define GET_BIT(REG,OFFSET) ((REG&(1<<OFFSET))>>OFFSET) // Get the value of a bit in a register

// Array of hexadecimal values for  7-segment display
unsigned char arr[]={0x7E,0x0C,0xB6,0x9E,0xCC,0xDA,0xFA,0x0E,0xFE,0xDE};


int main(void)
{
	DDRA=0xFE; // Set Port A as output, except PA0
	DDRC=0xFF; // Set Port C as output
	DDRD=0x00; // Set Port D as input
	uint8_t counter; // Declare an  8-bit unsigned integer variable named counter
	counter=0; // Initialize counter to  0

	while (1) // Infinite loop
	{
		
		// Check if the bit at offset  2 in Port D is not set
		if(!(GET_BIT(PIND,2)))
		{
			if (counter==99)
			{
				counter=0;
			}
			else
			{
				counter=counter+1; // Increment counter
				_delay_ms(4000); // Delay for  4000 milliseconds
			}
		}
		// Check if the bit at offset  3 in Port D is not set
		else if(!(GET_BIT(PIND,3)))
		{
			if(counter==0)
			{
				counter=0;
			}
			else
			{
				counter=counter-1; // Decrement counter
				_delay_ms(4000); // Delay for  4000 milliseconds
			}
			
		}
		// Check if the bit at offset  4 in Port D is not set
		else if(!(GET_BIT(PIND,4)))
		{
			counter=0; // Reset counter to  0
		}

		// Set bit  7 of Port C and clear bit  6
		SET_BIT(PORTC,7);
		CLR_BIT(PORTC,6);

		// Calculate the tens digit of counter
		int a=counter/10;
		// Set the value of Port A to the value at index 'a' in the arr array
		PORTA=arr[a];
		_delay_ms(3); // Delay for  3 milliseconds

		// Set bit  6 of Port C and clear bit  7
		SET_BIT(PORTC,6);
		CLR_BIT(PORTC,7);

		// Calculate the ones digit of counter
		int b=counter-(a*10);
		// Set the value of Port A to the value at index 'b' in the arr array
		PORTA=arr[b];
		CLR_BIT(PORTC,7); // Clear bit  7 of Port C
		_delay_ms(3); // Delay for  3 milliseconds
	}
}
