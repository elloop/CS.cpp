#include "EmergecyVehicle.h"
#include "common.h"
#include <cstring>

/***************************************************************************************
	函数名称:  EmergencyVehicle
	函数描述:  constructor.
	输入参数:
	输出参数: N/A
	返回值:   N/A
	备注:     N/A
 ***************************************************************************************/
EmergecyVehicle::EmergecyVehicle ( const char * type /*= "car"*/, const char * driver
																	 , const char * station, int numWorkers /*= 5*/ )
	: Vehicle ( type, "ottawa01", 100, 11 )
	, PassengerVehicle ( type )
	, LoadVehicle ( type )
	, EmergencyEquipment()
	, numWorkers_ ( numWorkers )
{
	// set driver.
	if ( driver ) {
		driver_ = new char [strlen ( driver ) + 1];
		strcpy ( driver_, driver );
	}
	else {
		driver_ = new char [1];
		strcpy ( driver_, "" );
	}

	// set station.
	if ( station ) {
		station_ = new char [strlen ( station ) + 1];
		strcpy ( station_, station );
	}
	else {
		station_ = new char [1];
		strcpy ( station_, "" );
	}
}

/***************************************************************************************
	函数名称:  EmergencyVehicle
	函数描述:  copy constructor.
	输入参数:
	输出参数: N/A
	返回值:   N/A
	备注:     N/A
 ***************************************************************************************/
EmergecyVehicle::EmergecyVehicle ( const EmergecyVehicle & other )
	: Vehicle ( other )
	, PassengerVehicle ( other )
	, LoadVehicle ( other )
	, EmergencyEquipment ( other )
	, numWorkers_ ( other.numWorkers_ )
{
	driver_ = new char [strlen ( other.driver_ ) + 1];
	strcpy ( driver_, other.driver_ );

	station_ = new char [strlen ( other.station_ ) + 1];
	strcpy ( station_, other.station_ );
}

EmergecyVehicle & EmergecyVehicle::operator= ( const EmergecyVehicle & other ) {
	if ( this != &other ) {
		Vehicle::operator= ( other );
		PassengerVehicle::operator= ( other );
		LoadVehicle::operator= ( other );
		EmergencyEquipment::operator= ( other );

		delete [] driver_;
		delete [] station_;

		driver_ = new char [strlen ( other.driver_ ) + 1];
		strcpy ( driver_, other.driver_ );

		station_ = new char [strlen ( other.station_ ) + 1];
		strcpy ( station_, other.station_ );

		numWorkers_ = other.numWorkers_;
	}
	return *this;
}

void EmergecyVehicle::setDriver ( const char * val ) {
	// avoid null, and self set.
	if ( val && val != driver_  ) {
		delete [] driver_;
		driver_ = new char [strlen ( val ) + 1];
		strcpy ( driver_, val );
	}
}

void EmergecyVehicle::setStation ( const char * val ) {
	// avoid null, and self set.
	if ( val && val != station_ ) {
		delete [] station_;
		station_ = new char [strlen ( val ) + 1];
		strcpy ( station_, val );
	}
}

void EmergecyVehicle::printSpecification() const {
	Vehicle::printSpecification();                // Vehicle's
	printLoadVehicle();                           // LoadVehicle's
	printPassengerVehicle();                      // PassengerVehicle's
	EmergencyEquipment::printSpecification();     // EmergencyEquipment's
	printEmergencyVehicle();                      // self's
	cr;
}

void EmergecyVehicle::printEmergencyVehicle() const {
	ps ( numWorkers_ );
	ps ( driver_ );
	ps ( station_ );
}

double EmergecyVehicle::computeTravelDistance() const {
	double lvDis = LoadVehicle::computeTravelDistance();
	double pvDis = PassengerVehicle::computeTravelDistance();
	return ( lvDis < pvDis ) ? lvDis : pvDis;
}

EmergecyVehicle::~EmergecyVehicle() {
	delete [] driver_;
	delete [] station_;
}

