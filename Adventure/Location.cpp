#include "Location.h"
#include <iostream>
#include <algorithm>
using namespace std;

Location::Location(const std::string& name, const std::string& keyword, const std::string& description, const int left, const int right, const int forward, const int back):
	m_Name(name),
	m_keyword(keyword),
	m_Description(description),
	m_Left(left),
	m_Right(right),
	m_Forward(forward),
	m_Back(back)
{
}

Location::~Location()
{
}

void Location::PrintDescription() const
{
	cout << m_Description;
}

int Location::goLeft() const
{
	return m_Left;
}

int Location::goRight() const
{
	return m_Right;
}

int Location::goForward() const
{
	return m_Forward;
}

int Location::goBack() const
{
	return m_Back;
}