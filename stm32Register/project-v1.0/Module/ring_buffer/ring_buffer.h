#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint16_t head;			// chi muc noi doc (GET)
    uint16_t tail;			// chi muc noi ghi (PUT)
    uint16_t fill_size; 	// so phan tu hien co (de kiem ra empty hoac full)
    uint16_t buff_size;		// kich thuoc cua buffer
    uint8_t *ptr_buff; 		// con tro toi mang buffer
} ring_buffer_t;

void ring_buffer_init(ring_buffer_t *rb, void *buff, uint16_t size);
void ring_buffer_put(ring_buffer_t *rb, uint8_t data);
bool ring_buffer_get(ring_buffer_t *rb, uint8_t *data);
void ring_buffer_clear(ring_buffer_t *rb);
bool ring_buffer_is_empty(ring_buffer_t *rb);
bool ring_buffer_is_full(ring_buffer_t *rb);

#endif // __RING_BUFFER_H__
