#pragma once
#include <memory>
#include <vector>

class ACurve;
class World;

class TrainBuilder
{
public:
	TrainBuilder(const std::shared_ptr<ACurve>& path, unsigned int block_count, float velocity, float block_length = 1.0f, float gap = 0.2f);
	
	void Build(World* world);
private:
	std::vector<float> _initial_params;
	std::shared_ptr<ACurve> _path;
	float _velocity;
	float _block_length;
	unsigned int _block_count;
};

