#pragma once

class Loader;

/// @serializable @abstract @shared
class GraphicalAsset
{
	friend class AssetManager;

public:
	virtual ~GraphicalAsset() = default;

	virtual void loadToGPU() = 0;
};
