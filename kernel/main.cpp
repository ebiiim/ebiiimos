#include <cstddef>
#include <cstdint>
#include <cstdio>

#include "font.hpp"
#include "frame_buffer_config.hpp"
#include "graphics.hpp"

// #include <new>
void* operator new(size_t size, void* buf) { return buf; }
void operator delete(void* obj) noexcept {}  // ~PixelWriter() needs this operator

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
    switch (frame_buffer_config.pixel_format) {
        case kPixelRGBResv8BitPerColor:
            pixel_writer = new (pixel_writer_buf) RGBResv8BitPerColorPixelWriter{frame_buffer_config};
            break;
        case kPixelBGRResv8BitPerColor:
            pixel_writer = new (pixel_writer_buf) BGRResv8BitPerColorPixelWriter{frame_buffer_config};
            break;
        default:
            while (1) __asm__("hlt");
    }

    // draw gray
    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            pixel_writer->Write(x, y, {0x88, 0x88, 0x88});
        }
    }
    // draw red rectangle
    for (int x = 50; x < 250; ++x) {
        for (int y = 50; y < 250; ++y) {
            pixel_writer->Write(x, y, {0xFF, 0x00, 0x00});
        }
    }
    // draw text
    PixelColor text_color = {0x33, 0x33, 0x33};
    auto text_x = 10;
    auto text_y = 100;
    auto text_count = 0;
    for (char x = '!'; x <= '~'; ++x) {
        WriteAscii(*pixel_writer, text_x + text_count * FONT_WIDTH, text_y, x, text_color);
        ++text_count;
    }
    text_y += FONT_HEIGHT;
    WriteString(*pixel_writer, text_x, text_y, "Hello, world!", text_color);
    text_y += FONT_HEIGHT;
    char buf[128];
    sprintf(buf, "1 + 2 = %d", 1 + 2);
    WriteString(*pixel_writer, text_x, text_y, buf, text_color);

    while (1) __asm__("hlt");
}
