#include "Vehicle.h"
#include "common.h"
#include <cstring>

/***************************************************************************************
	函数名称:  Vehicle::Vehicle
	函数描述:  constructor.
	输入参数:
	输出参数: N/A
	返回值:   N/A
	备注:     N/A
 ***************************************************************************************/
Vehicle::Vehicle ( const char * type, const char * licensePlate, double gasTankSize, double fuelConsumption )
  : gasTankSize_ ( gasTankSize ), fuelConsumption_ ( fuelConsumption ) {

		// set type.
    if ( type ) {
      type_ = new char[strlen ( type ) + 1];
      if ( type_ ) {
        strcpy ( type_, type );
      }
    } else {
      type_ = new char[1];
      strcpy(type_, "");
    }

		// set licensePlate_.
    if ( licensePlate && strlen(licensePlate) < 9 ) {
      strcpy(licensePlate_, licensePlate);
    } else {
      memset(licensePlate_, 0, 9);
    }

		// set make_, defualt china.
    make_ = new char[strlen("china") + 1];
    strcpy(make_, "china");
}  

// copy constructor.
Vehicle::Vehicle ( const Vehicle & other ) 
  : gasTankSize_(other.gasTankSize_), fuelConsumption_(other.fuelConsumption_) {

    type_ = new char[strlen(other.type_) + 1];
    strcpy(type_, other.type_);

    make_ = new char[strlen(other.make_) + 1];
    strcpy(make_, other.make_);

    strcpy(licensePlate_, other.licensePlate_);
}  

Vehicle::~Vehicle () {
    delete [] type_;
    delete [] make_;
}  

// assignment operator.
Vehicle & Vehicle::operator = ( const Vehicle & other ) {
  if ( this != &other ) {
    type_ = new char[strlen(other.type_) + 1];
    strcpy(type_, other.type_);

    make_ = new char[strlen(other.make_) + 1];
    strcpy(make_, other.make_);

    strcpy(licensePlate_, other.licensePlate_);
    gasTankSize_ = other.gasTankSize_;
    fuelConsumption_ = other.fuelConsumption_;
  }
  return *this;
}  

void Vehicle::setMake ( const char * value ) {
	// avoid null, and self set.
  if ( value ) {
    if ( value != make_ ) {
      delete [] make_;
      make_ = new char[strlen ( value ) + 1];
      strcpy ( make_, value );
    }
  }
}		

void Vehicle::setType_ ( const char * value ) {
	// avoid null, and self set.
  if ( value ) {
    if ( value != type_ ) {
      delete [] type_;
      type_ = new char[strlen ( value ) + 1];
      strcpy ( type_, value );
    }
  }
}		

void Vehicle::setLicensePlate_ ( const char * value ) {
  if ( value && (strlen(value) <= 8)) {
    if ( value != licensePlate_ ) {
      strcpy(licensePlate_, value);
    }
  }
}		

double Vehicle::computeTravelDistance() const
{
  return fuelConsumption_ * gasTankSize_;
}

void Vehicle::printSpecification (  ) const {
  ps ( type_ );
  ps ( make_ );
  ps ( gasTankSize_ );
  ps ( fuelConsumption_ );
  ps ( licensePlate_ );
}		

