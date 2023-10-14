#ifndef MIN_AGGREGATOR_H_
#define MIN_AGGREGATOR_H_

#include "aggregator.hpp"

/**
 * @brief Aggregate values and calculate the minimum value
 *
 */
class MinAggregator : public Aggregator {
 private:
  int min;

 public:
  MinAggregator() : Aggregator{"Min"} { init(); }

  void feed_data(const int data) override;

  double evaluate() const override;

  void init() override;
};

#endif