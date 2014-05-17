#include <iostream>
#include "OBATargetMachine.h"
#include "PortsLayout.h"
#pragma comment(lib, "OBAVirtualTarget.lib")

#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../OBAAPI/OBA-THRO_Interface/OBA_THRO_Interface.h"
#include "../OBAAPI/OBA-MMI_Interface/OBA_MMI_Interface.h"
#include "../OBAAPI/OBA-DSTA_Interface/OBA_DSTA_Interface.h"
#include "../OBACruise/OBA_Cruising.h"
#include "../OBAMAintenance/OBA_Maintenance.h"

using namespace std;

static const unsigned int	periodInMillisecond = 1000; 

static unsigned int tick = 4;

void myInterruptHandler (Interrupt sig) {
	
	ControlPanelInterruptStatusWord *keyId = (ControlPanelInterruptStatusWord *) (OTM::controlPanelInterruptWordAddress);
	OBA_MMI_Interface::KEYMAP pressedKey;
	DrivingStationInterruptStatusWord *eventDSTA = (DrivingStationInterruptStatusWord *) (OTM::drivingControlsInterruptWordAddress);

	switch (sig)
	{
	case IT_controlPanel: 
		OBA_MMI_Interface::keyPressHandler(keyId->keyCode);
		break;

	case IT_drivingControls:
		DSTA::handleDSTAinterrupt(eventDSTA);
		break;

	case IT_timer:
			SHAFT::calculateSpeed();
			if (CRUISE::getIsActive() == 1) {
				THRO::maintainSpeed();
			}

			MAINT::maintenanceRoutine(tick--);

			if (tick==0) {
				tick = 4;
			}
		break;

	default :
	cout << "handler " << sig <<endl;
	}
}


int main() {

try {
		OTM::interruptVector[IT_controlPanel] = myInterruptHandler;
        OTM::interruptVector[IT_drivingControls] = myInterruptHandler;
		OTM::interruptVector[IT_timer] = myInterruptHandler;

		OTM::setPeriodicTimer(periodInMillisecond, 0);

        OTM::enabledInterruptsRegister = allObaRelatedInterrupts;

        for (;;) {
        }
   }

   catch (const char *const message) {

      throw;
   }

}
