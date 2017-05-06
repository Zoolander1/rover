#ifndef ROBOTSTATEMACHINE_H
#define ROBOTSTATEMACHINE_H

class RobotStateMachine{
	
	public:
		enum class State{
			DISCONNECTED,
			SAFE,
			ACTIVE
		};
	
		RobotStateMachine();
		virtual ~RobotStateMachine();
	
		bool Transition_To_State(const State target_state);
		const State Get_Robot_Current_State(){return m_current_state;};
		const State Get_Robot_Previous_State(){return m_previous_state;};

	private:
		State m_current_state;
		State m_previous_state;
};

#endif
