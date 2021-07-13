#include <cstdint>

#include "frame_buffer_config.hpp"

struct PixelColor {
    uint8_t r, g, b;
};

int WritePixel(const FrameBufferConfig& config, int x, int y, const PixelColor& c) {
    const int pixel_position = config.pixels_per_scan_line * y + x;
    uint8_t* p = &config.frame_buffer[4 * pixel_position];
    switch (config.pixel_format) {
        case kPixelRGBResv8BitPerColor:
            p[0] = c.r;
            p[1] = c.g;
            p[2] = c.b;
            break;
        case kPixelBGRResv8BitPerColor:
            p[0] = c.b;
            p[1] = c.g;
            p[2] = c.r;
            break;
        default:
            return -1;
    }
    return 0;
}

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
    // draw gray
    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            WritePixel(frame_buffer_config, x, y, {0x88, 0x88, 0x88});
        }
    }
    // draw red rectangle
    for (int x = 50; x < 250; ++x) {
        for (int y = 50; y < 250; ++y) {
            WritePixel(frame_buffer_config, x, y, {0xFF, 0x00, 0x00});
        }
    }
    while (1) __asm__("hlt");
}
