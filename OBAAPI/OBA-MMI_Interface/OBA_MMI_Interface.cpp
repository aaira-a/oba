#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_MMI_Interface.h"
#include "../OBA-THRO_Interface/OBA_THRO_Interface.h"
#include "../../OBACruise/OBA_Cruising.h"
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

	if (ledNumber == 2) {
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
  	char * cstr = new char [str1.length()+1];
  	std::strcpy (cstr, str1.c_str());

	static  char *msg;
	msg=cstr;

	for (int i=0;i<20;i++)
		display->displaymessage[i]=msg[i];
}

//unused char arrays from eg
//static	char msg2[] = "Keyboard Pressed         ";
//static	char msg3[] = "Driving Control          ";
//static	char msg4[] = "                         ";


void MMI::keyPressHandler(int pressedKey) {

	KEYMAP keyEnum = static_cast<MMI::KEYMAP>(pressedKey);

	switch (keyEnum) {

	case KEY_ACTIVATION:
		OBA_Cruising::activateCruising();
		break;

	default :
		break;
	}

}