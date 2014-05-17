#ifndef OBA_MAINT_H
#define OBA_MAINT_H

class OBA_Maintenance {
	public:
		OBA_Maintenance();

		static void maintenanceRoutine();
		static unsigned int getCurrentMileage();
};

typedef OBA_Maintenance		MAINT;

#endif