// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "CANTalon.h"

#include "DriveTrain.h"
#include "../Commands/TeleopDrive.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveTrain::DriveTrain() :
		Subsystem("DriveTrain"), kCountsPerRev(
				Preferences::GetInstance()->GetInt("WheelCountPerRev", 360)), kDefaultVoltageRamp(
				Preferences::GetInstance()->GetDouble("VoltageRamp", 27.0)), kYawGain(
				Preferences::GetInstance()->GetDouble("GyroYawGain", -0.10)), kLeftSensorDirection(
				Preferences::GetInstance()->GetBoolean("LeftSensorDir", true)), kRightSensorDirection(
				Preferences::GetInstance()->GetBoolean("RightSensorDir", true)), kDriveVelocityMode(
				Preferences::GetInstance()->GetBoolean("DriveVelocityMode",
						false)), kDriveMaxVelocity(
				Preferences::GetInstance()->GetDouble("DriveMaxVelocity",
						500.0)), kThrottleBreak(
				Preferences::GetInstance()->GetDouble("ThrottleBreak", 0.5)), kStickBreak(
				Preferences::GetInstance()->GetDouble("StickBreak", 0.75)), InchesPerRotation(
				Preferences::GetInstance()->GetDouble("WheelDiameter",
						4.0) * M_PI) {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	cANTalonLeft = RobotMap::driveTrainCANTalonLeft;
	cANTalonRight = RobotMap::driveTrainCANTalonRight;
	robotDrive = RobotMap::driveTrainRobotDrive;
	cANTalonSlaveLeft = RobotMap::driveTrainCANTalonSlaveLeft;
	cANTalonSlaveRight = RobotMap::driveTrainCANTalonSlaveRight;

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
//    gyro = RobotMap::driveTrainAHRS;
	prefs = Preferences::GetInstance();
	LeftLog.reset(
			new CANTalonLogger(cANTalonLeft,
					"/home/lvuser/LeftDrivetrain.csv"));
	RightLog.reset(
			new CANTalonLogger(cANTalonRight,
					"/home/lvuser/RightDrivetrain.csv"));
	InitTalons();

}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

	SetDefaultCommand(new TeleopDrive());

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::ArcadeDriveWithJoysticks(double moveVal, double rotateVal) {
	robotDrive->ArcadeDrive(moveVal, rotateVal, true);
}

void DriveTrain::ResetChassisYaw() {
//	if (gyro->IsConnected()) {
//		gyro->Reset();
//	}
}

double DriveTrain::ReadChassisYaw() {
	double result = 0.0;
//	result = gyro->GetAngle();

	return result;
}

void DriveTrain::DriveStraight(bool Backwards) {
	if (Backwards) {
		DriveStraight(-mAutoVelocity);
	} else {
		DriveStraight(mAutoVelocity);
	}
}

void DriveTrain::DriveStraight(double magnitude) {

	double ChassisAngle = ReadChassisYaw();

	if (mReverseDrive) {
		magnitude = -magnitude;
	}
	if (magnitude > 0.0) {
		robotDrive->Drive(magnitude, kYawGain * ChassisAngle);
	} else {
		robotDrive->Drive(magnitude, -kYawGain * ChassisAngle);
	}
}

void DriveTrain::StopMotors(void) {

	robotDrive->StopMotor();

}

void DriveTrain::SetVoltagePercentMode() {
	cANTalonLeft->SetTalonControlMode(
			CANTalon::TalonControlMode::kThrottleMode);
	cANTalonRight->SetTalonControlMode(
			CANTalon::TalonControlMode::kThrottleMode);
	SetRampRate(kDefaultVoltageRamp);
	cANTalonLeft->Set(0.0);
	cANTalonRight->Set(0.0);
	LeftLog->EndSession();
	RightLog->EndSession();
}

