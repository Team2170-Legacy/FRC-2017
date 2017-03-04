/*
 * VisionProcessing.h
 *
 *  Created on: Mar 1, 2017
 *      Author: nollchr
 */

#ifndef SRC_VISION_VISIONPROCESSING_H_
#define SRC_VISION_VISIONPROCESSING_H_
#include "WPILib.h"
#include "GearTwoNEW.h"
#include "BBoilerPipeline.h"

#include "../ProfileData.h"

#include "BS1_to_BP1.h"
#include "BS2_to_BP2.h"
#include "BS3_to_BP3.h"
#include "RS1_to_RP1.h"
#include "RS2_to_RP2.h"
#include "RS3_to_RP3.h"

class VisionProcessing {
private:
	static void VisionThreadBBoiler();

public:
	VisionProcessing();
	static void VisionThread();
	virtual ~VisionProcessing();

	//cs::CvSink GearCameraSink;

	// MK 2/4 8:47pm static grip::GearTargetPipeline GearPipeline;

	// MK 2/4/8:26pm
	grip::GearTwoNEW GearPipeline;
	grip::BBoilerPipeline BBoilerPipeline;
	static int Gear_x;			// Global Gear Target x-location (in 320x240 image coordinates)
	static int e_Gear_x;		// Global variable for error in Gear_x location

	static int BBoiler_x; 		// Global Blue Boiler x-location (in 320x240 image coordinates)
	static int e_BBoiler_x;	// Global variable for error in Gear_x location

};

#endif /* SRC_VISION_VISIONPROCESSING_H_ */
