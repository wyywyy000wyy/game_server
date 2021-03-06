#ifndef NOSQL_CLIENT_H__
#define NOSQL_CLIENT_H__
#include <string>
#include <memory>

//template<typename T>
struct GetOperationBase
{
	typedef void (*func)(const std::string&);

	GetOperationBase(func f):m_f(f){}

	void call(const std::string& v)
	{
		m_f(v);
	}
private:
	func m_f;
};

namespace cpp_redis
{
	class redis_client;
}

template<typename func>
struct GetOperation : public GetOperationBase
{
	GetOperation() :GetOperationBase(CallFunction)
	{

	}

	static void CallFunction(const std::string& v)
	{
		call(v);
	}
};

typedef GetOperationBase GetStringFunc;

class NosqlClient : public std::enable_shared_from_this<NosqlClient>
{
public:
	NosqlClient();
	~NosqlClient();

	void Connect(int port);
	void Connect(std::string host, int port);
	void Get(std::string key, GetStringFunc::func);
	void Set(const std::string& key, const std::string& value);
	void Update(int dt);
private:
	cpp_redis::redis_client* m_client;
};

typedef std::shared_ptr<NosqlClient> NosqlClientPtr;
#endif // !NOSQL_CLIENT_H__
