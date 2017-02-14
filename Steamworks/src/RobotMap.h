// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "WPILib.h"
#include "CANTalon.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "AHRS.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<CANTalon> driveTrainCANTalonLeft;
	static std::shared_ptr<CANTalon> driveTrainCANTalonRight;
	static std::shared_ptr<RobotDrive> driveTrainRobotDrive;
	static std::shared_ptr<CANTalon> driveTrainCANTalonSlaveLeft;
	static std::shared_ptr<CANTalon> driveTrainCANTalonSlaveRight;
	static std::shared_ptr<Servo> payloadDoorServoA;
	static std::shared_ptr<Servo> payloadDoorServoB;
	static std::shared_ptr<CANTalon> payloadCANTalonElevator;
	static std::shared_ptr<CANTalon> payloadCANTalonClimber;
	static std::shared_ptr<SpeedController> payloadSpeedControllerIntake;
	static std::shared_ptr<DigitalInput> payloadLimitSwitchHome;
	static std::shared_ptr<SpeedController> dumperSpeedControllerDumper;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<AHRS> driveTrainAHRS;
	static void init();
};
#endif
