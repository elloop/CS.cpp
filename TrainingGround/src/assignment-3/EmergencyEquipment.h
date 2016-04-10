#ifndef ELLOOP_EMERGENCYEQUIPMENT_H
#define ELLOOP_EMERGENCYEQUIPMENT_H
class EmergencyEquipment {
public:
  EmergencyEquipment(int sirenNoiseDistance = 500, int numBeds = 2);

  virtual ~EmergencyEquipment();

  int getSirenNoiseDistance() const { return sirenNoiseDistance_; }
  void setSirenNoiseDistance(int val) { sirenNoiseDistance_ = val; }

  int getNumBeds() const { return numBeds_; }
  void setNumBeds(int val) { numBeds_ = val; }

  virtual void printSpecification() const;
private:
  int sirenNoiseDistance_;
  int numBeds_;
};
#endif
