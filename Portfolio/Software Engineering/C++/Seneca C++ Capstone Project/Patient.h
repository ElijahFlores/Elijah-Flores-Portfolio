#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H

#include <iostream>
#include "Time.h"
#include "IOAble.h"
#include "Ticket.h"

#define MAX_NAME_LENGTH 50

namespace seneca {
    class Patient : public IOAble {
        char* m_name{};
        int m_ohipNumber{};
        Ticket m_ticket{};
    public:
        Patient() = default;
        Patient(int ticketNumber);
        Patient(const Patient&);
        Patient& operator=(const Patient&);
        virtual ~Patient();

        //Own Functions
        void setEmpty();
        void alloCopyName(char name[]);
        int ohipNumber()const;

        //Member Functions
        virtual char type() const = 0;

        //Operator== Overloads
        bool operator==(char RO) const;
        bool operator==(const Patient& RO) const;

        void setArrivalTime();
        Time time()const;
        int number()const;

        //Cast Overloads
        operator bool() const;
        operator char*() const;

        //pure virtual function overwrites.
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);

    };
}

#endif // !SENECA_PATIENT_H
