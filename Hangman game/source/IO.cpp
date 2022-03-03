#include <algorithm>
#include "IO.h"

namespace Console
{

Istream &cin = std::cin;
Ostream cout {console_buffer};


Ostream::Ostream() = default;
Ostream::Ostream(ConsoleBuffer &buffer) : buffer(&buffer) {}
Ostream::~Ostream()
{
    if (*this) this->flush();
}

Ostream::operator bool() const
{
    return this->buffer != nullptr;
}
Ostream& Ostream::operator << (int i)
{
    if (!*this) throw std::runtime_error("Ostream::operator<< called on an invalid buffer");
    return *this << std::to_string(i);
}

Ostream& Ostream::operator << (char c)
{
    if (!*this) throw std::runtime_error("Ostream::operator<< called on an invalid buffer");
    write(c, *buffer);
    return *this;
}

Ostream& Ostream::operator << (const std::string &str)
{
    if (!*this) throw std::runtime_error("Ostream::operator<< called on an invalid buffer");
    int start_x = this->buffer->cursor.x;
    for (auto it = str.begin(); it != str.end(); ++it) {
      if (isEscape(*it)) {
        if (*it == Console::NEXT_ROW) 
          this->setPosition({start_x, this->buffer->cursor.y + 1});
        else write(*it, *this->buffer);
      }
      else {
        auto end_of_token = std::find_if(it, str.end(), isEscape);
        std::string token = str.substr(it - str.begin(), end_of_token - it);
        unformattedWrite(token, *this->buffer);
        it = end_of_token;
        --it;
      }
    }
    return *this;
}

Ostream& operator << (Ostream &os, const StrAndPos &str)
{
    return os.setPosition(str.pos) << str.str;
}

Coord Ostream::getPosition() const
{
    if (!*this) throw std::runtime_error("Ostream::getPosition() called on an invalid buffer");
    return cursorPosition(*this->buffer);
}
Ostream& Ostream::setPosition(Coord pos)
{
    moveCursor(pos, *this->getBuffer());
    return *this;
}

Ostream& Ostream::flush()
{
    if (!*this) throw std::runtime_error("Ostream::flush() called on an invalid buffer");
    render(*this->buffer);
    return *this;
}

Ostream& Ostream::clear()
{
    if (!*this) throw std::runtime_error("Ostream::clear() called on an invalid buffer");
    Console::clearConsole(*this->buffer);
    return *this;
}
Ostream& Ostream::clearLine()
{
    if (!*this) throw std::runtime_error("Ostream::clearLine() called on an invalid buffer");
    Console::clearLine(*this->buffer);
    return *this;
}


ConsoleBuffer* Ostream::getBuffer() 
{
    return this->buffer;
}
const ConsoleBuffer* Ostream::getBuffer() const
{
    return this->buffer;
}


Ostream& flush(Ostream& os)
{
    os.flush();
    return os;
}

Ostream& operator << (Ostream &os, SetPosFunc f)
{
    os.setPosition(f.pos);
    return os;
}

SetPosFunc setPosition(Coord pos)
{
    return {pos};
}
Ostream& clear(Ostream& os)
{
    os.clear();
    return os;
}
Ostream& clearLine(Ostream& os)
{
    os.clearLine();
    return os;
}

}