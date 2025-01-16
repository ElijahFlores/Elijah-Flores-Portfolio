/***********************************************************************
// OOP244 Project
//
// File  TriagePatient.cpp
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
#include "TriagePatient.h"

using namespace std;
int nextTriageTicket = 1;

namespace seneca {
    TriagePatient::TriagePatient() : Patient(nextTriageTicket)
    {
        nextTriageTicket++;
    }
    TriagePatient::~TriagePatient()
    {
        setEmpty();
    }
    TriagePatient::TriagePatient(const TriagePatient& T)
    {
        *this = T;
    }
    TriagePatient& TriagePatient::operator=(const TriagePatient& T)
    {
        setEmpty();

        if (T.m_symptoms && T.m_symptoms[0]) {
            m_symptoms = new char[strlen(T.m_symptoms) + 1] {};
            strcpy(m_symptoms, T.m_symptoms);
        }

        return *this;
    }
    void TriagePatient::setEmpty()
    {
        delete[] m_symptoms;
        m_symptoms = nullptr;
    }
    void TriagePatient::alloCopySymptoms(char symptoms[])
    {
        if (m_symptoms) {
            setEmpty();
        }

        m_symptoms = new char[strlen(symptoms) + 1];
        strcpy(m_symptoms, symptoms);
    }
    char TriagePatient::type() const
    {
        return 'T';
    }
    std::ostream& TriagePatient::write(std::ostream& ostr) const
    {
        if (&ostr == &cout) {
            ostr << "TRIAGE" << endl;
            Patient::write(ostr);
            ostr << "Symptoms: " << m_symptoms << endl;
        }
        else if (&ostr == &clog){
            Patient::write(ostr);
        }
        else {
            Patient::write(ostr);
            ostr << "," << m_symptoms;
        }

        return ostr;
    }
    std::istream& TriagePatient::read(std::istream& istr)
    {
        char symptoms[511 + 1]{};

        if (m_symptoms && m_symptoms[0]) {
            setEmpty();
        }
        
        Patient::read(istr);
        
        if (&istr != &cin) {
            istr.ignore();
            istr.get(symptoms, 511, '\n');

            alloCopySymptoms(symptoms);

            nextTriageTicket = this->number() + 1;
            //istr.ignore(10000, '\n');
        }
        else {
            cout << "Symptoms: ";
            istr.get(symptoms, 511, '\n');

            alloCopySymptoms(symptoms);
        }

        if (!istr) {
            setEmpty();
        }

        istr.ignore(10000, '\n');

        return istr;
    }
}