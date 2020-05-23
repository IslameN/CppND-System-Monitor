#include <string>

#include "format.h"

#include <iostream>
using std::string;

// This namespace with two similar funtions is just done for learning purposes.
namespace {
std::string AddDigitIfNeeded(const std::string& digits) {
    if (digits.size() == 1) {
        return std::to_string(0) + digits;
    } else {
        return digits;
    }
}
void AddDigitIfNeededPointer(std::string* digits) {
    if (digits->size() == 1) {
        *digits = std::to_string(0) + *digits;
    }
}
}  // namespace

string Format::ElapsedTime(long secondsString) {
    string hours = std::to_string(secondsString / 3600);
    hours = AddDigitIfNeeded(hours);

    string minutes = std::to_string(secondsString % 3600 / 60);
    AddDigitIfNeededPointer(&minutes);

    string seconds = std::to_string(secondsString % 60);
    AddDigitIfNeededPointer(&seconds);
    return hours + ":" + minutes + ":" + seconds;
}
