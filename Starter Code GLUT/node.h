#ifndef NODE
#define NODE
#include "furniture.h"

class node {
public:
	node* parent;
	vector<node*>* children;
	furniture* nodeFurniture;
	float rotation;
	glm::vec3 scale;
	glm::vec3 translation;
	glm::vec3 color;
	bool selected;
	// parent, children, funiture, rotation, scale, translation
	node(node* _parent, vector<node*>* _children, furniture* _nodeFurniture, float _rotation, glm::vec3 _scale, glm::vec3 _translation, glm::vec3 _color) {
		parent = _parent;
		children = _children;
		nodeFurniture = _nodeFurniture;
		rotation = _rotation;
		scale = _scale;
		translation = _translation;
		color = _color;
		selected = false;
	}
	node* head;
	node* selectedNode;
	void traverse(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 matrix);
};
#endif