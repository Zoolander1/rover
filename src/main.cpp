#include "mbed.h"
#include <string>
#include <vector>
#include "CustomTCPSocket.h"
#include "NetworkInterface.h"
#include "CommonTypes.h"
#include "RobotStateMachine.h"
//#include "RF.h"


//PwmOut mypwm(PWM_OUT);
    
   // mypwm.period_ms(10);
   // mypwm.pulsewidth_ms(1);
	
	 //  printf("pwm set to %.2f %%\n", mypwm.read() * 100);
	
	
		//Control loop reading pos and vel initially - if any fail then stop control loop.
		//mutex_value is declared as volatile.
		//if compareandset has failed then report back expected value (which has been set with the actual value), for error message sent to PC
//		if(!compareandsset(mutex_value, expected_value, 1)
//			break;
//	
//		read global_position
//		read global_velocity
//	
//		if(!compareandset(mutex_value, expected_value, 0))
//			break;
//  
//		
//		//Timer interrupt setting pos and vel
//		
//		calculate local_pos
//		calculate local_vel
//		
//		ISR_expected_value = 0
//		
//		if(compareandset(muxtex_value, ISR_expected_value, 0))			//Is 0 when Control loop is not reading from it
//			set global_position
//			set global_velocity


//DigitalOut myled(LED1);
Serial* pc;
NetworkInterface* network_interface;
//CustomTCPSocket* tcp_send_data;
//CustomTCPSocket* tcp_receive_data;
CustomTCPSocket* tcp_receive_command;
CustomTCPSocket* tcp_send_status;
//std::vector<uint8_t> send_data;
//std::vector<uint8_t> received_data;
std::vector<uint8_t> received_command_data;
std::vector<uint8_t> send_status_data;
//RobotStructUnion robot;
//RobotStruct received_robot_data;
//int send_fail_count;
//bool receive_socket_initialised;
ldiv_t received_data_size_check;
//int timeout_occurred;
//int start_receiving_and_sending_data;
//int connected_to_hmi;
bool receive_command_socket_connected = false;

RobotStateMachine* robot_state;
CommandMessage received_command_message;


//uint8_t buffer[128];
//size_t message_length;
//bool status;

void CastVectorCharToRobotStruct(std::vector<uint8_t> vector_array, RobotStruct& robot_struct){
	
	RobotStruct* cast_data;
	
	cast_data = reinterpret_cast<RobotStruct*>(&vector_array.at(0));
	
	robot_struct.Position.left = cast_data->Position.left;
	robot_struct.Position.right = cast_data->Position.right;
	robot_struct.Velocity.left = cast_data->Velocity.left;
	robot_struct.Velocity.right = cast_data->Velocity.right;
	robot_struct.Status.loop_timeout = cast_data->Status.loop_timeout;
	robot_struct.Status.encoder_read_error = cast_data->Status.encoder_read_error;
}

void CastRobotStructToVector(RobotStruct robot_struct, std::vector<uint8_t>& vector_array){
	
	char* cast_data;
	
	cast_data = reinterpret_cast<char*>(&robot_struct);
	vector_array.assign(&cast_data[0], cast_data+sizeof(RobotStruct));
}

void CastVectorCharToCommandMessage(std::vector<uint8_t> vector_array, CommandMessage& command_message){
	CommandMessage* cast_data;
	
	cast_data = reinterpret_cast<CommandMessage*>(&vector_array.at(0));
	
	command_message.commanded_state = cast_data->commanded_state;	
}

