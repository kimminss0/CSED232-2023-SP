#ifndef AVG_AGGREGATOR_H_
#define AVG_AGGREGATOR_H_

#include "aggregator.hpp"

/**
 * @brief Aggregate values and calculate the average value
 *
 */
class AvgAggregator : public Aggregator {
 private:
  int sum;
  int count;

 public:
  AvgAggregator() : Aggregator{"Min"} { init(); }

  void feed_data(const int data) override;

  double evaluate() const override;

  void init() override;
};

#endif