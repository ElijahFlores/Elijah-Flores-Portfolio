/***********************************************************************
// OOP244 Project
//
// File  PreTriage.h
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

#ifndef SENECA_PRETRIAGE_H
#define SENECA_PRETRIAGE_H
#include <iostream>

#include "Time.h"
#include "Patient.h"

const int maximumLineUpValue = 100;

namespace seneca {
    class PreTriage {
        Time m_waitTimeTest{};
        Time m_waitTimeTriage{};
        Patient* m_patientLineup[maximumLineUpValue]{};
        char* m_fileName{};
        int m_lineUpValue{};

        //Private Methods
        Time getWaitTime(const Patient&) const;
        void setAverageWaitTime(Patient&);
        int indexOfFirstInLine(const char typeChar)const;
        void load(std::ifstream& in);
        void save();
        void lineup();
        void admit();
        void Register();

    public:
        PreTriage(const char* fileName);
        virtual ~PreTriage();

        //Public Methods
        void run();
    };
}

#endif // !SENECA_PRETRIAGE_H
