#include "PageElementHandler.h"

using namespace merge_lib;

std::set<std::string> PageElementHandler::_allPageFields;

void PageElementHandler::_createAllPageFieldsSet()
{
   if(!_allPageFields.empty())
      return;
   _allPageFields.insert(std::string("Type"));
   _allPageFields.insert(std::string("Parent"));
   _allPageFields.insert(std::string("LastModified"));
   _allPageFields.insert(std::string("Resources"));
   _allPageFields.insert(std::string("MediaBox"));
   _allPageFields.insert(std::string("CropBox"));
   _allPageFields.insert(std::string("BleedBox"));
   _allPageFields.insert(std::string("TrimBox"));
   _allPageFields.insert(std::string("ArtBox"));
   _allPageFields.insert(std::string("BoxColorInfo"));
   _allPageFields.insert(std::string("Contents"));
   _allPageFields.insert(std::string("Rotate"));
   _allPageFields.insert(std::string("Group"));
   _allPageFields.insert(std::string("Thumb"));
   _allPageFields.insert(std::string("B"));
   _allPageFields.insert(std::string("Dur"));
   _allPageFields.insert(std::string("Trans"));
   _allPageFields.insert(std::string("Annots"));
   _allPageFields.insert(std::string("AA"));
   _allPageFields.insert(std::string("Metadata"));
   _allPageFields.insert(std::string("PieceInfo"));
   _allPageFields.insert(std::string("StructParents"));   
   _allPageFields.insert(std::string("ID"));   
   _allPageFields.insert(std::string("PZ"));   
   _allPageFields.insert(std::string("SeparationInfo"));   
   _allPageFields.insert(std::string("Tabs"));   
   _allPageFields.insert(std::string("TemplateInstantiated"));   
   _allPageFields.insert(std::string("PresSteps"));   
   _allPageFields.insert(std::string("UserUnit"));   
   _allPageFields.insert(std::string("VP"));
   //for correct search all fields of XObject should be present to
   _allPageFields.insert(std::string("Subtype"));
   _allPageFields.insert(std::string("FormType"));
   _allPageFields.insert(std::string("BBox"));
   _allPageFields.insert(std::string("Matrix"));
   _allPageFields.insert(std::string("Ref"));
   _allPageFields.insert(std::string("StructParent"));
   _allPageFields.insert(std::string("OPI"));
   _allPageFields.insert(std::string("OC"));
   _allPageFields.insert(std::string("Name"));

}

unsigned int PageElementHandler::_findEndOfElementContent(unsigned int startOfPageElement)
{
   static std::string whitespacesAndDelimeters(" \t\f\v\n\r<<[/");
   unsigned int foundSlash = _pageContent.find("/", startOfPageElement + 1);
   std::string fieldType;
   while(foundSlash != std::string::npos)
   {
      unsigned int foundWhitespace = _pageContent.find_first_of(whitespacesAndDelimeters, foundSlash + 1);
      if(foundWhitespace != std::string::npos)      
         fieldType = _pageContent.substr(foundSlash + 1, foundWhitespace - foundSlash - 1);
      else 
         break;
      //is this any page element between "/" and " "
      if(_allPageFields.count(fieldType))
      {         
         return foundSlash;
      }
      foundSlash = foundWhitespace;
   }
   return _pageContent.rfind(">>");
}