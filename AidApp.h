// Created by Xiaochen Wang
// // 2017-08-11
#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "general.h"
#include "Product.h"


using namespace std;

namespace sict {
  class AidApp {
  private:
    char filename_[256];
    Product* product_[MAX_NO_RECS];
    fstream datafile_;
    int noOfProducts_;

    void pause()const;
    int menu();
    void loadRecs();
    void saveRecs();
    void listProducts()const;
    int SearchProducts(const char* sku)const;
    void addQty(const char* sku);
    void addProduct(bool isPerishable);
    
  public:
    AidApp(const char* filename);
    int run();


  };

}

#endif // end of SICT_AIDAPP_H__