int main() {
	
	//connected_to_hmi = 0;
	//timeout_occurred = 0;
	//start_receiving_and_sending_data=1;
	//send_fail_count = 0;
	//receive_socket_initialised = false;
	
	
	//Create Objects & Initialise
	robot_state = new RobotStateMachine();
	pc = new Serial(USBTX, USBRX);
	network_interface = new NetworkInterface(D8, D2, pc);
	network_interface->Connect_To_Network("BTHub6-TX3W", "xVxvEQfdky4Y", NSAPI_SECURITY_WPA2);
	tcp_receive_command = new CustomTCPSocket("192.168.1.215", 5010, network_interface->Get_Network_Interface(), pc);
	tcp_send_status = new CustomTCPSocket("192.168.1.215", 5011, network_interface->Get_Network_Interface(), pc);
	
	
	//tcp_send_data = new CustomTCPSocket("192.168.1.215", 5003, network_interface->Get_Network_Interface(), pc);
	//tcp_receive_data = new CustomTCPSocket("192.168.1.215", 5004, network_interface->Get_Network_Interface(), pc);
	
	//tcp_receive_data->Open_Socket();
	//tcp_receive_data->Connect_Socket();
	//tcp_receive_data->Set_Socket_Timeout_Ms(1000);
	
	//tcp_send->Open_Socket();
	//tcp_send->Connect_Socket();
	//tcp_send_data->Set_Socket_Timeout_Ms(1000);
	
	//tcp_receive_command->Close_Socket();
	
	//tcp_receive_command->Open_Socket();
	//receive_command_socket_connected = tcp_receive_command->Connect_Socket();
	//tcp_receive_command->Set_Socket_Timeout_Ms(1000);
	
	//tcp_status->Open_Socket();
	//tcp_status->Connect_Socket();
	//tcp_status->Set_Socket_Timeout_Ms(1000);
	
	//robot.robot_struct.Position.left = 1.234f;
	//robot.robot_struct.Position.right = 4.321f;
	//robot.robot_struct.Velocity.left = 5.678f;
	//robot.robot_struct.Velocity.right = 67.89f;
	//robot.robot_struct.Status.loop_timeout = 1;
	//robot.robot_struct.Status.encoder_read_error = 1;
	
	//send_data_buffer.assign(&robot.array[0], robot.array+sizeof(RobotStruct));

	while(1) {	
		if(robot_state->Get_Robot_Current_State() == RobotStateMachine::State::DISCONNECTED){
			//pc->printf("In Disconnected State\n\r");																								//REMOVE AFTER TESTING
			if(robot_state->Get_Robot_Previous_State() == RobotStateMachine::State::ACTIVE){

				//Set Motor Demand = 0
				//Set Motors Enabled = FALSE
				
			}
			//Close all sockets
			tcp_receive_command->Close_Socket();
			//tcp_status->Close_Socket();
			//tcp_send_data->Close_Socket();
			//tcp_receive_data->Close_Socket();
			pc->printf("Closed all sockets\n\r");
			
			tcp_receive_command->Open_Socket();
			receive_command_socket_connected = tcp_receive_command->Connect_Socket();
			
			if(receive_command_socket_connected){
				tcp_receive_command->Set_Socket_Timeout_Ms(1000);
				
				//Reconnect all other sockets & set timeouts
				
				//If All Sockets Reconnect then transition to SAFE
				robot_state->Transition_To_State(RobotStateMachine::State::SAFE);
				pc->printf("Connected to PC\n\r");
			}
			else{
				pc->printf("Not connected to PC\n\r");
				wait_ms(1000);
			}
		}
		
		if(robot_state->Get_Robot_Current_State() != RobotStateMachine::State::DISCONNECTED){
			if(tcp_receive_command->Check_Data_Available()){
				if(tcp_receive_command->Received_Data(received_command_data)){
					//CHECK RECEIVED COMMAND DATA SIZE
					received_data_size_check = ldiv(received_command_data.size(),sizeof(CommandMessage));
					if(received_data_size_check.quot > 0 && received_data_size_check.rem == 0){
						CastVectorCharToCommandMessage(received_command_data, received_command_message);
						robot_state->Transition_To_State(received_command_message.commanded_state);
						if((robot_state->Get_Robot_Current_State() == RobotStateMachine::State::ACTIVE)  && (robot_state->Get_Robot_Previous_State() == RobotStateMachine::State::SAFE)){
							pc->printf("Reset Timers\n\r");											//REMOVE AFTER TESTING
							//Control Loop Timer Reset
							//Time Since Last Control Data Received Timer Stop
							//Time Since Last Control Data Received Timer Reset
						}
					}
				}
				else{
					robot_state->Transition_To_State(RobotStateMachine::State::DISCONNECTED);
					pc->printf("Receive Command Socket Disconnected\n\r");
				}
			}
			if(robot_state->Get_Robot_Current_State() != RobotStateMachine::State::DISCONNECTED){
				if(robot_state->Get_Robot_Current_State() == RobotStateMachine::State::ACTIVE){
					//pc->printf("In Active State\n\r");																													//REMOVE AFTER TESTING
					//if(Control Loop Timer <= 10ms){
					//	Control Loop Timer Reset
					//	Control Loop Timer Start
					//	
					//	if(Time Since Last Control Data Received Timer <= 50ms){
					//		if(Receive Control Data Available){
					//			if(Receive Control Data == TRUE){
					//				if(Check Received Control Data Size == TRUE){
					//					Time Since Last Control Data Received Timer Stop
					//					Time Since Last Control Data Received Timer Reset
					//					Cast Received Control Data to Control Data Struct
					//					Set Motor Demand
					//				}
					//				else{
					//					Time Since Last Control Data Received Timer Start			//WHAT HAPPENS WHEN START CALLED MULTIPLE TIMES?
					//				}
					//			}
					//			else{
					//				robot_state->Transition_To_State(RobotStateMachine::State::DISCONNECTED);
					//				pc->printf("Receive Control Data Socket Disconnected\n\r");
					//			}
					//		}
					//		else{
					//			Time Since Last Control Data Received Timer Start						//WHAT HAPPENS WHEN START CALLED MULTIPLE TIMES?
					//		}
					//		wait_ms(remaining control loop time);
					//	}
					//	else{
					//		robot_state->Transition_To_State(RobotStateMachine::State::SAFE);
					//		pc->printf("Control Data Not Received Timer Elapsed\n\r");		
					//	}
					//
					//	Control Loop Timer Stop
					//}
					//else{
					//	robot_state->Transition_To_State(RobotStateMachine::State::SAFE);
					//	pc->printf("Control Loop Timed Out\n\r");
					//}
				}
				else{
					//pc->printf("In Safe State\n\r");																								//REMOVE AFTER TESTING
					//Set Motor Demand to 0
				}
					
				//Get Motor Velocities
					
				//Send Motor Velocities
					
				//If Send Status Socket Writeable
				//		Send Status
				//Else
				//		Transition to Safe State
				//		Print Send Status Socket Unavailable
			}
		}
		
		
		
		
//		//Listen for state command
//		//if(robot_state->Get_Robot_State() == RobotStateMachine::State::SAFE || robot_state->Get_Robot_State() == RobotStateMachine::State::ACTIVE){
//		if(tcp_receive_command->Check_Data_Available()){
//			if(tcp_receive_command->Received_Data(received_command_data)){
//				pc->printf("Size of struct: %d\n\r", received_command_data.size());
//				received_data_size_check = ldiv(received_command_data.size(),sizeof(CommandMessage));
//				if(received_data_size_check.quot > 0 && received_data_size_check.rem == 0){
//					CastVectorCharToCommandMessage(received_command_data, received_command_message);
//					pc->printf("Received command message: %i\n\r", static_cast<int>(received_command_message.commanded_state));
//					robot_state->Transition_To_State(received_command_message.commanded_state);
//					pc->printf("Robot State: %i\n\r", static_cast<int>(robot_state->Get_Robot_Current_State()));
//				}
//				else{
//					pc->printf("Received non multiple of command struct, number of bytes: %d\n\r", received_command_data.size());
//				}
//			}
//			else{
//				pc->printf("Receive Command Socket Disconnected\n\r");
//			}
//		}
//	
//		if(robot_state->Get_Robot_Current_State() == RobotStateMachine::State::SAFE){
//			
//			//Set motors to 0 output, etc.
//			//-3011 means no connection to HMI
//			
//		}
//		
//		if(robot_state->Get_Robot_Current_State() == RobotStateMachine::State::ACTIVE){
//			
//			
//			//Check recieved data timer
//		}
			
			
			//Send Status Message here
			//If status message fails to send then set robot state to DISCONNECTED 
		//}
		
		
//		if(!connected_to_hmi){
//			if(!tcp_command->Open_Socket()==0 || !tcp_status->Open_Socket()==0){
//				pc->printf("Could not connect to HMI");
//			}
//		}
//		else{
//			if(timeout_occurred){
//				tcp_send->Close_Socket();
//				tcp_receive->Close_Socket();
//				tcp_send->Open_Socket();
//				tcp_receive->Open_Socket();
//				if(tcp_receive->Connect_Socket()==0 && tcp_send->Connect_Socket() ==0) start_receiving_and_sending_data = 1;
//				else start_receiving_and_sending_data = 0;
//			}
//			if(tcp_receive->Received_Data(received_data) && start_receiving_and_sending_data)
//			{
//				
//				//Reset mlast_received_data milliseconds
//				
//				pc->printf("Size of struct: %d\n", received_data.size());
//				received_data_size_check = ldiv(received_data.size(),sizeof(RobotStruct));
//				if(received_data_size_check.quot > 0 && received_data_size_check.rem == 0){
//					
//					CastVectorCharToRobotStruct(received_data, received_robot_data);
//					
//					pc->printf("Received: %f\n\r", received_robot_data.Position.left);
//					pc->printf("Received: %f\n\r", received_robot_data.Position.right);
//					pc->printf("Received: %f\n\r", received_robot_data.Velocity.left);
//					pc->printf("Received: %f\n\r", received_robot_data.Velocity.right);
//					pc->printf("Received: %d\n\r", received_robot_data.Status.loop_timeout);
//					pc->printf("Received: %d\n\r", received_robot_data.Status.encoder_read_error);
//					
//					//Do something
//					
//					//Send Data
//					wait_ms(500);
//					myled.write(1);
//					//wait_ms(1000);
//					myled.write(0);
//					//robot.robot_struct.Position.left += 1.0f;
//					//robot.robot_struct.Velocity.right += 2.5f;
//					//send_data_buffer.assign(&robot.array[0], robot.array+sizeof(RobotStruct));
//					//if(!tcp_send->Send_Data(send_data_buffer)){
//					//	send_fail_count++;
//					//}
//					CastRobotStructToVector(received_robot_data, send_data);
//					if(!tcp_send->Send_Data(send_data)){
//						pc->printf("Send Timeout Occurred");
//						timeout_occurred = 1;
//					}
//					
//				}
//				else{
//					pc->printf("Received non multiple of struct, number of bytes: %d", received_data.size());
//					
//					//Receive ready message here	
//					//If received data = received start message then continue
//					//Else timeout_occurred = 1;
//				}
//			}
//			else{
//				pc->printf("Receieve Timeout Occured");
//				timeout_occurred = 1;
//			}
//		}
	}
    
}
