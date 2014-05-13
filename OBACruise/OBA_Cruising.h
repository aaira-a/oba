#ifndef OBA_CRUISING_H
#define OBA_CRUISING_H

class OBA_Cruising {
	public:
		OBA_Cruising();
		static bool isActive;
		static bool isSuspended;
		static int cruisingSpeed;

		static void activateCruising();
		static void stopCruising();
		static void suspendCruising();
		static void resumeCruising();
		static bool validateCruisingRequest();
		static void requestCurrentSpeed();     		// delegate call to shaft ? or move method to shaft ?
		static void setCruisingSpeed();
		static void requestCalibrationStatus();		// delegate call to calibration controller ? or move method to calibration ?
		static void requestDrivingStationStatus();	// delegate call to dsta ? or move method to dsta?
		static void requestMaintainSpeed();			// delegate call to thro? or maintain logic here ?
		static void requestStopMaintainSpeed();		// delegate call to thro? or maintain logic here ?
};

#endif