#include "ring_buffer.h"

/**
 * @brief  Khởi tạo ring buffer với các tham số ban đầu
 * @param  rb   Con trỏ tới cấu trúc ring_buffer_t cần khởi tạo
 * @param  buff Con trỏ tới mảng bộ nhớ đã cấp phát để lưu trữ dữ liệu
 * @param  size Kích thước tối đa của buffer (số byte có thể chứa)
 */
void ring_buffer_init(ring_buffer_t *rb, void *buff, uint16_t size)
{
    rb->head = 0;                   // Vị trí đọc dữ liệu bắt đầu từ index 0
    rb->tail = 0;                   // Vị trí ghi dữ liệu bắt đầu từ index 0
    rb->fill_size = 0;              // Ban đầu buffer rỗng, chưa có dữ liệu
    rb->buff_size = size;           // Lưu kích thước tối đa của buffer
    rb->ptr_buff = (uint8_t *)buff; // Gán con trỏ tới vùng nhớ lưu trữ dữ liệu
}

/**
 * @brief  Ghi một byte dữ liệu vào ring buffer
 *         Nếu buffer đầy, dữ liệu cũ nhất sẽ bị ghi đè (overwrite)
 * @param  rb   Con trỏ tới cấu trúc ring buffer
 * @param  data Byte dữ liệu cần ghi vào buffer
 * @note   Hàm này luôn ghi thành công, ngay cả khi buffer đầy
 */
void ring_buffer_put(ring_buffer_t *rb, uint8_t data)
{
    rb->ptr_buff[rb->tail] = data;             // Ghi dữ liệu vào vị trí tail hiện tại
    rb->tail = (rb->tail + 1) % rb->buff_size; // Di chuyển tail tới vị trí tiếp theo (quay vòng nếu cần)

    if (rb->fill_size == rb->buff_size) // Nếu buffer đã đầy
    {
        rb->head = (rb->head + 1) % rb->buff_size; // Di chuyển head để ghi đè dữ liệu cũ nhất
    }
    else
    {
        rb->fill_size++; // Tăng số lượng dữ liệu trong buffer
    }
}

/**
 * @brief  Đọc một byte dữ liệu từ ring buffer
 * @param  rb   Con trỏ tới cấu trúc ring buffer
 * @param  data Con trỏ để lưu dữ liệu đọc được từ buffer
 * @retval true  Đọc thành công, dữ liệu được lưu vào *data
 * @retval false Buffer rỗng, không có dữ liệu để đọc
 * @note   Dữ liệu đọc sẽ bị xóa khỏi buffer sau khi đọc
 */
bool ring_buffer_get(ring_buffer_t *rb, uint8_t *data)
{
    if (rb->fill_size == 0) // Kiểm tra buffer có rỗng không
        return false;       // Buffer rỗng, không thể đọc

    *data = rb->ptr_buff[rb->head];            // Đọc dữ liệu tại vị trí head
    rb->head = (rb->head + 1) % rb->buff_size; // Di chuyển head tới vị trí tiếp theo (quay vòng nếu cần)
    rb->fill_size--;                           // Giảm số lượng dữ liệu trong buffer

    return true; // Đọc thành công
}

/**
 * @brief  Xóa toàn bộ dữ liệu trong ring buffer và reset về trạng thái ban đầu
 * @param  rb Con trỏ tới cấu trúc ring buffer cần xóa
 * @note   Hàm này không thực sự xóa dữ liệu trong bộ nhớ mà chỉ reset các con trỏ
 */
void ring_buffer_clear(ring_buffer_t *rb)
{
    rb->head = 0;      // Reset vị trí đọc về đầu buffer
    rb->tail = 0;      // Reset vị trí ghi về đầu buffer
    rb->fill_size = 0; // Đánh dấu buffer rỗng
}

/**
 * @brief  Kiểm tra ring buffer có rỗng hay không
 * @param  rb Con trỏ tới cấu trúc ring buffer cần kiểm tra
 * @retval true  Buffer rỗng (không có dữ liệu)
 * @retval false Buffer có ít nhất 1 byte dữ liệu
 */
bool ring_buffer_is_empty(ring_buffer_t *rb)
{
    return (rb->fill_size == 0);
}

/**
 * @brief  Kiểm tra ring buffer đã đầy hay chưa
 * @param  rb Con trỏ tới cấu trúc ring buffer cần kiểm tra
 * @retval true  Buffer đã đầy (không thể ghi thêm dữ liệu mà không ghi đè)
 * @retval false Buffer còn chỗ trống
 */
bool ring_buffer_is_full(ring_buffer_t *rb)
{
    return (rb->fill_size == rb->buff_size);
}
