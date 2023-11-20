#include <string>
#include <stack>
#include <unordered_set>
#include <vector>

class LogManager
{
private:
	std::string _dirPath;
	std::unordered_set<std::string> _logs;

	std::stack<std::string> _stack;
	std::string _cachedText;

public:
	~LogManager();
	static LogManager& getInstance();

	void init(const std::string& directory, const std::vector<std::string>& logs);

	void push(const std::string& logName, const std::string& title);
	void pop(const std::string& logName);
	void text(const std::string& logName, const std::string& msg);
};

#define LOG(msg) LogManager::getInstance().text("common", msg)
#define LOG_PUSH(title) LogManager::getInstance().push("common", title)
#define LOG_POP() LogManager::getInstance().pop("common")

#define LOG_EX(name, msg) LogManager::getInstance().text(name, msg)
#define LOG_PUSH_EX(name, title) LogManager::getInstance().push(name, title)
#define LOG_POP_EX(name) LogManager::getInstance().pop(name)

#ifdef _DEBUG

#define LOG_DEBUG(msg) LogManager::getInstance().text("common", msg)
#define LOG_DEBUG_PUSH(title) LogManager::getInstance().push("common", title)
#define LOG_DEBUG_POP() LogManager::getInstance().pop("common")

#define LOG_DEBUG_EX(name, msg) LogManager::getInstance().text(name, msg)
#define LOG_DEBUG_PUSH_EX(name, title) LogManager::getInstance().push(name, title)
#define LOG_DEBUG_POP_EX(name) LogManager::getInstance().pop(name)

#else

#define LOG_DEBUG(msg)
#define LOG_DEBUG_PUSH(title)
#define LOG_DEBUG_POP()

#define LOG_DEBUG_EX(name, msg)
#define LOG_DEBUG_PUSH_EX(name, title)
#define LOG_DEBUG_POP_EX(name)

#endif // _DEBUG
