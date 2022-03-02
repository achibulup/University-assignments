#include <cctype>
#include <algorithm>
#include "hangman.h"
#include "IO.h"
#include "assets.h"

namespace Hangman
{

enum class GameProgress {Playing, Won, Lost};

struct GameState
{
    std::string secret_word;
    int bad_guesses;
    int guesses;
    std::vector<char> guessed_letters;
    GameProgress progress;
}state;



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

bool isRepeated(char guess, GameState &game_state = state)
{
    return std::find(game_state.guessed_letters.begin(), 
                     game_state.guessed_letters.end(), guess) 
        != game_state.guessed_letters.end();
}

void addGuessedLetter(char guess, GameState &game_state = state)
{
    game_state.guessed_letters.push_back(guess);
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

void updateImage(int bad_guesses, GameState &game_state = state)
{
    int update_index = bad_guesses - 1;
    Console::cout << IMAGES_UPDATES[update_index];
}

void initGame()
{
    state.secret_word = chooseWord();
    state.bad_guesses = 0;
    state.guesses = 0;
    state.guessed_letters.clear();
    state.progress = GameProgress::Playing;

    Console::cout.setPosition(TITLE_LINE) << TITLE;
    Console::cout.setPosition(HANGMAN_IMAGE_LINE) << HANGMAN_IMAGE;
}

void playSequence()
{
    std::string guess_str 
        = getGuessStr(state.secret_word, state.guessed_letters);

    while(true) {
      Console::cout.setPosition(WORD_LINE).clearLine() << guess_str;
      Console::cout.setPosition(GUESS_PROMPT_LINE).clearLine() << GUESS_PROMPT;
      
      Console::cout.flush();
      if (state.bad_guesses == MAX_BAD_GUESSES) {
        state.progress = GameProgress::Lost;
        break;
      }
      if (checkWin(state.secret_word, state.guessed_letters)) {
        state.progress = GameProgress::Won;
        break;
      }

      std::string str;
      getline(Console::cin, str);
      str = toLower(str);
      if (str.size() != 1) {
        Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
        Console::cout << "Please enter a single letter." << '\n';
        continue;
      }
      char guess = str[0];
      if (isRepeated(guess, state)) {
        Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
        Console::cout << REPEAT_MESSAGE << guess;
        continue;
      }
      addGuessedLetter(guess, state);
      if (goodGuess(guess, state.secret_word)) {
        guess_str = getGuessStr(state.secret_word, state.guessed_letters);
        Console::cout.setPosition(WORD_LINE).clearLine() << guess_str;
        Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
        Console::cout << guess << GOOD_MESSAGE;
      } else {
        updateImage(++state.bad_guesses, state);
        Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
        Console::cout << guess << BAD_MESSAGE;
      }
    }

}

void ending()
{
    Console::cout.setPosition(GUESS_PROMPT_LINE).clearLine();
    Console::cout.setPosition(GUESS_FEEDBACK_LINE).clearLine();
    if (state.progress == GameProgress::Won) {
      Console::cout << WIN_MESSAGE << '\n';
    } 
    else {
      Console::cout << LOSE_MESSAGE << '\n';
      Console::cout << REVEAL_MESSAGE << state.secret_word << '\n';
    }
    Console::cout.flush();
}

void cleanUp()
{
    std::cout << "Press enter to continue...";
    std::cin.get();
    Console::clearConsole();
}

void run()
{
    initGame();
    playSequence();
    ending();
    cleanUp();
}

}