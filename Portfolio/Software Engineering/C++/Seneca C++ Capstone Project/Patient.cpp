/***********************************************************************
// OOP244 Project
//
// File  Patient.cpp
// Author  Elijah Alton Flores
// Email eaflores1@myseneca.ca
// ID 106480239
// Date April 8, 2024
// I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "Patient.h"
#include "Utils.h"

#include <iostream>
#include <cstring>
#include <cmath> // Use pow function

using namespace std;

namespace seneca {
    Patient::Patient(int ticketNumber)
    {
        m_ticket = ticketNumber;
    }
    Patient::Patient(const Patient& P)
    {
        *this = P;
    }
    Patient& Patient::operator=(const Patient& P)
    {
        //clean up (deallocate previously allocated dynamic memory)
        delete[] m_name;
        m_name = nullptr;

        if (bool(P)) {
            m_ohipNumber = P.m_ohipNumber;

            if (P.m_name && P.m_name[0]) {
                m_name = new char[strlen(P.m_name) + 1] {};
                strcpy(m_name, P.m_name);
                m_ticket = P.m_ticket;
            }
            else {
                delete[] m_name;
                m_name = nullptr;
            }
        }
        else {
            setEmpty();
        }

        return *this;
    }

    Patient::~Patient()
    {
        setEmpty();
    }

    void Patient::setEmpty()
    {
        delete[] m_name;
        m_name = nullptr;
        m_ohipNumber = 0;
    }

    void Patient::alloCopyName(char name[])
    {
        if (m_name) {
            delete[] m_name;
            m_name = nullptr;
        }

        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
    }

    int Patient::ohipNumber() const
    {
        return m_ohipNumber;
    }

    bool Patient::operator==(char RO) const
    {
        return this->type() == RO;
    }

    bool Patient::operator==(const Patient& RO) const
    {
        return this->type() == RO.type();
    }

    void Patient::setArrivalTime()
    {
        m_ticket.resetTime();
    }

    Time Patient::time() const
    {
        return m_ticket.time();
    }

    int Patient::number() const
    {
        return m_ticket.number();
    }

    Patient::operator bool() const
    {
        return (m_ticket.number() > 0 && m_name && m_name[0] && (m_ohipNumber > 99999999 && m_ohipNumber <= 999999999));
    }

    Patient::operator char* () const
    {
        return &m_name[0];
    }

    ostream& Patient::write(ostream& ostr) const
    {
        if (&ostr == &cout) {
            if (m_name && m_name[0]) {

                m_ticket.write(ostr) << endl;
                ostr << m_name;
                ostr << ", OHIP: " << m_ohipNumber << endl;
            }
            else {
                ostr << "Invalid Patient Record" << endl;;
            }
        }
        else if (&ostr == &clog) {
            if (m_name && m_name[0]) {

                ostr.fill('.');
                ostr.width(53);
                ostr.setf(ios::left);
                ostr << m_name;
                ostr.unsetf(ios::left);
                ostr << m_ohipNumber;

                ostr.fill(' ');
                ostr.width(5);
                ostr.setf(ios::right);
                ostr << m_ticket.number();
                ostr.unsetf(ios::right);

                ostr << " " << m_ticket.time();
            }
            else {
                ostr << "Invalid Patient Record" << endl;
            }
        }
        else {
            ostr << type() << ",";
            ostr << m_name << ",";
            ostr << m_ohipNumber << ",";
            ostr << m_ticket.number() << ",";
            ostr << m_ticket.time();
        }
        return ostr;
    }

    istream& Patient::read(istream& istr)
    {
        char name[MAX_NAME_LENGTH + 1]{};
        int ohipNumber = 0;
        int ohipLength = 0;
        char ohipChar[9 + 1]{};
        int done = 0;

        if (&istr == &cin) {
            cout << "Name: ";
            istr.get(name, 51, '\n');

            alloCopyName(name);

            istr.ignore(10000, '\n');
            
            cout << "OHIP: ";
            while (!done) {
                istr >> ohipNumber;

                if (istr) {
                    if (ohipNumber > 99999999 && ohipNumber <= 999999999) {
                        m_ohipNumber = ohipNumber;
                        istr.ignore(10000, '\n');
                        done = 1;
                    }
                    else {
                        cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
                        istr.clear();
                        istr.ignore(10000, '\n');
                    }
                }
                else {
                    istr.clear();
                    istr.ignore(10000, '\n');
                    cout << "Bad integer value, try again: ";
                }
            }
        }
        else {
            istr.get(name, 51, ',');

            //Check if name is not null
            if (name[0]) {
                alloCopyName(name);

                istr.ignore(10000, ',');

                istr.get(ohipChar, 10, ',');
                ohipLength = strlen(ohipChar);

                //Switch Char to Int
                for (int i = 0; ohipChar[i]; i++) {
                    ohipNumber += ((ohipChar[i] - '0') * pow(10, (ohipLength - 1 - i)));
                }

                if (istr) {
                    if (ohipNumber > 99999999 && ohipNumber <= 999999999) {
                        m_ohipNumber = ohipNumber;
                        done = 1;
                    }
                    else {
                        cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
                        istr.clear();
                        istr.ignore(10000, '\n');
                    }
                }
                else {
                    istr.clear();
                    istr.ignore(10000, '\n');
                    cout << "Bad integer value, try again: ";
                }

                istr.ignore(10000, ',');

                m_ticket.read(istr);
            }
            else {
                setEmpty();
            }
        }

        return istr;
    }
}