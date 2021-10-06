#pragma once
#include <exception>
#include <string>

class FileIsNotFound : public std::exception {
private:
	std::string error;
public:
	FileIsNotFound(const std::string& error) noexcept;
	const char* what() const noexcept override;
};

class WrongFormat : public std::exception {
private:
	std::string error;
public:
	WrongFormat(const std::string& error) noexcept;
	const char* what() const noexcept override;
};
