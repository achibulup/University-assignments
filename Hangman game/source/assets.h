#ifndef ASSETS_H
#define ASSETS_H
#include "consolemanip.h"

namespace Hangman
{
extern const std::string WORDS[];


/// corresponds to the virtual terminal line drawing characters
// l -> ┌   k -> ┐   j -> ┘   m -> └
// q -> ─   x -> │   n -> ┼
// w -> ┬   u -> ┤   t -> ├   v -> ┴
/// additional characters
// s -> \ .
// L -> ╔   K -> ╗   J -> ╝   M -> ╚
// Q -> ═   X -> ║   N -> ╬
// W -> ╦   U -> ╣   T -> ╠   V -> ╩
// '\n' -> NEXT_ROW
std::string toDrawString(const std::string &str);

extern const std::string TITLE;
extern const std::string HANGMAN_IMAGE;
extern const std::string GUESS_PROMPT;
extern const std::string GOOD_MESSAGE;
extern const std::string BAD_MESSAGE;
extern const std::string REPEAT_MESSAGE;
extern const std::string SHOW_BAD_GUESSES;
extern const std::string WIN_MESSAGE;
extern const std::string LOSE_MESSAGE;
extern const std::string REVEAL_MESSAGE;

extern const Console::Coord TITLE_POS;
extern const Console::Coord HANGMAN_IMAGE_POS;
extern const Console::Coord WORD_LINE;
extern const Console::Coord GUESS_PROMPT_LINE;
extern const Console::Coord GUESS_FEEDBACK_LINE;
extern const Console::Coord BAD_GUESSES_POS;

extern const Console::StrAndPos IMAGES_UPDATES[];

extern const int MAX_BAD_GUESSES;

std::string toLower(const std::string &str);

std::string chooseWord();

}

#endif // ASSETS_H