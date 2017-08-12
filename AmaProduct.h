// AmaProduct.h

// Final Project Milestone 5
// Version 1.0
// Date 2017-07-20
// Author  Xiaochen Wang
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__
#include <cstring>
#include "Product.h"
#include "Streamable.h"
#include "ErrorMessage.h"

namespace sict {
  class AmaProduct : public Product {
  private:
    char fileTag_;
    char unit_[11];

  protected:
    ErrorMessage err_;

  public:
    AmaProduct(char tag = 'N');
    const char* unit() const;
    void unit(const char* value);

     virtual std::fstream& store(std::fstream& file, bool addNewLine = true) const;

    virtual std::fstream& load(std::fstream& file);

    virtual std::ostream& write(std::ostream& os, bool linear)const;

    virtual std::istream& read(std::istream& istr);

  };

}

#endif // !SICT_AMAPRODUCT_H__

