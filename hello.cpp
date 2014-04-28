#include <iostream>
#include "OBATargetMachine.h"
#include "PortsLayout.h"
#pragma comment(lib, "OBAVirtualTarget.lib")

using namespace std;

int main(){

	
	cout << OBATargetMachine::pulseCounterWordAddress;
	cout << "\r\n  \r\n";
	//OBATargetMachine::setPeriodicTimer(5,5);
	cout << "\r\nHello World!\r\n";
	cout << "\r\nPress any key to continue...\r\n";
	cin.get();
}