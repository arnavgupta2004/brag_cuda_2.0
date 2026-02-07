// main.cpp
#include "TspDecoder.h"
#include <brkga-cuda/Brkga.hpp>
#include <brkga-cuda/BrkgaConfiguration.hpp>
#include <brkga-cuda/DecodeType.hpp>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  // input
  unsigned n;
  std::cin >> n;
  std::vector<std::pair<float, float>> points(n);
  for (unsigned i = 0; i < n; ++i)
    std::cin >> points[i].first >> points[i].second;

  // setup
  TspDecoder decoder(points);
  auto dt = box::DecodeType::fromString("cpu-permutation");
            // or `box::DecodeType(false, false, false)`

  auto config =
      box::BrkgaConfiguration::Builder()
          .decoder(&decoder)
          .decodeType(dt)
          .numberOfPopulations(3)
          .populationSize(256)  // works better with powers of 2
          .chromosomeLength(n)
          .numberOfElites(25)  // or `.elitePercentage(.10)`
          .numberOfMutants(25)  // or `.mutantPercentage(.10)`
          .rhoe(.75)
          .numberOfElitesToExchange(3)
          .seed(1)
          .gpuThreads(256)  // works better with powers of 2
          .ompThreads(6)  // number of CPU threads using OpenMP
          .build();

  box::Brkga brkga(config);
  unsigned maxGenerations = 1000;  // or other stopping condition
  unsigned exchangeInterval = 25;  // optional
  unsigned updateRhoeInterval = 200;  // optional

  // execution
  for (unsigned g = 1; g <= maxGenerations; ++g) {
    brkga.evolve();
    if (g % exchangeInterval == 0)
      brkga.exchangeElites();
    if (g % updateRhoeInterval == 0) {
      // intensifying the search around the elites
      brkga.config.setRhoe(brkga.config.rhoe() + .05);

      // other parameters can be updated too, e.g.:
      //   `brkga.config.setNumberOfElites(10)`
      //   `brkga.config.setOmpThreads(1)`
      //   `brkga.config.setNumberOfElitesToExchange(5)`
    }
  }

  // output
  std::cout << brkga.getBestFitness() << '\n';
  return 0;
}