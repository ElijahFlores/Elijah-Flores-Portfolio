/***********************************************************************
// OOP244 Project
//
// File  Time.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"
#include "Utils.h"

#include <iostream>
#include <cstring>
#include <cmath> // Use pow function

using namespace std;

namespace seneca {
    Time& Time::reset()
    {
        m_time = U.getTime();
        return *this;
    }

    Time::Time(unsigned int min)
    {
        m_time = min;
    }
    void Time::write(ostream& ostr) const
    {
        int hours = m_time / 60;
        int mins = (m_time % 60);

        ostr.width(2);
        ostr.fill('0');
        ostr.setf(ios::right);

        ostr << hours;
        ostr << ":";
        ostr.width(2);
        ostr << mins;

        ostr.unsetf(ios::right);
    }
    void Time::read(istream& istr)
    {
        int done = 0;

        while (!done)
        {
            char hoursChar[3]{};
            char colon = 'X';
            char minsChar[8]{};
            int hours{};
            int mins{};
            int hoursLength{};
            int minsLength{};

            istr.get(hoursChar, 3, ':');
            istr.get(colon);

            if (colon != ':') {
                istr.setstate(ios::failbit);
                cout << "Bad time entry, retry (HH:MM): ";

                //Clear if error
                if (colon != '\n')
                {
                    istr.clear();
                    istr.ignore(10000, '\n');
                }
                else {
                    istr.clear();
                }
            }
            else {

                istr.get(minsChar, 3);
                //istr.ignore();
                //istr.get(minsChar, 8, ','); // For MS4
                hoursLength = strlen(hoursChar);
                minsLength = strlen(minsChar);

                //Switch Char to Int
                for (int i = 0; hoursChar[i]; i++) {
                    hours += ((hoursChar[i] - '0') * pow(10, (hoursLength - 1 - i)));
                }
                for (int i = 0; minsChar[i]; i++) {
                    mins += ((minsChar[i] - '0') * pow(10, (minsLength - 1 - i)));
                }

                m_time = (hours * 60) + mins;

                done = 1;
            }
        }
    }
    Time::operator unsigned int() const
    {
        return m_time;
    }

    Time& Time::operator*=(int val)
    {
        m_time *= val;

        return *this;
    }

    Time& Time::operator-=(const Time& D)
    {

        m_time = *this - D;

        return *this;
    }
    Time Time::operator-(const Time& T) const
    {
        int temp;

        if (m_time < T.m_time) {
            temp = m_time + 1440 - T.m_time;
        }
        else {
            temp = m_time - T.m_time;
        }

        return temp;
    }
    ostream& operator<<(ostream& out, const Time& t)
    {
        t.write(out);
        return out;
    }
    istream& operator>>(istream& in, Time& t)
    {
        t.read(in);
        return in;
    }
}