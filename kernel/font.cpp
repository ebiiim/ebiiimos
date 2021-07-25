#include "font.hpp"

#define _binary_font_start _binary____day05c_hankaku_bin_start
#define _binary_font_end _binary____day05c_hankaku_bin_end
#define _binary_font_size _binary____day05c_hankaku_bin_size

extern const uint8_t _binary_font_start;
extern const uint8_t _binary_font_end;
extern const uint8_t _binary_font_size;

const uint8_t* GetFont(char c) {  // returns a pointer cuz this function may return null
    auto index = 16 * static_cast<unsigned int>(c);
    if (index >= reinterpret_cast<uintptr_t>(&_binary_font_size)) return nullptr;
    return &_binary_font_start + index;
}

void WriteAscii(PixelWriter& writer, int x, int y, char c, const PixelColor& color) {
    const uint8_t* font = GetFont(c);
    if (font == nullptr) return;
    for (int dy = 0; dy < 16; ++dy) {
        for (int dx = 0; dx < 8; ++dx) {
            if (font[dy] << dx & 0x80u) writer.Write(x + dx, y + dy, color);
        }
    }
}
