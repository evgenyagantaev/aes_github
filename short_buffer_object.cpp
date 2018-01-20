
int add_new_charachter_to_short_buffer(uint8_t byte_to_add)
{
	if(short_buffer_in_index < SHORT_BUFFER_LENGTH)
	{
		short_buffer[short_buffer_in_index] = byte_to_add;
		short_buffer_in_index++;
		// reset new char received flag (which is set by usart irq)
		reset_new_charachter_received_flag();
		if(short_buffer_in_index >= SHORT_BUFFER_LENGTH)
		{
			short_buffer_overflow_flag = 1; // buffer overflow
			short_buffer_in_index = 0;

			// buffer overflow code return
			return 2;
		}
		else
		{
			// all right
			return 0;
		}
	}
	else 
	{
		// something wrong with index
		return 1;
	}
}


uint8_t read_charachter_from_short_buffer()
{
	uint8_t charachter_to_return;
	int i;

	if((short_buffer_off_index >= 0) && (short_buffer_off_index <= SHORT_BUFFER_LENGTH))
	{
		if((short_buffer_in_index > 0) && (short_buffer_in_index < SHORT_BUFFER_LENGTH))
		{
			charachter_to_return = short_buffer[short_buffer_off_index];

			//shift out char from buffer
			for(i=0; i<(short_buffer_in_index-1); i++)
			{
				short_buffer[i] = short_buffer[i+1];
			}
			// decrement in_index
			short_buffer_in_index--;
		}
	}
	else 
	{
		// something wrong with index
		return 0xff;
	}
}






void reset_new_charachter_received_flag();
{
	new_charachter_received_flag = 0;
}
void set_new_charachter_received_flag();
{
	new_charachter_received_flag = 1;
}
uint8_t get_new_charachter_received_flag();
{
	return new_charachter_received_flag;
}


void set_new_charachter(uint8_t byte_to_set)
{
	new_charachter = byte_to_set;
}
uint8_t get_new_charachter();
{
	return new_charachter;
}
