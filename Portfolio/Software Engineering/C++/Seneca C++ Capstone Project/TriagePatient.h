/***********************************************************************
// OOP244 Project
//
// File  TriagePatient.h
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

#ifndef SENECA_TRIAGE_PATIENT_H
#define SENECA_TRIAGE_PATIENT_H

namespace seneca {
    class TriagePatient : public Patient {
        char* m_symptoms{};
    public:
        TriagePatient();
        virtual ~TriagePatient();
        //Rule of 3
        TriagePatient(const TriagePatient&);
        TriagePatient& operator=(const TriagePatient&);

        //Own Functions
        void setEmpty();
        void alloCopySymptoms(char symptoms[]);

        char type()const;

        //pure virtual function overwrites.
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);
    };
}

#endif // !SENECA_TRIAGE_PATIENT_H

