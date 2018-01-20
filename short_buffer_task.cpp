#include "short_buffer_object.h"


void short_buffer_task()
{
	
	add_new_charachter_to_short_buffer();
	// reset new char received flag (which is set by usart irq)
	reset_new_charachter_received_flag();
}