void DriveTrain::TankDriveWithTriggers(double Left, double Right,
		double Trigger) {
	double newLeft = 0.0;
	double newRight = 0.0;
	double ProcessedLeft = Left;
	double ProcessedRight = Right;
	double fExponent = 1.0;

	ProcessedLeft = DEADBAND(AxisPower(ProcessedLeft, fExponent), 0.07);

	ProcessedRight = DEADBAND(AxisPower(ProcessedRight, fExponent), 0.07);

	ProcessedLeft = MapStick(ProcessedLeft);
	ProcessedRight = MapStick(ProcessedRight);

	newLeft = fmax(fmin(ProcessedLeft + (Trigger * .8), 1.0), -1.0);
	newRight = fmax(fmin(ProcessedRight + (Trigger * .8), 1.0), -1.0);

	// Select velocity mode or throttle mode
	if (kDriveVelocityMode) {
		SetChassisMode(CANTalon::TalonControlMode::kSpeedMode);
	} else {
		SetChassisMode(CANTalon::TalonControlMode::kThrottleMode);
	}

	// Determine if we are using gyro corrected straight movement
	if ((ProcessedLeft == 0.0) && (ProcessedRight == 0.0)) {
		if (DEADBAND(Trigger, 0.10) == 0.0) {
			ResetChassisYaw();
			bDriveStraight = true;
		}
	} else {
		bDriveStraight = false;
	}

	if (bDriveStraight) {
		if (kDriveVelocityMode) {
			Trigger *= kDriveMaxVelocity;
			printf("Speed: %f    Error:  %d\n", Trigger,
					cANTalonLeft->GetClosedLoopError());
		}
		DriveStraight(Trigger * 0.8f);
	} else {
		if (kDriveVelocityMode) {
			newLeft *= kDriveMaxVelocity;
			newRight *= kDriveMaxVelocity;
			printf("Speed: %f    Error:  %d\n", newLeft,
					cANTalonLeft->GetClosedLoopError());
		}
		if (!mReverseDrive) {
			robotDrive->TankDrive(newLeft, newRight, false);
		} else {
			robotDrive->TankDrive(-newRight, -newLeft, false);
		}
	}
	cANTalonSlaveRight->Set(2);
	cANTalonSlaveLeft->Set(1);
}

double DriveTrain::AxisPower(double axis, double exponent) {
	double retVal = 0.0;

	retVal = pow(fabs(axis), exponent);
	retVal = (axis < 0.0) ? -1.0 * retVal : retVal;

	return retVal;
}

void DriveTrain::SetClosedLoopMode() {
	cANTalonLeft->SetTalonControlMode(
			CANTalon::TalonControlMode::kPositionMode);
	cANTalonRight->SetTalonControlMode(
			CANTalon::TalonControlMode::kPositionMode);

	SetRampRate(0.0);

	cANTalonLeft->SetPosition(0.0);
	cANTalonLeft->Set(0.0);

	cANTalonRight->SetPosition(0.0);
	cANTalonRight->Set(0.0);
}

void DriveTrain::SetMotionProfileMode() {
	SetMotorGains(0);
	cANTalonLeft->SetTalonControlMode(
			CANTalon::TalonControlMode::kMotionProfileMode);
	cANTalonLeft->SetPosition(0.0);
	cANTalonLeft->Set(
			CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);

	cANTalonRight->SetTalonControlMode(
			CANTalon::TalonControlMode::kMotionProfileMode);
	cANTalonRight->SetPosition(0.0);
	cANTalonRight->Set(
			CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);

	LeftLog->StartSession();
	RightLog->StartSession();
	SetRampRate(0.0);
}

double DriveTrain::ReadChassisDistance() {
	return (FrontSonar->GetRangeInches());
}

void DriveTrain::Rotate(float velocity) {
	if ((cANTalonLeft->GetTalonControlMode()
			== CANTalon::TalonControlMode::kSpeedMode)
			&& (cANTalonRight->GetTalonControlMode()
					== CANTalon::TalonControlMode::kSpeedMode)) {
		cANTalonLeft->Set(velocity);
		cANTalonRight->Set(velocity);
	}
}

double DriveTrain::ReadPositionError() {
	return (cANTalonLeft->GetClosedLoopError() / kCountsPerRev);
}

void DriveTrain::SetVelocityMode() {
	SetMotorGains(1);
	cANTalonLeft->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
	cANTalonLeft->Set(0.0);
	cANTalonRight->SetTalonControlMode(CANTalon::TalonControlMode::kSpeedMode);
	cANTalonRight->Set(0.0);
	LeftLog->StartSession();
	RightLog->StartSession();
}

