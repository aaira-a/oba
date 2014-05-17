#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Maintenance.h"
#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../OBAAPI/OBA-MMI_Interface/OBA_MMI_Interface.h"

#include <iostream>

using namespace std;

OBA_Maintenance::OBA_Maintenance() {
}

	static unsigned int currentMileage = 0;

	static unsigned int OIL_CHANGE_REMIND	= 	7600;
	static unsigned int OIL_CHANGE_WARN 	= 	7920;
	static unsigned int AIR_FILTER_REMIND	= 	14600;
	static unsigned int AIR_FILTER_WARN 	= 	14920;
	static unsigned int GENERAL_REMIND 		= 	24600;
	static unsigned int GENERAL_WARN 		= 	24920; 

	static unsigned int lastOilChange		=	0;
	static unsigned int lastAirFilterChange =	0;
	static unsigned int lastGeneralService  =	0;

void MAINT::maintenanceRoutine() {
	
	maintenanceChecker();
}

void MAINT::maintenanceChecker() {

	cout << getCurrentMileage() << endl;

	if (currentMileage >= OIL_CHANGE_REMIND) {
		MMI::displayMessage("OIL CHANGE REMINDER       ");
	}

	if (currentMileage >= OIL_CHANGE_WARN) {
		MMI::displayMessage("OIL CHANGE WARNING        ");
	}

	if (currentMileage >= AIR_FILTER_REMIND) {
		MMI::displayMessage("AIR FILTER REMINDER       ");
	}

	if (currentMileage >= AIR_FILTER_WARN) {
		MMI::displayMessage("AIR FILTER WARNING        ");
	}

	if (currentMileage >= GENERAL_REMIND) {
		MMI::displayMessage("GEN.SERVICE REMINDER      ");
	}

	if (currentMileage >= GENERAL_WARN) {
		MMI::displayMessage("GEN.SERVICE WARNING       ");
	}
}

unsigned int MAINT::getCurrentMileage() {
	//currentMileage = SHAFT::getCurrentPulse() / SHAFT::getCalibrationReference();
	return currentMileage;
}

void MAINT::debugger(unsigned int overrideMileage) {
	currentMileage = overrideMileage;
}