// Created by Xiaochen Wang
// 2017-08-11
#include <iostream>
#include<iomanip>
#include "AidApp.h"
#include "AmaPerishable.h"
#include "AmaProduct.h"

using namespace std;

namespace sict {

  AidApp::AidApp(const char* filename)
  {
    strncpy(filename_, filename, 256);
    noOfProducts_ = 0;
    product_[noOfProducts_] = nullptr;
    this->loadRecs();
  } // end of constructor
  
  void AidApp::pause() const
  {
    std::cout << "Press Enter to continue..." << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  int AidApp::menu()
  {
   cout << "Disaster Aid Supply Management Program" << endl
        << "1- List products" << endl
        << "2- Display product" << endl
        << "3- Add non-perishable product" << endl
        << "4- Add perishable product" << endl
        << "5- Add to quantity of purchased products" << endl
        << "0- Exit program" << endl
        << "> ";
    int option = -1;
    cin >> option;
    cout << endl;
    if (option > 5 || option < 0 || cin.fail()) {
      option = -1;
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return option;
  }

  void AidApp::loadRecs()
  {
    int readIndex = 0;
    char id;
    //TODO: OPEN THE FILE.
    //fstream fileload;
    datafile_.open(filename_, ios::in);

    if (datafile_.is_open()) {
      while (datafile_.good()) {
        delete product_[readIndex];
        product_[readIndex] = nullptr;
        datafile_ >> id;
        if (id == 'P') {
          product_[readIndex] = new AmaPerishable();
        }
        else if (id == 'N') {
          product_[readIndex] = new AmaProduct();
        }
        else {
          datafile_.ignore();
        }
        product_[readIndex]->load(datafile_);
        readIndex++;
      }
      noOfProducts_ = readIndex - 1;
      datafile_.close();
    }
    else {
      datafile_.clear();
      datafile_.close();
      datafile_.open(filename_, ios::out);
      datafile_.close();
    }
  }  

  void AidApp::saveRecs()
  {
    datafile_.open(filename_, ios::out);
    for (int i = 0; i < noOfProducts_; i++) {
      product_[i]->store(datafile_);
    }
    datafile_.close();
    loadRecs();
  }

  void AidApp::listProducts() const
  {
    double totalCost = 0;
    std::cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   " << endl;
    std::cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;
    for (int i = 0; i < noOfProducts_; i++ ) {
      if (i == 10) {
        pause();
      }
      std::cout << setw(4) << right << i + 1 << " | ";
      product_[i]->write(std::cout, true);
      totalCost += *product_[i];
      std::cout << endl;
    }
    std::cout << "---------------------------------------------------------------------------" << endl;
    std::cout << left << "Total cost of support: $" << setprecision(2) << fixed << totalCost << endl << endl;
  } 

  int AidApp::SearchProducts(const char * sku) const {
    int index = -1;
    for (int i = 0; i < noOfProducts_; i++) {
      if (*product_[i] == sku) { 
        index = i;
        break;
      }
    }
    return index;
  } // end of function SearchProducts

  void AidApp::addQty(const char * sku)
  {
    int addIndex = SearchProducts(sku);
    if (addIndex == -1) {
      cout << "Not found!" << endl << endl;
    }
    else {
      product_[addIndex]->write(std::cout, false);
      cout << endl << endl << "Please enter the number of purchased items: ";
      int purchasedNumber;
      int productNeeded = product_[addIndex]->qtyNeeded() - product_[addIndex]->quantity();
      cin >> purchasedNumber;
      //cout << endl;
      if (cin.fail()) {
        cout << "Invalid quantity value!" << endl;
      }
      else {
        if (purchasedNumber <= productNeeded) {
          *product_[addIndex] += purchasedNumber;
        }
        else {
          std::cout << endl << "Too many items; only " << productNeeded << " is needed, please return the extra " << purchasedNumber - productNeeded << " items." << endl;
          *product_[addIndex] += productNeeded;
        }
        saveRecs();
        cout << endl << "Updated!" << endl << endl;
      }
      cout.clear();
    }
  } 

  void AidApp::addProduct(bool isPerishable)
  {
    loadRecs();
    if (isPerishable == true) {
      product_[noOfProducts_] = new AmaPerishable();
    }
    else {
      product_[noOfProducts_] = new AmaProduct();
    }
    product_[noOfProducts_]->read(cin);
    if (cin.fail()) {
      cin.clear();
      cout << *product_[noOfProducts_] << endl << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      delete product_[noOfProducts_];
    }
    else {
      noOfProducts_++;
      saveRecs();
      cout << endl << "Product added" << endl << endl;
    }
  } 

  int AidApp::run()
  {
    int menu_selection;
    do {
      menu_selection = menu();
      if (menu_selection == 1) {
        listProducts();
        pause();
      }
      else if (menu_selection == 2) {
        std::cout << "Please enter the SKU: ";
        char sku[MAX_SKU_LEN + 1];
        cin >> sku;
        cout << endl;
        int displayIndex = SearchProducts(sku);
        if (displayIndex == -1) {
          cout << "Not found!" << endl << endl;
        }
        else {
          product_[displayIndex]->write(std::cout, false) << endl << endl;
          pause();
          cout << endl;
        }
      }
      else if (menu_selection == 3) {
        addProduct(false);
      }
      else if (menu_selection == 4) {
        addProduct(true);
      }
      else if (menu_selection == 5) {
        cout << "Please enter the SKU: ";
        char sku[MAX_SKU_LEN + 1];
        cin >> sku;
        cout << endl;
        addQty(sku);
      }
      else if (menu_selection == -1) {
        cout << "===Invalid Selection, try again.===" << endl;
        pause();
      }
    } while (menu_selection != 0);
      cout << "Goodbye!!" << endl;
      return 0;
    
  } 




} // end of namespace sict
