// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "VelocityStep.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

VelocityStep::VelocityStep(double timeout) : TimedCommand(timeout) {
    // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void VelocityStep::Initialize() {
	Robot::driveTrain->SetChassisMode(CANTalon::TalonControlMode::kSpeedMode);
}

// Called repeatedly when this Command is scheduled to run
void VelocityStep::Execute() {
	Robot::driveTrain->SetChassisWheelVelocity(500.0, 500.0);
}

// Called once after command times out
void VelocityStep::End() {
	Robot::driveTrain->SetChassisVelocity(0.0);
	Robot::driveTrain->SetChassisMode(
			CANTalon::TalonControlMode::kThrottleMode);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VelocityStep::Interrupted() {
End();
}
