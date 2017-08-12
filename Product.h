// Final Project Milestone 4
// Version 1.0
// Date 2017-07-13
// Author  Xiaochen Wang 
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef SICT_PRODUCT_H__
#define SICT_PRODUCT_H__
#include <iostream>
#include <cstring>
#include "general.h"
#include "Streamable.h"


namespace sict {
  class Product : public Streamable {
  private:
    char sku_[MAX_SKU_LEN + 1];
    char * name_;
    double price_;
    bool taxed_;
    int quantity_;
    int qtyNeeded_;
  public:
    // constructor
    Product();
    Product(const char* sku, const char* name, bool taxed = true, double price = 0, int quantity = 0);

    // Copy Constructor
    Product(const Product& src);
    Product& operator=(const Product& src);

    // virtual destructor
    virtual ~Product();

    // Setters
    void sku(const char* setSku) { strncpy(sku_, setSku, MAX_SKU_LEN); }
    void name(const char* setName);
    void price(double setPrice) { price_ = setPrice; }
    void taxed(bool setTaxed) { taxed_ = setTaxed; }
    void quantity(int setQuantity) { quantity_ = setQuantity; }
    void qtyNeeded(int setQtyNeeded) { qtyNeeded_ = setQtyNeeded; }

    // Getters 
    const char* sku() const { return sku_; }
    double price() const;
    const char* name() const { return name_; }
    bool taxed() const { return taxed_; }
    int quantity() const { return quantity_; }
    int qtyNeeded() const { return qtyNeeded_; }
    double cost() const;
    bool isEmpty() const { return ((sku_[0] == '\0') && (name_ == nullptr) && (price_ == 0) && (quantity_ == 0)); }

    // Member Operator overloads
    bool operator==(const char* src) { return strcmp(sku_, src) == 0; }
    int operator+=(int src) { return quantity_ += src; }
    int operator-=(int src) { return quantity_ -= src; }
  };

  // Non-Member operator overload
  double operator+=(double & lhs, const Product& rhs);

  // Non-member IO operator overloads
  std::istream& operator>>(std::istream& is,  Product& p);
  std::ostream& operator<<(std::ostream& os, const Product& p);

}

#endif // !SICT_PRODUCT_H__
