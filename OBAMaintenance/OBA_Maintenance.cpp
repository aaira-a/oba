#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Maintenance.h"
#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../OBAAPI/OBA-MMI_Interface/OBA_MMI_Interface.h"

#include <iostream>

using namespace std;

OBA_Maintenance::OBA_Maintenance() {
}

	enum MAINT_MSG {
		EMPTY,
		OIL_REMIND,
		OIL_WARN,
		AIR_REMIND, 
		AIR_WARN,
		GEN_REMIND,
		GEN_WARN,
	};

	static unsigned int currentMileage 		= 	0;

	static unsigned int OIL_CHANGE_REMIND	= 	7600;
	static unsigned int OIL_CHANGE_WARN 	= 	7920;
	static unsigned int AIR_FILTER_REMIND	= 	14600;
	static unsigned int AIR_FILTER_WARN 	= 	14920;
	static unsigned int GENERAL_REMIND 		= 	24600;
	static unsigned int GENERAL_WARN 		= 	24920; 

	static unsigned int lastOilChange		=	0;
	static unsigned int lastAirFilterChange =	0;
	static unsigned int lastGeneralService  =	0;

	static bool maintenanceMessageOn		=	0;
	static bool intermittentMessage 		= 	0;
	static enum MAINT_MSG MESSAGE 			=	EMPTY;

void MAINT::maintenanceRoutine() {
	
	maintenanceChecker();
}

void MAINT::maintenanceChecker() {

	cout << getCurrentMileage() << endl;

	if (currentMileage >= OIL_CHANGE_REMIND) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 0;
		MESSAGE 			 = OIL_REMIND;
	}

	if (currentMileage >= OIL_CHANGE_WARN) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 1;
		MESSAGE 			 = OIL_WARN;
	}

	if (currentMileage >= AIR_FILTER_REMIND) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 0;
		MESSAGE 			 = AIR_REMIND;
	}

	if (currentMileage >= AIR_FILTER_WARN) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 1;
		MESSAGE 			 = AIR_WARN;
	}

	if (currentMileage >= GENERAL_REMIND) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 0;
		MESSAGE 			 = GEN_REMIND;		
	}

	if (currentMileage >= GENERAL_WARN) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 1;
		MESSAGE 			 = GEN_WARN;		
	}

	cout << MESSAGE << endl;
}

unsigned int MAINT::getCurrentMileage() {
	//currentMileage = SHAFT::getCurrentPulse() / SHAFT::getCalibrationReference();
	return currentMileage;
}

void MAINT::debugger(unsigned int overrideMileage) {
	currentMileage = overrideMileage;
}

/*
MMI::displayMessage("OIL CHANGE REMINDER       ");
MMI::displayMessage("OIL CHANGE WARNING        ");
MMI::displayMessage("AIR FILTER REMINDER       ");
MMI::displayMessage("AIR FILTER WARNING        ");
MMI::displayMessage("GEN.SERVICE REMINDER      ");
MMI::displayMessage("GEN.SERVICE WARNING       ");

*/