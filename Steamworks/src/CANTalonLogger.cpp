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
		tLog << LogTimer.Get() << "," << Talon->GetPosition()
				<< "," << Talon->GetClosedLoopError() << ","
				<< Talon->GetSpeed() << "," << Talon->GetOutputVoltage() << ","
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
	LogTimer.Reset();
	LogTimer.Start();
}

void CANTalonLogger::EndSession() {
	if (tLog.is_open()) {
		tLog.close();
	}
	LogTimer.Stop();
}

CANTalonLogger::~CANTalonLogger() {
	// TODO Auto-generated destructor stub
	if (tLog.is_open()) {
		tLog.close();
	}
}

CANTalonLogger::CANTalonLogger(std::shared_ptr<CANTalon> talon, std::string name) {
	printf("construct\n");
	Talon = talon;
	mFilename = name;
	tLog.open(mFilename, std::ofstream::out | std::ofstream::trunc);
	tLog << "Time,Position,Error,Speed,Voltage" << std::endl;
}

