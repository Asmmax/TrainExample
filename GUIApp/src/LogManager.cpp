#include "LogManager.hpp"
#include <filesystem>
#include <assert.h>

LogSmartSection::LogSmartSection(const std::string& title):
	_isValid(true),
	_title(title)
{
}

LogSmartSection::~LogSmartSection()
{
	release();
}

void LogSmartSection::release()
{
	if (_isValid) {
		LogManager& logManager = LogManager::getInstance();
		assert(logManager._stack.top() == _title);
		logManager.pop();
		_isValid = false;
	}
}

LogManager::~LogManager()
{
	if (!_file.is_open()) {
		_file.close();
	}
}

LogManager& LogManager::getInstance()
{
	static LogManager instance;
	return instance;
}

void LogManager::init(const std::string& directory)
{
	std::filesystem::create_directories(directory);
	if (std::filesystem::is_directory(directory)) {
		_dirPath = directory;
		_currentFilePath = directory + "/log.txt";
		_file.open(_currentFilePath, std::ios::ios_base::out);
	}
}

void LogManager::push(const std::string& title)
{
	text(title + " - Begin:");
	_stack.push(title);
}

LogSmartSection LogManager::pushSmart(const std::string& title)
{
	push(title);
	return LogSmartSection(title);
}

void LogManager::pop()
{
	const std::string title = _stack.top();
	_stack.pop();
	text(title + " - End:");
}

void LogManager::text(const std::string& msg)
{
	for (int i = 0; i < _stack.size(); i++) {
		_file << "\t";
	}
	_file << msg << std::endl;
}
