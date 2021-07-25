#pragma once

#include <cstdint>

#include "graphics.hpp"

const uint8_t* GetFont(char c);

void WriteAscii(PixelWriter& writer, int x, int y, char c, const PixelColor& color);