#ifndef OBA_CRUISING_H
#define OBA_CRUISING_H

class OBA_Cruising {
	public:
		OBA_Cruising();

		static void activateCruising(int ifZeroisForResume);
		static void stopCruising();
		static void startAccelerationRequest();
		static void stopAccelerationRequest();
		static void suspendCruising();
		static void resumeCruising();
		static bool validateCruisingRequest();

		static bool getIsActive();
		static bool FisSuspended(); 
		static int getCruisingSpeed();

};

typedef OBA_Cruising	CRUISE;

#endif