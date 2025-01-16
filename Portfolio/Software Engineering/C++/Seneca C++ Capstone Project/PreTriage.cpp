/***********************************************************************
// OOP244 Project
//
// File  PreTriage.cpp
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
//#include "Patient.h"
//#include "Utils.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include "PreTriage.h"
#include "TestPatient.h"
#include "TriagePatient.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace seneca {
    Time PreTriage::getWaitTime(const Patient& P) const
    {
        size_t numberPatient = 0;

        for (int i = 0; i < m_lineUpValue; i++) {
            if (m_patientLineup[i]->type() == P.type()) {
                numberPatient++;
            }
        }

        return P == 'C' ? numberPatient * m_waitTimeTest : numberPatient * m_waitTimeTriage;
    }

    void PreTriage::setAverageWaitTime(Patient& P)
    {
        if (P == 'C') {
            m_waitTimeTest = ((U.getTime() - P.time()) + (m_waitTimeTest * (P.number() - 1))) / P.number();
        }
        else if (P == 'T') {
            m_waitTimeTriage = ((U.getTime() - P.time()) + (m_waitTimeTriage * (P.number() - 1))) / P.number();
        }
    }

    int PreTriage::indexOfFirstInLine(const char typeChar) const
    {
        int indexFound = -1;
        size_t done = 0;

        for (int i = 0; i < m_lineUpValue && done == 0; i++) {
            if (m_patientLineup[i]->type() == typeChar) {
                indexFound = i;
                done = 1;
            }
        }

        return indexFound;
    }

    void PreTriage::load(ifstream& in)
    {
        Patient* localPatientLineup[maximumLineUpValue]{};
        char localType{};
        int done = 0;

        cout << "Loading data..." << endl;
        if (in.is_open()) {           
            in >> m_waitTimeTest;
            in.ignore();
            in >> m_waitTimeTriage;
            in.ignore();

            for (int i = 0; i < maximumLineUpValue && done == 0; i++) {
                in.get(localType);
                in.ignore();

                if (localType == 'C' && !in.eof()) {
                    localPatientLineup[i] = { new TestPatient };
                }
                else if (localType == 'T' && !in.eof()) {
                    localPatientLineup[i] = { new TriagePatient };
                }

                if (localType && !in.eof()) {
                    localPatientLineup[i]->read(in);
                    m_patientLineup[i] = localPatientLineup[i];
                    m_lineUpValue++;
                }

                if (!in.eof() && m_lineUpValue >= maximumLineUpValue) {
                    cout << "Warning: number of records exceeded 100" << endl;
                    cout << m_lineUpValue << " Records imported..." << endl;
                    done = 1;
                }

                if (m_lineUpValue == 0) {
                    cout << "No data or bad data file!" << endl;
                    done = 1;
                }

                if (in.eof() && m_lineUpValue != 0) {
                    cout << m_lineUpValue << " Records imported..." << endl;
                    done = 1;
                }
            }
        }
        else {
            cout << "No data or bad data file!" << endl;
        }
    }

    void PreTriage::save()
    {
        ofstream file(m_fileName);
        size_t testCount = 0;
        size_t triageCount = 0;

        cout << "Saving lineup..." << endl;

        file << m_waitTimeTest << "," << m_waitTimeTriage << endl;

        if (m_patientLineup && m_patientLineup[0]) {
            for (int i = 0; i < maximumLineUpValue && m_patientLineup[i]; i++) {
                if (m_patientLineup[i]->type() == 'C') {
                    testCount++;
                }
                else if (m_patientLineup[i]->type() == 'T') {
                    triageCount++;
                }
                m_patientLineup[i]->write(file) << endl;
            }
        }

        cout << testCount << " Contagion Tests and " << triageCount << " Triage records were saved!" << endl;
        
    }

    void PreTriage::lineup()
    {
        Menu sub_menu("Select The Lineup:\n1- Contagion Test\n2- Triage", 1);
        int selection;
        int rowCount = 1;

        switch (sub_menu >> selection) {
        case 1:
            cout << "Row - Patient name                                          OHIP     Tk #  Time" << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
            for (int i = 0; i < m_lineUpValue; i++) {
                if (m_patientLineup[i]->type() == 'C') {
                    clog << rowCount << "   - ";
                    m_patientLineup[i]->write(clog) << endl;
                    rowCount++;
                }
            }

            if (rowCount == 1) {
                cout << "Line up is empty!\n";
            }
            break;
        case 2:
            cout << "Row - Patient name                                          OHIP     Tk #  Time" << endl;
            cout << "-------------------------------------------------------------------------------" << endl;
            for (int i = 0; i < m_lineUpValue; i++) {
                if (m_patientLineup[i]->type() == 'T') {
                    clog << rowCount << "   - ";
                    m_patientLineup[i]->write(clog) << endl;
                    rowCount++;
                }
            }

            if (rowCount == 1) {
                cout << "Line up is empty!\n";
            }
            break;
        }
        cout << "-------------------------------------------------------------------------------";
    }

    void PreTriage::admit()
    {
        int indexNextPatient = 0;
        Menu sub_menu("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 1);
        int selection;
        Time callTime = U.getTime();

        switch (sub_menu >> selection) {
        case 1:
            indexNextPatient = indexOfFirstInLine('C');
            if (indexNextPatient == -1) {
                cout << "Lineup is empty!\n" << endl;
            }
            else {
                cout << endl;
                cout << "******************************************" << endl;
                //Confusing
                //cout << "Call time: [" << m_patientLineup[indexNextPatient]->time() << "]" << endl;
                cout << "Call time: [" << callTime << "]" << endl;
                cout << "Calling at for ";
                m_patientLineup[indexNextPatient]->write(cout);
                cout << "******************************************";
                cout << endl;
                setAverageWaitTime(*m_patientLineup[indexNextPatient]);
                U.removeDynamicElement<Patient>(m_patientLineup, indexNextPatient, m_lineUpValue);
            }
            break;
        case 2:
            indexNextPatient = indexOfFirstInLine('T');
            if (indexNextPatient == -1) {
                cout << "Lineup is empty!\n" << endl;
            }
            else {
                cout << endl;
                cout << "******************************************" << endl;
                //Confusing
                //cout << "Call time: [" << m_patientLineup[indexNextPatient]->time() << "]" << endl;
                cout << "Call time: [" << callTime << "]" << endl;
                cout << "Calling at for ";
                m_patientLineup[indexNextPatient]->write(cout);
                cout << "******************************************";
                cout << endl;
                setAverageWaitTime(*m_patientLineup[indexNextPatient]);
                U.removeDynamicElement<Patient>(m_patientLineup, indexNextPatient, m_lineUpValue);
            }
            break;
        }
    }

    void PreTriage::Register()
    {
        Menu sub_menu("Select Type of Registration:\n1- Contagion Test\n2- Triage", 1);
        int selection;

        if (m_lineUpValue == maximumLineUpValue) {
            cout << "Line up full!";
        }
        else {
            switch (sub_menu >> selection) {
            case 1:
                m_patientLineup[m_lineUpValue] = { new TestPatient };
                m_patientLineup[m_lineUpValue]->setArrivalTime();
                cout << "Please enter patient information: " << endl;
                m_patientLineup[m_lineUpValue]->read(cin);
                cout << endl;

                cout << "******************************************" << endl;
                m_patientLineup[m_lineUpValue]->write(cout);
                cout << "Estimated Wait Time: " << getWaitTime(*m_patientLineup[m_lineUpValue]);
                cout << endl;
                cout << "******************************************" << endl;
                m_lineUpValue++;

                break;
            case 2:
                m_patientLineup[m_lineUpValue] = { new TriagePatient };
                m_patientLineup[m_lineUpValue]->setArrivalTime();
                cout << "Please enter patient information: " << endl;
                m_patientLineup[m_lineUpValue]->read(cin);
                cout << endl;

                cout << "******************************************" << endl;
                m_patientLineup[m_lineUpValue]->write(cout);
                cout << "Estimated Wait Time: " << getWaitTime(*m_patientLineup[m_lineUpValue]);
                cout << endl;
                cout << "******************************************" << endl;
                m_lineUpValue++;

                break;
            }
        }

        
    }

    PreTriage::PreTriage(const char* fileName)
    {
        if (fileName) {
            delete[] m_fileName;
            m_fileName = nullptr;
            m_fileName = new char[strlen(fileName) + 1]{};
            m_fileName[0] = '\0';
            strcpy(m_fileName, fileName);
        }

        m_waitTimeTest = 15;
        m_waitTimeTriage = 5;
        
        ifstream file(fileName);

        load(file);
    }
    PreTriage::~PreTriage()
    {
        //To Do: Saves the data.
        for (int i = 0; i < m_lineUpValue; i++) {
            m_patientLineup[i]->setEmpty();
            delete m_patientLineup[i];
            m_patientLineup[i] = nullptr;
        }
        delete[] m_fileName;
        m_fileName = nullptr;
    }
    void PreTriage::run()
    {
        Menu m("\nGeneral Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup");
        int selection;
        while (m >> selection) {
            switch (selection) {
            case 1: 
                Register();
                break;
            case 2:
                admit();
                break;
            case 3:
                lineup();
                break;
            default:
                cout << "This will never happen!!!!" << endl;
                break;
            }
        }

        save();
    }
}