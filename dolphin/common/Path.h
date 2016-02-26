#pragma once
#include <string>
#include <vector>
namespace dolphin_common
{
	class Path
	{
	public:
		Path(const std::string& path);
		~Path();
		typedef std::vector<std::string> StringVec;

		static std::string GetCurPath();
	private:
		std::string _node;
		std::string _device;
		std::string _name;
		std::string _version;
		StringVec   _dirs;
		bool        _absolute;
	};
}