void DriveTrain::SetChassisVelocity(double vIPS) {
	if ((cANTalonLeft->GetTalonControlMode()
			== CANTalon::TalonControlMode::kSpeedMode)
			&& (cANTalonRight->GetTalonControlMode()
					== CANTalon::TalonControlMode::kSpeedMode)) {
		cANTalonLeft->Set(vIPS * 60.0 / InchesPerRotation);
		cANTalonRight->Set(-vIPS * 60.0 / InchesPerRotation);
	}
}

void DriveTrain::SetChassisVelocity(double vIPS, double error) {
	if ((cANTalonLeft->GetTalonControlMode()
			== CANTalon::TalonControlMode::kSpeedMode)
			&& (cANTalonRight->GetTalonControlMode()
					== CANTalon::TalonControlMode::kSpeedMode)) {
		cANTalonLeft->Set(vIPS * InchesPerRotation + error);
		cANTalonRight->Set(-vIPS * InchesPerRotation - error);
	}
}

void DriveTrain::SetChassisPosition(double positionInches) {
	if ((cANTalonLeft->GetControlMode() == CANTalon::ControlMode::kPosition)
			&& (cANTalonRight->GetTalonControlMode()
					== CANTalon::TalonControlMode::kPositionMode)) {
		cANTalonLeft->Set(positionInches / InchesPerRotation);
		cANTalonRight->Set(-positionInches / InchesPerRotation);
	}
}

