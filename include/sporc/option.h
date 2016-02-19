#ifndef _OPTION_H_
#define _OPTION_H_

#include <sporc/option.h>

#include <algorithm>

namespace sporc{


/**
TODO: comment me!
*/
  class Option{
  public:
    /// option type definition
    typedef enum{OT_PUT, OT_CALL} OptionT;

    /// std ctor
    Option(OptionT type, double maturity = 0., double strike = 0.):
      type_(type), Maturity_(maturity), StrikePrice_(strike), OptionPrice_(0.)
      { }

    /// copy ctor
    Option(Option const& option):
      type_(option.type_), Maturity_(option.Maturity_),
      StrikePrice_(option.StrikePrice_), OptionPrice_(option.OptionPrice_)
      { }


    /// assignment operator
    Option& operator=(Option const& option){
      if(this != &option){
        // copy values
        // TODO
      }
      return *this;
    }

    /// return option type
    OptionT getType() const
      { return type_; }

    /// abstract payoff method
    virtual
      double getPayoff(double S_T) const = 0;

    /// return option price
    double getOptionPrice() const
      { return OptionPrice_; }

    /// set option price
    void setOptionPrice(double price)
      { OptionPrice_ = price; }

    /// return Maturity
    double getMaturity() const
      {
        return Maturity_;
      }

    /// return StrikePrice
    double getStrikePrice() const
      {
        return StrikePrice_;
      }

  protected:
    Option();

    double  Maturity_;
    double  StrikePrice_;
    double  OptionPrice_;
    OptionT type_;
  };


/**

*/
class Equity: public Option{
public:
  Equity(Option::OptionT type, double maturity = 0., double strike = 0.):
    Option(type, maturity, strike)
    { }

};



/**

*/
class European: public Equity{
 public:

  ///
  European(Option::OptionT type, double maturity = 0., double strike = 0.):
    Equity(type, maturity, strike)
    { }

  ///
  European(European const& european);

  ///
  European& operator=(European const& european);


  // implement Option interface
  // --------------------------

  double getPayoff(double S_T) const
    {
      switch(this->type_){
      case Option::OT_PUT:
        return std::max(this->StrikePrice_ - S_T, 0.);
      case Option::OT_CALL:
        return std::max(S_T - this->StrikePrice_, 0.);
      default:
        assert(0);
      }
    }


 private:
  European();
};


}

#endif
