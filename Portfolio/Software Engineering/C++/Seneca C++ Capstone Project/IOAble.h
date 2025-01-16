/***********************************************************************
// OOP244 Project ms2
//
// File  IOAble.h
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

#ifndef SENECA_IOABLE_H
#define SENECA_IOABLE_H

#include <iostream>

namespace seneca {
    class IOAble {

    public:
        virtual std::ostream& write(std::ostream& out) const = 0;
        virtual std::istream& read(std::istream& in) = 0;

        virtual ~IOAble() = default;
    };

    std::ostream& operator<<(std::ostream& out, const IOAble& ioa);
    std::istream& operator>>(std::istream& in, IOAble& ioa);
}
#endif // !SENECA_IOABLE_H
