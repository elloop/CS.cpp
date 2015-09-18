#ifndef ELLOOP_EMERGECYVEHICLE_H
#define ELLOOP_EMERGECYVEHICLE_H
#include "PassengerVehicle.h"
#include "LoadVehicle.h"
#include "EmergencyEquipment.h"

class EmergecyVehicle : public PassengerVehicle, public LoadVehicle
		, public EmergencyEquipment {
public:
	EmergecyVehicle ( const char * type = "car", const char * driver = "",
										const char * station = "", int numWorkers = 5 );

	EmergecyVehicle ( const EmergecyVehicle & other );
	virtual ~EmergecyVehicle();
	EmergecyVehicle & operator = ( const EmergecyVehicle & other );

	int setNumWorkers() const { return numWorkers_; }
	void getNumWorkers ( int val ) { numWorkers_ = val; }

	const char * getDriver() const { return driver_; }
	void setDriver ( const char * val );

	const char * getStation() const { return station_; }
	void setStation ( const char * val );

	void setAssignment ( const char * driver, const char * station );

	void printEmergencyVehicle() const;

	// derived methods.
	virtual void printSpecification() const;
	virtual double computeTravelDistance() const;

private:
	int numWorkers_;
	char * driver_;
	char * station_;
};

#endif
