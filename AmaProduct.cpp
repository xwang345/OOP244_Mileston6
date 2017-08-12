// Created by Xiaochen Wang
// // 2017-08-11
// AmaProduct.cpp
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "AmaProduct.h"

using namespace std;

namespace sict {

  AmaProduct::AmaProduct(char tag)
  {
    fileTag_ = tag;
  }

  const char * AmaProduct::unit() const
  {
    return unit_;
  }

  void AmaProduct::unit(const char * value)
  {
    strncpy(unit_, value, 11);
  }

  std::fstream & AmaProduct::store(std::fstream & file, bool addNewLine) const
  {
    if (file.is_open()) {
      file << fileTag_ << ","
        << Product::sku() << ","
        << Product::name() << ","
        << Product::price() << ","
        << Product::taxed() << ","
        << Product::quantity() << ","
        << AmaProduct::unit() << ","
        << Product::qtyNeeded();
      if (addNewLine) {
        file << std::endl;
      }

    }
    return file;
  }

  std::fstream & AmaProduct::load(std::fstream & file)
  {
    char temSku[MAX_SKU_LEN + 1];
    char temName[30 + 1];
    double tmpPrice;
    bool temTaxed;
    int temQuantity;
    char temUnit[11 + 1];
    int temQtyNeeded;
    if (file.is_open()) {
      
      file.ignore(10, ',');  // read the comma
      file.getline(temSku, MAX_SKU_LEN + 1, ',');
      file.getline(temName, 21, ',');
      file >> tmpPrice;
      file.ignore();
      file >> temTaxed;
      file.ignore();
      file >> temQuantity;
      file.ignore();
      file.getline(temUnit, 11, ',');
      file >> temQtyNeeded;

      Product::sku(temSku);
      Product::name(temName);
      Product::price(tmpPrice);
      Product::taxed(temTaxed);
      Product::quantity(temQuantity);
      AmaProduct::unit(temUnit);
      Product::qtyNeeded(temQtyNeeded);
    }
    return file;
  }

  std::ostream & AmaProduct::write(std::ostream & os, bool linear) const
  {
    if (err_.isClear()) {
      if (linear) {
        // os.setf(std::ios::left);
        os << std::setw(7) << std::left << Product::sku() << "|";
        os << std::setw(20) << std::left << Product::name() << "|";
        os << std::setw(7) << std::fixed << std::right << std::setprecision(2) << Product::cost() << "|";
        os << std::setw(4) << std::right << Product::quantity() << "|";
        os << std::setw(10) << std::left << AmaProduct::unit() << "|";
        os << std::setw(4) << std::right << Product::qtyNeeded() << "|";
       
      }
      else {
        os << "Sku: " << Product::sku() << std::endl;
        os << "Name: " << Product::name() << std::endl;
        os << "Price: " << std::fixed << Product::price() << std::endl;
        os << "Price after tax: ";
        if (Product::taxed()) {
          os << std::fixed << Product::cost() << std::endl;
        }
        else {
          os << "N/A" << std::endl;
        }
        os << "Quantity On Hand: " << Product::quantity() << " " << AmaProduct::unit() << std::endl;
        os << "Quantity Needed: " << Product::qtyNeeded();
        
      }
    }
    else {
      os << err_.message();
    }
    return os;
  }

  std::istream & AmaProduct::read(std::istream & istr)
  {
    char tempSku[MAX_SKU_LEN + 1];
    char tempName[30];
    char tempUnit[11];
    char tempTaxed;
    double tempPrice;
    int tempQuantity;
    int tempQtyNeeded;

    //istr.clear();
    //istr.ignore(); 
    err_.clear();
    cout << "Sku: ";
    istr.getline(tempSku, MAX_SKU_LEN, '\n');
    if (istr.fail()) { return istr; }
    sku(tempSku);

    cout << "Name: ";
    istr.getline(tempName, 30, '\n');
    if (istr.fail()) { return istr; }
    name(tempName);

    cout << "Unit: ";
    istr.getline(tempUnit, 11, '\n');
    if (istr.fail()) { return istr; }
    unit(tempUnit);

    if (err_.isClear())
    {
      cout << "Taxed? (y/n): ";
      istr >> tempTaxed;

      if (istr.fail())
      {
        err_.message("Only (Y)es or (N)o are acceptable");
        istr.setstate(ios::failbit);
      }
      else
      {
        if (tempTaxed == 'Y' || tempTaxed == 'y')
          taxed(1);
        else if (tempTaxed == 'N' || tempTaxed == 'n')
          taxed(0);
        else
        {
          err_.message("Only (Y)es or (N)o are acceptable");
          istr.setstate(ios::failbit);
        }
      }
    }
    else
      return istr;


    if (err_.isClear())
    {
      cout << "Price: ";
      istr >> tempPrice;
      if (istr.fail())
      {
        err_.message("Invalid Price Entry");
        istr.setstate(ios::failbit);
      }
      else
        price(tempPrice);
    }
    else
      return istr;


    if (err_.isClear())
    {
      cout << "Quantity On hand: ";
      istr >> tempQuantity;
      if (istr.fail())
      {
        err_.message("Invalid Quantity Entry");
        istr.setstate(ios::failbit);
      }
      else
        quantity(tempQuantity);
    }
    else
      return istr;


    if (err_.isClear())
    {
      cout << "Quantity Needed: ";
      istr >> tempQtyNeeded;
      if (istr.fail())
      {
        err_.message("Invalid Quantity Needed Entry");
        istr.setstate(ios::failbit);
      }
      else
        qtyNeeded(tempQtyNeeded);
    }

    return istr;
  }     // end of read function 

}
