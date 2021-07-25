#pragma once

#include <cstdint>

#include "graphics.hpp"

const uint8_t FONT_WIDTH = 8;
const uint8_t FONT_HEIGHT = 16;

const uint8_t* GetFont(char c);

void WriteAscii(PixelWriter& writer, int x, int y, char c, const PixelColor& color);

void WriteString(PixelWriter& writer, int x, int y, const char* s, const PixelColor& color);
