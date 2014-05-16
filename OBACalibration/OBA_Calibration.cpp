#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Calibration.h"

OBA_Calibration::OBA_Calibration() {
}

	
	static bool isCalibrating;


void CALIB::startCalibration() {
	if (validateCalibrationRequest()) {
		// do calibration
		// // check for file existence
		// // // if exist, load
		// // // else create

		// // read file
		// // // format ok?
		// // // load
		// // // set state

		//  during calib

		// start pulse
		// end pulse
		// validate error range
		// save to file
		// if fail to save, revert to default
		// set internal var: calibvalue & iscalibrating=0

	}

}

void CALIB::stopCalibration() {

}

bool CALIB::validateCalibrationRequest() {
	// check for iscruising


	return true;

}