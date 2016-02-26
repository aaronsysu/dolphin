#include "stdafx.h"
#include "Utility.h"

namespace dolphin_utility
{
	void Utility::GetParam(const std::string src, const std::string key, std::string &value)
	{
		std::string target = key + "=";
		std::string::size_type posBeg = src.find(target);
		if (posBeg == std::string::npos)
		{
			return;
		}
		posBeg += (key.length() + 1);
		std::string::size_type posEnd = src.find(";", posBeg);
		if (posEnd == std::string::npos)
		{
			posEnd = src.length();
		}
		value = src.substr(posBeg, posEnd - posBeg);
		return;
	}

	void Utility::GetParam(const std::string src, const std::string key, short &value)
	{
		std::string target = key + "=";
		std::string::size_type posBeg = src.find(target);
		if (posBeg == std::string::npos)
		{
			return;
		}
		posBeg += (key.length() + 1);
		std::string::size_type posEnd = src.find(";", posBeg);
		if (posEnd == std::string::npos)
		{
			posEnd = src.length();
		}
		value = atoi(src.substr(posBeg, posEnd - posBeg).c_str());
		return;
	}
}