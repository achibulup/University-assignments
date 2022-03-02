#ifndef IO_H
#define IO_H
#include <iostream>
#include <cstdio>
#include "consolemanip.h"

namespace Console
{
    
using Istream = std::istream;
extern Istream &cin;

class Ostream
{
  public:
    Ostream();
    Ostream(ConsoleBuffer &buffer);
    ~Ostream();

    explicit operator bool () const;

    /// insert to the underlying buffer
    Ostream& operator << (int);
    Ostream& operator << (char);
    Ostream& operator << (const std::string&);

    /// invoke the manipulator
    Ostream& operator << (Ostream& (*manipulator)(Ostream&));

    /// get/set the buffer cursor position
    Coord getPosition() const;
    Ostream& setPosition(Coord);

    ///calls render() on the underlying buffer
    Ostream& flush();

    Ostream& clearLine();
    Ostream& clear();

    ConsoleBuffer* getBuffer();
    const ConsoleBuffer* getBuffer() const;

  private:
    ConsoleBuffer *buffer = nullptr;
};
extern Ostream cout;

Ostream& flush(Ostream&);

struct SetPosFunc
{
    Coord pos;
};

Ostream& operator << (Ostream&, SetPosFunc);
SetPosFunc setPosition(Coord);

Ostream& clear(Ostream&); 
Ostream& clearLine(Ostream&);


/// write a string at a position
Ostream& operator << (Ostream&, const StrAndPos&);

}


#endif // IO_H