#ifndef MESH
#define MESH
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "glew.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../freeglut/include/GL/glut.h"
#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

class mesh {
public:
	mesh(char* filename);
	glm::vec3 meshColor;
	void draw(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 transform);
	struct face {
		glm::vec3 ind1;
		glm::vec3 ind2;
		glm::vec3 ind3;
		glm::vec3 faceNormal;
		face(glm::vec3 i1, glm::vec3 i2, glm::vec3 i3,glm::vec3 _faceNormal) {
			ind1 = i1;
			ind2 = i2;
			ind3 = i3;
			faceNormal = _faceNormal;
		}
	};
private:
	bool isExtrusion;
	int numVerts;
	bool extrusionIsConvex;
	float extrusionLength;
	unsigned int numSlices;
	bool hasCaps;

	void readFile(char* filename);
	void constructBuffers();

	vector<glm::vec3> vertices;
	vector<face> faces;
	vector<glm::vec3> normals;
	vector<unsigned short> indices;
	vector<glm::vec3> colors;

	void constructExtrusion();
	void constructRevolution();
};

#endif