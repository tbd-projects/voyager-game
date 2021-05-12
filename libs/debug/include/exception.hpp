#pragma once
//
// Created by flashie on 04.05.2021.
//
#include <exception>
#include <string>
#include <cstring>
#include <chrono>

class BaseExceptions : public std::exception {
public:
    BaseExceptions(std::string filename, std::string classname, std::string methodname, std::string arg = "") {
        _error_info = "\nFile: " + filename + \
                     "\nClass: " + classname + \
                     "\nMethod: " + methodname;
        if (!arg.empty()) {
            _error_info += "\n Argument: " + arg;
        }
    }

    virtual const char *what() const noexcept override {
        std::string message = "\nERROR: Something is wrong with your game." + _error_info;
        return message.c_str();
    }

protected:
    std::string _error_info;
};

class InvalidArg : public BaseExceptions {
public:
    InvalidArg(std::string filename, std::string classname, std::string methodname) :
            BaseExceptions(filename, classname, methodname) {};

    virtual const char *what() const noexcept override {
        std::string message = "\nERROR: Invalid argument. " + _error_info;
        return message.c_str();
    }
};
class FileError : public BaseExceptions {
public:
    FileError(std::string filename, std::string classname, std::string methodname, std::string arg) :
            BaseExceptions(filename, classname, methodname, arg) {};

    virtual const char *what() const noexcept override {
        std::string message = "\nERROR: Invalid argument. " + _error_info;
        return message.c_str();
    }
};
class LoadError: public BaseExceptions {
public:
    LoadError(std::string filename, std::string classname, std::string methodname, std::string arg) :
            BaseExceptions(filename, classname, methodname, arg) {};

    virtual const char *what() const noexcept override {
        std::string message = "\nERROR: Error load data from file. " + _error_info;
        return message.c_str();
    }
};
class LogicError: public BaseExceptions {
public:
    LogicError(std::string filename, std::string classname, std::string methodname, std::string arg) :
            BaseExceptions(filename, classname, methodname, arg) {};

    virtual const char *what() const noexcept override {
        std::string message = "\nERROR: Logic error. " + _error_info;
        return message.c_str();
    }
};