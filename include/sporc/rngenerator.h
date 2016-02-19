#ifndef _RNGENERATOR_H_
#define _RNGENERATOR_H_

#include <cstdlib>
#include <ctime>            // std::time

/*
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/generator_iterator.hpp>
*/

namespace sporc{


/**
   Generic random number generator interface.
*/
  class RNGenerator{
  public:
    /// get random number (interface method)
    virtual
    double operator()() const = 0;
  };



/**
   Linear congruential generator.
*/
  class LCG:
    public RNGenerator{
    public:
    /// ctor
    LCG(long seed = 123456)
      {
        srand(seed);
      }


    ///
    double operator()() const
      {
        double x1, x2, w, y1, y2;
 
        do {
          x1 = 2.0 * (double)rand() / ((double)(RAND_MAX)+1.) - 1.0;
          x2 = 2.0 * (double)rand() / ((double)(RAND_MAX)+1.) - 1.0;
          w = x1 * x1 + x2 * x2;
        } while ( w >= 1.0 );

        w = sqrt( (-2.0 * log( w ) ) / w );
        y1 = x1 * w;
        y2 = x2 * w;

        return y1;
      }
  };



/**
   Boost random number generator class.
*/
/*class BoostRNGenerator:
  public RNGenerator{
 public:

  /// random number types
  typedef enum {RNG_MINSTD, RNG_MT19937, RNG_ECUYER1988}       RNG_T;

  typedef boost::normal_standard<>                                              ns_dist_T;
  typedef boost::variate_generator<boost::minstd_rand&, ns_distribution_type>   minstd_gen_T;
  typedef boost::generator_iterator<minstd_gen_T>                               minstd_it_T;
  typedef boost::variate_generator<boost::mt19937_rand&, ns_distribution_type>  mt19937_gen_T;
  typedef boost::generator_iterator<minstd_gen_T>                               mt19937_it_T;
  typedef boost::variate_generator<boost::ecuyer1988_rand&, ns_distribution_type> ecuyer1988_gen_T;
  typedef boost::generator_iterator<minstd_gen_T>                               ecuyer1988_it_T;

  /// ctor
  RNGenerator(RNG_T type = RNG_MINSTD):
    type_(type),
    gen0(g0_, ns_dist_T(0.,1.)), gen1(g1_, ns_dist_T(0., 1.)), gen2(g2_, ns_dist(0., 1.)),
    it0(&gen0), it1(&gen1), it2(&gen2)
    { }


  /// return next random number
  double operator() const
    {
      switch(type_){
        case RNG_MINSTD:
          return *it0++;
        break;
        case RNG_MT19937:
          return *it1++;
        break;
        case RNG_ECUYER1988:
          return *it2++;
        break;
      default:
        assert(!"invalid random generator type");
      }
    }


 protected:
  RNG_T       type_;

  // available generators/iterators
  minstd_gen_T          gen0;
  minstd_it_T           it0;
  mt19937_gen_T         gen1;
  mt19937_it_T          it1;
  ecuyer1988_gen_T      gen2;
  ecuyer1988_it_T       it2;

  static boost::minstd_rand     g0_;
  static boost::mt19937_rand    g1_;
  static boost::ecuyer1988_rand g2_;
};


// initialise static members
boost::minstd_rand      BoostRNGenerator::g0_(42u);
boost::mt19937_rand     BoostRNGenerator::g1_(42u);
boost::ecuyer1988_rand  BoostRNGenerator::g2_(42u);
*/
}

#endif
