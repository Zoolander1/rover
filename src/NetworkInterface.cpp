#include "NetworkInterface.h"

NetworkInterface::NetworkInterface(const PinName &tx_pin, const PinName &rx_pin, Serial* pc_usart):
	mspwf(new SpwfSAInterface(tx_pin, rx_pin, false)),
	mtx_pin(tx_pin),
	mrx_pin(rx_pin),
	mpc(pc_usart)
{
}

NetworkInterface::~NetworkInterface()
{
	delete mspwf;
}

bool NetworkInterface::Connect_To_Network(const char* network_ssid, const char* network_passphrase, const nsapi_security_t &network_security)
{
	int32_t err = 0;

  mpc->printf("Connecting to Network\r\n");      
  err = mspwf->connect(network_ssid, network_passphrase, network_security);
  if(!err){
		mpc->printf("Interface failed to connect with code %d\r\n", err);
		return false;
	}
	else{
		mpc->printf("Connected\r\n");
		if(!mspwf->get_ip_address()[0]){
			mpc->printf("error: 'get_ip_address()' did not return an IP address\r\n");
			return false;
		}
		else{
			mpc->printf("IP address: %s\r\n", mspwf->get_ip_address());
			return true;
		}
	}
}

bool NetworkInterface::Disconnect_From_Network()
{
	return mspwf->disconnect();
}
