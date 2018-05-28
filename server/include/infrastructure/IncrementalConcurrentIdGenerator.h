//
// Created by mwypych on 28/05/18.
//

#ifndef JIMP_EXERCISES_INCREMENTALCONCURRENTIDGENERATOR_H
#define JIMP_EXERCISES_INCREMENTALCONCURRENTIDGENERATOR_H

#include <atomic>
#include "IdGenerator.h"

class IncrementalConcurrentIdGenerator : public IdGenerator {
 public:
  IncrementalConcurrentIdGenerator(unsigned int current_value) : current_value_(current_value) {}

  unsigned int NextId() override {
    return current_value_++;
  }

 private:
  std::atomic<unsigned int> current_value_;
};

#endif //JIMP_EXERCISES_INCREMENTALCONCURRENTIDGENERATOR_H
