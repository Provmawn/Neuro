#ifndef RUNTIMEERROR_H
#define RUNTIMEERROR_H
#include <memory>
#include <stdexcept>
#include <string>

class RuntimeError : public std::runtime_error
{
public:
	RuntimeError() = default;
	explicit RuntimeError(const std::string &error_message, const std::string &path = "")
		: std::runtime_error(error_message)
		, m_error_message{ error_message + path }
	{
	}
	virtual const char* what() const noexcept
	{
		return m_error_message.c_str();
	}
private:
	std::string m_error_message;
};
#endif