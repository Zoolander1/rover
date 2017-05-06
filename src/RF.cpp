#include "include/RF.h"

uint8_t read_ack;

RF::RF(PinName RX, PinName TX, IRQn_Type usart_rx_tx_irq, XRF_Type Transceiver_Type, int baud):
	RF_Module(RX,TX),    
	received_data_buffer(),
	buffer_index(0),
	usart_irq(usart_rx_tx_irq)
{
	rx_data = new Robot_Struct();
	RF_Module.baud(baud);
	if(Transceiver_Type == RX){
		//RF_Module.attach(callback(this, &RF::Receive_Data_ISR), Serial::RxIrq);			TEST THIS
		//RF_Module.attach(this, &RF::Receive_Data_ISR, Serial::RxIrq);
	}
	
	read_ack = 0;
	
}

RF::~RF(){	
	delete rx_data;
}

bool RF::Send_Data(Robot_Struct& tx_data){
	
	uint8_t* start_ptr;
	uint8_t  start_data[4];
	uint8_t* end_ptr;
	uint8_t  end_data[4];
	
	start_data[0] = 0x00;
	start_data[1] = 0x00;
	start_data[2] = 0xC0;
	start_data[3] = 0xFF;
	
	end_data[0] = 0x00;
	end_data[1] = 0x00;
	end_data[2] = 0x80;
	end_data[3] = 0xFF;
	
	start_ptr = &start_data[0];
	end_ptr = &end_data[0];
	
	NVIC_DisableIRQ(usart_irq);
	OrderRobotStructForTx(tx_data);															//Reorder anything larger than a byte before sending
	uint8_t* data = reinterpret_cast<uint8_t*>(&tx_data);
	
	RF_Module.putc('A');
	if(!RF_Module.readable()) return false;
	
	if(RF_Module.getc() != 'B') return false;
	wait_ms(10);
	for(int i = 0; i < sizeof(Robot_Struct); i++){
		RF_Module.putc(data[i]);
	}
	
	NVIC_EnableIRQ(usart_irq);
}

void RF::OrderRobotStructForTx(Robot_Struct RobotData){							//Change from reference to value copy
	ToBigEndian(RobotData.Position.X);
	ToBigEndian(RobotData.Position.Y);
	ToBigEndian(RobotData.Position.Z);
	ToBigEndian(RobotData.Orientation.ThetaX);
	ToBigEndian(RobotData.Orientation.ThetaY);
}

template <typename T>
	void RF::ToBigEndian(T& num){																				//Change from to value copy + sort template stuff + return value?
		
		char* numswapped = new char[sizeof(num)];
    for(long i = 0; i < static_cast<long>(sizeof(num)); i++)
        numswapped[sizeof(num) - 1 - i] = ((char*)(&num))[i];
    for(long i = 0; i < static_cast<long>(sizeof(num)); i++)
        ((char*)(&num))[i] = numswapped[i];
    delete[] numswapped;
	}

void RF::Receive_Data_ISR(){
	
	NVIC_DisableIRQ(usart_irq);
	if(RF_Module.readable()){
		//received_data_buffer[buffer_index] = RF_Module.getc();
		if(RF_Module.getc() == 'A'){
			//read_ack = 1;
		}
		//buffer_index++;
		//if(buffer_index == sizeof(Robot_Struct)){
			//rx_data = reinterpret_cast<Robot_Struct*>(&received_data_buffer);
			//buffer_index=0;
			//Clear received_data_buffer here
		//}
	}
	NVIC_EnableIRQ(usart_irq);
}
