#include "AutonomousStop.h"

AutonomousStop::AutonomousStop() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
}

// Called once when the command executes
void AutonomousStop::Initialize() {
	Robot::driveTrain->StopMotors();
}
