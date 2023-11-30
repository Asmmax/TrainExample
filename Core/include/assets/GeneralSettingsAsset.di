bind "assets/GeneralSettingsAsset.hpp";

value LogSettings
{
	std::string logDir;
	vector<std::string> logs;
};

value GraphicsSettings
{
	int width = 640;
	int height = 420;
	int framerate = 60;
	bool fullscreen = false;
	bool vsync = true;
	int storedFrameCount = 1;
};

shared GeneralSettingsAsset
{
	GeneralSettingsAsset(LogSettings log, GraphicsSettings graphics);
} generalSettings;
