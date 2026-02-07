// TspDecoder.h
#include <brkga-cuda/Decoder.hpp>
#include <cmath>
#include <utility>
#include <vector>

class TspDecoder : public box::Decoder {
private:
  std::vector<float> distances;  // "matrix" of 2d distances

public:
  // required since we made just one overload
  using box::Decoder::decode;

  TspDecoder(const std::vector<std::pair<float, float>>& points)
      : distances(points.size() * points.size(), 0.0f) {
    const auto n = points.size();
    for (unsigned i = 0; i < n; ++i)
      for (unsigned j = i + 1; j < n; ++j)
        distances[i * n + j] = distances[j * n + i] =
            std::hypotf(points[i].first - points[j].first,
                        points[i].second - points[j].second);
  }

  // implement a deterministic decoder for permutations
  box::Fitness decode(
      const box::Chromosome<box::GeneIndex>& tour) const override {
    const auto n = config->chromosomeLength();  // from box::Decoder
    float fitness = distances[tour[0] * n + tour[n - 1]];  // use operator[]
    for (unsigned i = 1; i < n; ++i)
      fitness += distances[tour[i - 1] * n + tour[i]];
    return fitness;
  }
};