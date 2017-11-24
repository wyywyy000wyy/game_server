#include "common/event/game_event.h"
#include <iostream>
using namespace std;
struct A
{
	void Print()
	{
		cout << "我是A" << endl;
	}
};
struct B
{
	void Print()
	{
		cout << "我是B" << endl;
	}
};
struct C
{
	void Print()
	{
		cout << "我是C" << endl;
	}
};

void testF(GameEventPtr ptr, void*)
{
	cout << "testF" << endl;
}

class TestEventClass : public GameEventListener
{

};

struct TestAAA
{
	TestAAA()
	{
		cout << "TestAAA()" << endl;
	}
	TestAAA(TestAAA& a)
	{
		cout << "(TestAAA& a)" << endl;
	}
	TestAAA& operator =(TestAAA& a)
	{
		cout << "operator =(" << endl;
	}
	int a = 5;
};

void TestAAAFunc()
{
	TestAAA a;
	cout << "TestAAAFunc" << endl;
	for (auto& i : {a,a,a})
	{
		cout << a.a << endl;
	}
}

#include <functional>
struct TestFuncC
{
	std::function<float (float, float, float)> f;
};

#include <iostream>
struct TestCopy
{
	TestCopy()
	{
		a = 0;
		//b = 0;
		cout << "TestCopy构造" << endl;
	}
	TestCopy(const TestCopy& r)
	{
		a = r.a;
	//	b = r.b;
		cout << "TestCopy赋值构造" << endl;
	}
	TestCopy& operator=(TestCopy& r)
	{
		cout << "赋值operator=" << endl;
		a = r.a;
	//	b = r.b;
		return *this;
	}
	bool operator < (const TestCopy& r) const
	{
		return a < r.a;
	}


	//bool operator == (const TestCopy& r)const
	//{
	//	return a == r.a;
	//}
	int a;
	//int b;
};
//bool operator < (const TestCopy& l ,const TestCopy& r)
//{
//	return true;
//}
//
//
//bool operator == (const TestCopy& l, const TestCopy& r) 
//{
//	return true;
//}
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>


struct SkillInfo
{
	int skillId;
	int level;
	int job;
	int damage;

	SkillInfo(int s = 0,int l = 0,int j = 0,int d = 0):skillId(s),level(l),job(j),damage(d)
	{

	}

	struct KeyType
	{
		KeyType(int a = 0, int c = 0):level(a),job(c)
		{
			int d = 9;
			d++;
		}

		KeyType(const SkillInfo& entry)
		{
			level = entry.level;
			job = entry.job;
		}

		bool operator<(const KeyType& r) const
		{
			return level < r.level || job < r.job;
		}

		int level;
		int job;
	};

	typedef KeyType KeyIndex;
};

#include <type_traits>
struct ItemInfo
{
	int itemId;
	int ItemLevel;
	int count;
};

template <typename T>
struct None
{
	bool IsNone(){ return true; };
	void AddEntry(int id, const T& k)
	{
	}
};

template <typename T>
struct TableIndex
{
	typedef typename T::KeyIndex TKey;
	int GetEntry(TKey k)
	{
		auto i = kmap.find(k);
		if (i != kmap.end())
		{
			return i->second;
		}
		return -1;
	}

	void AddEntry(int id,const TKey& k)
	{
		kmap[k] = id;
	}
	map<TKey, int> kmap;

	bool IsNone(){ return false; }
};

template <typename T>
struct HasIndexFunction
{
	typedef char yes;
	typedef void* no;

	template<typename C>
	static yes check(int,typename C::KeyIndex = typename C::KeyIndex());

	template<typename C>
	static no check(...);

	enum {value = (sizeof(check<T>(0)) == sizeof(yes))};
};

template<bool C, typename T1, typename T2>
struct TableIf
{
	template <bool>
	struct TableIfImpl;

	template<>
	struct TableIfImpl<true>
	{
		typedef T1 type;
	};
	template<>
	struct TableIfImpl<false>
	{
		typedef T2 type;
	};
	typedef typename TableIfImpl<C>::type type;
};

#define TABLE_DEDUCER(T) TableIf<HasIndexFunction<T>::value, TableIndex<T>, None<T>>::type

template <typename T>
struct TableDeducer : public TableIf<HasIndexFunction<T>::value, TableIndex<T>, None<T>>::type
{
	int testFunc(){}
};

template <typename T>
class FileTableCache : public TableDeducer<T>
{
public:
	typedef TableDeducer<T> IndexKeyType;
	bool IsNone()
	{
		return IndexKeyType::IsNone();
	}

	void AddEntry(int id, T& k)
	{
		tmap[id] = k;
		IndexKeyType::AddEntry(id, k);
		//kmap[T::KeyIndex(GetEntry(id))] = id;
	}

	const T& GetEntry(int id )
	{
		return tmap[id];
	}
	template<typename KeyType>
	const T& GetEntry(KeyType t)
	{
		return GetEntry(IndexKeyType::GetEntry(t));
	}

	void LoadTable()
	{
	}
protected:
	map<int, T> tmap;
	//map<TKey, int> kmap;
};

//template<typename FUNC>
//struct TEMPLETE_FOR
//{
//
//};

template <typename FUNC,typename T, typename ... TVetex>
struct TEMPLETE_FOR : public TEMPLETE_FOR<FUNC, TVetex...>
{
	typedef TEMPLETE_FOR<FUNC, TVetex...> PFOR;
	const static int value = typename PFOR::value + 1 ;
};

template <typename FUNC, typename T>
struct TEMPLETE_FOR<FUNC,T>
{
	const static int value = 1;
};

struct TEM_FUNC
{

};

template <typename ... TVetex>
struct TableDeducerPlus : public TEMPLETE_FOR<TEM_FUNC, TVetex...>
{

};




int main()
{
	
	TableDeducerPlus<int,int,bool> t;

	cout << t.value << endl;

	/*int a;
	FileTableCache<SkillInfo> table;
	table.AddEntry(1, SkillInfo{ 1,10001,20001,30001 });
	table.AddEntry(2, SkillInfo{ 2,10002,20002,30002 });
	table.AddEntry(3, SkillInfo{ 3,10003,20003,30003 });
	FileTableCache<ItemInfo> table_item;

	SkillInfo::KeyType t(10003,20002);
	SkillInfo s = table.GetEntry(3);
	bool b1 = table.IsNone();
	bool b2 = table_item.IsNone();

	cout << s.skillId << endl;
	cout << s.level << endl;
	cout << s.job << endl;
	cout << s.damage << endl;*/
	return 0;
}