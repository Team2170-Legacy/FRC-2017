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
#include "AutonomousStop.h"
#include "../Vision/VisionProcessing.h"
#include "../automoves/RP1_to_RB.h"
#include "../automoves/RP2_to_RB.h"
#include "../automoves/RP3_to_RB.h"
#include "../automoves/BP1_to_BB.h"
#include "../automoves/BP2_to_BB.h"
#include "../automoves/BP3_to_BB.h"
#include "../automoves/BB_to_F.h"
#include "../automoves/RB_to_F.h"

AutonomousGearGroup::AutonomousGearGroup(PegLocation loc, bool GotoBoiler) {
	// TODO Auto-generated constructor stub
	AddParallel(new ElevatorInitialize());

	switch (loc) {
	case kCenterPegRed:
		AddSequential(
				new AutonomousBlendedMove(&AutoMove_RS2_to_RP2_L,
						&AutoMove_RS2_to_RP2_R, t_auto_end_RS2_to_RP2,
						&VisionProcessing::e_Gear_x));
		break;
	case kLeftPegRed:
		AddSequential(
				new AutonomousBlendedMove(&AutoMove_RS1_to_RP1_L,
						&AutoMove_RS1_to_RP1_R, t_auto_end_RS1_to_RP1,
						&VisionProcessing::e_Gear_x));
		break;
	case kRightPegRed:
		AddSequential(
						new AutonomousBlendedMove(&AutoMove_RS3_to_RP3_L,
								&AutoMove_RS3_to_RP3_R, t_auto_end_RS3_to_RP3,
						&VisionProcessing::e_Gear_x));
		break;
	case kCenterPegBlue:
		AddSequential(
				new AutonomousBlendedMove(&AutoMove_BS2_to_BP2_L,
						&AutoMove_BS2_to_BP2_R, t_auto_end_BS2_to_BP2,
						&VisionProcessing::e_Gear_x));
		break;
	case kRightPegBlue:
		AddSequential(
				new AutonomousBlendedMove(&AutoMove_BS3_to_BP3_L,
						&AutoMove_BS3_to_BP3_R, t_auto_end_BS3_to_BP3,
						&VisionProcessing::e_Gear_x));
		break;
	case kLeftPegBlue:
		AddSequential(
				new AutonomousBlendedMove(&AutoMove_BS1_to_BP1_L,
						&AutoMove_BS1_to_BP1_R, t_auto_end_BS1_to_BP1,
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
			AddSequential(new BackDoorClose());
			AddSequential(new AutonomousLowBoiler());
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RB_to_F_L,
							&AutoMove_RB_to_F_R));
			break;
		case kLeftPegRed:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RP1_to_RB_L,
							&AutoMove_RP1_to_RB_R));
			AddSequential(new BackDoorClose());
			AddSequential(new AutonomousLowBoiler());
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RB_to_F_L,
							&AutoMove_RB_to_F_R));
			break;
		case kRightPegRed:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RP3_to_RB_L,
							&AutoMove_RP3_to_RB_R));
			AddSequential(new BackDoorClose());
			AddSequential(new AutonomousLowBoiler());
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_RB_to_F_L,
							&AutoMove_RB_to_F_R));
			break;
		case kCenterPegBlue:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_BP2_to_BB_L,
							&AutoMove_BP2_to_BB_R));
			AddSequential(new BackDoorClose());
			AddSequential(new AutonomousLowBoiler());
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_BB_to_F_L,
							&AutoMove_BB_to_F_R));
			break;
		case kLeftPegBlue:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_BP1_to_BB_L,
							&AutoMove_BP1_to_BB_R));
			AddSequential(new BackDoorClose());
			AddSequential(new AutonomousLowBoiler());
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_BB_to_F_L,
							&AutoMove_BB_to_F_R));
			break;
		case kRightPegBlue:
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_BP3_to_BB_L,
							&AutoMove_BP3_to_BB_R));
			AddSequential(new BackDoorClose());
			AddSequential(new AutonomousLowBoiler());
			AddSequential(
					new AutonomousMotionProfile(&AutoMove_BB_to_F_L,
							&AutoMove_BB_to_F_R));
			break;
		default:
			break;
		}
	}
	else {
		AddSequential(new AutonomousMotionProfile(&MoveOffPeg));
		AddSequential(new AutonomousStop);
	}
	AddSequential(new BackDoorClose());
	AddSequential(new AutonomousStop);
}
