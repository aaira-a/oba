#include <iostream>
#include "OBATargetMachine.h"
#include "PortsLayout.h"
#pragma comment(lib, "OBAVirtualTarget.lib")

using namespace std;

static char * msg; 
static	char msg1[] = "Hello World!             ";
static	char msg2[] = "Keyboard Pressed         ";
static	char msg3[] = "Driving Control          ";
static	char msg4[] = "                         ";
static volatile int temp = 100;
static const unsigned int	periodInMillisecond = 100; 

void periodicHandler (/*OTM::*/Interrupt sig) {
	ControlPanelInterruptStatusWord *keyId;

	// in function of the signal number, a specific treatment is done
	switch (sig)
	{
	case IT_controlPanel : 
		// read the Interrupt word 
		keyId = (ControlPanelInterruptStatusWord *) (OTM::controlPanelInterruptWordAddress);
		// perform the treatment
		cout << "Key Id :" << keyId->keyCode << endl;
		msg = msg2; temp = 10;
		break;
	case IT_drivingControls :
		// to be done	
		cout << "IT driving" <<endl;
		msg = msg3; temp = 10;
		break;
	case IT_timer :
		
		// very simple treatement
		temp--;
		// if the time is consumed to display Interrupt message, the default message is set
		if (temp < 0)
			msg = msg4;

		cout << ".";cout.flush();
		break;
	default :
	cout << "handler " << sig <<endl;
	}
}



int main(){

	cout << " " << endl;
	cout << "bool:\t\t" << sizeof(bool) << " bytes" << endl;
    cout << "char:\t\t" << sizeof(char) << " bytes" << endl;
    cout << "wchar_t:\t" << sizeof(wchar_t) << " bytes" << endl;
    cout << "short:\t\t" << sizeof(short) << " bytes" << endl;
    cout << "int:\t\t" << sizeof(int) << " bytes" << endl;
    cout << "long:\t\t" << sizeof(long) << " bytes" << endl;
    cout << "float:\t\t" << sizeof(float) << " bytes" << endl;
    cout << "double:\t\t" << sizeof(double) << " bytes" << endl;
    cout << "long double:\t" << sizeof(long double) << " bytes" << endl;
	cout << "unsigned:\t" << sizeof(unsigned) << " bytes" << endl;
    cout << " " << endl;
	
	cout << " " << endl;

	cout << "OBATargetMachine::pulseCounterWordAddress \t\t" << OBATargetMachine::pulseCounterWordAddress << endl;
	cout << "OBATargetMachine::throttlePositionWordAddress \t\t" << OBATargetMachine::throttlePositionWordAddress << endl;
	cout << "OBATargetMachine::drivingControlsInterruptWordAddress \t" << OBATargetMachine::drivingControlsInterruptWordAddress << endl;
	cout << "OBATargetMachine::drivingControlsStateWordAddress \t" << OBATargetMachine::drivingControlsStateWordAddress << endl;
	cout << "OBATargetMachine::controlPanelInterruptWordAddress \t" << OBATargetMachine::controlPanelInterruptWordAddress << endl;
	cout << "OBATargetMachine::throttleCommandWordAddress \t\t" << OBATargetMachine::throttleCommandWordAddress << endl;
	cout << "OBATargetMachine::displayBufferAddress \t\t\t" << OBATargetMachine::displayBufferAddress << endl;	
	cout << "OBATargetMachine::ledCommandByteAddress \t\t" << OBATargetMachine::ledCommandByteAddress << endl;	

	cout << " " << endl;

	//cout << "OBATargetMachine::interruptVector [interruptCardinal] \t" << OBATargetMachine::interruptVector [interruptCardinal] << endl;

	cout << " " << endl;

	cout << "OBATargetMachine::allInterrupts \t" << OBATargetMachine::allInterrupts << endl;
	cout << "OBATargetMachine::noInterrupt \t\t" << OBATargetMachine::noInterrupt << endl;

	cout << " " << endl;

	cout << "OBATargetMachine::enabledInterruptsRegister \t" << OBATargetMachine::enabledInterruptsRegister << endl;
	cout << "OBATargetMachine::autoResetInterruptsRegister \t" << OBATargetMachine::autoResetInterruptsRegister << endl;

	cout << " " << endl;

	//pointer dereference, using unsigned short casting since ori is void pointer
    //cout << *(unsigned short *) OBATargetMachine::ledCommandByteAddress;

    cout << " " << endl;

    //attempt to write to that
	unsigned short ledAll = 131;
	//*(unsigned short *) OBATargetMachine::ledCommandByteAddress = ledAll;

    cout << *(unsigned short *) OBATargetMachine::ledCommandByteAddress;

	//cout << &OBATargetMachine::ledCommandByteAddress;

	//OBATargetMachine::setPeriodicTimer(5,5);
	//cout << "\r\nHello World!\r\n";
	//cout << "\r\nPress any key to continue...\r\n";
	//cin.get();
	//errorful         *data = (bool)input2;
	//supposedtowork   *(bool *) data = (bool) input2;


    int i=0;
	msg=msg1;
	DisplayBufferAddress	 *display;

try {
// initialisation of the interrupt vector

		OTM::interruptVector[IT_controlPanel] = periodicHandler;
        OTM::interruptVector[IT_drivingControls] = periodicHandler;
		OTM::interruptVector[IT_timer] = periodicHandler;
// set the timer

		OTM::setPeriodicTimer(periodInMillisecond, 0);
// enable the interrupt

        OTM::enabledInterruptsRegister = allObaRelatedInterrupts;

// keep the display buffer 

		display =  (DisplayBufferAddress*)(OTM::displayBufferAddress);
		


// infinite loop

 for (;;)
	{
		
	
// write the message to the display

		for (int j=0;j<20;j++)
			display->displaymessage[j]=msg[j];
// idle the CPU		

		OTM::idleWait (75);
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
