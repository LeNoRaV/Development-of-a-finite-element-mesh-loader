ContainerError::ContainerError(const std::string& error) noexcept : error("Container Error: " + error) {}
const char* ContainerError::what() const noexcept {
	return error.c_str();
}

IteratorError::IteratorError(const std::string& error) noexcept : error("Iterator Error: " + error) {}
const char* IteratorError::what() const noexcept {
	return error.c_str();
}
