#ifndef _INPUT_H_
#define _INPUT_H_

#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdio>
#include "tree.hh"
#include "../expat.h"

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif

using namespace std;

struct XMLElementStruct
{
  string Name;
  map<string,string> Attributes;
};

XMLElementStruct CreateXMLElement(string Name)
{
           XMLElementStruct XMLElement;
           XMLElement.Name = Name;
           return XMLElement;
}
           
tree<XMLElementStruct> XMLTree;
tree<XMLElementStruct>::iterator XMLTreeElement;

void PrintXMLTree()
{ 
    for(XMLTreeElement = XMLTree.begin(); XMLTreeElement != XMLTree.end(); XMLTreeElement++)
    {
     for(int i=0; i<XMLTree.depth(XMLTreeElement); i++) cout << " ";
     cout << XMLTreeElement->Name << endl;
     for(map<string,string>::iterator Attribute=XMLTreeElement->Attributes.begin();
          Attribute!=XMLTreeElement->Attributes.end();
          Attribute++)
      {
       for(int i=0; i<XMLTree.depth(XMLTreeElement); i++) cout << " ";
       cout << "-> " << Attribute->first << " = " << Attribute->second << endl;
      }
    }
}

string tolower (const string & s)
{
  string d (s);

  transform (d.begin (), d.end (), d.begin (), (int(*)(int)) tolower);
  return d;
}

int casecompare(const string s1, const string s2)
{
  return tolower(s1).compare(tolower(s2));
}

tree<XMLElementStruct>::iterator FindElement(tree<XMLElementStruct>::iterator StartElement,string Name)
{
 tree<XMLElementStruct>::iterator XMLTreeElement;
 for(XMLTreeElement = XMLTree.begin(); XMLTreeElement != XMLTree.end(); XMLTreeElement++)
  if(casecompare(Name,XMLTreeElement->Name)==0)
   return XMLTreeElement;
 return NULL;
}

static void XMLCALL
XMLElementStart(void *userData, const char *name, const char **atts)
{
  tree<XMLElementStruct>::iterator *XMLTreeElement = (tree<XMLElementStruct>::iterator*)userData;
  string first,second;
  if(XMLTree.empty())
   *XMLTreeElement = XMLTree.insert(*XMLTreeElement,CreateXMLElement(name));
  else
   *XMLTreeElement = XMLTree.append_child(*XMLTreeElement,CreateXMLElement(name));
  while((*atts)!=NULL) 
  {
   first = tolower(*(atts++));
   second = *(atts++);
   (*XMLTreeElement)->Attributes[first] = second;
  } 
}

static void XMLCALL
XMLElementEnd(void *userData, const char *name)
{
  tree<XMLElementStruct>::iterator *XMLTreeElement = (tree<XMLElementStruct>::iterator*)userData;
  if(!XMLTree.empty())
   *XMLTreeElement = XMLTree.parent(*XMLTreeElement);
}

int XML_ParseFile(string XMLFileName)
{
     XML_Parser parser = XML_ParserCreate(NULL); 
     char buf[500];
     FILE *fp;
     int done;

     XML_SetUserData(parser,(int*)&XMLTreeElement);
     XML_SetElementHandler(parser,XMLElementStart,XMLElementEnd);
     
     fp = fopen(XMLFileName.c_str(),"r");
     
     do {
       size_t len = fread(buf, 1, sizeof(buf), fp);
       done = len < sizeof(buf);
       if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
         fprintf(stderr,
                 "%s at line %" XML_FMT_INT_MOD "u\n",
                 XML_ErrorString(XML_GetErrorCode(parser)),
                 XML_GetCurrentLineNumber(parser));
         fclose(fp);
         XML_ParserFree(parser);  
         return 1;
    }
  } while (!done);
  XML_ParserFree(parser);  
  return 0;
}

#endif
