#include <cstddef>
#include <cstdint>
#include <cstdio>

#include "console.hpp"
#include "font.hpp"
#include "frame_buffer_config.hpp"
#include "graphics.hpp"

// #include <new>
void* operator new(size_t size, void* buf) { return buf; }
void operator delete(void* obj) noexcept {}  // ~PixelWriter() needs this operator

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

char console_buf[sizeof(Console)];
Console* console;

int printk(const char* format, ...) {
    va_list ap;
    int result;
    char s[1024];

    va_start(ap, format);
    result = vsprintf(s, format, ap);
    va_end(ap);

    console->PutString(s);
    return result;
}

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
    PixelColor console_fg_color = {0xCC, 0xCC, 0xCC};
    PixelColor console_bg_color = {0x33, 0x33, 0x33};
    console = new (console_buf) Console{*pixel_writer, console_fg_color, console_bg_color};

    for (int i = 0; i < 28; ++i) {
        printk("line %d\n", i);
    }
    printk("01234567890123456789012345678901234567890123456789012345678901234567890123456789");

    while (1) __asm__("hlt");
}
