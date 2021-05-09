#include "exception.hpp"

namespace debug {


//  -------------------------------Exception-----------------------------------


Exception::Exception()
        : _name_error("Some error") {}

Exception::Exception(std::string&& error)
        : _name_error(error) {}


//  --------------------------PhysicalException--------------------------------


PhysicalException::PhysicalException()
        : Exception("Some physical error") {}

PhysicalException::PhysicalException(std::string&& error)
        : Exception("Error in physics: " + error) {}


//  --------------------------MathException------------------------------------


MathException::MathException()
        : Exception("Some math error") {}

MathException::MathException(std::string&& error)
        : Exception("Error in math: " + error) {}

}  // namespace debug
