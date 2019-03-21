#include <vector>

#pragma once
class GLUtils
{
public:
	static RawModel loadToVAO(std::vector<float>, std::vector<unsigned int>);
private:
	static void bindPositionsVBO(std::vector<float>);
	static void bindIndicesVBO(std::vector<unsigned int>);
};