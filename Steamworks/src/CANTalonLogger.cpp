/*
 * CANTalonLogger.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: GEH-Magnet School 1
 */

#include "CANTalonLogger.h"

CANTalonLogger::CANTalonLogger() {
	// TODO Auto-generated constructor stub

}

void CANTalonLogger::Update() {
	if (tLog.is_open()) {
		printf("update\n");
		tLog << Talon->GetPosition() << ", ";
		tLog << Talon->GetSetpoint() << ", ";
		tLog << Talon->GetClosedLoopError() << ", ";
		tLog << Talon->GetSpeed() << ", ";
		tLog << Talon->GetOutputVoltage() << ", ";
		tLog << Talon->GetOutputCurrent() << std::endl;
	}
}

void CANTalonLogger::Flush() {
	tLog.flush();
}

void CANTalonLogger::StartSession() {
	if (!tLog.is_open()) {
		printf("start session\n");
		tLog.open(mFilename, std::ofstream::out | std::ofstream::app);
	}
}

void CANTalonLogger::EndSession() {
	if (tLog.is_open()) {
		printf("end session\n");
		tLog.close();
	}
}

CANTalonLogger::~CANTalonLogger() {
	// TODO Auto-generated destructor stub
	tLog.close();
}

CANTalonLogger::CANTalonLogger(std::shared_ptr<CANTalon> talon, std::string name) {
	printf("construct\n");
	Talon = talon;
	mFilename = name;
	tLog.open(mFilename, std::ofstream::out | std::ofstream::trunc);
	tLog << "Position, Setpoint, Error, Speed, Voltage, Current" << std::endl;
}

