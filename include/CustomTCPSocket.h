#ifndef CUSTOMTCPSOCKET_H
#define CUSTOMTCPSOCKET_H

#include "TCPSocket.h"
#include "SpwfInterface.h"
#include "mbed.h"
#include <string>
#include <vector>

class CustomTCPSocket{
	
	public:
		CustomTCPSocket(const char* host_name, const int &port_number, SpwfSAInterface* spwf, Serial* pc_usart);
		virtual ~CustomTCPSocket();

		bool Open_Socket();
		bool Connect_Socket();
		void Set_Socket_Timeout_Ms(const int &timeout_ms);
		void Set_Socket_Blocking(const bool &blocking);
		bool Check_Data_Writeable();
		bool Send_Data(const std::vector<uint8_t> &send_data);				//(const uint8_t &send_data);
		bool Check_Data_Available();
		bool Received_Data(std::vector<uint8_t> &received_data);
		bool Close_Socket();
		const int Get_Time_Since_Last_Data_Sent_Ms(){return mlast_sent_data->read_ms();};
		const int Get_Time_Since_Last_Data_Received_Ms(){return mlast_received_data->read_ms();};
	
	private:	
		TCPSocket* msocket;
		SpwfSAInterface* mspwf;
		SocketAddress* mhost_address;
		int mport_number;
		const char* mhost_name;
		Serial* mpc;
		Timer* mlast_received_data;
		Timer* mlast_sent_data;
};

#endif
