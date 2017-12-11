#include "common/event/game_event.h"
#include <iostream>
using namespace std;

#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#define MAX_SUPPORT_INDEX_COUNT 10

#define CHECK_I_INDEX(_I_INDEX)	  \
static_assert(_I_INDEX > 0, "Table Index must greater than zero");	 \
static_assert(_I_INDEX <= MAX_SUPPORT_INDEX_COUNT, "Table Index must less than or equal to MAX_SUPPORT_INDEX_COUNT");	 

#define INDEX_TABLE2(_I_INDEX, TABLE_TYPE, INDEX_TYPE, VALUE1, VALUE2)  \
	CHECK_I_INDEX(_I_INDEX)\
	struct INDEX_TYPE		   \
	{									\
		typedef decltype(TABLE_TYPE::VALUE1) TYPE1;	\
		typedef decltype(TABLE_TYPE::VALUE2) TYPE2;	  \
		INDEX_TYPE(TYPE1 VALUE1 = TYPE1(), TYPE2 VALUE2 = TYPE2()) :VALUE1(VALUE1), VALUE2(VALUE2)	   \
		{				  \
		}		  \
				\
		INDEX_TYPE(const INDEX_TYPE& r)	  \
		{			   \
			VALUE1 = r.VALUE1;	\
			VALUE2 = r.VALUE2;	\
		}			 \
					 \
		INDEX_TYPE(const TABLE_TYPE& entry)	 \
		{			\
			VALUE1 = entry.VALUE1; \
			VALUE2 = entry.VALUE2;	 \
		}		 \
			 \
														\
		bool operator<(const INDEX_TYPE& r) const  			\
		{												  		\
			return VALUE1 < r.VALUE1 || VALUE2 < r.VALUE2;	 		\
		}												 \
															\
		bool operator==(const INDEX_TYPE& r) const	  \
		{											   \
			return VALUE1 == r.VALUE1 && VALUE2 == r.VALUE2; \
		}													 \
													  \
		TYPE1 VALUE1; \
		TYPE2 VALUE2; \
	};

//struct str_hash {
//	\
//		size_t operator()(const INDEX_TYPE& str) const	  \
//	{												 \
//		return str.VALUE1 + str.VALUE2;			   \
//	}											\
//}; \

struct SkillInfo
{
	int skillId;
	int level;
	int job;
	int damage;

	SkillInfo(int s = 0,int l = 0,int j = 0,int d = 0):skillId(s),level(l),job(j),damage(d)
	{

	}
	typedef decltype(SkillInfo::skillId) TYPE1;
	void Print()
	{
		cout << "skillId=" << skillId << " level=" << level << " job=" << job << " damage=" << damage << endl;
	}

	INDEX_TABLE2(SkillInfo, KeyType, skillId, level);
	typedef KeyType KeyIndex1;
	INDEX_TABLE2(SkillInfo, KeyType2, skillId, job);
	typedef KeyType2 KeyIndex2;

};

template <int count>
struct PrintN
{
	void print()
	{
		cout << "count = " << count << endl;
	}
};

#include <type_traits>
#include <unordered_map>
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

template <typename IndexType>
struct TableIndex
{
	int GetEntry(const IndexType& k) const
	{
		auto i = kmap.find(k);
		if (i != kmap.end())
		{
			return i->second;
		}
		return -1;
	}

	void AddEntry(int id,const IndexType& k)
	{
		kmap[k] = id;
	}

	//unordered_map<IndexType, int, typename IndexType::str_hash> kmap;
	map<IndexType, int> kmap;

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
struct TypeIf
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



template <typename TableType,typename ... BaseClasses>
class IndexedTable : public TableIndex<BaseClasses>...
{
private:
	struct TEnd{};

	template<typename IndexT, typename ...IndexTypes>
	void _AddEntry(int id, TableType& k)
	{
		TableIndex<IndexT>::AddEntry(id, k);
		_AddEntry<IndexTypes...>(id, k);
	}

	template<>
	void _AddEntry<TEnd>(int id, TableType& k)
	{
	}

public:
	void AddEntry(int id, TableType& k)
	{
		_AddEntry<BaseClasses..., TEnd>(id, k);
	}

	template<typename IT>
	int GetEntry(const IT& index) const
	{
		return TableIndex<IT>::GetEntry(index);
	}
};


template <typename T, typename ...Indexers>
class FileTableCache : public IndexedTable<T, Indexers...>
{
public:
	typedef IndexedTable<T, Indexers...> BaseClass;

	void AddEntry(int id, T& k)
	{
		tmap[id] = k;
		BaseClass::AddEntry(id, k);
		//kmap[T::KeyIndex(GetEntry(id))] = id;
	}

	bool GetEntry(int id, T& r)
	{
		auto i = tmap.find(id);
		if (i != tmap.end())
		{
			r = i->second;
			return true;
		}
		return false;
	}
	template<typename KeyType>
	bool GetEntry(KeyType& t, T& rt)
	{
		auto i = BaseClass::GetEntry(t);
		return GetEntry(i, rt);
	}

