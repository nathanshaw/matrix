#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  public:
    virtual void poll();
    virtual void setup();
  private:
    // identity
    int _id;
    String _type;
    int _val;
    int _past_vals[];
    String _smoothing; // the type of smoothing applied
};

#endif // SENSOR_H
