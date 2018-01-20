#define SHORT_BUFFER_LENGTH 7

static uint8_t short_buffer[SHORT_BUFFER_LENGTH];
static int short_buffer_in_index = 0;
static int short_buffer_off_index = 0;
static   int short_buffer_overflow_flag = 0;

static int new_charachter_received_flag = 0;
int get_new_charachter_received_flag();
void set_new_charachter_received_flag();
void reset_new_charachter_received_flag();

static uint8_t new_charachter;
void set_new_charachter(uint8_t byte_to_set);
uint8_t get_new_charachter();


int add_new_charachter_to_short_buffer(uint8_t byte_to_add);
uint8_t read_charachter_from_short_buffer();
