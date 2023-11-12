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
	std::string _cachedText;

public:
	~LogManager();
	static LogManager& getInstance();

	void init(const std::string& directory);
	void push(const std::string& title);
	LogSmartSection pushSmart(const std::string& title);
	void pop();
	void text(const std::string& msg);
};

#ifdef _DEBUG

#define LOG_DEBUG(msg) LogManager::getInstance().text(msg)
#define LOG_DEBUG_PUSH(title) LogManager::getInstance().push(title)
#define LOG_DEBUG_POP() LogManager::getInstance().pop()

#else

#define LOG_DEBUG(msg)
#define LOG_DEBUG_PUSH(title)
#define LOG_DEBUG_POP()

#endif // _DEBUG