void DriveTrain::FillProfileBuffer(
		std::shared_ptr<const ProfileData> LeftWheel) {
	size_t i;
	CANTalon::TrajectoryPoint pt;

	pt.zeroPos = true;
	pt.isLastPoint = false;
	pt.profileSlotSelect = 0;
	pt.velocityOnly = false;

	cANTalonLeft->Set(
			CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonRight->Set(
			CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonLeft->ClearMotionProfileTrajectories();
	cANTalonLeft->ClearMotionProfileHasUnderrun();
	cANTalonRight->ClearMotionProfileTrajectories();
	cANTalonRight->ClearMotionProfileHasUnderrun();

	for (i = 0; i < LeftWheel->size(); i++) {
		// check if this is the last point
		if ((i + 1) == LeftWheel->size()) {
			pt.isLastPoint = true;
		}

		pt.position = LeftWheel->at(i).at(0);
		pt.velocity = LeftWheel->at(i).at(1);
		pt.timeDurMs = LeftWheel->at(i).at(2);
		if (!cANTalonLeft->PushMotionProfileTrajectory(pt)) {
			printf("left can push failed\n");
		}

		// Negative position and velocity for right side
		pt.position = -pt.position;
		pt.velocity = -pt.velocity;
		if (!cANTalonRight->PushMotionProfileTrajectory(pt)) {
			printf("right can push failed\n");
		}
		pt.zeroPos = false;
	}

}

void DriveTrain::FillProfileBuffer(std::shared_ptr<const ProfileData> LeftWheel,
		std::shared_ptr<const ProfileData> RightWheel) {
	size_t i;
	CANTalon::TrajectoryPoint pt;

	pt.zeroPos = true;
	pt.isLastPoint = false;
	pt.profileSlotSelect = 0;
	pt.velocityOnly = false;

	cANTalonLeft->Set(
			CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonRight->Set(
			CANTalon::SetValueMotionProfile::SetValueMotionProfileDisable);
	cANTalonLeft->ClearMotionProfileTrajectories();
	cANTalonLeft->ClearMotionProfileHasUnderrun();
	cANTalonRight->ClearMotionProfileTrajectories();
	cANTalonRight->ClearMotionProfileHasUnderrun();

	for (i = 0; i < LeftWheel->size(); i++) {
		// check if this is the last point
		if ((i + 1) == LeftWheel->size()) {
			pt.isLastPoint = true;
		}

		pt.position = LeftWheel->at(i).at(0);
		pt.velocity = LeftWheel->at(i).at(1);
		pt.timeDurMs = LeftWheel->at(i).at(2);
		cANTalonLeft->PushMotionProfileTrajectory(pt);

		// Use right wheel profile for right side
		pt.position = -RightWheel->at(i).at(0);
		pt.velocity = -RightWheel->at(i).at(1);
		pt.timeDurMs = RightWheel->at(i).at(2);
		cANTalonRight->PushMotionProfileTrajectory(pt);
		pt.zeroPos = false;
	}
}

void DriveTrain::ServiceMotionProfile() {
	cANTalonLeft->ProcessMotionProfileBuffer();
	cANTalonRight->ProcessMotionProfileBuffer();
}

void DriveTrain::SetBrakeMode(CANTalon::NeutralMode Mode) {
	cANTalonLeft->ConfigNeutralMode(Mode);
	cANTalonSlaveLeft->ConfigNeutralMode(Mode);
	cANTalonRight->ConfigNeutralMode(Mode);
	cANTalonSlaveRight->ConfigNeutralMode(Mode);
}

void DriveTrain::SetMotionProfileState(CANTalon::SetValueMotionProfile mode) {
	if (cANTalonLeft->GetControlMode()
			== CANSpeedController::ControlMode::kMotionProfile) {
		cANTalonLeft->Set(mode);
	}
	if (cANTalonLeft->GetControlMode()
			== CANSpeedController::ControlMode::kMotionProfile) {
		cANTalonRight->Set(mode);
	}
}

void DriveTrain::SetMotorGains(int idx) {
	cANTalonLeft->SelectProfileSlot(idx);
	cANTalonRight->SelectProfileSlot(idx);
}

bool DriveTrain::MotionProfileComplete() {
	bool Complete = false;

	cANTalonLeft->GetMotionProfileStatus(LeftStatus);
	cANTalonRight->GetMotionProfileStatus(RightStatus);

#ifdef DEBUG_TALON
	printf("Remaining top buffer points:  %d\n", LeftStatus.topBufferRem);
	printf("Bottom buffer count:  %d\n", LeftStatus.btmBufferCnt);
	printf("IsUnderrun status:  %d\n", LeftStatus.isUnderrun);
#endif

	// Start motion profile processing after 5 points are in talon buffer
	if ((!mMotionProcessingActive) && (LeftStatus.btmBufferCnt > 5)) {
		SetMotionProfileState(
				CANTalon::SetValueMotionProfile::SetValueMotionProfileEnable);
		mMotionProcessingActive = true;
	}

	if ((LeftStatus.activePointValid && LeftStatus.activePoint.isLastPoint)
			&& (RightStatus.activePointValid
					&& RightStatus.activePoint.isLastPoint)) {
		Complete = true;
		mMotionProcessingActive = false;
	}

	return Complete;
}

CANTalon::TalonControlMode DriveTrain::GetChassisMode() {
	return cANTalonLeft->GetTalonControlMode();
}

void DriveTrain::SetChassisMode(CANTalon::TalonControlMode mode) {
	switch (mode) {
	case CANTalon::TalonControlMode::kMotionProfileMode:
		SetMotionProfileMode();
		break;
	case CANTalon::TalonControlMode::kPositionMode:
		SetClosedLoopMode();
		break;
	case CANTalon::TalonControlMode::kSpeedMode:
		SetVelocityMode();
		break;
	case CANTalon::TalonControlMode::kMotionMagicMode:
		break;
	case CANTalon::TalonControlMode::kThrottleMode:
	default:
		SetVoltagePercentMode();
		break;
	}
}

void DriveTrain::InitTalons(void) {
	cANTalonSlaveLeft->SetTalonControlMode(
			CANTalon::TalonControlMode::kFollowerMode);
	cANTalonSlaveLeft->SetSafetyEnabled(false);
	cANTalonSlaveLeft->Set(1);
	cANTalonSlaveRight->SetTalonControlMode(
			CANTalon::TalonControlMode::kFollowerMode);
	cANTalonSlaveRight->SetSafetyEnabled(false);
	cANTalonSlaveRight->Set(2);

	cANTalonLeft->ChangeMotionControlFramePeriod(5);
	cANTalonSlaveLeft->ChangeMotionControlFramePeriod(5);
	cANTalonRight->ChangeMotionControlFramePeriod(5);
	cANTalonSlaveRight->ChangeMotionControlFramePeriod(5);

	cANTalonLeft->SetFeedbackDevice(CANTalon::QuadEncoder);
	cANTalonLeft->ConfigEncoderCodesPerRev(kCountsPerRev);

	cANTalonRight->SetFeedbackDevice(CANTalon::QuadEncoder);
	cANTalonRight->ConfigEncoderCodesPerRev(kCountsPerRev);

	cANTalonLeft->SetSensorDirection(
			prefs->GetBoolean("SensorDirection", kLeftSensorDirection)); //changed this
	cANTalonRight->SetSensorDirection(
			prefs->GetBoolean("SensorDirection", kRightSensorDirection));

	cANTalonLeft->SetStatusFrameRateMs(
			CANTalon::StatusFrameRate::StatusFrameRateFeedback, 20);
	cANTalonRight->SetStatusFrameRateMs(
			CANTalon::StatusFrameRate::StatusFrameRateFeedback, 20);

	if (prefs->GetBoolean("LeftReverse", false)) {
		cANTalonLeft->SetInverted(true);
		cANTalonLeft->SetClosedLoopOutputDirection(true);
	}
	if (prefs->GetBoolean("RightReverse", false)) {
		cANTalonRight->SetInverted(true);
		cANTalonRight->SetClosedLoopOutputDirection(true);
	}

	SetMotorGains();
	SetBrakeMode(CANTalon::NeutralMode::kNeutralMode_Coast);

	cANTalonLeft->EnableControl();
	cANTalonSlaveLeft->EnableControl();
	cANTalonRight->EnableControl();
	cANTalonSlaveRight->EnableControl();
}

void DriveTrain::SetRampRate(double ramp) {
	cANTalonLeft->SetVoltageRampRate(ramp);
	cANTalonSlaveLeft->SetVoltageRampRate(ramp);
	cANTalonRight->SetVoltageRampRate(ramp);
	cANTalonSlaveRight->SetVoltageRampRate(ramp);
}

double DriveTrain::GetChassisPosition() {
	return (cANTalonLeft->GetPosition() * InchesPerRotation);
}

void DriveTrain::TankDrive(float Left, float Right) {

	// Select velocity mode or throttle mode
	if (kDriveVelocityMode) {
		SetChassisMode(CANTalon::TalonControlMode::kSpeedMode);
	} else {
		SetChassisMode(CANTalon::TalonControlMode::kThrottleMode);
	}

	Left = DEADBAND(Left, 0.07);
	Right = DEADBAND(Right, 0.07);

	if (kDriveVelocityMode) {
		Left *= kDriveMaxVelocity;
		Right *= kDriveMaxVelocity;
		printf("Speed: %f    Error:  %d\n", Left,
				cANTalonLeft->GetClosedLoopError());
		if (!mReverseDrive) {
			cANTalonLeft->Set(Left);
			cANTalonRight->Set(-Right);
		} else {
			cANTalonLeft->Set(-Right);
			cANTalonRight->Set(Left);
		}
	} else {
		if (!mReverseDrive) {
			robotDrive->TankDrive(Left, Right, false);
		} else {
			robotDrive->TankDrive(-Right, -Left, false);
		}
	}
	cANTalonSlaveRight->Set(2);
	cANTalonSlaveLeft->Set(1);
}

void DriveTrain::TelemetryFlush() {
	LeftLog->Flush();
	RightLog->Flush();
}

void DriveTrain::TelemetryUpdate() {
	RightLog->Update();
	LeftLog->Update();
}

double DriveTrain::MapStick(double stick) {
	double NewStick = fabs(stick);

	if (NewStick < kStickBreak) {
		NewStick = (NewStick / kStickBreak) * kThrottleBreak;
	} else {
		NewStick = kThrottleBreak
				+ ((1 - NewStick) / (1 - kStickBreak)) * (1 - kThrottleBreak);
	}

	if (stick < 0.0) {
		NewStick = -NewStick;
	}

	return NewStick;
}

void DriveTrain::SetChassisWheelVelocity(double left, double right) {
	if ((cANTalonLeft->GetTalonControlMode()
			== CANTalon::TalonControlMode::kSpeedMode)
			&& (cANTalonRight->GetTalonControlMode()
					== CANTalon::TalonControlMode::kSpeedMode)) {
		cANTalonLeft->Set(left);
		cANTalonRight->Set(-right);
		TelemetryUpdate();
	}
}
