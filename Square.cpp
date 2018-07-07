#include "constants.h"
#include "Square.h"

const Square& Square::operator+(Square& s){
    this->value+=s.value;
    return *this;
}

