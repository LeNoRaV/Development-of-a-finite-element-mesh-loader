#include "Exceptions.h"

FileIsNotFound::FileIsNotFound(const std::string& error) noexcept:  error("The file " + error + " is not found ") {}

const char* FileIsNotFound::what() const noexcept {
	return error.c_str();
}


WrongFormat::WrongFormat(const std::string& error) noexcept : error("The wrong format of the file " + error) {}

const char* WrongFormat::what() const noexcept {
	return error.c_str();
}
