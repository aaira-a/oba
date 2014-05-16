#ifndef OBA_CALIB_H
#define OBA_CALIB_H

class OBA_Calibration {
	public:
		OBA_Calibration();

		static void startCalibration();
		static void stopCalibration();

};

typedef OBA_Calibration	CALIB;

#endif