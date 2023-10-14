#ifndef MAX_AGGREGATOR_H_
#define MAX_AGGREGATOR_H_

#include "aggregator.hpp"

/**
 * @brief Aggregate values and calculate the maximum value
 *
 */
class MaxAggregator : public Aggregator {
 private:
  int max;

 public:
  MaxAggregator() : Aggregator{"Max"} { init(); }

  void feed_data(const int data) override;

  double evaluate() const override;

  void init() override;
};

#endif