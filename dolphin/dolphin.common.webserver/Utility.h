#pragma once
#include <string>
#include <vector>
namespace dolphin_utility
{
	class Utility
	{
	public:
		static void GetParam(const std::string src, const std::string key, std::string &value);
		static void GetParam(const std::string src, const std::string key, short &value);
	};
}