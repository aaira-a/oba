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

	static unsigned int KM_OIL_CHANGE_REMIND	= 	7600;
	static unsigned int KM_OIL_CHANGE_WARN 		= 	7920;
	static unsigned int KM_AIR_FILTER_REMIND	= 	14600;
	static unsigned int KM_AIR_FILTER_WARN 		= 	14920;
	static unsigned int KM_GENERAL_REMIND 		= 	24600;
	static unsigned int KM_GENERAL_WARN 		= 	24920; 

	static unsigned int lastOilChange		=	0;
	static unsigned int lastAirFilterChange =	0;
	static unsigned int lastGeneralService  =	0;

	static bool maintenanceMessageOn		=	0;
	static bool intermittentMessage 		= 	0;
	static enum MAINT_MSG MESSAGE 			=	EMPTY;

void MAINT::maintenanceRoutine(int tick) {
	maintenanceChecker();
	maintenanceMessageService(tick);
}

void MAINT::maintenanceMessageService(int tick) {

	if (maintenanceMessageOn) {
	
		if (intermittentMessage) {

			if (tick==2 || tick==1) {
				MESSAGE = EMPTY;
			}
		}

		showMaintenanceMessage();
	}

}

void MAINT::maintenanceChecker() {

	if (currentMileage - lastOilChange >= KM_OIL_CHANGE_REMIND) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 1;
		MESSAGE 			 = OIL_REMIND;
	}

	if (currentMileage - lastOilChange >= KM_OIL_CHANGE_WARN) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 0;
		MESSAGE 			 = OIL_WARN;
	}

	if (currentMileage - lastAirFilterChange >= KM_AIR_FILTER_REMIND) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 1;
		MESSAGE 			 = AIR_REMIND;
	}

	if (currentMileage - lastAirFilterChange >= KM_AIR_FILTER_WARN) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 0;
		MESSAGE 			 = AIR_WARN;
	}

	if (currentMileage - lastGeneralService >= KM_GENERAL_REMIND) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 1;
		MESSAGE 			 = GEN_REMIND;		
	}

	if (currentMileage - lastGeneralService >= KM_GENERAL_WARN) {
		maintenanceMessageOn = 1;
		intermittentMessage  = 0;
		MESSAGE 			 = GEN_WARN;		
	}

}

unsigned int MAINT::getCurrentMileage() {
	//currentMileage = SHAFT::getCurrentPulse() / SHAFT::getCalibrationReference();
	return currentMileage;
}

void MAINT::debugger(unsigned int overrideMileage) {
	currentMileage = overrideMileage;
	cout << "\n currentMileage : " << getCurrentMileage() << endl;

}

void MAINT::showMaintenanceMessage() {

	switch (MESSAGE) {

	case EMPTY:
		MMI::displayMessage("                          ");
		break;

	case OIL_REMIND:
		MMI::displayMessage("OIL CHANGE REMINDER       ");
		break;

	case OIL_WARN:
		MMI::displayMessage("OIL CHANGE WARNING        ");
		break;

	case AIR_REMIND:
		MMI::displayMessage("AIR FILTER REMINDER       ");
		break;

	case AIR_WARN:
		MMI::displayMessage("AIR FILTER WARNING        ");
		break;

	case GEN_REMIND:
		MMI::displayMessage("GEN.SERVICE REMINDER      ");
		break;

	case GEN_WARN:
		MMI::displayMessage("GEN.SERVICE WARNING       ");
	}
}

void MAINT::serviceDoneHandler() {
	
	if (maintenanceMessageOn) {
		
		switch (MESSAGE) {

		case OIL_REMIND:
		lastOilChange = currentMileage;
		break;

		case OIL_WARN:
		lastOilChange = currentMileage;
		break;

		case AIR_REMIND:
		lastOilChange = currentMileage;
		lastAirFilterChange = currentMileage;
		break;

		case AIR_WARN:
		lastOilChange = currentMileage;
		lastAirFilterChange = currentMileage;
		break;

		case GEN_REMIND:
		lastOilChange = currentMileage;
		lastAirFilterChange = currentMileage;		
		lastGeneralService = currentMileage;
		break;

		case GEN_WARN:
		lastOilChange = currentMileage;
		lastAirFilterChange = currentMileage;		
		lastGeneralService = currentMileage;
		}

	maintenanceMessageOn	= 	0;
	intermittentMessage		= 	0;
	MESSAGE 				= 	EMPTY;
	MMI::displayMessage("                          ");

	cout << "\n\n service done~ " << 
			"\n last oilchange : " << lastOilChange <<
			"\n last airfilter : " << lastAirFilterChange <<
			"\n last gensvc : "	<<	lastGeneralService <<
			"\n";

	}

	else {cout << "\n\n service not due~ " <<
			"\n last oilchange : " << lastOilChange <<
			"\n last airfilter : " << lastAirFilterChange <<
			"\n last gensvc : "	<<	lastGeneralService <<
			"\n";
	}
}
