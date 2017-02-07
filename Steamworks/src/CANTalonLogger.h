/*
 * CANTalonLogger.h
 *
 *  Created on: Feb 6, 2017
 *      Author: GEH-Magnet School 1
 */

#ifndef SRC_CANTALONLOGGER_H_
#define SRC_CANTALONLOGGER_H_
#include "WPILib.h"
#include "CANTalon.h"
#include <iostream>
#include <fstream>

class CANTalonLogger {
public:
	CANTalonLogger();
	CANTalonLogger(std::shared_ptr<CANTalon> talon, std::string name);
	void Update();
	virtual ~CANTalonLogger();
private:
	std::shared_ptr<CANTalon> Talon;
	std::ofstream tLog;
};

#endif /* SRC_CANTALONLOGGER_H_ */
