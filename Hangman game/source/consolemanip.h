#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

namespace Console
{

struct Coord { int x, y; };

constexpr Coord MAX_SCREEN_SIZE {200, 40};

struct ConsoleBuffer
{
    char buffer[MAX_SCREEN_SIZE.y][MAX_SCREEN_SIZE.x + 1];
    Coord cursor;
    int cache_max_y;
    int cache_max_x[MAX_SCREEN_SIZE.y];
    ConsoleBuffer();
};
extern ConsoleBuffer console_buffer;

struct StrAndPos
{
    std::string str;
    Coord pos;
};

enum class Direction : int { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

bool isEscape(char);

Coord cursorPosition(const ConsoleBuffer& = console_buffer);
void moveCursor(Direction, int amount, ConsoleBuffer& = console_buffer);
void moveCursor(Direction, ConsoleBuffer& = console_buffer);
void moveCursor(Coord pos, ConsoleBuffer& = console_buffer);

void unformattedWrite(const std::string&, ConsoleBuffer& = console_buffer);
void unformattedWrite(char, ConsoleBuffer& = console_buffer);

void write(char, ConsoleBuffer& = console_buffer);

void clearLine(ConsoleBuffer& = console_buffer);
void clearConsole(ConsoleBuffer& = console_buffer);
void render(const ConsoleBuffer& = console_buffer);


}

#endif // CONSOLE_H