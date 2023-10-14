#include "aggregator/avg_aggregator.hpp"

void AvgAggregator::feed_data(const int data) {
  sum += data;
  ++count;
}

double AvgAggregator::evaluate() const { return double(sum) / count; }

void AvgAggregator::init() {
  sum = 0;
  count = 0;
}