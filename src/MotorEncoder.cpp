#include "include/MotorEncoder.h"

MotorEncoder::MotorEncoder(int adcsamplingfreqhz, int adcsamplingresolution) : 
	madcsamplingfreqhz(adcsamplingfreqhz), 
	madcsamplingresolution(adcsamplingresolution)
{
	
}
	
MotorEncoder::~MotorEncoder(){
}

bool MotorEncoder::Initialise(){
	
	return false;
}

bool MotorEncoder::CalculatePosition(int& currentposition){
	
	return false;
}
