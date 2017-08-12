// Final Project Milestone 1
//
// Version 1.0
// Date: 2017-07-06
// Author: Xiaochen Wang
#include "Date.h"
#include "general.h"
namespace sict {

  void Date::errCode(int errorCode)
  {
    readErrorCode_ = errorCode;
  }

  int Date::value()const {
    return year_ * 372 + mon_ * 31 + day_;
  }

  // default constructor
  Date::Date()
  {
    year_ = 0;
    mon_ = 0;
    day_ = 0;
    readErrorCode_ = NO_ERROR;
  }

  Date::Date(int year, int mon, int day)
  {
    year_ = year;
    mon_ = mon;
    day_ = day;
    readErrorCode_ = NO_ERROR;
  }

  // Comparison Logical operator overloads:

  bool Date::operator==(const Date & D) const
  {
    return (this->value() == D.value());
  }

  bool Date::operator!=(const Date & D) const
  {
    return (this->value() != D.value());
  }

  bool Date::operator<(const Date & D) const
  {
    return (this->value() < D.value());
  }

  bool Date::operator>(const Date & D) const
  {
    return (this->value() > D.value());
  }

  bool Date::operator<=(const Date & D) const
  {
    return (this->value() <= D.value());
  }

  bool Date::operator>=(const Date & D) const
  {
    return (this->value() >= D.value());
  }

  int Date::mdays()const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
    mon--;
    return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
  }

  int Date::errCode() const
  {
    return readErrorCode_;
  }

  bool Date::bad() const
  {
    return (readErrorCode_ != NO_ERROR);
  }

  std::istream & Date::read(std::istream & istr)
  {
    char gapOne, gapTwo;
    //int year, mon, day;
    errCode(NO_ERROR);
    istr >> year_ >> gapOne >> mon_ >> gapTwo >> day_;
    if (istr.fail()) {
      errCode(CIN_FAILED);
    }
    else if (year_ > MAX_YEAR || year_ < MIN_YEAR) {
      errCode(YEAR_ERROR);
    }
    else if (mon_ > 12 || mon_ < 1) {
      errCode(MON_ERROR);
    }
    else if (day_ > mdays() || day_ < 1) {
      errCode(DAY_ERROR);
    }
    return istr;
  }

  std::ostream & Date::write(std::ostream & ostr) const
  {
    ostr.setf(std::ios::fixed);
    ostr.setf(std::ios::right);
    ostr << year_ << "/";

    ostr.setf(std::ios::right);
    ostr.width(2);
    ostr.fill('0');
    ostr << mon_ << "/";

    
    ostr.width(2);
    ostr.fill('0');
    ostr << day_;

    ostr.fill(' ');
    ostr.unsetf(std::ios::fixed);
    return ostr;
  }

  std::istream & operator>>(std::istream & istr, Date & d)
  {
    return d.read(istr);
  }

  std::ostream & operator<<(std::ostream & ostr, const Date & d)
  {
    return d.write(ostr);
  }
}
