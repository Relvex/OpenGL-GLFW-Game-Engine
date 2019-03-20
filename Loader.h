#include <vector>

#pragma once
class Loader
{
public:
	Loader();
	RawModel loadToVAO(std::vector<float>);
private:
	int createVAO();
	void unbindVAO();
	void storeDataInAttribute(int, std::vector<float>);
};