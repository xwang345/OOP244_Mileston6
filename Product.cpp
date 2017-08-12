// Created by Xiaochen Wang
// // 2017-08-11
#define _CRT_SECURE_NO_WARNINGS
#include <cstring> 
#include "Product.h"


namespace sict {

  Product::Product()
  {
    sku_[0] = '\0';
    name_ = nullptr;
    price_ = 0;
    quantity_ = 0;
    taxed_ = false;
    qtyNeeded_ = 0;
  }

  Product::Product(const char * sku, const char * name, bool taxed, double price, int quantity)
  {
    if (sku[0] != '\0' && name != nullptr) {
      strncpy(sku_, sku, MAX_SKU_LEN);
      //strcpy(sku_, sku);
      name_ = nullptr;
      name_ = new char[strlen(name) + 1];
      strcpy(name_, name);
      quantity_ = quantity;
      price_ = price;
      taxed_ = taxed;
      qtyNeeded_ = 0;
    }
    else {
      sku_[0] = '\0';
      name_ = nullptr;
      price_ = 0;
      quantity_ = 0;
      taxed_ = false;
      qtyNeeded_ = 0;
    }
  }

  Product::Product(const Product & src)
  {
    strcpy(sku_, src.sku_);
    price_ = src.price_;
    taxed_ = src.taxed_;
    quantity_ = src.quantity_;
    qtyNeeded_ = src.qtyNeeded_;

    if (src.name_ != nullptr) {
      name_ = new char[strlen(src.name_) + 1];
      strncpy(name_, src.name_, (strlen(src.name_) + 1));
    }
    else {
      name_ = nullptr;
    }
  }

  //Product & Product::operator=(const Product & src)
  //{
  //  if (!Product::isEmpty() && this != &src) {
  //    Product::sku(src.sku_);
  //    Product::name(src.name_);
  //    Product::price(src.price_);
  //    Product::taxed(src.taxed_);
  //    Product::quantity(src.quantity_);
  //    Product::qtyNeeded(src.qtyNeeded_);
  //  }
  //  return *this;
  //}

  Product & Product::operator=(const Product & src)
  {
    if (this != &src) {
      strcpy(sku_, src.sku_);
      price_ = src.price_;
      taxed_ = src.taxed_;
      quantity_ = src.quantity_;
      qtyNeeded_ = src.qtyNeeded_;

      if (src.name_ != nullptr) {
        name_ = new char[strlen(src.name_) + 1];
        strncpy(name_, src.name_, (strlen(src.name_) + 1));
      }
      else {
        name_ = nullptr;
      }
    }
    return *this;
  }


  Product::~Product()
  {
    delete[] name_;
    name_ = nullptr;
  }

  //void Product::sku(const char * setSku)
  //{
  //  //strncpy(sku_, setSku, MAX_SKU_LEN);
  //  strcpy(sku_, setSku);
  //}

  void Product::name(const char *setname)
  {
    delete[] name_;
    name_ = new char[strlen(setname) + 1];
    strcpy(name_, setname);
  }


  double Product::price() const
  {
     return price_; 
  }

  double Product::cost() const
  {
    if (Product::taxed()) {
      return price_ * (1 + TAX);
    }
    else {
      return price_;
    }
  }

  double operator+=(double & lhs, const Product & rhs)
  {
    return lhs += rhs.cost() * rhs.quantity();
  }

  std::istream & operator>>(std::istream & is, Product & p)
  {
    p.read(is);
    return is;
  }

  std::ostream & operator<<(std::ostream & os, const Product & p)
  {
    p.write(os, true);
    return os;
  }

}
