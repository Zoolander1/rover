#include "include/Motor.h"

Motor::Motor(int samplingfreqhz, int pwmfreqhz, int pinnumber, int pwmchannelnumber, 
						 int encoderadcsamplingfreqhz, int encoderadcsamplingresolution):
		msamplingfreqhz(samplingfreqhz),
		mpwmfreqhz(pwmfreqhz),
		mpinnumber(pinnumber),
		mpwmchannelnumber(pwmchannelnumber),
		mencoder(new MotorEncoder(encoderadcsamplingfreqhz,encoderadcsamplingresolution))
{
	
}

Motor::~Motor(){
	delete mencoder;
}

bool Motor::Initialise(){
	
	return false;
}

bool Motor::SetPWMDuty(const float& pwmdutysetpoint){

	return false;
}

bool Motor::GetPosition(float& position){
	
	return false;
}

bool Motor::GetVelocity(float& speed){
			
	return false;
}
