#pragma once

#include <stdexcept>
#include <string_view>


namespace debug {

class VAException : public std::exception {
  public:
    VAException();

    explicit VAException(const std::string_view &error);

    [[nodiscard]]
    const char *what() const noexcept override;

  protected:
    std::string _name_error;
};

class BaseExceptions : public VAException {
  public:
    BaseExceptions();

    explicit BaseExceptions(const std::string_view &error);

    BaseExceptions(const std::string_view &filename,
                   const std::string_view &classname,
                   const std::string_view &method_name,
                   const std::string_view &arg = "");
};

class PhysicalException : public BaseExceptions {
  public:
    PhysicalException();

    explicit PhysicalException(const std::string_view &error);
};

class MathException : public BaseExceptions {
  public:
    MathException();

    explicit MathException(const std::string_view &error);
};


#define ARG_LOAD_ERROR(args) LoadException(__FILE__, typeid(*this).name() \
                                                    , __FUNCTION__, args)
#define LOAD_ERROR() LoadException(__FILE__, typeid(*this).name(), __FUNCTION__)

class LoadException : public BaseExceptions {
  public:
    LoadException();

    LoadException(const std::string_view &filename,
                  const std::string_view &classname,
                  const std::string_view &method_name,
                  const std::string_view &arg = "");
};


#define ARG_ARGUMENT_ERROR(args) ArgumentException(__FILE__ \
                                        , typeid(*this).name() \
                                        , __FUNCTION__, args)
#define ARGUMENT_ERROR() ArgumentException(__FILE__, typeid(*this).name() \
                                                        , __FUNCTION__)

class ArgumentException : public BaseExceptions {
  public:
    ArgumentException();

    ArgumentException(const std::string_view &filename,
                      const std::string_view &classname,
                      const std::string_view &method_name,
                      const std::string_view &arg = "");
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

    UnexpectedCallException(const std::string_view &filename,
                            const std::string_view &classname,
                            const std::string_view &method_name,
                            const std::string_view &arg = "");
};

}  // namespace debug
