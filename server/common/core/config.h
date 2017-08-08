#ifndef _CONFIG_H_
#define _CONFIG_H_
class config 
{
public:
	config();
	~config();

	int GetInteger(const std::string& section, const std::string& name, int default_value = 0) const;

	bool Open(const std::string& filename);

private:
	void* _impl;
};

#endif  // _CONFIG_H_
