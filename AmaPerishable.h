// Created by Xiaochen Wang
// 2017-08-11
// AmaPerishable.h

#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__
#include "AmaProduct.h"
#include "Date.h"

namespace sict {

  class AmaPerishable : public AmaProduct {
  private:
    Date expiry_;

  public:
    AmaPerishable();
    const Date& expiry()const;
    void expiry(const Date &value);
    
    virtual std::fstream& store(std::fstream& file, bool addNewLine = true) const;
    virtual std::fstream& load(std::fstream& file);
    virtual std::ostream& write(std::ostream& os, bool linear)const;
    virtual std::istream& read(std::istream& istr);

  };
}


#endif // !SICT_AMAPERISHABLE_H__
