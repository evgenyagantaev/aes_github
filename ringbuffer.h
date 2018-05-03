// ringbuffer.h
#include "stdint.h"

template <int SIZE, class DATA_TYPE = uint8_t, class INDEX_TYPE = uint32_t>
class RingBuffer
{
public:
    inline bool push(DATA_TYPE value)
    {
        if (is_full()) {
            return false;
        }

        _data[_write_count++ % SIZE] = value;
        return true;
    }
    inline DATA_TYPE peek()
    {
        return _data[_read_count % SIZE];
    }
    inline DATA_TYPE pop()
    {
        return _data[_read_count++ % SIZE];
    }

    inline bool is_full()
    {
        return (_write_count - _read_count) >= SIZE;
    }
    inline bool is_empty()
    {
        return _read_count == _write_count;
    }
    inline bool has_data()
    {
        return !is_empty();
    }
    inline void clear()
    {
        _read_count = 0;
        _write_count = 0;
    }

private:
    DATA_TYPE _data[SIZE];
    int _capacity = SIZE;

    volatile INDEX_TYPE _read_count = 0;
    volatile INDEX_TYPE _write_count = 0;

};
// end ringbuffer.h
