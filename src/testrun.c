#include <iostream>

#include <sporc/poptions.h>
#include <sporc/model.h>
#include <sporc/option.h>
#include <sporc/mcengine.h>
#include <sporc/rngenerator.h>

using namespace sporc;

int main(int argc, char** argv){
  // read in program parameters
  assert(argc == 2 && "wrong number of arguments");
  POptions::init(argv[1]);  
  
  //POptions::test();
    
  // create option
  European european(POptions::getParam<Option::OptionT>("option","type"),
                    POptions::getParam<double>("option","maturity"),
                    POptions::getParam<double>("option","strikeprice"));

  // create model
  GBM gbm(european, POptions::getParam<double>("equity","volatility"),
          POptions::getParam<double>("solver","timestep"),
          POptions::getParam<double>("option","interestrate"),
          POptions::getParam<double>("equity","currentprice"));

  // create RNG
  LCG generator;

  // create engine
  MCEngine MC;

  // MC solve
  MC.run(generator,gbm,
         POptions::getParam<double>("option","interestrate"),
         POptions::getParam<int>("solver","steps"));
/*  MC.run(generator, gbm,
         POptions::getParam<double>("confidence"),
         POptions::getParam<double>("accuracy"));*/

  // print out result
  std::cout<<"\nfinal price: "<<european.getOptionPrice()<<"\n";

  system("pause");
  return 0;
}
