#include <iostream>
#include "OBATargetMachine.h"
#include "PortsLayout.h"
#pragma comment(lib, "OBAVirtualTarget.lib")

using namespace std;

static volatile int temp = 100;
static const unsigned int	periodInMillisecond = 1000; 
unsigned x = 0;


#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../OBAAPI/OBA-THRO_Interface/OBA_THRO_Interface.h"
#include "../OBAAPI/OBA-MMI_Interface/OBA_MMI_Interface.h"
#include "../OBAAPI/OBA-DSTA_Interface/OBA_DSTA_Interface.h"
#include "../OBACruise/OBA_Cruising.h"


void myInterruptHandler (Interrupt sig) {
	
	ControlPanelInterruptStatusWord *keyId = (ControlPanelInterruptStatusWord *) (OTM::controlPanelInterruptWordAddress);
	OBA_MMI_Interface::KEYMAP pressedKey;
	DrivingStationInterruptStatusWord *eventDSTA = (DrivingStationInterruptStatusWord *) (OTM::drivingControlsInterruptWordAddress);

	switch (sig)
	{
	case IT_controlPanel : 
		
		OBA_MMI_Interface::keyPressHandler(keyId->keyCode);
		//pressedKey = static_cast<OBA_MMI_Interface::KEYMAP>(keyId->keyCode);

		cout << "Key Id : " << keyId->keyCode << endl;
		//msg = msg2; temp = 10;
		break;

	case IT_drivingControls :
	
		DSTA::handleDSTAinterrupt(eventDSTA);
		/*
		cout << "\n\naccelerator: " << eventDSTA->acceleratorFlag <<
		"\nbrake: " << eventDSTA->brakeFlag <<
		"\nclutch:" << eventDSTA->clutchFlag <<
		"\nignition:" << eventDSTA-> ignitionFlag;
		*/

		//cout << "IT driving" <<endl;
		//msg = msg3; temp = 10;
		break;

	case IT_timer :
		//temp--;
		// if the time is consumed to display Interrupt message, the default message is set
		//if (temp < 0)
		//	msg = msg4;
		//cout << ++x << endl;cout.flush();
		//getCurrentSpeed();
		//cout << OBA_SHAFT_Interface::getCurrentPulse() << endl;

			/*
			cout << "\n\ngear: " << OBA_DSTA_Interface::getEngagedGearState() << 
			"\nignition: " << OBA_DSTA_Interface::getIgnitionState() << 
			"\nclutch: " << OBA_DSTA_Interface::getClutchState() << 
			"\nbrake: " << OBA_DSTA_Interface::getBrakeState() << 
			"\naccelerator: " << OBA_DSTA_Interface::getAcceleratorState();
			*/

			SHAFT::calculateSpeed();

			if (CRUISE::getIsActive() == 1) {
				THRO::maintainSpeed();
			}

			/*cout << "\n\ncruise isActive : " << CRUISE::FisActive() <<
					"  \ncruise cruisingSpeed : " << CRUISE::getCruisingSpeed() <<
					"  \ncruise isSuspended : " << CRUISE::FisSuspended() << endl;*/

			/*cout << "\n\nthrottle signal   : 40" << 
					"\nthrottle response : " << THRO::getThrottleResponse() << endl;*/

		break;
	default :
	cout << "handler " << sig <<endl;
	}
}

int main(){

    int i=0;
	
try {
// initialisation of the interrupt vector

		OTM::interruptVector[IT_controlPanel] = myInterruptHandler;
        OTM::interruptVector[IT_drivingControls] = myInterruptHandler;
		OTM::interruptVector[IT_timer] = myInterruptHandler;
// set the timer

		OTM::setPeriodicTimer(periodInMillisecond, 0);
// enable the interrupt

        OTM::enabledInterruptsRegister = allObaRelatedInterrupts;

// keep the display buffer 


// infinite loop

 for (;;)
	{
		//OBA_MMI_Interface::sendLEDsignal();

// write the message to the display



// idle the CPU		

			//OTM::idleWait (75);

			//THRO::sendThrottleSignal(40); 
	}
   }

   catch (const char *const message) {
 //     cout 
  //    << "Unexpected issue previous to OBA::run():" << endl 
   //   << "   " << message << endl;
      // context failure : useless to run OBA.
      throw;
   }

}
