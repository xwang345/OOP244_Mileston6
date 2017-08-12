
// Final Project Milestone 2
// Version 1.0
// Date	2017-7-11
// Author: Xiaochen Wang
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "ErrorMessage.h"

namespace sict {
  ErrorMessage::ErrorMessage(const char * errorMessage)
  {
    message_ = nullptr;
    ErrorMessage::message(errorMessage);
  }

  ErrorMessage & ErrorMessage::operator=(const char * errorMessage)
  {
    ErrorMessage::clear();
    ErrorMessage::message(errorMessage);
    return *this;
  }

  ErrorMessage::~ErrorMessage()
  {
    delete[] message_;
  }

  void ErrorMessage::clear()
  {
    delete[] message_;
    message_ = nullptr;
  }

  void ErrorMessage::message(const char * value)
  {
    delete[] message_;
    message_ = new char[strlen(value) + 1];
    strcpy(message_, value);
  }

  const char * ErrorMessage::message() const
  {
    return message_;
  }

  std::ostream & operator<<(std::ostream & os, const ErrorMessage & errMsg)
  {
    if (!errMsg.isClear()) {
      os << errMsg.message();
    }
    return os;
  }

}
