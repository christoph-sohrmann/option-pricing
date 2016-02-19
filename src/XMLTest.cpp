#include <iostream>
#include "sporc/input.h"


int main(int argc, char *argv[])
{
  if(XML_ParseFile("pricing.xml")!=0)
  {
   cout << "Error parsing input file!" << endl;
   return 1;
  }
      
  PrintXMLTree();
   
  if((XMLTreeElement = FindElement(XMLTree.begin(),"solver"))!=NULL)
   cout << XMLTreeElement->Attributes["model"] << endl;
  else
   cout << "Element not found." << endl;
  
  system("PAUSE");
  return 0;
}
