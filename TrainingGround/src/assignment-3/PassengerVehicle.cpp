#include "PassengerVehicle.h"
#include "common.h"

/***************************************************************************************
	函数名称:  PassengerVehicle
	函数描述:  constructor.
	输入参数:
	输出参数: N/A
	返回值:   N/A
	备注:     N/A
 ***************************************************************************************/
PassengerVehicle::PassengerVehicle ( const char * type /*= "car"*/, int numberOfPassenger /*=5 */
																		 , double gasTankSize /*= 100.0*/, double fuelConsumption /*= 11.0*/ )
	: Vehicle ( type, "ottawa01", gasTankSize, fuelConsumption )
	, numberOfPassenger_ ( numberOfPassenger )
{ }

void PassengerVehicle::printSpecification() const {
	Vehicle::printSpecification();                // Vehicle's print.
	printPassengerVehicle();                      // self's print.
	cr;
}

void PassengerVehicle::printPassengerVehicle() const {
	ps ( numberOfPassenger_ );
}

double PassengerVehicle::computeTravelDistance() const {
	double distance = Vehicle::computeTravelDistance();
	if ( numberOfPassenger_ < 6 ) {
		return distance;
	} else {
		return distance * ( 100 - ( numberOfPassenger_ - 5 ) * 2.5 ) / 100;
	}
}

PassengerVehicle::~PassengerVehicle() { }
