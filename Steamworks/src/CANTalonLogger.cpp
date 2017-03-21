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
		tLog << Talon->GetPosition() << ", " << Talon->GetSetpoint() << ", "
				<< Talon->GetClosedLoopError() << ", "<< Talon->GetSpeed() << ", "
				<< Talon->GetOutputVoltage() << ", " << Talon->GetOutputCurrent()
				<< std::endl;
	}
}

void CANTalonLogger::Flush() {
	tLog.flush();
}

void CANTalonLogger::StartSession() {
	if (!tLog.is_open()) {
		tLog.open(mFilename, std::ofstream::out | std::ofstream::app);
	}
}

void CANTalonLogger::EndSession() {
	if (tLog.is_open()) {
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
	tLog.open(mFilename, std::ofstream::out | std::ofstream::trunc | std::ofstream::app);
	tLog << "Pos (rotation), Setpoint, Error (counts), Speed, Voltage, Current" << std::endl;
}

