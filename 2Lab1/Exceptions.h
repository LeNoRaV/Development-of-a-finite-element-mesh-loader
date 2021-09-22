#pragma once

class ContainerError : public std::exception {
private:
	std::string error;
public:
	ContainerError(const std::string& error) noexcept;
	const char* what() const noexcept override;
};

class IteratorError : public std::exception {
private:
	std::string error;
public:
	IteratorError(const std::string& error) noexcept;
	const char* what() const noexcept override;
};
