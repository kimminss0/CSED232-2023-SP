#include "aggregator/min_aggregator.hpp"

void MinAggregator::feed_data(const int data) {
  if (min > data) {
    min = data;
  }
}

double MinAggregator::evaluate() const { return double(min); }

void MinAggregator::init() { min = LARGE_INT; }