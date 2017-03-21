// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<Joystick> rightDriverJoystick;
	std::shared_ptr<Joystick> supportJoystick;
	std::shared_ptr<JoystickButton> supportJoystickLeftBumper;
	std::shared_ptr<JoystickButton> supportJoystickRightBumper;
	std::shared_ptr<JoystickButton> supportJoystickButtonY;
	std::shared_ptr<JoystickButton> supportJoystickButtonX;
	std::shared_ptr<JoystickButton> supportJoystickButtonB;
	std::shared_ptr<JoystickButton> supportJoystickButtonA;
	std::shared_ptr<Joystick> leftDriverJoystick;
	std::shared_ptr<JoystickButton> leftDriverTrigger;
	std::shared_ptr<JoystickButton> leftDriverButtonLeft;
	std::shared_ptr<JoystickButton> dirverJoystickButtonY;
	std::shared_ptr<JoystickButton> driverJoystickButtonX;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<Joystick> getLeftDriverJoystick();
	std::shared_ptr<Joystick> getSupportJoystick();
	std::shared_ptr<Joystick> getRightDriverJoystick();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
