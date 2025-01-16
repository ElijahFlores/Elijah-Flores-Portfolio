/***********************************************************************
// OOP244 Project
//
// File  TestPatient.h
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

#ifndef SENECA_TEST_PATIENT_H
#define SENECA_TEST_PATIENT_H

namespace seneca {
    class TestPatient : public Patient {
    public:
        TestPatient();
        char type()const;

        virtual ~TestPatient() = default;

        //pure virtual function overwrites.
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);
    };

}

#endif // !SENECA_TEST_PATIENT_H
