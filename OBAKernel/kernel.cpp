#include <iostream>
#include "OBATargetMachine.h"
#include "PortsLayout.h"
#pragma comment(lib, "OBAVirtualTarget.lib")

using namespace std;

static	char msg2[] = "Keyboard Pressed         ";
static	char msg3[] = "Driving Control          ";
static	char msg4[] = "                         ";
static volatile int temp = 100;
static const unsigned int	periodInMillisecond = 1000; 
unsigned x = 0;


#include "../OBAAPI/OBA-SHAFT_Interface/OBA_SHAFT_Interface.h"
#include "../OBAAPI/OBA-THRO_Interface/OBA_THRO_Interface.h"
#include "../OBAAPI/OBA-MMI_Interface/OBA_MMI_Interface.h"
#include "../OBAAPI/OBA-DSTA_Interface/OBA_DSTA_Interface.h"


void myInterruptHandler (Interrupt sig) {
	
	ControlPanelInterruptStatusWord *keyId;
	OBA_MMI_Interface::KEYMAP pressedKey;

	switch (sig)
	{
	case IT_controlPanel : 
		keyId = (ControlPanelInterruptStatusWord *) (OTM::controlPanelInterruptWordAddress);
		
		pressedKey = static_cast<OBA_MMI_Interface::KEYMAP>(keyId->keyCode);

		cout << "Key Id : " << pressedKey << endl;
		//msg = msg2; temp = 10;
		break;
	case IT_drivingControls :
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

			cout << "\n\ngear: " << OBA_DSTA_Interface::getEngagedGearState() << 
			"\nignition: " << OBA_DSTA_Interface::getIgnitionState() << 
			"\nclutch: " << OBA_DSTA_Interface::getClutchState() << 
			"\nbrake: " << OBA_DSTA_Interface::getBrakeState() << 
			"\naccelerator: " << OBA_DSTA_Interface::getAcceleratorState();

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
		OBA_MMI_Interface::sendLEDsignal();

// write the message to the display

		OBA_MMI_Interface::displayMessage();

// idle the CPU		

			//OTM::idleWait (75);

			OBA_THRO_Interface::sendThrottleSignal();
			//cout << OBA_THRO_Interface::getThrottleResponse() <<endl;

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
