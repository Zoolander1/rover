#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include "SpwfInterface.h"
#include "mbed.h"

class NetworkInterface{
	
	public:
		NetworkInterface(const PinName &tx_pin, const PinName &rx_pin, Serial* pc_usart);
		virtual ~NetworkInterface();
	
		bool Connect_To_Network(const char* network_ssid, const char* network_passphrase, const nsapi_security_t &network_security);
		bool Disconnect_From_Network();
		SpwfSAInterface* Get_Network_Interface(){return mspwf;};
		
	private:
		SpwfSAInterface* mspwf;
		SocketAddress* mhost_address;
		PinName mtx_pin;
		PinName mrx_pin;
		Serial* mpc;
};

#endif
