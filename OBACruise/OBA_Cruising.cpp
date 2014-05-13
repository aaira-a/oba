#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Cruising.h"
#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../OBAAPI/OBA-THRO_Interface/OBA_THRO_Interface.h"
#include "../OBAAPI/OBA-DSTA_Interface/OBA_DSTA_Interface.h"
#include "../OBAAPI/OBA-MMI_Interface/OBA_MMI_Interface.h"

OBA_Cruising::OBA_Cruising() {

	static bool isActive;
	static bool isSuspended;
	static int cruisingSpeed;
}

void OBA_Cruising::activateCruising() {
	
	if (validateCruisingRequest()) {
		//OBA_THRO_Interface::maintainSpeed();
		THRO::sendThrottleSignal(77);
		MMI::sendLEDsignal(1, 1);
	}

}

void OBA_Cruising::stopCruising() {

}

void OBA_Cruising::suspendCruising() {

}

void OBA_Cruising::resumeCruising() {

}

bool OBA_Cruising::validateCruisingRequest() {
	
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

void OBA_Cruising::requestCurrentSpeed() {  			// delegate call to shaft ? or move method to shaft ?

}   

void OBA_Cruising::setCruisingSpeed() {

}

void OBA_Cruising::requestCalibrationStatus() {		// delegate call to calibration controller ? or move method to calibration ?

}	

void OBA_Cruising::requestDrivingStationStatus() { 	// delegate call to dsta ? or move method to dsta?

}	

void OBA_Cruising::requestMaintainSpeed() {			// delegate call to thro? or maintain logic here ?
// start with activate cruising to handle first
}	

void OBA_Cruising::requestStopMaintainSpeed() {		// delegate call to thro? or maintain logic here ?

}	