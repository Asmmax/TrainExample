#include <string>
#include <fstream>
#include <stack>

class LogSmartSection
{
private:
	bool _isValid;
	std::string _title;
public:
	LogSmartSection(const std::string& title);
	~LogSmartSection();
	void release();
};

class LogManager
{
	friend class LogSmartSection;
private:
	std::string _dirPath;
	std::string _currentFilePath;
	std::ofstream _file;

	std::stack<std::string> _stack;

public:
	~LogManager();
	static LogManager& getInstance();

	void init(const std::string& directory);
	void push(const std::string& title);
	LogSmartSection pushSmart(const std::string& title);
	void pop();
	void text(const std::string& msg);
};