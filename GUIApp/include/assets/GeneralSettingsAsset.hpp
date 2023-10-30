#include <string>

/// @serializable
struct GeneralSettings
{
	std::string logDir;
	float frameFrequence{ 60.f };
	bool fullscreen{ false };
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