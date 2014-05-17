#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Calibration.h"
#include "../OBACruise/OBA_Cruising.h"
#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../OBAAPI/OBA-MMI_Interface/OBA_MMI_Interface.h"
#include <iostream>

using namespace std;

OBA_Calibration::OBA_Calibration() {
}

	static const double calibrationDefault = 5291.0053; 
	static double calibrationValue = 5291.0053;
	static bool isCalibrating = 0;
	static unsigned int initialPulse = 0;
	static unsigned int endPulse = 0;
	static double tempCalibrationValue = 0;


void CALIB::startCalibration() {
	if (!CRUISE::getIsActive()) {
		MMI::displayMessage("Calibration On            ");
		isCalibrating = 1;
		initialPulse = SHAFT::getCurrentPulse();

		cout << "\n\n Start Calibration - "				 					<<
				"\n Auto Cruise isActive : " 	<< CRUISE::getIsActive()	<<
				"\n isCalibrating : " 			<< isCalibrating 			<<
				"\n initialPulse  : "			<< initialPulse				<<
				"\n";
	}

	else {
		cout << "\n\n Calibration not started - "
				"\n Auto Cruise isActive : " 	<< CRUISE::getIsActive()	<<
				"\n";
	}

}

void CALIB::stopCalibration() {

	if (isCalibrating) {
		MMI::displayMessage("Calibration Stop           ");
		endPulse = SHAFT::getCurrentPulse();
		tempCalibrationValue = endPulse - initialPulse;
	
		if ( (abs(tempCalibrationValue-calibrationDefault))/static_cast<double>(5921)*100 <= 20) {
			calibrationValue = tempCalibrationValue;

			cout << "\n\n Stopping Calibration - " 			<<
					"\n isCalibrating : "					<<	isCalibrating 			<<
					"\n initialPulse : "					<<	initialPulse 			<<
					"\n endPulse : "						<<	endPulse				<<
					"\n tempCalibrationValue : "			<<	tempCalibrationValue 	<<
					"\n New calibrationValue : "			<<	calibrationValue 		<<
					"\n Within Tolerance : Yes \n"			;
		}

		else {
			calibrationValue = calibrationDefault;

			cout << "\n\n Stopping Calibration - "			<<
					"\n isCalibrating : "					<<	isCalibrating 			<<
					"\n initialPulse : "					<<	initialPulse 			<<
					"\n endPulse : "						<<	endPulse				<<
					"\n tempCalibrationValue : "			<<	tempCalibrationValue 	<<
					"\n New calibrationValue : "			<<	calibrationValue 		<<
					"\n Within Tolerance : No \n"			;
		}

		SHAFT::setCalibrationReference(calibrationValue);
		isCalibrating = 0;
		initialPulse = 0;
		endPulse = 0;
		tempCalibrationValue = 0;

		cout << "\n\n Reset state - "			<<
		     	"\n isCalibrating : "			<<		isCalibrating		<<
		     	"\n initialPulse : "			<<		initialPulse		<<
		        "\n endPulse : "				<<		endPulse 			<<
		        "\n tempCalibrationValue : "	<<		tempCalibrationValue<<
		        "\n";
	}

	else {
		cout << "\n\n Stopping Calibration - "	<<
				"\n isCalibrating : "			<<	isCalibrating 			<<
				"\n Auto Cruise isActive : " 	<< CRUISE::getIsActive()	<<
				"\n Ignore input \n";	
	}
}

bool CALIB::getIsCalibrating() {
	return isCalibrating;
}

double CALIB::getCalibrationValue() {
	return calibrationValue;

}
