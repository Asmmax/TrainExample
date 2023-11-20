#define _CRT_SECURE_NO_WARNINGS

#include "LogManager.hpp"
#include <filesystem>
#include <fstream>
#include <ctime>

LogManager::~LogManager()
{
	if (_cachedText.empty()) {
		return;
	}

	std::ofstream file;

	std::filesystem::create_directories(_dirPath);
	if (std::filesystem::is_directory(_dirPath)) {
		std::time_t currentTime_t = std::time(nullptr);
		std::string currentTimeStr;
		currentTimeStr.resize(std::size("yyyy.mm.dd_hh.mm.ss"), '_');
		std::strftime(currentTimeStr.data(), currentTimeStr.size(), "%Y.%m.%d_%H.%M.%S", std::localtime(&currentTime_t));
		currentTimeStr.resize(currentTimeStr.size() - 1);
		std::string currentFilePath = _dirPath + "/log_" + currentTimeStr + ".txt";
		file.open(currentFilePath, std::ios::ios_base::out);
	}

	if (file.is_open()) {
		file << _cachedText;
		file.close();
	}
}

LogManager& LogManager::getInstance()
{
	static LogManager instance;
	return instance;
}

void LogManager::init(const std::string& directory, const std::vector<std::string>& logs)
{
	_dirPath = directory;
	for (auto& logName : logs) {
		_logs.emplace(logName);
	}
}

void LogManager::push(const std::string& logName, const std::string& title)
{
	if (!_logs.count(logName)) {
		return;
	}

	text(logName, title + " - Begin:");
	_stack.push(title);
}

void LogManager::pop(const std::string& logName)
{
	if (!_logs.count(logName)) {
		return;
	}

	const std::string title = _stack.top();
	_stack.pop();
	text(logName, title + " - End:");
}

void LogManager::text(const std::string& logName, const std::string& msg)
{
	if (!_logs.count(logName)) {
		return;
	}

	for (int i = 0; i < _stack.size(); i++) {
		_cachedText.append("\t");
	}
	_cachedText.append(msg + "\n");
}
