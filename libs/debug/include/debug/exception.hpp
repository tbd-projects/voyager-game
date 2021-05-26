#pragma once

#include <stdexcept>
#include <string>


namespace debug {

class Exception : public std::exception {
  public:
    Exception();

    explicit Exception(std::string &&error);

    [[nodiscard]]
    const char *what() const noexcept override;

  protected:
    std::string _name_error;
};

class BaseExceptions : public Exception {
  public:
    BaseExceptions();

    explicit BaseExceptions(std::string &&error);

    BaseExceptions(const std::string &filename, const std::string &classname
                   , const std::string &method_name
                   , const std::string &arg = "");
};

class PhysicalException : public BaseExceptions {
  public:
    PhysicalException();

    explicit PhysicalException(std::string &&error);
};

class MathException : public BaseExceptions {
  public:
    MathException();

    explicit MathException(std::string &&error);
};


#define ARG_LOAD_ERROR(args) LoadException(__FILE__, typeid(*this).name() \
                                                    , __FUNCTION__, args)
#define LOAD_ERROR() LoadException(__FILE__, typeid(*this).name(), __FUNCTION__)

class LoadException : public BaseExceptions {
  public:
    LoadException();

    LoadException(const std::string &filename, const std::string &classname
                  , const std::string &method_name
                  , const std::string &arg = "");
};


#define ARG_ARGUMENT_ERROR(args) ArgumentException(__FILE__ \
                                        , typeid(*this).name() \
                                        , __FUNCTION__, args)
#define ARGUMENT_ERROR() ArgumentException(__FILE__, typeid(*this).name() \
                                                        , __FUNCTION__)

class ArgumentException : public BaseExceptions {
  public:
    ArgumentException();

    ArgumentException(const std::string &filename, const std::string &classname
                      , const std::string &method_name
                      , const std::string &arg = "");
};


#define ARG_UNEXPECTED_CALL_ERROR(args) ArgumentException(__FILE__ \
                                        , typeid(*this).name() \
                                        , __FUNCTION__, args)
#define UNEXPECTED_CALL_ERROR() ArgumentException(__FILE__ \
                                        , typeid(*this).name() \
                                        , __FUNCTION__)

class UnexpectedCallException : public BaseExceptions {
  public:
    UnexpectedCallException();

    UnexpectedCallException(const std::string &filename
                            , const std::string &classname
                            , const std::string &method_name
                            , const std::string &arg = "");
};

typedef BaseExceptions LogicError;


#define INVALID_ARG_ERROR() InvalidArg(__FILE__ \
                                    , typeid(*this).name() \
                                    , __FUNCTION__)

class InvalidArg : public BaseExceptions {
  public:
    InvalidArg(const std::string& filename, const std::string& classname
               , const std::string& methodname);

    [[nodiscard]]
    const char *what() const noexcept override;
};


#define ARG_FILE_ERROR_ERROR(args) FileError(__FILE__ \
                                        , typeid(*this).name() \
                                        , __FUNCTION__, args)

class FileError : public BaseExceptions {
  public:
    FileError(const std::string& filename, const std::string& classname
              , const std::string& methodname, const std::string& arg);

    [[nodiscard]]
    const char *what() const noexcept override;
};

}  // namespace debug
