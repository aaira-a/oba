#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Calibration.h"
#include "../OBACruise/OBA_Cruising.h"
#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include <iostream>

using namespace std; 

OBA_Calibration::OBA_Calibration() {
}

	static const double calibrationDefault = 5291.0053; 
	static double calibrationValue = 0;
	static bool isCalibrating = 0;
	static unsigned int initialPulse = 0;
	static unsigned int endPulse = 0;
	static double tempCalibrationValue = 0;


void CALIB::startCalibration() {
	if (validateCalibrationRequest()) {
		cout << "\nstartcalib after validated true\n" << endl;

		// do calibration
		// // check for file existence
		// // // if exist, load
		// // // else create

		// // read file
		// // // format ok?
		// // // load
		// // // set state

		//  during calib

		isCalibrating = 1;

		initialPulse = SHAFT::getCurrentPulse();
		cout << "\ninitialPulse : " << initialPulse << endl;
		// speed must be 0
		// start pulse
		// end pulse
		// validate error range
		// save to file
		// if fail to save, revert to default
		// set internal var: calibvalue & isCalibrating=0

	}

}

void CALIB::stopCalibration() {

	if (isCalibrating) {
		endPulse = SHAFT::getCurrentPulse();
		cout << "\nendPulse : " << endPulse << endl;
	}
	tempCalibrationValue = endPulse - initialPulse;

	cout << "\ntempCalibrationValue : " << tempCalibrationValue << endl;

	initialPulse = 0;
	endPulse = 0;

	if ( (abs(tempCalibrationValue-calibrationDefault))/static_cast<double>(5921)*100 <= 20) {
		cout << "\nok within 20 percent\n" << endl;
		calibrationValue = tempCalibrationValue;
		isCalibrating = 0;
		initialPulse = 0;
		endPulse = 0;
		tempCalibrationValue = 0;

		cout << "\n isCalibrating : " << isCalibrating <<
				"\n initialPulse : " << initialPulse <<
				"\n endPulse : " << endPulse <<
				"\n tempCalibrationValue : " << tempCalibrationValue <<
				"\n calibrationValue : " <<calibrationValue << endl;
	}

	else {
		calibrationValue = calibrationDefault;
	}

}

bool CALIB::validateCalibrationRequest() {
	if (!CRUISE::getIsActive()) {
		cout << "\ncruise isnotactive, return true to calib request\n" << endl;
		return true;

	}

	else return false;

}