	void LoadTable()
	{
	}
protected:
	map<int, T> tmap;
	//map<TKey, int> kmap;
};

//---------------------------------------------------------//---------------------------------------------------------//---------------------------------------------------------
//---------------------------------------------------------//---------------------------------------------------------//---------------------------------------------------------

#if 2

template <typename T, int N>
struct HasIndexFunction2;

template <typename TableType, int  N>
struct GetTypeN;

#define DEFINE_INDEX_FUNCTION(_INDEX___)	\
template <typename T>	  \
struct HasIndexFunction2<T, _INDEX___>	  \
{				\
	typedef char yes;	\
	typedef void* no;	\
						  \
	template<typename C>  \
	static yes check(int, typename C::KeyIndex##_INDEX___ = typename C::KeyIndex##_INDEX___() ); \
	template<typename C>		  \
	static no check(...);		  \
	enum { value = (sizeof(check<T>(0)) == sizeof(yes)) }; \
};								  \
						   \
template <typename TableType>	 \
struct GetTypeN<TableType, _INDEX___>	  \
{										  \
	typedef TableIndex<typename TableType::KeyIndex##_INDEX___> type;  \
};

DEFINE_INDEX_FUNCTION(1);
DEFINE_INDEX_FUNCTION(2);
DEFINE_INDEX_FUNCTION(3);
DEFINE_INDEX_FUNCTION(4);
DEFINE_INDEX_FUNCTION(5);
DEFINE_INDEX_FUNCTION(6);
DEFINE_INDEX_FUNCTION(7);
DEFINE_INDEX_FUNCTION(8);
DEFINE_INDEX_FUNCTION(9);
DEFINE_INDEX_FUNCTION(10);
template<typename T>
struct NoneWrapper
{
	typedef T type;
};

template<typename TableType,int N>
struct IndexTypeDeducer
{
private:
	typedef typename TypeIf< HasIndexFunction2<TableType, N>::value, typename GetTypeN<TableType, N>, NoneWrapper<None<TableType>> >::type ret_type;

public:
	typedef typename ret_type::type type;
};

template<typename TableType>
struct IndexTypeDeducer<TableType, 0>
{
	typedef None<TableType> type;
};

template <typename TableType, int index>
struct IndexedTable2 : public IndexTypeDeducer<TableType, index>::type, public IndexedTable2<TableType, index - 1>
{
	typedef  typename IndexTypeDeducer<TableType, index>::type CurIndexType;
	typedef  typename  IndexedTable2<TableType, index - 1> NextIndexType;
	typedef  CurIndexType type;

	template<typename KeyType>
	int GetEntry(KeyType& t)
	{
		return TableIndex<KeyType>::GetEntry(t);
	}

	void AddEntry(int id, TableType& k)
	{
		CurIndexType::AddEntry(id, k);
		NextIndexType::AddEntry(id, k);
	}
};

template <typename TableType>
struct IndexedTable2<TableType, 0>
{
	typedef None<TableType> type;
	void AddEntry(int id, TableType& k)
	{

	}
};

template <typename T>
class FileTableCache2 : public IndexedTable2<T, MAX_SUPPORT_INDEX_COUNT>
{
public:
	typedef typename IndexedTable2<T, MAX_SUPPORT_INDEX_COUNT> BaseClass;

	void AddEntry(int id, T& k)
	{
		tmap[id] = k;
		BaseClass::AddEntry(id, k);
	}

	bool GetEntry(int id, T& r)
	{
		auto i = tmap.find(id);
		if (i != tmap.end())
		{
			r = i->second;
			return true;
		}
		return false;
	}
	template<typename KeyType>
	bool GetEntry(KeyType& t, T& rt)
	{
		auto i = BaseClass::GetEntry(t);
		return GetEntry(i, rt);
	}

	void LoadTable()
	{
	}
protected:
	map<int, T> tmap;
};

#endif

int main()
{
	//FileTableCache<SkillInfo, SkillInfo::KeyType, SkillInfo::KeyType2> table;
	FileTableCache2<SkillInfo> table;
	table.AddEntry(1, SkillInfo{ 1,10001,20001,30001 });
	table.AddEntry(2, SkillInfo{ 2,10002,20002,30002 });
	table.AddEntry(3, SkillInfo{ 3,10003,20003,30003 });

	std::map<SkillInfo::KeyType, int> sm = { {{ 10001,20001 },1},{{ 10002,20002 },2} };

	auto k = SkillInfo::KeyType(1, 10001);
	auto i = sm.find(k);
	SkillInfo s;
	if (table.GetEntry(k, s))
	{
		s.Print();
	}
	if (table.GetEntry(SkillInfo::KeyType2(2, 20002), s))
	{
		s.Print();
	}

	return 0;
}