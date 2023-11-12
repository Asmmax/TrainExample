#pragma once
#include <string>

/// @serializable
struct GeneralSettings
{
	std::string logDir;
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
	GeneralSettings _settings;

public:
	GeneralSettingsAsset(const GeneralSettings& settings);

	const GeneralSettings& getSettings() const { return _settings; }
};