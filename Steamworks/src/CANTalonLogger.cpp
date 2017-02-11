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
		tLog << Talon->GetPosition() << ", ";
		tLog << Talon->GetSetpoint() << ", ";
		tLog << Talon->GetClosedLoopError() << ", ";
		tLog << Talon->GetSpeed() << ", ";
		tLog << Talon->GetOutputVoltage() << ", ";
		tLog << Talon->GetOutputCurrent() << "\n";
	}
}

void CANTalonLogger::Flush() {
	tLog.flush();
}

CANTalonLogger::~CANTalonLogger() {
	// TODO Auto-generated destructor stub
	tLog.close();
}

CANTalonLogger::CANTalonLogger(std::shared_ptr<CANTalon> talon, std::string name) {
	Talon = talon;
	tLog.open(name, std::ofstream::out | std::ofstream::app);
	tLog << "Postion, Setpoint, Error, Speed, Voltage, Current\n";
}

