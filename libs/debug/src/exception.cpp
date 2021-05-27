// Дмитрий Варин BaseException, FileError, InvalidArg, LoadException
// Ветошкин Артём Exception, PhysicalException, MathException
// , ArgumentException, UnexpectedCallException
#include "exception.hpp"

namespace debug {


//  -------------------------------Exception------------------------------------


Exception::Exception()
        : _name_error("\nERROR:" + (std::string) "Some error") {}

Exception::Exception(std::string &&error)
        : _name_error(error) {}

const char *Exception::what() const noexcept {
    return _name_error.c_str();
}


//  -----------------------------BaseExceptions---------------------------------


BaseExceptions::BaseExceptions()
        : Exception("\nError: unknown game error") {}

BaseExceptions::BaseExceptions(const std::string &filename
                               , const std::string &classname
                               , const std::string &method_name
                               , const std::string &arg) {
    _name_error = "\nFile: " + filename + \
                     "\nClass: " + classname + \
                     "\nMethod: " + method_name;
    if (!arg.empty()) {
        _name_error += "\n Argument: " + arg;
    }

    _name_error = "\nError: " + _name_error;
}

BaseExceptions::BaseExceptions(std::string &&error)
        : Exception(std::move(error)) {}


//  --------------------------PhysicalException---------------------------------


PhysicalException::PhysicalException()
        : BaseExceptions("\nError: some physical error") {}

PhysicalException::PhysicalException(std::string &&error)
        : BaseExceptions("\nError in physics: " + error) {}


//  --------------------------MathException-------------------------------------


MathException::MathException()
        : BaseExceptions("\nError: some math error") {}

MathException::MathException(std::string &&error)
        : BaseExceptions("\nError in math: " + error) {}


//  --------------------------LoadException-------------------------------------


LoadException::LoadException()
        : BaseExceptions("\nError: some load error") {}

LoadException::LoadException(const std::string &filename
                             , const std::string &classname
                             , const std::string &method_name
                             , const std::string &arg)
        : BaseExceptions(filename, classname, method_name, arg) {}


//  --------------------------ArgumentException---------------------------------


ArgumentException::ArgumentException()
        : BaseExceptions("\nError: some incorrect argument") {}

ArgumentException::ArgumentException(const std::string &filename
                                     , const std::string &classname
                                     , const std::string &method_name
                                     , const std::string &arg)
        : BaseExceptions(filename, classname, method_name, arg) {}


//  ---------------------UnexpectedCallException--------------------------------


UnexpectedCallException::UnexpectedCallException()
        : BaseExceptions("\nError: some function unexpect, "
                         "that it will be called") {}

UnexpectedCallException::UnexpectedCallException(const std::string &filename
                                             , const std::string &classname
                                             , const std::string &method_name
                                             , const std::string &arg)
        : BaseExceptions(filename, classname, method_name, arg) {}


//  -----------------------------InvalidArg-------------------------------------


InvalidArg::InvalidArg(const std::string& filename, const std::string& classname
                       , const std::string& methodname) :
        BaseExceptions(filename, classname, methodname) {}

const char *InvalidArg::what() const noexcept {
    std::string message = "\nERROR: Invalid argument. " + _name_error;
    return message.c_str();
}


//  ------------------------------FileError-------------------------------------


FileError::FileError(const std::string& filename, const std::string& classname
                     , const std::string& methodname, const std::string& arg) :
        BaseExceptions(filename, classname, methodname, arg) {}

const char *FileError::what() const noexcept {
    std::string message = "\nERROR: Invalid argument. " + _name_error;
    return message.c_str();
}

}  // namespace debug
