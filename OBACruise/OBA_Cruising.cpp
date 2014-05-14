#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Cruising.h"
#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../OBAAPI/OBA-THRO_Interface/OBA_THRO_Interface.h"
#include "../OBAAPI/OBA-DSTA_Interface/OBA_DSTA_Interface.h"
#include "../OBAAPI/OBA-MMI_Interface/OBA_MMI_Interface.h"

OBA_Cruising::OBA_Cruising() {
}

	static bool isActive = 		0;
	static bool isSuspended = 	0;
	static int cruisingSpeed = 	0;

void CRUISE::activateCruising() {
	
	if (validateCruisingRequest()) {
		cruisingSpeed = SHAFT::getCurrentSpeed();
		isActive = 1;
		THRO::maintainSpeed(cruisingSpeed);
		MMI::sendLEDsignal(1, 1);
		MMI::displayMessage(cruisingSpeed);
	}

}

void CRUISE::stopCruising() {

}

void CRUISE::suspendCruising() {

}

void CRUISE::resumeCruising() {

}

bool CRUISE::validateCruisingRequest() {
	
	if (/*add !calib::isCalibrating()?*/ 
		DSTA::getIgnitionState() && 
		!DSTA::getBrakeState() && 
		!DSTA::getClutchState() &&
		DSTA::getEngagedGearState()==5) {

			if (SHAFT::getCurrentSpeed() >= 80 && 
				SHAFT::getCurrentSpeed() <= 130) {
				return true;
			}
			
			else return false;
	}

	else return false;
}

void CRUISE::requestCurrentSpeed() {  			// delegate call to shaft ? or move method to shaft ?

}   

void CRUISE::setCruisingSpeed() {

}

void CRUISE::requestCalibrationStatus() {		// delegate call to calibration controller ? or move method to calibration ?

}	

void CRUISE::requestDrivingStationStatus() { 	// delegate call to dsta ? or move method to dsta?

}	

void CRUISE::requestMaintainSpeed() {			// delegate call to thro? or maintain logic here ?
// start with activate cruising to handle first
}	

void CRUISE::requestStopMaintainSpeed() {		// delegate call to thro? or maintain logic here ?

}

bool CRUISE::FisActive() {
	return isActive;
}

bool CRUISE::FisSuspended() {
	return isSuspended;
}

int CRUISE::FcruisingSpeed() {
	return cruisingSpeed;
}