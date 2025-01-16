/***********************************************************************
// OOP244 Project ms1
//
// File  Menu.cpp
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

#include <cstring>
#include <iostream>
#include "Menu.h"
#include <cmath> // Use pow function in Time.cpp. If this is not included the error 'function was not declared in this scope' will occur

using namespace std;

namespace seneca {
	Menu::Menu(const char* menuContent, int numberOfTabs)
	{
		int numberOfOptions = 0;

		if (m_text) {
			setEmpty();
		}

		if (menuContent && numberOfTabs >= 0) {
			m_text = new char[strlen(menuContent) + 1];
			strcpy(m_text, menuContent);

			for (int i = 0; m_text[i]; i++) {
				if (m_text[i] == '\n') {
					numberOfOptions += 1;
				}
			}

			m_options = numberOfOptions;
			m_tabs = numberOfTabs;
		}
	}
	Menu::~Menu()
	{
		setEmpty();
	}
	void Menu::setEmpty()
	{
		delete[] m_text;
		m_text = nullptr;
	}
	void Menu::display() const
	{
		for (int i = 0; m_text[i]; i++) {
			if ((i == 0) || (i != 0 && m_text[i - 1] == '\n')) {
				displayTabs(m_tabs);
				cout << m_text[i];
			}
			else {
				cout << m_text[i];
			}
		}
		cout << endl;
		displayTabs(m_tabs);
		cout << "0- Exit" << endl;
		displayTabs(m_tabs);
		cout << "> ";
	}

	void Menu::displayTabs(const int tabs) const
	{
		for (int j = 0; j < tabs; j++) {
			cout << "   ";
		}
	}

	int& Menu::operator>>(int& Selection)
	{
		int done = 0;

		display();

		while (!done) {
			char buffer[2];
			char newLine = 'X';
			int bufferLength{};
			int negativeValue = 0;

			cin.get(buffer, 2, ' ');
			cin.get(newLine);
			//Own way of handling negative values, not good but there's not enough time to figure it out
			if (buffer[0] == '-') {
				buffer[0] = newLine;
				buffer[1] = 0;
				newLine = '\n';
				negativeValue = 1;
			}
			if (cin && ((int)buffer[0] >= 48 && (int)buffer[0] <= 57)) { //Using Ascii values to know if the user input a number
				if (newLine != '\n') {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Only enter an integer, try again: ";
				}
				else {
					//Switch Char to Int
					bufferLength = strlen(buffer);
					Selection = 0;
					for (int i = 0; buffer[i]; i++) {
						Selection += ((buffer[i] - '0') * pow(10, (bufferLength - 1 - i)));
					}

					if (negativeValue) {
						Selection *= -1;
					}

					if (Selection < 0 || Selection > m_options) {
						//Clear if error
						if (newLine != '\n')
						{
							cin.clear();
							cin.ignore(10000, '\n');
						}
						else {
							//Negative Value handling
							cin.clear();
							if (negativeValue) {
								cin.ignore(10000, '\n');
							}
						}
						cout << "Invalid value enterd, retry[0 <= value <= " << m_options << "]: ";
					}
					else {
						done = 1;
					}
				}
				
			}
			else {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Bad integer value, try again: ";
			}
		}	

		return Selection;
	}
}