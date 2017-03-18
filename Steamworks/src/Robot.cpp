// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "Vision/VisionProcessing.h"
#include "Robot.h"
#include "WPiLib.h"
#include <vector>
#include <unistd.h>
#include <chrono>
#include "Commands/AutonomousCommand.h"
#include "Commands/AutonomousTestGroup.h"
#include "Commands/AutonomousInitGroup.h"
#include "Commands/AutonomousBlendedMove.h"
#include "Commands/AutonomousMotionProfile.h"
#include "Commands/ElevatorInitialize.h"
#include "ProfileData.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Payload> Robot::payload;
std::shared_ptr<Dumper> Robot::dumper;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

int Gear_x;			// Global Gear Target x-location (in 320x240 image coordinates)
int e_Gear_x;		// Global variable for error in Gear_x location

int BBoiler_x; 		// Global Blue Boiler x-location (in 320x240 image coordinates)
int e_BBoiler_x;	// Global variable for error in Gear_x location

void Robot::RobotInit() {
	RobotMap::init();

	mVisionEnabled =
			Preferences::GetInstance()->GetBoolean("VisionEnabled", false);

	std::thread visionThread(VisionProcessing::VisionThread);
	visionThread.detach();

//	std::thread visionThreadBBoiler(VisionThreadBBoiler);
//	visionThreadBBoiler.detach();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveTrain.reset(new DriveTrain());
    payload.reset(new Payload());
    dumper.reset(new Dumper());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand.reset(new AutonomousTestGroup());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	//Adds a sendable chooser
	chooser.AddObject("Autonomous", new (AutonomousCommand));
	chooser.AddObject("Auto Testing - Don't choose in match!!", new (AutonomousTestGroup));
	chooser.AddObject("Do Nothing", new (ElevatorInitialize));
	chooser.AddObject("MoveToBaseline",
			new AutonomousInitGroup(&AutonomousMoveToBaseline));
	chooser.AddObject("MoveToGearPeg",
			new AutonomousInitGroup(&AutonomousMoveToGearPeg));
	chooser.AddDefault("RS1 to RP1",
			new AutonomousBlendedMove(&AutoMove_RS1_to_RP1_L, &AutoMove_RS1_to_RP1_R, t_auto_end_RS1_to_RP1, &e_Gear_x));
	SmartDashboard::PutData("Autonomous Modes", &chooser);
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	payload->SetIntakeSpeed(Payload::IntakeSpeed::kIntakeStop);
	dumper->DumperSetSpeed(Dumper::DumperSpeed::kDumperOff);
	SmartDashboard::PutBoolean("Dumper Running", dumper->IsDumperMoving());
	SmartDashboard::PutBoolean("DoorOpen", payload->IsDoorOpen());
	SmartDashboard::PutBoolean("Intake Running", payload->IsIntakeRunning());
}

void Robot::DisabledPeriodic() {
	UpdateSmartDash();
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand.release();
	autonomousCommand.reset((Command *)chooser.GetSelected());

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {

	std::cout << "Gear x-Location = " << VisionProcessing::Gear_x << std::endl;
	std::cout << "Gear x-Location Error = " << VisionProcessing::e_Gear_x << std::endl;

//	std::chrono::high_resolution_clock::time_point<std::chrono::system_clock> now;
//	now = std::chrono::system_clock::now();
	std::cout << "Time: " << GetFPGATime() << std::endl;

	SmartDashboard::PutNumber("Error for Gear_x: ", VisionProcessing::e_Gear_x);

	UpdateSmartDash();
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

void Robot::UpdateSmartDash() {
	SmartDashboard::PutBoolean("Intake Running", payload->IsIntakeRunning());
	SmartDashboard::PutBoolean("Dumper Running", dumper->IsDumperMoving());
	SmartDashboard::PutBoolean("DoorOpen", payload->IsDoorOpen());
	SmartDashboard::PutBoolean("Drive Reverse", driveTrain->isReverseDrive());
	SmartDashboard::PutNumber("Elevator Position", payload->GetElevatorPosition());
	SmartDashboard::PutBoolean("Gyro Active", driveTrain->isDriveStraight());
}
