// Created by Xiaochen Wang
// // 2017-08-11
// AmaPersishable.cpp
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "general.h"
#include "Product.h"
#include "ErrorMessage.h"
#include "AmaProduct.h"
#include "AmaPerishable.h"

//using namespace std;

namespace sict {
  AmaPerishable::AmaPerishable() : AmaProduct('P') { }

  const Date & AmaPerishable::expiry() const
  {
    return expiry_;
  }

  void AmaPerishable::expiry(const Date & value)
  {
    expiry_ = value;
  }

  std::fstream & AmaPerishable::store(std::fstream & file, bool addNewLine) const
  {
    AmaProduct::store(file, false);
    file << "," 
	 << AmaPerishable::expiry() 
	 << std::endl;
 
    return file;
  }

  std::fstream & AmaPerishable::load(std::fstream & file)
  {
    AmaProduct::load(file);
    file.ignore();
    expiry_.read(file);
    file.ignore();
    return file;
  }

  std::ostream & AmaPerishable::write(std::ostream & ostr, bool linear) const
  {
    AmaProduct::write(ostr, linear);
    if (err_.isClear()) {
      if (linear) {
        ostr << AmaPerishable::expiry();
      }
      else {
        ostr << std::endl << "Expiry date: ";
        ostr << AmaPerishable::expiry();
      }
    }
    return ostr;
  }

  std::istream & AmaPerishable::read(std::istream & istr)
  {
    Date temdate;
    AmaProduct::read(istr);

    if (err_.isClear()) {
      std::cout << "Expiry date (YYYY/MM/DD): ";
      istr >> temdate;
      if (temdate.errCode() == CIN_FAILED) {
        err_.message("Invalid Date Entry"); 
        istr.setstate(std::ios::failbit);
      }
      else if (temdate.errCode() == YEAR_ERROR) {
       
        err_.message("Invalid Year in Date Entry");
        istr.setstate(std::ios::failbit);
      }
      else if (temdate.errCode() == MON_ERROR) {
      
        err_.message("Invalid Month in Date Entry");
        istr.setstate(std::ios::failbit);
      }
      else if (expiry_.errCode() == DAY_ERROR) {
     
        err_.message("Invalid Day in Date Entry");
        istr.setstate(std::ios::failbit);
      }
      else {
        expiry(temdate);
      }
    }

    return istr;
  } // end of read function


} // end of namespace
