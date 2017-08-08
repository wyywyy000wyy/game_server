//TODO #include "preHeader.h"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include "config.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

using namespace std;


struct configImpl
{
	fstream _file;
	string _filename;
	rapidjson::Document _doc;
};

#define IMPL ((configImpl*)_impl)
#define _FILE (IMPL->_file)
#define _DOC (IMPL->_doc)
config::config():_impl(new configImpl)
{

}
config::~config()
{

}

bool config::Open(const std::string& filename)
{
	if (_FILE.is_open())
	{
		return false;
	}
	_FILE.open(filename);
	if (_FILE.gcount() <= 0)
	{
		_FILE.close();
		return false;
	}
	IMPL->_filename = filename;
	char* buf = new char[_FILE.gcount()];
	_FILE.read(buf, _FILE.gcount());
	_FILE.close();
	_DOC.Parse(buf);
	delete[] buf;
	return true;
}

int config::GetInteger(const std::string& section, const std::string& name, int default_value = 0) const
{
	auto& obj = _DOC[section.c_str()];
	if (!obj.IsObject())
	{
		return default_value;
	}
	auto& v = obj[name.c_str()];
	if (!obj.IsInt())
	{
		return default_value;
	}
	return v.GetInt();
}
