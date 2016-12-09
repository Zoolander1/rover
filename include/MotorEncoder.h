

class MotorEncoder{
	
	public:
		
		//Constructor
		MotorEncoder(int adcsamplingfreqhz, int adcsamplingresolution);
	
		//Deconstructor
		virtual ~MotorEncoder();
	
		/**
		Initialises ADC sampling of quadrature motor encoder
		**/
		bool Initialise();
	
		/**
		Calculates current quadrature motor encoder position
		**/
		bool CalculatePosition(int& currentposition);
	
	private:
	
		int madcsamplingfreqhz;
		int madcsamplingresolution;
		int mcurrentposition;
	
};
