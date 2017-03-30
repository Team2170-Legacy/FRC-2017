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
#include "AutonomousLowBoiler.h"
#include "AutonomousAllianceCmd.h"
#include "AutonomousBlendedMove.h"
#include "../Vision/VisionProcessing.h"

AutonomousGearGroup::AutonomousGearGroup() {
	// TODO Auto-generated constructor stub
	AddParallel(new ElevatorInitialize());
	AddSequential(
			new AutonomousAllianceCmd(
					new AutonomousBlendedMove(&AutoMove_RS1_to_RP1_L,
							&AutoMove_RS1_to_RP1_R, t_auto_end_RS1_to_RP1,
							&VisionProcessing::e_Gear_x),
					new AutonomousBlendedMove(&AutoMove_RS3_to_RP3_L,
							&AutoMove_RS3_to_RP3_R, t_auto_end_RS3_to_RP3,
							&VisionProcessing::e_Gear_x)));
	AddSequential(new BackDoorOpen());
	AddSequential(new frc::WaitCommand(.5));

	// Drive to Boiler
//	AddSequential(
//			new AutonomousAllianceCmd(new AutonomousMotionProfile(),
//					new AutonomousMotionProfile()));
	AddSequential(new AutonomousLowBoiler());

	AddSequential(new BackDoorClose());
}

AutonomousGearGroup::AutonomousGearGroup(frc::Command* cmd) {
	AddParallel(new ElevatorInitialize());
	AddSequential(cmd);
	AddSequential(new BackDoorOpen());
	AddSequential(new frc::WaitCommand(.5));
	AddSequential(new AutonomousMotionProfile(&MoveOffPeg));
	AddSequential(new BackDoorClose());
}
