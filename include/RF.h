#include "mbed.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <functional>
#include "Robot.h"
#include <iterator>
#include <algorithm>
#include <vector>

enum XRF_Type : unsigned char{
			RX = 0 ,
			TX = 1
};

class RF{
	
	public:
	
		RF(PinName RX, PinName TX, IRQn_Type usart_rx_tx_irq, XRF_Type Transceiver_Type, int baud);
		virtual ~RF();
	
		bool Send_Data(Robot_Struct& tx_data);
		void Receive_Data_ISR();
		void Transmit_Data_ISR();
	
	private:
		
		template <typename T>
		void ToBigEndian(T& num);
		void OrderRobotStructForTx(Robot_Struct RobotData);
		
		Robot_Struct* rx_data;
	
		Serial RF_Module;
		char received_data_buffer[sizeof(Robot_Struct)];
		int buffer_index;
		IRQn_Type usart_irq;
	
};
