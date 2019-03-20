#include <vector>

#pragma once
class Loader
{
public:
	RawModel loadToVAO(std::vector<float>);
private:
	int createVAO();
	void unbindVAO();
	void storeDataInAttribute(int, std::vector<float>);
};