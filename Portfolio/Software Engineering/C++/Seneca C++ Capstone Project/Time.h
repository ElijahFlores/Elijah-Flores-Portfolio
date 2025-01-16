/***********************************************************************
// OOP244 Project
//
// File  Time.h
// Author  Elijah Alton Flores
// Email eaflores1@myseneca.ca
// ID 106480239
// Date March 20, 2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/

#ifndef SENECA_TIME_H
#define SENECA_TIME_H

#include <iostream>

namespace seneca {
    class Time {
        int m_time{};

    public:
        Time& reset();
        Time(unsigned int min = 0u);

        void write(std::ostream& ostr) const;
        void read(std::istream& istr);

        operator unsigned int()const;
        Time& operator*= (int val);
        Time& operator-= (const Time& D);
        Time operator-(const Time& T)const;

        virtual ~Time() = default;
    };
    std::ostream& operator<<(std::ostream& out, const Time& t);
    std::istream& operator>>(std::istream& in, Time& t);
}

#endif // !SENECA_TIME_H
