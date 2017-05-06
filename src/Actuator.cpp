#include "include/Actuator.h"

Actuator::Actuator(float outputfreqhz, float feedbacksamplingfreqhz, float feedbacksamplingresolution):
		moutputfreqhz(outputfreqhz),
		mfeedbacksamplingfreqhz(feedbacksamplingfreqhz),
		mfeedbacksamplingresolution(feedbacksamplingfreqhz)
{
	
}

Actuator::~Actuator(){
	
}

bool Actuator::SetPosition(const float& positionsetpoint){
	
	return false;
}

bool Actuator::SetVelocity(const float& velocitysetpoint){
	
	return false;
}

bool Actuator::GetPosition(float& currentposition){
	
	return false;
}

bool Actuator::GetVelocity(float& currentvelocity){
	
	return false;
}

bool Actuator::SetCartesianForce(const float& cartesianforcesetpoint){
	
	return false;
}
