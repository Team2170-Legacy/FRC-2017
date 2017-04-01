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
#include "../automoves/RP1_to_RB.h"
#include "../automoves/RP2_to_RB.h"
#include "../automoves/RP3_to_RB.h"
#include "../automoves/BP1_to_BB.h"
#include "../automoves/BP2_to_BB.h"
#include "../automoves/BP3_to_BB.h"

AutonomousGearGroup::AutonomousGearGroup(PegLocation loc, bool GotoBoiler) {
	// TODO Auto-generated constructor stub
//	AddSequential(new ElevatorInitialize());

	switch (loc) {
	case kCenterPegRed:
		AddSequential(new frc::PrintCommand("Center Peg\n"));
		AddSequential(
				new AutonomousBlendedMove(&AutoMove_RS2_to_RP2_L,
						&AutoMove_RS2_to_RP2_R, t_auto_end_RS2_to_RP2,
						&VisionProcessing::e_Gear_x));
		break;
	case kLeftPegRed:
		AddSequential(new frc::PrintCommand("Left Peg\n"));
		AddSequential(
				new AutonomousBlendedMove(&AutoMove_RS1_to_RP1_L,
						&AutoMove_RS1_to_RP1_R, t_auto_end_RS1_to_RP1,
						&VisionProcessing::e_Gear_x));
		break;
	case kRightPegRed:
		AddSequential(new frc::PrintCommand("Right Peg\n"));
		AddSequential(
						new AutonomousBlendedMove(&AutoMove_RS3_to_RP3_L,
								&AutoMove_RS3_to_RP3_R, t_auto_end_RS3_to_RP3,
						&VisionProcessing::e_Gear_x));
		break;
	case kCenterPegBlue:
		AddSequential(
				new AutonomousBlendedMove(&AutoMove_RS2_to_RP2_L,
						&AutoMove_RS2_to_RP2_R, t_auto_end_RS2_to_RP2,
						&VisionProcessing::e_Gear_x));
		break;
	case kLeftPegBlue:
		AddSequential(
						new AutonomousBlendedMove(&AutoMove_RS3_to_RP3_L,
								&AutoMove_RS3_to_RP3_R, t_auto_end_RS3_to_RP3,
						&VisionProcessing::e_Gear_x));
		break;
	case kRightPegBlue:
		AddSequential(
						new AutonomousBlendedMove(&AutoMove_RS1_to_RP1_L,
								&AutoMove_RS1_to_RP1_R, t_auto_end_RS1_to_RP1,
						&VisionProcessing::e_Gear_x));
		break;
	default:
		break;
	}

	AddSequential(new BackDoorOpen());
	AddSequential(new frc::WaitCommand(.3));

	if (GotoBoiler) {
		switch (loc) {
		case kCenterPegRed:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RP2_to_RB_L,
							&AutoMove_RP2_to_RB_R));
			break;
		case kLeftPegRed:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RP1_to_RB_L,
							&AutoMove_RP1_to_RB_R));
			break;
		case kRightPegRed:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RP3_to_RB_L,
							&AutoMove_RP3_to_RB_R));
			break;
		case kCenterPegBlue:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_BP2_to_BB_L,
							&AutoMove_BP2_to_BB_R));
			break;
		case kRightPegBlue:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_BP1_to_BB_L,
							&AutoMove_RP1_to_RB_R));
			break;
		case kLeftPegBlue:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RP3_to_RB_L,
							&AutoMove_RP3_to_RB_R));
			break;
		default:
			break;
		}
		AddSequential(new AutonomousLowBoiler());
	}
	else {
		AddSequential(new AutonomousMotionProfile(&MoveOffPeg));
	}

	AddSequential(new BackDoorClose());
}
