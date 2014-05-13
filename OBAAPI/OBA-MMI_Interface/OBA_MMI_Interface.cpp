#include "../../OBAKERNEL/OBATargetMachine.h"
#include "../../OBAKERNEL/PortsLayout.h"
#include "OBA_MMI_Interface.h"
#include "../OBA-THRO_Interface/OBA_THRO_Interface.h"
#include "../../OBACruise/OBA_Cruising.h"

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

void MMI::sendLEDsignal() {
	LedCommandWord *led;
	led =  (LedCommandWord *)(OTM::ledCommandByteAddress);

	//assign/override accordingly
	led->led_1=1;   //left   // green
	led->led_2=1;   //center // yellow
	led->led_3=1;   //right  // red
}

void MMI::displayMessage() {
	static  char *msg;
	static	char msg1[] = "Hello World!             ";
	DisplayBufferAddress	 *display;
	display =  (DisplayBufferAddress*)(OTM::displayBufferAddress);

	msg=msg1;

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