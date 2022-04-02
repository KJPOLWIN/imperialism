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

    bool testForProbability(double chance)
    {
      int threshold{ static_cast<int>(chance * 100) };
      return getRandomInt(1, 100) <= threshold;
    }
  }

#endif
