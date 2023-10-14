#ifndef AGGREGATE_H_
#define AGGREGATE_H_

#include <string>

#define LARGE_INT 100000000

/**
 * Interface for aggregators.
 * Aggregate data and evaluate such as min, max, average, etc.
 * usage: feed data -> evaluate -> init -> (loop)
 */
class Aggregator {
 private:
  /** name of the aggregator to be displayed */
  const std::string name;

 public:
  /** return the name of the aggregator */
  std::string get_name() const { return name; }

  /** constructor */
  Aggregator(std::string name_) : name{name_} {}

  /** feed data to aggregator */
  virtual void feed_data(const int data) = 0;

  /** evaluate the aggregated data */
  virtual double evaluate() const = 0;

  /** initialize the aggregator */
  virtual void init() = 0;

  virtual ~Aggregator() {}
};

#endif