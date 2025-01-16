/***********************************************************************
// OOP244 Project ms1
//
// File  Menu.h
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
#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>

namespace seneca {
	class Menu {
		char* m_text{};
		int m_options{};
		int m_tabs{};

	public:
		Menu(const char* menuContent, int numberOfTabs = 0);
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;
		
		virtual ~Menu();
		void setEmpty();
		void display() const;
		void displayTabs(const int tabs) const;
		int& operator>>(int& Selection);
	};
}
#endif // !SENECA_MENU_H
