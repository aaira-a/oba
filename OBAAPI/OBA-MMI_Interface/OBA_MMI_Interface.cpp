#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_MMI_Interface.h"
#include "../OBA-THRO_Interface/OBA_THRO_Interface.h"
#include "../../OBACruise/OBA_Cruising.h"
#include "../../OBACalibration/OBA_Calibration.h"
#include "../../OBAMaintenance/OBA_Maintenance.h"
#include <string>
#include <cstring>

OBA_MMI_Interface::OBA_MMI_Interface() {

}

	enum KEYMAP {
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_ACTIVATION,
		KEY_DEACTIVATION,
		KEY_RESUME,
		KEY_START_ACCELERATION,
		KEY_STOP_ACCELERATION,
		KEY_START_CALIBRATION,
		KEY_STOP_CALIBRATION,
		KEY_TRIP_START,
		KEY_FUEL_QUANTITY,
		KEY_AVERAGE_SPEED,
		KEY_SERVICE_COMPLETED,
		KEY_VALIDATION,
		KEY_CANCEL,
		KEY_AVERAGE_CONSUMPTION,
		KEY_DECIMAL
	};


void MMI::sendLEDsignal(int ledNumber, bool ledBool) {
	
	LedCommandWord *led;
	led =  (LedCommandWord *)(OTM::ledCommandByteAddress);

	//assign/override accordingly
	if (ledNumber == 1) {
		led -> led_1 = ledBool;	//left   // green	// on/off
	}

	if (ledNumber == 2) {
		led -> led_2 = ledBool;	//center // yellow	// care to speed
	}

	if (ledNumber == 3) {
		led -> led_3 = ledBool;	//right  // red		// hazard bolting
	}

}


void MMI::displayMessage(char message[]) {
	static  char *msg;
	//static	char msg1[] = "Hello World!             ";
	DisplayBufferAddress	 *display;
	display =  (DisplayBufferAddress*)(OTM::displayBufferAddress);

	msg=message;

	for (int i=0;i<20;i++)
		display->displaymessage[i]=msg[i];
}


void MMI::displayMessage(int speed) {
	
	DisplayBufferAddress	 *display;
	display =  (DisplayBufferAddress*)(OTM::displayBufferAddress);

	std::string str1 = "Auto Cruise " + std::to_string(static_cast<long long>(speed));
	std::string str2 = str1 + " km/h ";

  	char * cstr = new char [str2.length()+1];
  	std::strcpy (cstr, str2.c_str());
	static  char *msg;
	msg=cstr;

	for (int i=0;i<20;i++)
		display->displaymessage[i]=msg[i];
}


void MMI::keyPressHandler(int pressedKey) {

	KEYMAP keyEnum = static_cast<MMI::KEYMAP>(pressedKey);

	switch (keyEnum) {

	case KEY_ACTIVATION:
		CRUISE::activateCruising(101);
		break;

	case KEY_DEACTIVATION:
		CRUISE::stopCruising();
		break;

	case KEY_START_ACCELERATION:
		CRUISE::startAccelerationRequest();
		break;

	case KEY_STOP_ACCELERATION:
		CRUISE::stopAccelerationRequest();
		break;

	case KEY_RESUME:
		CRUISE::resumeCruising();
		break;

	case KEY_START_CALIBRATION:
		CALIB::startCalibration();
		break;

	case KEY_STOP_CALIBRATION:
		CALIB::stopCalibration();
		break;

	case KEY_SERVICE_COMPLETED:
		MAINT::serviceDoneHandler();
		break;

	case KEY_1:
		MAINT::debugger(7600);
		break;

	case KEY_2:
		MAINT::debugger(7920);
		break;

	case KEY_3:
		MAINT::debugger(14600);
		break;

	case KEY_4:
		MAINT::debugger(14920);
		break;

	case KEY_5:
		MAINT::debugger(24600);
		break;

	case KEY_6:
		MAINT::debugger(24920);
		break;
		
	default :
		break;
	}

}
