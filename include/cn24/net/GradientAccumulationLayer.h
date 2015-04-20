/**
 * @file GradientAccumulationLayer.h
 * @class GradientAccumulationLayer
 * @brief Accumulates the gradients at the outputs
 *
 * @author Clemens-Alexander Brust (ikosa dot de at gmail dot com)
 */

#ifndef CONV_GRADIENTACCUMULATIONLAYER_H
#define CONV_GRADIENTACCUMULATIONLAYER_H

#include <string>

#include "Layer.h"
#include "NetGraph.h"
#include "CombinedTensor.h"

namespace Conv {

class GradientAccumulationLayer: public Layer {
public:
  GradientAccumulationLayer(unsigned int output_count);

  // Layer implementations
  bool CreateOutputs (const std::vector< CombinedTensor* >& inputs,
                      std::vector< CombinedTensor* >& outputs);
  bool Connect (const std::vector< CombinedTensor* >& inputs,
                const std::vector< CombinedTensor* >& outputs,
                const NetStatus* status );
  void FeedForward();
  void BackPropagate();

  std::string GetLayerDescription() { return "Gradient Accumulation Layer"; }
  void CreateBufferDescriptors(std::vector< NetGraphBuffer >& buffers) {
    for(unsigned int i = 0; i < output_count_; i++) {
      NetGraphBuffer buffer;
      buffer.description = "Output " + i;
      buffers.push_back(buffer);
    }
  };
private:
  std::vector<CombinedTensor*> outputs_;
  CombinedTensor* input_ = nullptr;
  
  unsigned int output_count_ = 0;
  unsigned int samples_ = 0;
  unsigned int elements_per_sample_ = 0;
};

}
#endif
