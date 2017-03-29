/*
 * AutonomousGearGroup.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: GEH-Magnet School 1
 */

#include "AutonomousGearGroup.h"
#include "AutonomousMotionProfile.h"
#include "ElevatorInitialize.h"
#include "BackDoorOpen.h"
#include "BackDoorClose.h"

AutonomousGearGroup::AutonomousGearGroup() {
	// TODO Auto-generated constructor stub

}

AutonomousGearGroup::AutonomousGearGroup(frc::Command* cmd) {
	AddParallel(new ElevatorInitialize());
	AddSequential(cmd);
	AddSequential(new BackDoorOpen());
	AddSequential(new frc::WaitCommand(.5));
	AddSequential(new AutonomousMotionProfile(&MoveOffPeg));
	AddSequential(new BackDoorClose());
}
