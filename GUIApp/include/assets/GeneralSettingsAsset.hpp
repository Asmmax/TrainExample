#pragma once
#include <string>
#include <vector>

/// @serializable
struct LogSettings
{
	std::string logDir;
	std::vector<std::string> logs;
};

/// @serializable
struct GraphicsSettings
{
	int width{ 640 };
	int height{ 420 };
	int framerate{ 60 };
	bool fullscreen{ false };
	bool vsync{ true };
	int storedFrameCount{ 1 };
};

/// @serializable @shared generalSettings
class GeneralSettingsAsset
{
private:
	LogSettings _logSettings;
	GraphicsSettings _graphicsSettings;

public:
	GeneralSettingsAsset(const LogSettings& log, const GraphicsSettings& graphics);

	const LogSettings& getLogSettings() const { return _logSettings; }
	const GraphicsSettings& getGraphicsSettings() const { return _graphicsSettings; }
};