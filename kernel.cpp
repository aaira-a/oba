#include <iostream>
#include "OBATargetMachine.h"
#include "PortsLayout.h"
#pragma comment(lib, "OBAVirtualTarget.lib")

using namespace std;

static  char * msg; 
static	char msg1[] = "Hello World!             ";
static	char msg2[] = "Keyboard Pressed         ";
static	char msg3[] = "Driving Control          ";
static	char msg4[] = "                         ";
static volatile int temp = 100;
static const unsigned int	periodInMillisecond = 1000; 
unsigned x = 0;
const double calibrationconst = 5291.0053;
unsigned int lastpulse = 0;
double speed = 0;


//prototypesssss:
double getCurrentSpeed();

void interruptHandler (Interrupt sig) {
	ControlPanelInterruptStatusWord *keyId;
	switch (sig)
	{
	case IT_controlPanel : 
		//keyId = (ControlPanelInterruptStatusWord *) (OTM::controlPanelInterruptWordAddress);
		//cout << "Key Id : " << keyId->keyCode << endl;
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
		getCurrentSpeed();
		break;
	default :
	cout << "handler " << sig <<endl;
	}
}

unsigned int getCurrentPulse() {
	CounterWord *pulse;
	pulse = (CounterWord *) (OTM::pulseCounterWordAddress);
	return pulse->pulsecount;
	//cout << " \n\t" << pulse->pulsecount;  //uncomment to see the value
}

double getCurrentSpeed() {
	
	speed = ((getCurrentPulse() - lastpulse)/calibrationconst)*3600;
	lastpulse = getCurrentPulse();
	cout << speed << " : " << getCurrentPulse()/calibrationconst << endl;
	return speed;
}

void sendThrottleSignal() {
	ThrottleCommandWord *throttle;
	throttle = (ThrottleCommandWord *)(OTM::throttleCommandWordAddress);
	throttle->outputvoltagevalue=80;
	throttle->paritybit=1;
}


void getThrottleResponse() {
	ThrottleResponseWord *throttle;
	throttle = (ThrottleResponseWord *)(OTM::throttlePositionWordAddress);
	//cout << throttle->inputvoltagevalue <<endl;  //uncomment to see the value
}

void sendLEDsignal() {
	LedCommandWord *led;  //init struct pointer
	led =  (LedCommandWord *)(OTM::ledCommandByteAddress); //mapping between local struct pointer to otm struct pointer 

	//assign/override accordingly
	led->led_1=1;   //left   // green
	led->led_2=1;   //center // yellow
	led->led_3=1;   //right  // red
}


int main(){

    int i=0;
	msg=msg1;
	DisplayBufferAddress	 *display;



try {
// initialisation of the interrupt vector

		OTM::interruptVector[IT_controlPanel] = interruptHandler;
        OTM::interruptVector[IT_drivingControls] = interruptHandler;
		OTM::interruptVector[IT_timer] = interruptHandler;
// set the timer

		OTM::setPeriodicTimer(periodInMillisecond, 0);
// enable the interrupt

        OTM::enabledInterruptsRegister = allObaRelatedInterrupts;

// keep the display buffer 

		display =  (DisplayBufferAddress*)(OTM::displayBufferAddress);
		


// infinite loop

 for (;;)
	{
		//getAndPrintPulse(); //print current pulse to console
		sendLEDsignal();

// write the message to the display

		for (int j=0;j<20;j++)
			display->displaymessage[j]=msg[j];
// idle the CPU		

			//OTM::idleWait (75);

			sendThrottleSignal();
			getThrottleResponse();
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
