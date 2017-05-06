#include "CustomTCPSocket.h"

CustomTCPSocket::CustomTCPSocket(const char* host_name, const int &port_number, SpwfSAInterface* spwf, Serial* pc_usart):
	msocket(new TCPSocket()),
	mspwf(spwf),
	mhost_address(new SocketAddress(host_name, port_number)),
	mport_number(port_number),
	mhost_name(host_name),
	mpc(pc_usart),
	mlast_received_data(new Timer()),
	mlast_sent_data(new Timer())
{
}

CustomTCPSocket::~CustomTCPSocket()
{
	//Release dynamically assigned memory
	delete msocket;
	delete mhost_address;
	delete mspwf;
	delete mpc;
	delete mlast_received_data;
	delete mlast_sent_data;
}

bool CustomTCPSocket::Open_Socket()
{
	int ret = 0;
	ret = msocket->open(mspwf);
	if(ret){
		mpc->printf("error: 'open(%p)' failed with code %d\r\n", mspwf, ret);
		return false;
	}
	else{
		mpc->printf("Opened TCP Port\r\n");
		return true;
	}
}
		
bool CustomTCPSocket::Connect_Socket()
{
	int ret = 0;

	ret = msocket->connect(*mhost_address);

	if(ret){
		mpc->printf("error: 'connect(SocketAddress(%s, %d))' failed with code %d\r\n", 
								mhost_address->get_ip_address(), mhost_address->get_port(), ret);
		return false;
	}
	else{
		mpc->printf("Connected to TCP Port\r\n");
		return true;
	}
}
		
void CustomTCPSocket::Set_Socket_Timeout_Ms(const int &timeout_ms)
{
	msocket->set_timeout(timeout_ms);
}
		
void CustomTCPSocket::Set_Socket_Blocking(const bool &blocking)
{
	msocket->set_blocking(blocking);
}

bool CustomTCPSocket::Check_Data_Writeable()
{
	if(msocket->writeable()) return true;		//Data Writeable
	else return false;											//Data Not Writeable
}
		
bool CustomTCPSocket::Send_Data(const std::vector<uint8_t> &send_data)
{
	int ret = 0;
	
	ret = msocket->send(&send_data[0], send_data.size());			//change to dynamic size of buffer		
	if(ret<0){
		mpc->printf("error: 'send(buffer, %d)' failed during test with code %d\r\n", send_data.size(), ret);
		return false;
  }
	else{
		mpc->printf("Sent data %d\r\n", &send_data[0]);
		//Set time last sent
		return true;
	}
}

bool CustomTCPSocket::Check_Data_Available()
{
	if(msocket->readable()) return true;		//Data Available
	else return false;											//Data Unavailable
}
		
bool CustomTCPSocket::Received_Data(std::vector<uint8_t> &received_data)
{
	int ret = 0;
	uint8_t test_buffer[512];
	
	ret = msocket->recv(test_buffer, sizeof test_buffer);
	mpc->printf("ret = %d\n\r", ret);
	
	if (ret != NSAPI_ERROR_WOULD_BLOCK) {
		if (ret < 0) {
			mpc->printf("error: 'recv(buffer, %d)' failed during test with code %d\r\n", received_data.size(), ret);
			return false;
		} 
		else {
		//	mpc->printf("error: 'recv(buffer, %d)' returned %d when no data was expected\r\n", received_data.size(), ret);
		//	return false;
			received_data.assign(&test_buffer[0], &test_buffer[ret]);
			return true;
		}
	}
	else{							//TIMEOUT OCCURED FOR BLOCKING CALL
		return false;				
	}
}
		
bool CustomTCPSocket::Close_Socket()
{
		if(msocket->close() == 0) return true;
		else return false;
}
 