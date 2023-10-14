#include "aggregator/max_aggregator.hpp"

void MaxAggregator::feed_data(const int data) {
  if (max < data) {
    max = data;
  }
}

double MaxAggregator::evaluate() const { return double(max); }

void MaxAggregator::init() { max = -1; }