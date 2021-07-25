#pragma once

#include "graphics.hpp"

const int CONSOLE_TEXT_LEFT = 0;
const int CONSOLE_TEXT_TOP = 0;
const int CONSOLE_SPACE_BETWEEN_LINES = 0;

class Console {
   public:
    static const int kRows = 25, kColumns = 80;
    Console(PixelWriter& writer, const PixelColor& fg_color, const PixelColor& bg_color);
    void PutString(const char* s);

   private:
    void Newline();

    PixelWriter& writer_;
    const PixelColor fg_color_, bg_color_;
    char buffer_[kRows][kColumns + 1];
    int cursor_row_, cursor_column_;
};
