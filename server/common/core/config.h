#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <string>
#include <iostream>
namespace game_common
{
	class config
	{
	public:
		config();
		~config();

		int get_integer(const std::string& section, const std::string& name, int defaultValue = 0) const;
		std::string get_string(const std::string& section, const std::string& name, std::string defaultString) const;


		bool open(const std::string& filename);

	private:
		void* _impl;
	};
}


#endif  // _CONFIG_H_
