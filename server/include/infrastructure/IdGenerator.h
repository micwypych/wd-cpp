//
// Created by mwypych on 28/05/18.
//

#ifndef JIMP_EXERCISES_IDGENERATOR_H
#define JIMP_EXERCISES_IDGENERATOR_H

class IdGenerator {
 public:
  virtual unsigned int NextId() =0;
  virtual ~IdGenerator() = default;
};

#endif //JIMP_EXERCISES_IDGENERATOR_H
