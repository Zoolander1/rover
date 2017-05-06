#include "mbed.h"
#include "include/MotorEncoder.h"
#include "include/Actuator.h"
#include <cstddef>

class Motor : private Actuator{
	
	public:
		
		/**
		Constructor
		**/
		Motor(int pinnumber, int pwmchannelnumber, float outputfreqhz,
					float feedbacksamplingfreqhz, float feedbacksamplingresolution);
	
		/**
		Deconstructor
		**/
		virtual ~Motor();

		/**
		Initialises	Pin Out number, PWM channel number, and PWM frequency (Hz).
		Initialises ADC interrupt frequency, and ADC sampling resolution.
		Initialises current position and velocity.
		**/
		virtual bool Initialise() override;
	
		/**
		Sets the motor velocity (PWM duty cycle to motor driver)
		**/
		virtual bool SetVelocity(const float& velocitysetpoint) override;
		
		/**
		Gets the current motor encoder position
		**/
		virtual bool GetPosition(float& currentposition) override;
	
		/**
		Gets the differential of the motor position with respect to the sampling
		frequency set in Initialise
		**/
		virtual bool GetVelocity(float& currentvelocity) override;
	
		//ISR for A and B encoder change in signal level (pull up A + B signal?).
		//Timeout when A or B signal change not detected for X microseconds.
		//Reset timeout timer every time ISR is triggered, when timeout time (X microseconds) has elapsed,
		//then set velocity to 0 rads/s.
	
		virtual bool SetCartesianForce(const float& cartesianforcesetpoint) override;
	
	private:
		int mpinnumber = 0;
		int mpwmchannelnumber = 0;
};
