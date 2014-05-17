#include "../OBAKERNEL/OBATargetMachine.h"
#include "../OBAKERNEL/PortsLayout.h"
#include "OBA_Maintenance.h"
//#include "../OBACruise/OBA_Cruising.h"
//#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
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

/* void MAINT::methodname() {

} */