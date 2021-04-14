#pragma once

#include <stdexcept>
#include <string>

namespace debug {

class Exception : public std::exception {
  public:
    Exception();

    explicit Exception(std::string&& error);

  private:
    std::string _name_error;
};

class PhysicalException: public debug::Exception {
  public:
    PhysicalException();
    explicit PhysicalException(std::string&& error);
};

class MathException: public debug::Exception {
  public:
    MathException();
    explicit MathException(std::string&& error);
};

}
