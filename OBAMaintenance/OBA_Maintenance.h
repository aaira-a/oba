#ifndef OBA_MAINT_H
#define OBA_MAINT_H

class OBA_Maintenance {
	public:
		OBA_Maintenance();

		static void maintenanceRoutine();
		static void maintenanceChecker();
		static unsigned int getCurrentMileage();
		static void debugger(unsigned int overrideMileage);
};

typedef OBA_Maintenance		MAINT;

#endif