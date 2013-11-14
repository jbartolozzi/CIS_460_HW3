#include "furniture.h"

void furniture::draw(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 transform, glm::vec3 _color, bool selected) {
	for (int i = 0; i < primatives.size(); i++) {
		primatives[i]->color = _color;
		primatives[i]->isSelected = selected;
		primatives[i]->constructBuffers();
		primatives[i]->drawPrimative(_vbo, _cbo, _ibo, _nbo, positionLocation, colorLocation, normalLocation, u_modelMatrixLocation, transform);
	}
}

ffloor::ffloor(int x, int z) {
	cube* c = new cube(glm::vec3(0.f,-0.1f,0.f),glm::vec3(0.9f,0.9f,0.9f),glm::vec3((float)x,0.1f,(float)z));
	primatives.push_back(c);
	height = 0.1f;
}

chair::chair(glm::vec3 _color) {
	furnitureColor = _color;
	cylinder* c1 = new cylinder(glm::vec3(0.5f,0.f,-0.5f),furnitureColor,glm::vec2(0.1f,1.f));
	cylinder* c2 = new cylinder(glm::vec3(0.5f,0.f,0.5f),furnitureColor,glm::vec2(0.1f,1.f));
	cylinder* c3 = new cylinder(glm::vec3(-0.5f,0.f,-0.5f),furnitureColor,glm::vec2(0.1f,1.f));
	cylinder* c4 = new cylinder(glm::vec3(-0.5f,0.f,0.5f),furnitureColor,glm::vec2(0.1f,1.f));
	primatives.push_back(c1);
	primatives.push_back(c2);
	primatives.push_back(c3);
	primatives.push_back(c4);

	cube* cb1 = new cube(glm::vec3(0.f,1.f,0.f),furnitureColor,glm::vec3(1.2f,0.2,1.2f));
	primatives.push_back(cb1);

	sphere* c5 = new sphere(glm::vec3(0.f,1.2f,-0.6f),furnitureColor,0.2f);
	primatives.push_back(c5);

	cube* cb2 = new cube(glm::vec3(0.f,1.8f,-0.5f),furnitureColor,glm::vec3(1.2f,0.8f,0.2f));
	primatives.push_back(cb2);

	height = 2.f;
}

table::table(glm::vec3 _color) {
	furnitureColor = _color;
	cylinder* c1 = new cylinder(glm::vec3(1.5f,0.f,-1.f),furnitureColor,glm::vec2(0.1f,1.3f));
	cylinder* c2 = new cylinder(glm::vec3(1.5f,0.f,1.f),furnitureColor,glm::vec2(0.1f,1.3f));
	cylinder* c3 = new cylinder(glm::vec3(-1.5f,0.f,-1.f),furnitureColor,glm::vec2(0.1f,1.3f));
	cylinder* c4 = new cylinder(glm::vec3(-1.5f,0.f,1.f),furnitureColor,glm::vec2(0.1f,1.3f));
	primatives.push_back(c1);
	primatives.push_back(c2);
	primatives.push_back(c3);
	primatives.push_back(c4);

	cube* cb1 = new cube(glm::vec3(0.f,1.3f,0.f),furnitureColor,glm::vec3(3.2f,0.2,2.2f));
	primatives.push_back(cb1);

	sphere* s1 = new sphere(glm::vec3(1.5f,0.1f,-1.f),furnitureColor,0.2f);
	sphere* s2 = new sphere(glm::vec3(1.5f,0.1f,1.f),furnitureColor,0.2f);
	sphere* s3 = new sphere(glm::vec3(-1.5f,0.1f,-1.f),furnitureColor,0.2f);
	sphere* s4 = new sphere(glm::vec3(-1.5f,0.1f,1.f),furnitureColor,0.2f);

	primatives.push_back(s1);
	primatives.push_back(s2);
	primatives.push_back(s3);
	primatives.push_back(s4);

	height = 1.5f;
}

fileCabinet::fileCabinet(glm::vec3 _color) {
	furnitureColor = _color;
	sphere* s1 = new sphere(glm::vec3(1.5f,0.1f,-0.5f),furnitureColor,0.2f);
	sphere* s2 = new sphere(glm::vec3(1.5f,0.1f,0.5f),furnitureColor,0.2f);
	sphere* s3 = new sphere(glm::vec3(-1.5f,0.1f,-0.5f),furnitureColor,0.2f);
	sphere* s4 = new sphere(glm::vec3(-1.5f,0.1f,0.5f),furnitureColor,0.2f);

	primatives.push_back(s1);
	primatives.push_back(s2);
	primatives.push_back(s3);
	primatives.push_back(s4);

	cube* cb1 = new cube(glm::vec3(0.f,0.3f,0.f),furnitureColor,glm::vec3(3.2f,0.2,1.2f));
	primatives.push_back(cb1);

	cube* cb2 = new cube(glm::vec3(0.f,1.3f,0.f),furnitureColor,glm::vec3(3.2f,0.2,1.2f));
	primatives.push_back(cb2);

	cube* cb3 = new cube(glm::vec3(0.f,2.3f,0.f),furnitureColor,glm::vec3(3.2f,0.2,1.2f));
	primatives.push_back(cb3);

	cylinder* c1 = new cylinder(glm::vec3(1.5f,0.2f,-0.5f),furnitureColor,glm::vec2(0.1f,2.1f));
	cylinder* c2 = new cylinder(glm::vec3(1.5f,0.2f,0.5f),furnitureColor,glm::vec2(0.1f,2.1f));
	cylinder* c3 = new cylinder(glm::vec3(-1.5f,0.2f,-0.5f),furnitureColor,glm::vec2(0.1f,2.1f));
	cylinder* c4 = new cylinder(glm::vec3(-1.5f,0.2f,0.5f),furnitureColor,glm::vec2(0.1f,2.1f));
	primatives.push_back(c1);
	primatives.push_back(c2);
	primatives.push_back(c3);
	primatives.push_back(c4);

	height = 2.5f;
}

lamp::lamp(glm::vec3 _color) {
	furnitureColor = _color;
	cube* cb1 = new cube(glm::vec3(0.f,0.25f,0.f),furnitureColor,glm::vec3(0.5f,0.5f,0.5f));
	primatives.push_back(cb1);

	sphere* s1 = new sphere(glm::vec3(0.f,0.5f,0.f),furnitureColor,0.2f);
	primatives.push_back(s1);

	cylinder* c1 = new cylinder(glm::vec3(0.f,0.7f,0.f),furnitureColor,glm::vec2(0.4f,0.1f));
	primatives.push_back(c1);

	cylinder* c2 = new cylinder(glm::vec3(0.f,0.9f,0.f),furnitureColor,glm::vec2(0.2f,0.1f));
	primatives.push_back(c2);

	height = 1.f;
}

meshFurniture::meshFurniture(glm::vec3 _color, char* filename) {
	furnitureColor = _color;
	mesh* m1 = new mesh(filename);
	height = m1->findHeight();
	primatives.push_back(m1);
}