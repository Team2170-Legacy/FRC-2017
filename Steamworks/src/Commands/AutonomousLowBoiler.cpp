#include "AutonomousLowBoiler.h"
#include "ElevatorPosition.h"
#include "IntakeReverse.h"
#include "IntakeOff.h"

AutonomousLowBoiler::AutonomousLowBoiler() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

	// Dump balls into low boiler
	double ElevatorPos = Preferences::GetInstance()->GetDouble(
			"ElevatorLowBoiler", 1000.0);

	AddSequential(new ElevatorPosition(ElevatorPos));
	AddSequential(new IntakeReverse());
	AddSequential(new frc::WaitCommand(2.0));
	AddSequential(new IntakeOff());
}
