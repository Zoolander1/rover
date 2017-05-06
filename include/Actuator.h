#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "include/ActuatorFeedback.h"

class Actuator{
	
	public:
		virtual ~Actuator();
		virtual bool Initialise()=0;
		virtual bool SetPosition(const float& positionsetpoint);
		virtual bool SetVelocity(const float& velocitysetpoint);
		virtual bool SetCartesianForce(const float& cartesianforcesetpoint);
		virtual bool GetPosition(float& currentposition);
		virtual bool GetVelocity(float& currentvelocity);
	
	protected:
		Actuator(float outputfreqhz, float feedbacksamplingfreqhz, float feedbacksamplingresolution);
		float mvelocitysetpoint = 0;
		float mpositionsetpoint = 0;
		float mcurrentposition = 0;
		float mcurrentvelocity = 0;
		float moutputfreqhz = 0;
		float mfeedbacksamplingfreqhz = 0;
		float mfeedbacksamplingresolution = 0;
	
	private:
	
};

#endif
