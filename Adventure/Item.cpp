#include "Item.h"
#include <algorithm>

Item::Item(const std::string& name, const std::string& keyword, const std::string& description, bool carryable, const std::vector<int> locations):
	m_Name(name),
	m_keyword(keyword),
	m_Description(description),
	m_IsCarrying(carryable),
	m_LocationIndexArr(locations)
{
}

Item::~Item()
{
}

bool Item::IsAtLocation(const int ID) const
{
	auto isAt = false;
	std::for_each(m_LocationIndexArr.begin(), m_LocationIndexArr.end(), [&](int i) {if (i == ID)isAt = true; });//more lambdas, okay this one actually makes sense
	return isAt;
}

std::string Item::GetKeyword() const
{
	return m_keyword;
}

bool Item::IsCarrying() const
{
	return m_IsCarrying;
}

void Item::Use()
{
	Helpers::PrintSlowly("\n" + m_Action + "\n");
}
