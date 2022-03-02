#include <iostream>
#include <cstdio>
#include <cstring>
#include "consolemanip.h"

namespace Console
{

const std::string CLEAR_SCREEN_STR = [] {
    std::string result;
    for (int i = 0; i < MAX_SCREEN_SIZE.y; ++i)
      result += '\n';
    return result;
}();



bool isEscape(char c)
{
    switch (c) {
      case '\n':
      case '\r':
      case '\t':
      case '\b':
      case '\a':
      case '\f':
      case '\v':
      case '\0':
        return true;
    }
    return false;
}




ConsoleBuffer console_buffer {};


ConsoleBuffer::ConsoleBuffer()
{
    cache_max_y = 0;
    for (int i = 0; i < MAX_SCREEN_SIZE.y; ++i) {
      cache_max_x[i] = 0;
      buffer[i][MAX_SCREEN_SIZE.x] = 0;
    }
    cursor = {0, 0};
}




Coord cursorPosition(const ConsoleBuffer& buffer)
{
    return buffer.cursor;
}

void moveCursor(Direction direction, int amount, ConsoleBuffer& buffer)
{
    if (amount < 0) throw std::runtime_error("Negative cursor move distance");
    switch (direction) {
      case Direction::UP:
        if (buffer.cursor.y - amount < 0)
          throw std::runtime_error("Cannot move cursor up past the top of the screen");
        buffer.cursor.y -= amount;
      break;
      case Direction::DOWN:
        if (buffer.cursor.y + amount >= MAX_SCREEN_SIZE.y)
          throw std::runtime_error("Cannot move cursor down past the bottom of the screen");
        buffer.cursor.y += amount;
      break;
      case Direction::LEFT:
        if (buffer.cursor.x - amount < 0)
          throw std::runtime_error("Cannot move cursor left past the left of the screen");
        buffer.cursor.x -= amount;
      break;
      case Direction::RIGHT:
        if (buffer.cursor.x + amount >= MAX_SCREEN_SIZE.x)
          throw std::runtime_error("Cannot move cursor right past the right of the screen");
        buffer.cursor.x += amount;
      break;
    }
}
void moveCursor(Direction direction, ConsoleBuffer& buffer)
{
    moveCursor(direction, 1, buffer);
}

void moveCursor(Coord pos, ConsoleBuffer& buffer)
{
    if (buffer.cursor.x < 0 || buffer.cursor.y < 0 
     || buffer.cursor.x >= MAX_SCREEN_SIZE.x 
     || buffer.cursor.y >= MAX_SCREEN_SIZE.y)
      throw std::runtime_error("Cannot move cursor to invalid position");
    buffer.cursor = pos;
}

void unformattedWrite(const std::string &str, ConsoleBuffer &buffer)
{
    if (str.empty()) return;
    if (buffer.cursor.x + str.size() > MAX_SCREEN_SIZE.x)
      throw std::runtime_error("Buffer overflow");
    if (buffer.cache_max_y == MAX_SCREEN_SIZE.y)
      throw std::runtime_error("Buffer overflow");

    int line = buffer.cursor.y;
    int old_max_x = buffer.cache_max_x[line];

    if (line >= buffer.cache_max_y)
      buffer.cache_max_y = line + 1;
      
    if (buffer.cursor.x > old_max_x) {
      memset(buffer.buffer[line] + old_max_x, ' ', 
             buffer.cursor.x - old_max_x);
      buffer.cache_max_x[line] = buffer.cursor.x;
    }

    memcpy(buffer.buffer[line] + buffer.cursor.x, 
           str.data(), str.size());
    buffer.cursor.x += str.size();
    if (buffer.cursor.x > buffer.cache_max_x[line]) {
      buffer.cache_max_x[line] = buffer.cursor.x;
      buffer.buffer[line][buffer.cache_max_x[line]] = 0;
    }
}

void unformattedWrite(char c, ConsoleBuffer &buffer)
{
    unformattedWrite(std::string(1, c), buffer);
}

void write(char c, ConsoleBuffer &buffer)
{
    static const int TAB_SIZE = 4;
    auto nextTabStop = [] (int x) { return (x / TAB_SIZE + 1) * TAB_SIZE; };
    auto moveThisCursor = [&] (Coord pos) { moveCursor(pos, buffer); };
    Coord cur_pos = cursorPosition(buffer);
    switch (c) {
      case '\n':
        moveThisCursor({0, cur_pos.y + 1});
      break;
      case '\r':
        moveThisCursor({0, cur_pos.y});
      break;
      case '\t':
        moveThisCursor({nextTabStop(cur_pos.x), cur_pos.y});
      break;
      case '\b':
        if (cur_pos.x == 0) {
          if (cur_pos.y == 0) {}
          else moveThisCursor({buffer.cache_max_x[cur_pos.y], 
                               cur_pos.y - 1});
        }
        else {
          moveThisCursor({cur_pos.x - 1, cur_pos.y});
        }
      break;
      case '\0':
      break;
      case '\a':
      case '\f':
      case '\v':
        throw std::runtime_error("Unsupported character");
      default:
        unformattedWrite(c, buffer);
    }
}


void clearScreen()
{
    std::cout << CLEAR_SCREEN_STR;
}

void clearLine(ConsoleBuffer &buffer)
{
    int line = buffer.cursor.y;
    buffer.cache_max_x[line] = 0;
    buffer.buffer[line][0] = 0;
}

void clearConsole(ConsoleBuffer &buffer)
{
    memset(buffer.buffer, ' ', sizeof(buffer.buffer[0]) * buffer.cache_max_y);
    for (int i = 0; i < buffer.cache_max_y; ++i)
      buffer.buffer[i][MAX_SCREEN_SIZE.x] = 0;
    buffer.cursor = {0, 0};
    buffer.cache_max_y = 0;
}

void render(const ConsoleBuffer &buffer)
{
    clearScreen();
    for (int i = 0; i < buffer.cache_max_y; ++i)
      std::cout << buffer.buffer[i] << '\n';
}

}