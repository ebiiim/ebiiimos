#include "console.hpp"

#include <cstring>

#include "font.hpp"

Console::Console(PixelWriter& writer, const PixelColor& fg_color, const PixelColor& bg_color)
    : writer_{writer}, fg_color_{fg_color}, bg_color_{bg_color}, buffer_{}, cursor_row_{0}, cursor_column_{0} {}

void Console::PutString(const char* s) {
    while (*s) {
        if (*s == '\n')
            Newline();
        else if (cursor_column_ < kColumns) {
            WriteAscii(writer_, CONSOLE_TEXT_LEFT + cursor_column_ * FONT_WIDTH,
                       CONSOLE_TEXT_TOP + cursor_row_ * (FONT_HEIGHT + CONSOLE_SPACE_BETWEEN_LINES), *s, fg_color_);
            buffer_[cursor_row_][cursor_column_] = *s;
            ++cursor_column_;
        }
        ++s;
    }
}

void Console::Newline() {
    cursor_column_ = 0;
    if (cursor_row_ < kRows - 1) {
        ++cursor_row_;
        return;
    }
    // scroll
    for (int y = CONSOLE_TEXT_TOP; y < CONSOLE_TEXT_TOP + kRows * (FONT_HEIGHT + CONSOLE_SPACE_BETWEEN_LINES); ++y) {
        for (int x = CONSOLE_TEXT_LEFT; x < CONSOLE_TEXT_LEFT + kColumns * FONT_WIDTH; ++x) writer_.Write(x, y, bg_color_);
    }
    for (int row = 0; row < kRows - 1; ++row) {
        memcpy(buffer_[row], buffer_[row + 1], kColumns + 1);
        WriteString(writer_, CONSOLE_TEXT_LEFT, CONSOLE_TEXT_TOP + row * (FONT_HEIGHT + CONSOLE_SPACE_BETWEEN_LINES),
                    buffer_[row], fg_color_);
    }
    memset(buffer_[kRows - 1], 0, kColumns + 1);
}
