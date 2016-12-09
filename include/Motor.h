#include "mbed.h"
#include "include/MotorEncoder.h"
#include <cstddef>
#include <memory>

class Motor{
	
	public:
		
		/**
		Constructor
		**/
		Motor(int samplingfreqhz, int pwmfreqhz, int pinnumber, int pwmchannelnumber, 
					int encoderadcsamplingfreqhz, int encoderadcsamplingresolution);
	
		/**
		Deconstructor
		**/
		virtual ~Motor();

		/**
		Initialises motor object with position/velocity sampling frequency (Hz),
		PWM frequency (Hz), Pin Out number, and PWM channel number.
		Initialises current position and velocity.
		**/
		bool Initialise();
	
		/**
		Sets the output PWM duty cycle (to motor driver)
		**/
		bool SetPWMDuty(const float& pwmdutysetpoint);
	
		/**
		Gets the current motor encoder position
		**/
		bool GetPosition(float& position);
	
		/**
		Gets the differential of the motor position with respect to the sampling
		frequency set in Initialise
		**/
		bool GetVelocity(float& speed);
	
	private:
		
		int msamplingfreqhz = 0;
		int mpwmfreqhz = 0;
		int mpinnumber = 0;
		int mpwmchannelnumber = 0;
		int mcurrentposition = 0;
		int mcurrentvelocity = 0;
		MotorEncoder* mencoder = NULL;
		int madcsamplingfreqhz = 0;
		int madcsamplingresolution = 0;
};
