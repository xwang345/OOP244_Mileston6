// Final Project Milestone 1
//
// Version 1.0
// Date: 2017-07-06
// Author: Xiaochen Wang
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef SICT_DATE_H__
#define SICT_DATE_H__

#include <iostream>
namespace sict {

  // define the error code
#define NO_ERROR   0  // No error the date is valid
#define CIN_FAILED 1  // istream failed when entering information
#define YEAR_ERROR 2  // Year value is invalid
#define MON_ERROR  3  // Month value is invalid
#define DAY_ERROR  4  // Day value is invalid

  class Date {
  private:
    // Member Data
    int year_;  // Holds the year; a four digit integer between MIN_YEAR and MAX_YEAR
    int mon_;   // Month of the year, between 1 to 12
    int day_;   // Day of the month, note that in a leap year February is 29 days
    int readErrorCode_; //holds an error code with which the caller program can reference to find out if the date value is valid, and if not, which part is erroneous

    //Private Member functions
    void errCode(int errorCode);  // Sets the readErrorCode_ member-variable to one of the values
    int value()const; //returns a unique integer number based on the date. This value is used to compare two dates

  public:

    // Constructors
    Date();
    Date(int year, int mon, int day);

    // Public member-functions and operators
    bool operator==(const Date& D)const;
    bool operator!=(const Date& D)const;
    bool operator<(const Date& D)const;
    bool operator>(const Date& D)const;
    bool operator<=(const Date& D)const;
    bool operator>=(const Date& D)const;

    int mdays()const; //Returns the number of days in a month

    // Accessor or getter member functions
    int errCode()const; 	// Returns the readErrorCode_ value.
    bool bad()const;      // Returns true if readErrorCode_ is not equal to zero.

    // IO member-funtions
    std::istream& read(std::istream& istr); // Reads the date in the following format: YYYY?MM?DD from the console.
    std::ostream& write(std::ostream& ostr)const; // Writes the date using the ostr argument in the following format: YYYY/MM/DD, then return the ostr.
  };

  // Non-member IO operator overloads
  std::istream& operator>>(std::istream& istr, Date& d);
  std::ostream& operator<<(std::ostream& ostr, const Date& d);

}
#endif
