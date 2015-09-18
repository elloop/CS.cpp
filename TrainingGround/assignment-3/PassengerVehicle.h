#ifndef ELLOOP_PASSENGERVEHICLE_H
#define ELLOOP_PASSENGERVEHICLE_H
#include "Vehicle.h"

class PassengerVehicle : virtual public Vehicle {
public:
  PassengerVehicle(const char* type = "car", int numberOfPassenger=5
    , double gasTankSize = 100.0, double fuelConsumption = 11.0);

  virtual ~PassengerVehicle();

  int getNumberOfPassenger() const { return numberOfPassenger_; }
  void setNumberOfPassenger(int val) { numberOfPassenger_ = val; }

  void printPassengerVehicle() const;

	// derived methods.
  virtual void printSpecification() const;
  virtual double computeTravelDistance() const;
private:
  int numberOfPassenger_;
};

#endif
