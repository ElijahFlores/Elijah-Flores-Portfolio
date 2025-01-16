/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Elijah Alton Flores
Student ID#: 106480239
Email      : eaflores1@myseneca.ca
Section    : ZGG

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for atoi

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;

    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (patient == NULL)
        {
            printf("*** No records found ***\n");
        }
        else if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i, freeIndex = 0;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            freeIndex = i;
            break;
        }
    }

    if (freeIndex == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[freeIndex].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[freeIndex]);
        printf("*** New patient record added ***\n\n");

    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int patientNumber, returnNumber;

    printf("Enter the patient number: ");
    patientNumber = inputIntRange(0, 9999);
    putchar('\n');
    returnNumber = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (returnNumber == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        menuPatientEdit(&patient[returnNumber]);
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int patientNumber, returnNumber, selection;

    printf("Enter the patient number: ");
    patientNumber = inputIntRange(0, 9999);
    putchar('\n');
    returnNumber = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (returnNumber == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        displayPatientData(&patient[returnNumber], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        selection = !(inputCharStringOption("yn") == 'y');
        if (!selection)
        {

            //strcpy(patient[returnNumber].name, '\0');
            patient[returnNumber].patientNumber = 0;
            //strcpy(patient[returnNumber].phone.number, '\0');
            //strcpy(patient[returnNumber].phone.description, '\0');
            printf("Patient record has been removed!\n");
            while (getchar() != '\n')
            {
                ; // do nothing!
            }
            putchar('\n');
        }
        else
        {
            printf("Operation aborted.\n");
            while (getchar() != '\n')
            {
                ; // do nothing!
            }
            putchar('\n');
        }
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// View ALL scheduled appointments
// Todo:


void viewAllAppointments(const struct ClinicData data[])
{
    int i = 0, j = 0;
    int sortedIndexData[MAX_APPOINTMENTS] = { 0 }, sortedTimeComputation[MAX_APPOINTMENTS] = { 0 }, patientIndexData[MAX_APPOINTMENTS] = { 0 };
    int temp = 0, tempIndex = 0;
    int countAppointment = 0;

    displayScheduleTableHeader(&data->appointments->date, 1);

    //Count number of appointments and put scoring/weight for the time for sorting comparison purposes
    //for (i = 0; strlen(&data->appointments[i].time.hour) == 1; i++) TO FIX
    for (i = 0; i < MAX_APPOINTMENTS; i++)
    {
        if (data->appointments[i].date.year != 0)
        {
            countAppointment++;
            sortedIndexData[i] = i;
            sortedTimeComputation[i] = data->appointments[i].date.year * 1000000 + data->appointments[i].date.month * 100000 + data->appointments[i].date.day * 1000 +
                data->appointments[i].time.hour * 100 + data->appointments[i].time.min;
        } 
    }

    //Bubble Sort the Time and Create an Index Mapping
    for (i = countAppointment; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            //if (sortedTimeComputation[j] > sortedTimeComputation[j + 1] && (sortedTimeComputation[j] != 0 || sortedTimeComputation[j + 1] !=0))
            if (sortedTimeComputation[j] > sortedTimeComputation[j + 1])
            {
                
                temp = sortedTimeComputation[j];
                sortedTimeComputation[j] = sortedTimeComputation[j + 1];
                sortedTimeComputation[j + 1] = temp;
                

                tempIndex = sortedIndexData[j];
                sortedIndexData[j] = sortedIndexData[j + 1];
                sortedIndexData[j + 1] = tempIndex;
            }
        }
    }

    //Match the Patient Data to the Sorted Appointment Data
    //for (i = 0; strlen(&data->appointments[i].time.hour) == 1; i++)
    for (i = 0; i < MAX_APPOINTMENTS; i++)
    {
        for (j = 0; j < MAX_PETS; j++)
        {
            //if (data->appointments[sortedIndexData[i]].patientNumber == data->patients[j].patientNumber && data->appointments[i].date.year != 0)
            if (data->appointments[sortedIndexData[i]].patientNumber == data->patients[j].patientNumber)
            {
                patientIndexData[i] = j;
                break;
            }
        }
        
    }
    

    //Print the Sorted Data
    //for (i = 0; strlen(&data->appointments[i].time.hour) == 1; i++)
    for (i = 0; i < MAX_APPOINTMENTS; i++)
    {
        //if (strlen(&data->appointments[i].time.hour) != 1 && &data->patients[i].patientNumber != 0)
        if (sortedTimeComputation[i] > 0)
        {
            displayScheduleData(&data->patients[patientIndexData[i]], &data->appointments[sortedIndexData[i]], 1);
        }
    }

    printf("\n");
}


// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(const struct ClinicData data[])
{
    struct Date searchDate;
    int i = 0, j = 0;
    int sortedIndexData[MAX_APPOINTMENTS] = {0}, sortedTimeComputation[MAX_APPOINTMENTS] = {0}, patientIndexData[MAX_APPOINTMENTS] = {0};
    int temp = 0, tempIndex = 0;
    int countAppointment = 0;

    printf("Year        : ");
    searchDate.year = inputIntRange(0, 9999);
    printf("Month (1-12): ");
    searchDate.month = inputIntRange(1, 12);
    if (searchDate.month == 1 || searchDate.month == 3 || searchDate.month == 5 || searchDate.month == 7 || searchDate.month == 8 || searchDate.month == 10 || searchDate.month == 12)
    {
        printf("Day (1-31)  : ");
        searchDate.day = inputIntRange(1, 31);
    }
    else if (searchDate.month == 2 && searchDate.year % 4 == 0)
    {
        printf("Day (1-29)  : ");
        searchDate.day = inputIntRange(1, 29);
    }
    else if (searchDate.month == 2 && searchDate.year % 4 != 0)
    {
        printf("Day (1-28)  : ");
        searchDate.day = inputIntRange(1, 28);
    }
    else
    {
        printf("Day (1-30)  : ");
        searchDate.day = inputIntRange(1, 30);
    }
    
    printf("\n");

    displayScheduleTableHeader(&searchDate, 0);

    //Count number of appointments and put scoring/weight for the time for sorting comparison purposes
    //for (i = 0; strlen(&data->appointments[i].time.hour) == 1; i++)
    for (i = 0; data->appointments[i].time.hour > 0; i++)
    {
        countAppointment++;
        sortedIndexData[i] = i;
        sortedTimeComputation[i] = data->appointments[i].time.hour * 100 + data->appointments[i].time.min;
    }

    //Bubble Sort the Time and Create an Index Mapping
    for (i = countAppointment - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (sortedTimeComputation[j] > sortedTimeComputation[j + 1])
            {
                temp = sortedTimeComputation[j];
                sortedTimeComputation[j] = sortedTimeComputation[j + 1];
                sortedTimeComputation[j + 1] = temp;

                tempIndex = sortedIndexData[j];
                sortedIndexData[j] = sortedIndexData[j + 1];
                sortedIndexData[j + 1] = tempIndex;
            }
        }
    }

    //Match the Patient Data to the Sorted Appointment Data
    for (i = 0; data->appointments[i].time.hour > 0; i++)
    {
        for (j = 0; j < MAX_PETS; j++)
        {
            if (data->appointments[sortedIndexData[i]].patientNumber == data->patients[j].patientNumber)
            {
                patientIndexData[i] = j;
                break;
            }
        }

    }

    //Print the Sorted Data
    for (i = 0; data->appointments[i].time.hour > 0; i++)
    {
        if (data->appointments[sortedIndexData[i]].date.year == searchDate.year && data->appointments[sortedIndexData[i]].date.month == searchDate.month &&
            data->appointments[sortedIndexData[i]].date.day == searchDate.day)
        {
            displayScheduleData(&data->patients[patientIndexData[i]], &data->appointments[sortedIndexData[i]], 0);
        }
    }

    printf("\n");
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    struct Date addDate;
    struct Time addTime;
    int patientNumber, i;
    int freeIndex = 0;
    int slotNotAvailable, returnNumber;
    
    printf("Patient Number: ");
    patientNumber = inputIntRange(0, 9999);
    returnNumber = findPatientIndexByPatientNum(patientNumber, patients, maxPatient);
    if (returnNumber == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        do
        {
            slotNotAvailable = 0;
            printf("Year        : ");
            addDate.year = inputIntRange(0, 9999);
            printf("Month (1-12): ");
            addDate.month = inputIntRange(1, 12);
            if (addDate.month == 1 || addDate.month == 3 || addDate.month == 5 || addDate.month == 7 || addDate.month == 8 || addDate.month == 10 || addDate.month == 12)
            {
                printf("Day (1-31)  : ");
                addDate.day = inputIntRange(1, 31);
            }
            else if (addDate.month == 2 && addDate.year % 4 == 0)
            {
                printf("Day (1-29)  : ");
                addDate.day = inputIntRange(1, 29);
            }
            else if (addDate.month == 2 && addDate.year % 4 != 0)
            {
                printf("Day (1-28)  : ");
                addDate.day = inputIntRange(1, 28);
            }
            else
            {
                printf("Day (1-30)  : ");
                addDate.day = inputIntRange(1, 30);
            }
            printf("Hour (0-23)  : ");
            addTime.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            addTime.min = inputIntRange(0, 59);


            for (i = 0; appointments[i].time.hour > 0; i++)
            {
                if (appointments[i].date.year == addDate.year && appointments[i].date.month == addDate.month && appointments[i].date.day == addDate.day &&
                    appointments[i].time.hour == addTime.hour && appointments[i].time.min == addTime.min)
                {
                    slotNotAvailable = 1;
                }
            }

            if (slotNotAvailable == 1)
            {
                putchar('\n');
                printf("ERROR: Appointment timeslot is not available!\n");
                putchar('\n');
            }
            else
            {
                break;
            }
        } while (1);

        if (addTime.hour < OPEN_HOURS || addTime.hour > CLOSING_HOURS || (addTime.min % 30 != 0 || addTime.min != 0))
        {
            printf("ERROR: Time must be between %d:00 and %d:00 in 30 minute intervals.\n", OPEN_HOURS, CLOSING_HOURS);
            putchar('\n');
            do
            {
                printf("Hour (0-23)  : ");
                addTime.hour = inputIntRange(0, 23);
                printf("Minute (0-59): ");
                addTime.min = inputIntRange(0, 59);

                if (addTime.hour < OPEN_HOURS || addTime.hour > CLOSING_HOURS || (addTime.min % 30 != 0 || addTime.min != 0))
                {
                    printf("ERROR: Time must be between %d:00 and %d:00 in 30 minute intervals.\n", OPEN_HOURS, CLOSING_HOURS);
                    putchar('\n');
                }
                else
                {
                    break;
                }
            } while (1);
        }

        for (i = 0; i < MAX_APPOINTMENTS; i++)
        {
            if (appointments[i].patientNumber == 0)
            {
                freeIndex = i;
                break;
            }
        }

        if (freeIndex == 0)
        {
            printf("ERROR: Appointment listing is FULL!\n\n");
        }
        else
        {
            appointments[freeIndex].patientNumber = patientNumber;
            appointments[freeIndex].date.year = addDate.year;
            appointments[freeIndex].date.month = addDate.month;
            appointments[freeIndex].date.day = addDate.day;
            appointments[freeIndex].time.hour = addTime.hour;
            appointments[freeIndex].time.min = addTime.min;

            putchar('\n');
            printf("*** Appointment scheduled! ***\n");
            putchar('\n');

        }
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatient)
{
    struct Date removeDate; 
    int returnNumber, patientNumber, selection;
    int i;
    
    printf("Patient Number: ");
    patientNumber = inputIntRange(0, 9999);
    returnNumber = findPatientIndexByPatientNum(patientNumber, patients, maxPatient);
    if (returnNumber == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        printf("Year        : ");
        removeDate.year = inputIntRange(0, 9999);
        printf("Month (1-12): ");
        removeDate.month = inputIntRange(1, 12);
        if (removeDate.month == 1 || removeDate.month == 3 || removeDate.month == 5 || removeDate.month == 7 || removeDate.month == 8 || removeDate.month == 10 || removeDate.month == 12)
        {
            printf("Day (1-31)  : ");
            removeDate.day = inputIntRange(1, 31);
        }
        else if (removeDate.month == 2 && removeDate.year % 4 == 0)
        {
            printf("Day (1-29)  : ");
            removeDate.day = inputIntRange(1, 29);
        }
        else if (removeDate.month == 2 && removeDate.year % 4 != 0)
        {
            printf("Day (1-28)  : ");
            removeDate.day = inputIntRange(1, 28);
        }
        else
        {
            printf("Day (1-30)  : ");
            removeDate.day = inputIntRange(1, 30);
        }

        putchar('\n');


        for (i = 0; appointments[i].time.hour > 0; i++)
        {
            
            if (appointments[i].date.year == removeDate.year && appointments[i].date.month == removeDate.month && appointments[i].date.day == removeDate.day && 
                    appointments[i].patientNumber == patientNumber)
            {
                displayPatientData(&patients[returnNumber], FMT_FORM);
                printf("Are you sure you want to remove this appointment (y,n): ");
                selection = !(inputCharOption("yn") == 'y');
                if (!selection)
                {

                    appointments[i].patientNumber = '\0';
                    appointments[i].date.year = 0;
                    appointments[i].date.month = 0;
                    appointments[i].date.day = 0;
                    appointments[i].time.hour = 0;
                    appointments[i].time.min = 0;
                    putchar('\n');
                    printf("Appointment record has been removed!\n");
                    while (getchar() != '\n')
                    {
                        ; // do nothing!
                    }
                    putchar('\n');
                    break;
                }
                else
                {
                    printf("Operation aborted.\n");
                    while (getchar() != '\n')
                    {
                        ; // do nothing!
                    }
                    putchar('\n');
                    break;
                }
            }
            
        }
        
    }
    

}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber, returnNumber;

    printf("Search by patient number: ");
    patientNumber = inputIntRange(0, 9999);
    putchar('\n');
    returnNumber = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (returnNumber == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[returnNumber], FMT_FORM);
    }
    putchar('\n');
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, validFlag = 0;
    char phoneNumber[DEFAULT_STRING_COUNT] = { '\0' };

    printf("Search by phone number: ");
    inputCString(phoneNumber, 10, 10);
    putchar('\n');

    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, phoneNumber) == 0)
        {
            validFlag = 1;
        }
    }

    if (validFlag == 0)
    {
        displayPatientTableHeader();
        putchar('\n');
        printf("*** No records found ***\n");
    }
    else if (validFlag == 1)
    {
        displayPatientTableHeader();
        for (i = 0; i < max; i++)
        {
            if (strcmp(patient[i].phone.number, phoneNumber) == 0)
            {
                displayPatientData(&patient[i], FMT_TABLE);
            }
        }
    }
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
    putchar('\n');
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int highestPatientNumber = 0, i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > highestPatientNumber)
        {
            highestPatientNumber = patient[i].patientNumber;
        }
    }

    return highestPatientNumber + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            return i;
        }
        else if (patient[i].patientNumber != patientNumber && i == max - 1)
        {
            return -1;
        }
    }

    return 0;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: 0%d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, 15);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int selection;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");
    selection = inputIntRange(0, 4);
    putchar('\n');
    switch (selection)
    {
    case 1:
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputPhone(phone->number, 10, 10);
        while (getchar() != '\n')
        {
            ; // do nothing!
        }
        putchar('\n');
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputPhone(phone->number, 10, 10);
        while (getchar() != '\n')
        {
            ; // do nothing!
        }
        putchar('\n');
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputPhone(phone->number, 10, 10);
        while (getchar() != '\n')
        {
            ; // do nothing!
        }
        putchar('\n');
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;
    }
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0, j = 0;
    FILE* fp = NULL;
    int patientNumber;
    char patientNumberString[DEFAULT_STRING_COUNT] = { '\0' };
    char phoneNumberString[DEFAULT_STRING_COUNT] = { '\0' };
    char name[DEFAULT_STRING_COUNT] = { '\0' };
    char blankString[DEFAULT_STRING_COUNT] = { '\0' };
    struct Phone phone;
    int record = 0;
    int stringCount = 0;

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {

        while (fscanf(fp, "%d|%[^|]|%[^|]| %[^\n]", &patientNumber, name, phone.description, phone.number) == 4&& i < max)
        {
            patients[i].patientNumber = patientNumber;
            strcpy(patients[i].name, name);
            strcpy(patients[i].phone.description, phone.description);
            if (strcmp(patients[i].phone.description, "TBD") == 0)
            {
                //Reset Strings
                strcpy(name, blankString);
                strcpy(phone.description, blankString);
                strcpy(phoneNumberString, blankString);
                stringCount = 0;

                strcpy(patients[i].phone.number, blankString);
                i++;
                for (j = 0; j < 4; j++)
                {
                    patientNumberString[j] = phone.number[j];
                }
                patients[i].patientNumber = atoi(patientNumberString);

                for (j = 5; phone.number[j] != '|'; j++)
                {
                    name[j - 5] = phone.number[j];
                    stringCount++;
                    if (strlen(name) > stringCount)
                    {
                        name[stringCount] = '\0';
                    }
                }
                strcpy(patients[i].name, name);

                for (j = 5 + strlen(name) + 1; phone.number[j] != '|'; j++)
                {
                    phone.description[j - 5 - strlen(name) - 1] = phone.number[j];
                }
                strcpy(patients[i].phone.description, phone.description);

                for (j = 5 + strlen(name) + strlen(phone.description) + 2; phone.number[j] != '\0'; j++)
                {
                    phoneNumberString[j - 5 - strlen(name) - strlen(phone.description) - 2] = phone.number[j];
                }
                strcpy(patients[i].phone.number, phoneNumberString);
                record++;

            }
            else
            {
                strcpy(patients[i].phone.number, phone.number);
            }
            
            record++;
            i++;
        }
    }
    else
    {
        printf("Failed to open file\n");
    }

    fclose(fp);
    return record;
}


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;
    FILE* fp = NULL;
    int patientNumber;
    struct Date date;
    struct Time time;
    int record = 0;

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &patientNumber, &date.year, &date.month, &date.day, &time.hour, &time.min) == 6 && i < max)
        {
            appoints[i].patientNumber = patientNumber;
            appoints[i].date.year = date.year;
            appoints[i].date.month = date.month;
            appoints[i].date.day = date.day;
            appoints[i].time.hour = time.hour;
            appoints[i].time.min = time.min;
            record++;
            i++;
        }    
    }
    else
    {
        printf("Failed to open file\n");
    }

    fclose(fp);
    return record;
}
