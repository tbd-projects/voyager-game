//
// Created by flashie on 04.05.2021.
//
#ifndef VOYAGER_EXCEPTIONS_HPP
#define VOYAGER_EXCEPTIONS_HPP

#include <exception>
#include <string>
#include <cstring>
#include <chrono>
#include <time.h>

class BaseExceptions : public std::exception {
public:
    BaseExceptions(std::string filename, std::string classname, std::string methodname, std::string arg = "") {
        error_info = "\nFile: " + filename + \
                     "\nClass: " + classname + \
                     "\nMethod: " + methodname;
        if (!arg.empty()) {
            error_info += "\n Argument: " + arg;
        }
    }

    virtual const char *what() const noexcept override {
        std::string message = "\nERROR: Something is wrong with your game." + error_info;
        return message.c_str();
    }

protected:
    std::string error_info;
};

class InvalidArg : public BaseExceptions {
public:
    InvalidArg(std::string filename, std::string classname, std::string methodname) :
            BaseExceptions(filename, classname, methodname) {};

    virtual const char *what() const noexcept override {
        std::string message = "\nERROR: Invalid argument. " + error_info;
        return message.c_str();
    }
};
class FileError : public BaseExceptions {
public:
    FileError(std::string filename, std::string classname, std::string methodname, std::string arg) :
            BaseExceptions(filename, classname, methodname, arg) {};

    virtual const char *what() const noexcept override {
        std::string message = "\nERROR: Invalid argument. " + error_info;
        return message.c_str();
    }
};


#endif //VOYAGER_EXCEPTIONS_HPP
