#ifndef RANDOM_H
#define RANDOM_H

  #include <random>

  namespace Random
  {
    std::mt19937 generator{ std::random_device{}() };

    int getRandomInt(int min, int max)
    {
      std::uniform_int_distribution dist{ min, max };
      return dist(generator);
    }
  }

#endif
