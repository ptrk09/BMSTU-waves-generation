#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

/*
Exclusion class when selecting a nonexistent array or matrix element
*/
class IndexException: public std::exception {
private:
    std::string m_error;
public:
    IndexException(std::string error);
    const char* what() const noexcept;
};


/*
Exception class when dealing with negative elements
*/
class NegativeValueException: public std::exception {
private:
    std::string m_error;
public:
    NegativeValueException(std::string error);
    const char* what() const noexcept;
};


class OutOfRangeException: public std::exception {
private:
    std::string m_error;
public:
    OutOfRangeException(std::string error);
    const char* what() const noexcept;
};



#endif
