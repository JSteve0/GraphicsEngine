/// \file KeyBuffer.hpp
/// \brief Implementation of KeyBuffer class and any associated global functions.
/// \author Justin Stevens
/// \version A04

#include "KeyBuffer.hpp"

KeyBuffer::KeyBuffer ()
{
  reset();
}

void
KeyBuffer::setKeyDown (int key)
{
  keyIsPressed[key] = true;
}

void
KeyBuffer::reset ()
{
  for (auto &key : keyIsPressed)
  {
    key = false;
  }
}

void
KeyBuffer::setKeyUp (int key) 
{
  keyIsPressed[key] = false;
}

bool
KeyBuffer::isKeyDown (int key) const
{
  return keyIsPressed[key];
}