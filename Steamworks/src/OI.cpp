// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousBlendedMove.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/AutonomousMotionProfile.h"
#include "Commands/AutonomousTestGroup.h"
#include "Commands/AutonomousVelocityProfile.h"
#include "Commands/BackDoorClose.h"
#include "Commands/BackDoorOpen.h"
#include "Commands/BackDoorToggle.h"
#include "Commands/ClimberUp.h"
#include "Commands/DriveTrainToggleDirection.h"
#include "Commands/DumperHighLoadWhileHeld.h"
#include "Commands/DumperOff.h"
#include "Commands/DumperOn.h"
#include "Commands/DumperOnWhileHeld.h"
#include "Commands/DumperToggle.h"
#include "Commands/ElevatorHome.h"
#include "Commands/ElevatorInitialize.h"
#include "Commands/ElevatorOffHome.h"
#include "Commands/ElevatorPosition.h"
#include "Commands/ElevatorTeleop.h"
#include "Commands/IntakeOff.h"
#include "Commands/IntakeOn.h"
#include "Commands/IntakeToggle.h"
#include "Commands/TankDriveTeleop.h"
#include "Commands/TeleopDrive.h"
#include "Commands/ZeroElevatorEncoder.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    supportJoystick.reset(new Joystick(1));
    
    supportJoystickButtonY.reset(new JoystickButton(supportJoystick.get(), 4));
    supportJoystickButtonY->WhileHeld(new ClimberUp());
    supportJoystickButtonX.reset(new JoystickButton(supportJoystick.get(), 3));
    supportJoystickButtonX->WhenPressed(new IntakeToggle());
    supportJoystickButtonB.reset(new JoystickButton(supportJoystick.get(), 2));
    supportJoystickButtonB->WhileHeld(new DumperHighLoadWhileHeld());
    supportJoystickButtonA.reset(new JoystickButton(supportJoystick.get(), 1));
    supportJoystickButtonA->WhileHeld(new DumperOnWhileHeld());
    driverJoystick.reset(new Joystick(0));
    
    driverLeftStickClick.reset(new JoystickButton(driverJoystick.get(), 9));
    driverLeftStickClick->WhenPressed(new DriveTrainToggleDirection());
    dirverJoystickButtonY.reset(new JoystickButton(driverJoystick.get(), 4));
    dirverJoystickButtonY->WhileHeld(new ClimberUp());
    driverJoystickButtonX.reset(new JoystickButton(driverJoystick.get(), 3));
    driverJoystickButtonX->WhenPressed(new BackDoorToggle());
    driverJoystickButtonB.reset(new JoystickButton(driverJoystick.get(), 2));
    driverJoystickButtonB->WhenPressed(new DumperToggle());
    driverJoystickButtonA.reset(new JoystickButton(driverJoystick.get(), 1));
    driverJoystickButtonA->WhenPressed(new IntakeToggle());

    // SmartDashboard Buttons
    SmartDashboard::PutData("Dumper High Load While Held", new DumperHighLoadWhileHeld());
    SmartDashboard::PutData("Elevator Initialize", new ElevatorInitialize());
    SmartDashboard::PutData("Autonomous Test Group", new AutonomousTestGroup());
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getDriverJoystick() {
   return driverJoystick;
}

std::shared_ptr<Joystick> OI::getSupportJoystick() {
   return supportJoystick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
