#include "RobotStateMachine.h"

RobotStateMachine::RobotStateMachine():
	m_current_state(RobotStateMachine::State::DISCONNECTED),
	m_previous_state(RobotStateMachine::State::DISCONNECTED)
{
}

RobotStateMachine::~RobotStateMachine()
{
}

bool RobotStateMachine::Transition_To_State(const State target_state)
{
	switch(target_state){
	
		case RobotStateMachine::State::DISCONNECTED:
			m_previous_state = m_current_state;
			m_current_state = RobotStateMachine::State::DISCONNECTED;
			return true;
			
		case RobotStateMachine::State::SAFE:
			m_previous_state = m_current_state;
			m_current_state = RobotStateMachine::State::SAFE;
			return true;
			
		case RobotStateMachine::State::ACTIVE:
			m_previous_state = m_current_state;
			if(m_current_state == RobotStateMachine::State::SAFE){
				m_current_state = RobotStateMachine::State::ACTIVE;
				return true;
			}
			else return false;
			
		default:
			return false;
	}
}
