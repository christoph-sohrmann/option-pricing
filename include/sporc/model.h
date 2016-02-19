#ifndef _MODEL_H_
#define _MODEL_H_

#include <sporc/option.h>

#include <cmath>
#include <cassert>

namespace sporc{


/**

*/
  class Model{
  public:
    /// ctor
    Model(Option& option, double sigma, double dt, double r, double S_0):
      Option_(option), sigma_(sigma), dt_(dt), r_(r), S_0_(S_0)
      { }


    /// model interface: evaluation
    virtual
    double operator()(double RN) const = 0;

    /// return option instance
    Option& getOption()
      { return Option_; }

  protected:
    Model();

    Option&       Option_;

    double        sigma_;
    double        dt_;
    double        r_;
    double        S_0_;
  };


/**
   Geometric Brownian Motion implementation.
*/
class GBM: public Model{
 public:
  /// ctor
  GBM(Option& option, double sigma, double dt, double r, double S_0):
    Model(option, sigma, dt, r, S_0)
    { }


  /// implement model interface
  double operator()(double RN) const
    {
      double t = this->S_0_ * exp( (this->r_ - .5 * this->sigma_ * this->sigma_ ) * this->Option_.getMaturity() + this->sigma_ * sqrt(this->Option_.getMaturity()) * RN );
      return t;
    }

 private:
};

}

#endif
