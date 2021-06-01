// Дмитрий Варин BaseException, FileError, InvalidArg, LoadException
// Ветошкин Артём Exception, PhysicalException, MathException
// , ArgumentException, UnexpectedCallException
#include "exception.hpp"
#include <string>

namespace debug {


//  -----------------------------VAException------------------------------------


VAException::VAException()
        : _name_error("\nERROR:" + (std::string) "Some error") {}

VAException::VAException(const std::string_view &error)
        : _name_error(error) {}

const char *VAException::what() const noexcept {
    return _name_error.c_str();
}


//  -----------------------------BaseExceptions---------------------------------


BaseExceptions::BaseExceptions()
        : VAException("\nError: unknown game error") {}

BaseExceptions::BaseExceptions(const std::string_view &filename,
                               const std::string_view &classname,
                               const std::string_view &method_name,
                               const std::string_view &arg) {
    _name_error = "\nFile: " + (std::string)filename + \
                     "\nClass: " + (std::string)classname + \
                     "\nMethod: " + (std::string)method_name;
    if (!arg.empty()) {
        _name_error += "\n Argument: " + (std::string)arg;
    }

    _name_error = "\nError: " + _name_error;
}

BaseExceptions::BaseExceptions(const std::string_view &error)
        : VAException(error) {}


//  --------------------------PhysicalException---------------------------------


PhysicalException::PhysicalException()
        : BaseExceptions("Error: some physical error") {}

PhysicalException::PhysicalException(const std::string_view &error)
        : BaseExceptions("Error in physics: " + (std::string)error) {}


//  --------------------------MathException-------------------------------------


MathException::MathException()
        : BaseExceptions("Error: some math error") {}

MathException::MathException(const std::string_view &error)
        : BaseExceptions("Error in math: " + (std::string)error) {}


//  --------------------------LoadException-------------------------------------


LoadException::LoadException()
        : BaseExceptions("Error: some load error") {}

LoadException::LoadException(const std::string_view &filename,
                             const std::string_view &classname,
                             const std::string_view &method_name,
                             const std::string_view &arg)
        : BaseExceptions(filename, classname, method_name, arg) {}


//  --------------------------ArgumentException---------------------------------


ArgumentException::ArgumentException()
        : BaseExceptions("Error: some incorrect argument") {}

ArgumentException::ArgumentException(const std::string_view &filename,
                                     const std::string_view &classname,
                                     const std::string_view &method_name,
                                     const std::string_view &arg)
        : BaseExceptions(filename, classname, method_name, arg) {}


//  ---------------------UnexpectedCallException--------------------------------


UnexpectedCallException::UnexpectedCallException()
        : BaseExceptions("Error: some function unexpect, "
                         "that it will be called") {}

UnexpectedCallException::UnexpectedCallException
        (const std::string_view &filename, const std::string_view &classname,
         const std::string_view &method_name, const std::string_view &arg)
        : BaseExceptions(filename, classname, method_name, arg) {}

}  // namespace debug
