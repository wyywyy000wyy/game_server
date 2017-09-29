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

int main()
{
	GameEventManager mgr;
	A a;
	B b;
	C c;
	const int TEST_EVENT_TYPE = 1;
	auto tf = [&a](GameEventPtr ptr, void*) { a.Print(); };
	auto tf2 = [&a](GameEventPtr ptr, void*) { a.Print(); };
	
	mgr.AddEvenHandler(TEST_EVENT_TYPE, tf);
	mgr.AddEvenHandler(TEST_EVENT_TYPE, [&b](GameEventPtr ptr, void*) { b.Print(); });
	mgr.AddEvenHandler(TEST_EVENT_TYPE, [&c](GameEventPtr ptr, void*) { c.Print(); });
	auto tb = tf;
	mgr.AddEvenHandler(TEST_EVENT_TYPE, testF);

	auto e = std::make_shared<GameEvent>();
	e->type = TEST_EVENT_TYPE;
	mgr.SendEvent(e);
	cout << "TEST_EVENT_TYPE + 1" << endl;
	mgr.RemoveEventHandler(TEST_EVENT_TYPE, testF);
	e->type = TEST_EVENT_TYPE + 1;
	mgr.SendEvent(e);
	cout << "RemoveEventHandler(TEST_EVENT_TYPE, 2)" << endl;
	mgr.RemoveEventHandler(TEST_EVENT_TYPE, 2);
	e->type = TEST_EVENT_TYPE;
	mgr.SendEvent(e);
	cout << "GameEventListener listener(&mgr)" << endl;
	{
		GameEventListener listener(&mgr);
		listener.AddEvenHandler(TEST_EVENT_TYPE, [](GameEventPtr ptr, void*) {cout << "child listener handler" << endl; });
		mgr.SendEvent(e);
		cout << "listener.SendEvent(e)" << endl;
		listener.SendEvent(e);
		cout << "sub {}" << endl;
		{
			GameEventListener listener2(&listener);
			listener2.AddEvenHandler(TEST_EVENT_TYPE, [](GameEventPtr ptr, void*) {
				cout << "sub child listener handler" << endl;
			});
			mgr.SendEvent(e);
		}
		cout << "~sub {}" << endl;
		mgr.SendEvent(e);
	}
	cout << "{}" << endl;
	mgr.SendEvent(e);
	return 0;
}