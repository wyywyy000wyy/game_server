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

int main()
{
	GameEventManager mgr;
	A a;
	B b;
	C c;
	const int TEST_EVENT_TYPE = 1;
	mgr.AddEvenHandler(TEST_EVENT_TYPE, [&a](GameEventPtr ptr) { a.Print(); }, 1);
	mgr.AddEvenHandler(TEST_EVENT_TYPE, [&b](GameEventPtr ptr) { b.Print(); }, 2);
	mgr.AddEvenHandler(TEST_EVENT_TYPE, [&c](GameEventPtr ptr) { c.Print(); }, 3);

	auto e = std::make_shared<GameEvent>();
	e->type = TEST_EVENT_TYPE;
	mgr.SendEvent(e);
	cout << "TEST_EVENT_TYPE + 1" << endl;
	e->type = TEST_EVENT_TYPE + 1;
	mgr.SendEvent(e);
	cout << "RemoveEventHandler(TEST_EVENT_TYPE, 2)" << endl;
	mgr.RemoveEventHandler(TEST_EVENT_TYPE, 2);
	e->type = TEST_EVENT_TYPE;
	mgr.SendEvent(e);
	cout << "RemoveEventHandler(TEST_EVENT_TYPE)" << endl;
	mgr.RemoveEventHandler(TEST_EVENT_TYPE);
	e->type = TEST_EVENT_TYPE;
	mgr.SendEvent(e);
	return 0;
}