#include "exception.h"


IndexException::IndexException(std::string error): m_error(error) {}


const char* IndexException::what() const noexcept {
    return m_error.c_str();
}


NegativeValueException::NegativeValueException(std::string error): m_error(error) {}


const char* NegativeValueException::what() const noexcept {
    return m_error.c_str();
}


OutOfRangeException::OutOfRangeException(std::string error): m_error(error) {}


const char* OutOfRangeException::what() const noexcept {
    return m_error.c_str();
}
