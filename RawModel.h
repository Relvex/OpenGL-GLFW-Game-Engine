#pragma once
class RawModel
{
public:
	RawModel(int, int);
	int getVaoID() const { return vaoID; };
	int getVertexCount() const { return vertexCount; };
private:
	int vaoID;
	int vertexCount;
};

