/*
* MIT License
*
* Copyright (c) 2020 International Business Machines
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef SIMPLETRAININGSET_H_
#define SIMPLETRAININGSET_H_

#include <vector>
#include "DoubleMatrixArray.h"
#include "DoubleMatrix.h"

struct Batch {
  DoubleMatrixArray samples;
  DoubleMatrixArray labels;
  Batch(){}
};


/** A class for holding data for inference.
 * 
 * It may hold just the inputs, or both inputs and expected outputs
 * (usually refered to as labels, or ground truth).
 * 
 * If it contains both it can be used for training, or for estimating
 * the accuracy of a given model. Otherwise it can only be used for inference.
 * 
 * It loads the data from an h5 file, and divides it to batches
 * according to a specified batch size.
 * 
 */
class SimpleTrainingSet {

  int batchSize;
  int numLabels;
  int numSamples;
  std::vector<Batch> batches;

  void loadSamples(const std::string&sampleFile,const std::string& sampleWeights);

  void loadLabels(const std::string&labelFile,const std::string& labelWeights);

public:
  SimpleTrainingSet(int batchSize) : batchSize(batchSize){}
  ~SimpleTrainingSet(){}

  void loadFromH5(const std::string&sampleFile,const std::string& sampleWeights,
          const std::string&labelFile,const std::string& labelWeights);

  void loadFromH5(const std::string&sampleFile,const std::string& sampleWeights);

  inline const DoubleMatrixArray& getSamples(int batch) const {
    return batches[batch].samples;
  }
  inline const DoubleMatrixArray& getLabels(int batch) const {
    return batches[batch].labels;
  }
  inline int getNumBatches() const {
    return batches.size();
  }
  inline int getBatchSize() const {
    return batchSize;
  }
  inline const DoubleMatrix& getSample(int batch, int i) const {
    return batches[batch].samples.getMat(i);
  }
  inline const DoubleMatrix& getLabel(int batch, int i) const {
    return batches[batch].labels.getMat(i);
  }
  inline int getNumSamples() const {
    return numSamples;
  }
  inline int getNumLabels() const {
    return numLabels;
  }
};

std::ostream& operator<<(std::ostream&out, const SimpleTrainingSet&ts);

#endif
