#ifndef AutonomousStop_H
#define AutonomousStop_H

#include "../Robot.h"
#include "Commands/InstantCommand.h"

class AutonomousStop : public InstantCommand {
public:
	AutonomousStop();
	void Initialize();
};

#endif  // AutonomousStop_H
