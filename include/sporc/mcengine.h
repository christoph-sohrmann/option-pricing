#ifndef _MCENGINE_H_
#define _MCENGINE_H_

#include <sporc/rngenerator.h>

namespace sporc{

/**

*/
  class MCEngine{
  public:
    /// ctor
    MCEngine()
      { }


    ///
    void run(RNGenerator const& rng, Model& model,
             double r, double confidence, double accuracy){
      assert(confidence > 0. && accuracy > 0. && "parameters invalid");
      // TODO
      model.getOption().setOptionPrice(1.);
    }


    ///
    void run(RNGenerator const& rng, Model& model,
             double r, int numSims){
      assert(numSims > 0 && "numSims invalid");

      // MC loop
      double sum = 0.;
      for(int run = 0; run < numSims; ++run){
        double rn = rng();
        sum += model.getOption().getPayoff( model(rn) );
      }
      sum /= (double)numSims;
      model.getOption().setOptionPrice(exp(-r * model.getOption().getMaturity()) * sum);
    }


  protected:
  };


}

#endif
