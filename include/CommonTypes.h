#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include "mbed.h"
#include "RobotStateMachine.h"

#pragma pack(1)

typedef struct{
    float left;
    float right;
} WheelPosition;

typedef struct{
    float left;
    float right;
} WheelVelocity;

typedef struct{
    bool loop_timeout;
    bool encoder_read_error;
} RobotStatus;

typedef struct{
    WheelPosition Position;
    WheelVelocity Velocity;
    RobotStatus Status;
} RobotStruct;

typedef union{
  RobotStruct robot_struct;
  char array[sizeof(RobotStruct)];
} RobotStructUnion;

typedef struct{
	RobotStateMachine::State commanded_state;
} CommandMessage;

typedef struct{
	RobotStateMachine::State robot_state;
} StatusMessage;

#endif
