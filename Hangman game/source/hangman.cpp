#include <cctype>
#include <algorithm>
#include "hangman.h"
#include "IO.h"
#include "assets.h"

namespace Hangman
{

enum class GameProgress {PLAYING, WON, LOST};

struct GameState
{
    std::string secret_word;
    std::vector<char> guessed_letters;
    std::vector<char> bad_guesses;
    GameProgress progress;
}global_state;

const char INVALID = '\0';




std::string getGuessStr(std::string_view secret_word, 
                        const std::vector<char> &guessed_letters)
{
    std::string result;
    for (char c : secret_word) {
      bool guessed = std::find(guessed_letters.begin(), 
                               guessed_letters.end(), c) 
                  != guessed_letters.end();
      if (guessed) result += c;
      else result += '_';
    }
    return result;
}

void showInitial(GameState &state = global_state)
{
    Console::cout.setPosition(HANGMAN_IMAGE_POS) << HANGMAN_IMAGE;
    Console::cout.setPosition(WORD_LINE).clearLine();
    Console::cout << getGuessStr(state.secret_word, state.guessed_letters);
}

void refreshPrompt(GameState& = global_state)
{
    Console::cout.setPosition(GUESS_PROMPT_LINE).clearLine() << GUESS_PROMPT;
}

char getPlayerGuess()
{
    std::string input;
    getline(Console::cin, input);
    if (input.size() != 1) {
      Console::cout << INVALID_GUESS_MESSAGE;
      return INVALID;
    }
    char c = input[0];
    if (!std::isalpha(c)) {
      Console::cout << INVALID_GUESS_MESSAGE;
      return INVALID;
    }
    return std::tolower(static_cast<unsigned char>(c));
}

bool isRepeated(char guess, GameState &state = global_state)
{
    return std::find(state.guessed_letters.begin(), 
                     state.guessed_letters.end(), guess) 
        != state.guessed_letters.end();
}

void addGuessedLetter(char guess, GameState &state = global_state)
{
    state.guessed_letters.push_back(guess);
}

bool goodGuess(char guess, std::string_view secret_word)
{
    return std::find(secret_word.begin(), secret_word.end(), guess) 
        != secret_word.end();
} 

bool checkWin(std::string_view secret_word, 
              const std::vector<char> &guessed_letters)
{
    auto notGuessed = [&guessed_letters](char c) {
        return std::find(guessed_letters.begin(), 
                         guessed_letters.end(), c) 
            == guessed_letters.end();
    };
    return std::find_if(secret_word.begin(), secret_word.end(), notGuessed) 
        == secret_word.end();
}

bool checkLose(const std::vector<char> &bad_guesses)
{
    return bad_guesses.size() >= MAX_BAD_GUESSES;
}

void updateImage(int bad_guesses, GameState &state = global_state)
{
    int update_index = bad_guesses - 1;
    auto rendered = IMAGES_UPDATES[update_index];
    rendered.pos = rendered.pos + HANGMAN_IMAGE_POS;
    Console::cout << rendered;
}

void update(char guess, GameState &state = global_state)
{
    if (isRepeated(guess, state)) {
      Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
      Console::cout << REPEAT_MESSAGE << guess;
      return;
    }
    addGuessedLetter(guess, state);
    if (goodGuess(guess, state.secret_word)) {
      Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
      Console::cout << guess << GOOD_MESSAGE;

      std::string guess_str = getGuessStr(state.secret_word, 
                                          state.guessed_letters);
      Console::cout.setPosition(WORD_LINE).clearLine() << guess_str;

      if (checkWin(state.secret_word, state.guessed_letters))
        state.progress = GameProgress::WON;
    } else {
      state.bad_guesses.push_back(guess);
      updateImage(state.bad_guesses.size(), state);
      Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
      Console::cout << guess << BAD_MESSAGE;

      Console::cout.setPosition(BAD_GUESSES_POS) << SHOW_BAD_GUESSES;
      Console::Coord bad_guess_pos = BAD_GUESSES_POS;
      bad_guess_pos.y += state.bad_guesses.size();
      Console::cout.setPosition(bad_guess_pos) << guess;

      if (checkLose(state.bad_guesses))
        state.progress = GameProgress::LOST;
    }
}

void initGame(GameState &state = global_state)
{
    state.secret_word = chooseWord();
    state.guessed_letters.clear();
    state.bad_guesses.clear();
    state.progress = GameProgress::PLAYING;

    Console::cout.setPosition(TITLE_POS) << TITLE;
}

void ending(GameState &state = global_state)
{
    Console::cout.setPosition(GUESS_PROMPT_LINE).clearLine();
    Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
    if (state.progress == GameProgress::WON) {
      Console::cout << WIN_MESSAGE << '\n';
    } 
    else {
      Console::cout << LOSE_MESSAGE << '\n';
      Console::cout << REVEAL_MESSAGE << state.secret_word << '\n';
    }
    Console::cout.flush();
}

void playSequence(GameState &state = global_state)
{
    showInitial(state);
    while(state.progress == GameProgress::PLAYING) {
      refreshPrompt();
      Console::cout.flush();
      char guess = getPlayerGuess();
      update(guess, state);
    }
    ending(state);
}

void cleanUp()
{
    std::cout << CONTINUE_PROMPT;
    std::cin.get();
    Console::clearConsole();
}

void run()
{
    initGame();
    playSequence();
    cleanUp();
}

}