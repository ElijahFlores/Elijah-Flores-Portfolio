/***********************************************************************
// OOP244 Project
//
// File  TestPatient.cpp
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
#include "TestPatient.h"

using namespace std;

int nextTestTicket = 1;

namespace seneca {
    TestPatient::TestPatient() : Patient(nextTestTicket)
    {
        nextTestTicket++;
    }
    char seneca::TestPatient::type() const
    {
        return 'C';
    }
    ostream& TestPatient::write(ostream& ostr) const
    {
        if (&ostr == &cout) {
            ostr << "Contagion TEST" << endl;
        }
        Patient::write(ostr);
        return ostr;
    }
    istream& TestPatient::read(istream& istr)
    {
        Patient::read(istr);
        if (&istr != &cin) {
            nextTestTicket = this->number() + 1;
            istr.ignore(10000, '\n');
        }
        return istr;
    }
}