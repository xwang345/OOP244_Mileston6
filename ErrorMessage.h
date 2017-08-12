// Final Project Milestone 2
// Version 1.0
// Date	2017-7-11
// Author Xiaochen Wang
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__

namespace sict {

  class ErrorMessage {
  private:
    char* message_;
  public:
    // constructors
    ErrorMessage() { message_ = nullptr; }
    ErrorMessage(const char* errorMessage);
    ErrorMessage(const ErrorMessage& em) = delete;

    ErrorMessage& operator=(const ErrorMessage& em) = delete;
    ErrorMessage& operator=(const char* errorMessage);

    virtual ~ErrorMessage();
    void clear();
    bool isClear()const { return (message_ == nullptr); }
    void message(const char* value);
    const char* message()const;
  };
  std::ostream& operator<<(std::ostream& os, const ErrorMessage& errMsg);
}

#endif // !SICT_ERRORMESSAGE_H__
