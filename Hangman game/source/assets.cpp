#include <random>
#include <chrono>
#include "assets.h"

namespace Hangman
{

const std::string WORDS[] {
    "apple", "banana", "orange", "pear", "grape", "strawberry", "tomato", 
    "watermelon", "pineapple", "peach", "cherry", "mango", "kiwi", "lemon", 
    "lime", "coconut", "avocado", "eggplant", "potato", "carrot", "cucumber",
    "onion", "garlic", "pepper", "parsley", "basil", "rosemary", "thyme", 
    "coriander", "lavender", "mint", "rose", "dill", "chive", "cabbage", 
    "broccoli", "spinach", "lettuce", "cauliflower", "mushroom"
};
std::string toDrawString(const std::string &str)
{
    std::string result(str);
#define MAKE_CASE(code, char) case code: c = char; break
    for (char &c : result) {
      switch (c) {
        MAKE_CASE('l', '\332');
        MAKE_CASE('k', '\277');
        MAKE_CASE('j', '\331');
        MAKE_CASE('m', '\300');
        MAKE_CASE('q', '\304');
        MAKE_CASE('x', '\263');
        MAKE_CASE('n', '\305');
        MAKE_CASE('w', '\302');
        MAKE_CASE('u', '\264');
        MAKE_CASE('t', '\303');
        MAKE_CASE('v', '\301');
        MAKE_CASE('s', '\\');
        MAKE_CASE('L', '\311');
        MAKE_CASE('K', '\273');
        MAKE_CASE('J', '\274');
        MAKE_CASE('M', '\310');
        MAKE_CASE('Q', '\315');    
        MAKE_CASE('X', '\272');
        MAKE_CASE('N', '\316');
        MAKE_CASE('W', '\313');
        MAKE_CASE('U', '\270');
        MAKE_CASE('T', '\314');
        MAKE_CASE('V', '\312');
        MAKE_CASE('\n', Console::NEXT_ROW);
      }
    }
    return result;
#undef MAKE_CASE
}

const std::string TITLE = "Hangman game!";
const std::string HANGMAN_IMAGE = toDrawString(R"(
    LQQQQQQK
    X      x
    X
    X
    X
  #qXqqqqqqqqq#
 /  X        /x
#qqqqqqqqqqq#/
mqqqqqqqqqqqj)");
const std::string GUESS_PROMPT = "Guess a letter: ";
const std::string GOOD_MESSAGE = " is in the secret word";
const std::string BAD_MESSAGE = " is not in the secret word";
const std::string REPEAT_MESSAGE = "You already guessed the letter "; 
const std::string SHOW_BAD_GUESSES = "Bad guesses: ";
const std::string WIN_MESSAGE = "You win!";
const std::string LOSE_MESSAGE = "You lose!";
const std::string REVEAL_MESSAGE = "The secret word was: ";

const Console::Coord TITLE_POS = {5, 0};
const Console::Coord HANGMAN_IMAGE_POS = {2, 1};
const Console::Coord WORD_LINE = {0, 11};
const Console::Coord GUESS_PROMPT_LINE = {0, 14};
const Console::Coord GUESS_FEEDBACK_LINE = {0, 13};
const Console::Coord BAD_GUESSES_POS = {22, 3};

const Console::StrAndPos IMAGES_UPDATES[] {
    {"O", HANGMAN_IMAGE_POS + Console::Coord{11, 3}},
    {"|", HANGMAN_IMAGE_POS + Console::Coord{11, 4}},
    {"/", HANGMAN_IMAGE_POS + Console::Coord{10, 4}},
    {"\\", HANGMAN_IMAGE_POS + Console::Coord{12, 4}},
    {"/", HANGMAN_IMAGE_POS + Console::Coord{10, 5}},
    {"\\", HANGMAN_IMAGE_POS + Console::Coord{12, 5}}
};

const int MAX_BAD_GUESSES = 6;

int random(int low, int high)
{
    using namespace std::chrono;
    static std::mt19937 generator(system_clock::now().time_since_epoch().count());
    return low + (generator() % (high - low + 1));
}

std::string toLower(const std::string &str)
{
    std::string result(str);
    for (char &c : result)
      c = tolower(static_cast<unsigned char>(c));
    return result;
}

std::string chooseWord()
{
    using std::size;
    int index = random(0, size(WORDS) - 1);
    return std::string(toLower(WORDS[index]));
}

}