/*
 * AutonomousInitGroup.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: GEH-Magnet School 1
 */

#include "AutonomousInitGroup.h"
#include "AutonomousMotionProfile.h"
#include "ElevatorInitialize.h"

AutonomousInitGroup::AutonomousInitGroup() {
	// TODO Auto-generated constructor stub

}

AutonomousInitGroup::AutonomousInitGroup(frc::Command* cmd) {
	AddParallel(new ElevatorInitialize());
	AddSequential(cmd);
}

AutonomousInitGroup::AutonomousInitGroup(const ProfileData* array) {
	AddParallel(new ElevatorInitialize());
	AddSequential(new AutonomousMotionProfile(array));
}
