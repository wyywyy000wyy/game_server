
#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
using namespace std;
int a;

namespace Learn111{
	namespace msm = boost::msm;
	namespace msmf = boost::msm::front;
	namespace mpl = boost::mpl;

	struct event_start {};
	struct event_stop {};
	struct event_reset {};



	struct tl_init : public boost::msm::front::state<>
	{
		template <class Event, class Fsm>
		void on_entry(Event const&, Fsm&) const {
			std::cout << "init::on_entry()" << std::endl;
		}
		// Exit action
		template <class Event, class Fsm>
		void on_exit(Event const&, Fsm&) const {
			std::cout << "init::on_exit()" << std::endl;
		}
	};

	struct running : public msm::front::state<>
	{
		template <class Event, class Fsm>
		void on_entry(Event const&, Fsm&) const {
			std::cout << "running::on_entry()" << std::endl;
		}
		// Exit action
		template <class Event, class Fsm>
		void on_exit(Event const&, Fsm&) const {
			std::cout << "running::on_exit()" << std::endl;
		}
	};

	struct stoped : public msm::front::state<>
	{
		template <class Event, class Fsm>
		void on_entry(Event const&, Fsm&) const {
			std::cout << "stoped::on_entry()" << std::endl;
		}
		// Exit action
		template <class Event, class Fsm>
		void on_exit(Event const&, Fsm&) const {
			std::cout << "stoped::on_exit()" << std::endl;
		}
	};

	struct TestStateFunc
	{
		template <class EVT, class FSM, class SourceState, class TargetState, class AllStates>
		void operator()(EVT const& evt, FSM& fsm, SourceState& src, TargetState& tgt)
		{
			cout << "haha" << endl;
		}
	};

	//struct End : boost::msm::front::terminate_state<> {};

	struct learn_state_mechine : public boost::msm::front::state_machine_def<learn_state_mechine>
	{
		typedef tl_init initial_state;
		

		struct transition_table : boost::mpl::vector<
			//			start			Event			Next			Action			Guard
			msmf::Row<	tl_init,		event_start,	running,	msmf::none,		msmf::none>,
			msmf::Row<	running,		event_stop,		stoped,			msmf::none,		msmf::none>,
			msmf::Row<	stoped,			event_reset,	running,		msmf::none,		msmf::none>
		> {};


		template <class FSM, class Event>
		void no_transition(Event const&, FSM&, int state)
		{
		}
	};

	struct StateMachine1 : public boost::msm::back::state_machine<learn_state_mechine>
	{
	};

	void test()
	{
		StateMachine1 sm1;
		sm1.start();

		sm1.process_event(event_stop());

		cout << "--" << endl;

		sm1.process_event(event_start());
		
		TestStateFunc();
	}
};









namespace CMR // Creature move regulator
{


	// events

	struct Evt_TooFar {};


	struct St_None : public boost::msm::front::state<>
	{
	/*	template <class Event, class FSM>
		void on_entry(Event const&, FSM& fsm)
		{
			dynamic_cast<IStateMachine&>(fsm).Set(false, None);
		}*/
	};

	struct St_Forward : public boost::msm::front::state<>
	{
	/*	template <class Event, class FSM>
		void on_entry(Event const&, FSM& fsm)
		{
			dynamic_cast<IStateMachine&>(fsm).Set(true, Forward);
		}*/
	};

	// state machine front-end define
	struct StateMachineDef : public boost::msm::front::state_machine_def<StateMachineDef>
	{

		// the initial state must be defined
		typedef St_None initial_state;

		struct transition_table : boost::mpl::vector<
			//     Start      Event           Next       Action                        Guard            
			//   +-------------+---------------+----------+-----------------------------+----------------------+
			_row < St_None, Evt_TooFar, St_Forward                                                     >
			//   +-------------+---------------+----------+-----------------------------+----------------------+
		> {};

		// Replaces the default no-transition response.
		
	};

	// state machine back-end define
	class StateMachine : public boost::msm::back::state_machine<StateMachineDef>
	{
	};

} // namespace CMR













int main()
{
	//CMR::StateMachine	m_state;
	Learn111::test();
	int i;
	return 5;
}
