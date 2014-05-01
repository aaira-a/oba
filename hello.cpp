#include <iostream>
#include "OBATargetMachine.h"
#include "PortsLayout.h"
#pragma comment(lib, "OBAVirtualTarget.lib")

using namespace std;

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
    cout << *(unsigned short *) OBATargetMachine::ledCommandByteAddress;

    cout << " " << endl;

    //attempt to write to that
	unsigned short ledAll = 1;
	*(unsigned short *) OBATargetMachine::ledCommandByteAddress = ledAll;

    cout << *(unsigned short *) OBATargetMachine::ledCommandByteAddress;

	//cout << &OBATargetMachine::ledCommandByteAddress;

	//OBATargetMachine::setPeriodicTimer(5,5);
	//cout << "\r\nHello World!\r\n";
	//cout << "\r\nPress any key to continue...\r\n";
	//cin.get();
	//errorful         *data = (bool)input2;
	//supposedtowork   *(bool *) data = (bool) input2;
}