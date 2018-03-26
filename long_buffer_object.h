#define LONG_BUFFER_LENGTH 1024

uint8_t long buffer[LONG_BUFFER_LENGTH];
int long_buffer_in_index = 0;
int long_buffer_off_index = 0;
int long_buffer_overflow_flag = 0;

void add_new_charachter_to_long_buffer();

