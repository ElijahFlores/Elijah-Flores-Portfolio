/***********************************************************************
// OOP244 Project ms2
//
// File  IOAble.cpp
// Author  Elijah Alton Flores
// ID 106480239
// Email eaflores1@myseneca.ca
// Date March 23, 2024
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include "IOAble.h"
#include <cstring>
#include <iostream>

namespace seneca {
    std::ostream& operator<<(std::ostream& out, const IOAble& ioa)
    {
        ioa.write(out);
        return out;
    }
    std::istream& operator>>(std::istream& in, IOAble& ioa)
    {
        ioa.read(in);
        return in;
    }
}
