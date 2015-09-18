#ifndef ELLOOP_LOADVEHICLE_H
#define ELLOOP_LOADVEHICLE_H
#include "Vehicle.h"

class LoadVehicle : virtual public Vehicle {
public:
  LoadVehicle(const char* type = "car", int numberOfWheels = 6
    , double loadCapacity = 500, double towingCapacity_ = 5000
    , double gasTankSize = 200, double fuelConsumption = 6);

  ~LoadVehicle();

  void setLoadData(double loadCapacity, double towingCapacity);

  void printLoadVehicle() const;

	// derived methods.
  virtual void printSpecification() const;
  virtual double computeTravelDistance() const;

  double getTowingCapacity() const { return towingCapacity_; }
  void setTowingCapacity(double val) { towingCapacity_ = val; }

  double getLoadCapacity() const { return loadCapacity_; }
  void setLoadCapacity(double val) { loadCapacity_ = val; }

  int getNumberOfWheels() const { return numberOfWheels_; }
  void setNumberOfWheels(int val) { numberOfWheels_ = val; }

private:
  int numberOfWheels_;
  double loadCapacity_;
  double towingCapacity_;
};

#endif
