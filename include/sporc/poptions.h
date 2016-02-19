#ifndef _POPTIONS_H_
#define _POPTIONS_H_

#include <sporc/option.h>
#include <sporc/input.h>

#include <string>
#include <map>
#include <sstream>

namespace sporc{

template<typename T>
struct Conversion_Traits;

class POptions{
public:
  static
  POptions& get()
    {
      return Instance;
    }

  template<typename T>
    static
    T getParam(std::string element,std::string key)
    {
     assert((XMLTreeElement = FindElement(XMLTree.begin(),element))!=NULL && "ERROR: Element not found in input file.");
     return Conversion_Traits<T>::convert(XMLTreeElement->Attributes[key]);
    }

  static
    void init(std::string initfile)
    {
      Instance.parseFile(initfile);
    }
    
  static
    void test()
    {
     cout << "Solver[steps]     : " << POptions::getParam<int>("solver","steps") << endl;
     cout << "Option[maturity]  : " << POptions::getParam<double>("option","maturity") << endl;
     cout << "Option[type]      : " << (POptions::getParam<Option::OptionT>("option","type") == Option::OT_CALL ? "call" : "put") << endl;
     cout << "Option[r]         : " << POptions::getParam<double>("option","interestrate") << endl;
     cout << "Option[s_0]       : " << POptions::getParam<double>("equity","currentprice") << endl;
     cout << "Pricing[currency] : " << POptions::getParam<std::string>("pricing","currency") << endl;
    }

private:
  POptions()
    {}

  POptions(POptions const&);
  void operator=(POptions const&);
  
  void parseFile(std::string filename)
    {     
     assert(XML_ParseFile(filename) == 0 && "ERROR: Error in parsing input file.");
    }

  // singleton instance
  static
    POptions Instance;

};


/// initialise static member
POptions POptions::Instance;

template<>
struct Conversion_Traits<std::string>{
  static
  std::string convert(std::string s)
    { return s; }
};

template<>
struct Conversion_Traits<int>{
  static
  int convert(std::string s)
    { int value;
      istringstream iss(s);
      iss >> value;
      return value; }
};

template<>
struct Conversion_Traits<double>{
  static
  double convert(std::string s)
    { double value;
      istringstream iss(s);
      iss >> value;
      return value; }
};

template<>
struct Conversion_Traits<Option::OptionT>{
  static
  Option::OptionT convert(std::string s)
    { return casecompare(s,"call")==0 ? Option::OT_CALL : Option::OT_PUT; }
};

}

#endif
