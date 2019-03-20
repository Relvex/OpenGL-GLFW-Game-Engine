#pragma once
class RawModel
{
public:
	RawModel(int, int);
	int getVaoID(void) const { return vaoID; };
	int getVertexCount(void) const { return vertexCount; };
private:
	int vaoID;
	int vertexCount;
};

