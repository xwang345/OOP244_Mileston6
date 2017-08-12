// Final Project Milestone 3
// Version 1.0
// Date 2017-07-11
// Author  Xiaochen Wang 
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef SICT_STREAMABLE_H__
#define SICT_STREAMABLE_H__
#include <iostream>
#include <fstream>

namespace sict {

  class Streamable {
  public:
    virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const = 0;
    virtual std::fstream& load(std::fstream& file) = 0;
    virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
    virtual std::istream& read(std::istream& is) = 0;
  };

}


#endif
