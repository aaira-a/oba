#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Cruising.h"

OBA_Cruising::OBA_Cruising() {

	static bool isActive;
	static bool isSuspended;
	static int cruisingSpeed;
}

void OBA_Cruising::activateCruising() {

}

void OBA_Cruising::stopCruising() {

}

void OBA_Cruising::suspendCruising() {

}

void OBA_Cruising::resumeCruising() {

}

void OBA_Cruising::validateCruisingRequest() {

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

}	

void OBA_Cruising::requestStopMaintainSpeed() {		// delegate call to thro? or maintain logic here ?

}	