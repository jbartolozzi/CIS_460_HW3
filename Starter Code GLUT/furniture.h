#ifndef FURNITURE
#define FURNITURE
#include "primative.h"

class furniture {
public:
	glm::vec3 furnitureColor;
	float height;
	vector<primative*> primatives;
	void draw(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 transform, glm::vec3 _color, bool selected);
};

class ffloor : public furniture {
public:
	ffloor(int x, int z);
};

class chair : public furniture {
public:
	chair(glm::vec3 _color);
};

class table : public furniture {
public:
	table(glm::vec3 _color);
};

class fileCabinet : public furniture {
public:
	fileCabinet(glm::vec3 _color);
};

class lamp : public furniture {
public:
	lamp(glm::vec3 _color);
};

class meshFurniture : public furniture {
public:
	meshFurniture(glm::vec3 _color, char* filename);
};
#endif