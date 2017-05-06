#include "include/Motor.h"

Motor::Motor(int pinnumber, int pwmchannelnumber, float outputfreqhz,
						 float feedbacksamplingfreqhz, float feedbacksamplingresolution):
		Actuator(outputfreqhz, feedbacksamplingfreqhz, feedbacksamplingresolution),
		mpinnumber(pinnumber),
		mpwmchannelnumber(pwmchannelnumber)
{
}

Motor::~Motor(){

}

bool Motor::Initialise(){
	
	return false;
}

bool Motor::SetVelocity(const float& velocitysetpoint){
	
	return false;
}

bool Motor::GetPosition(float& position){
	
	return false;
}

bool Motor::GetVelocity(float& speed){
			
	return false;
}

bool Motor::SetCartesianForce(const float& cartesianforcesetpoint){
	
	return true;
}
