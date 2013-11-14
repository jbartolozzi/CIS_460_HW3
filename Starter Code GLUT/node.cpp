#include "node.h"

void node::traverse(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 matrix){
		
		glm::mat4 scaleNode = glm::scale(scale.x,scale.y,scale.z);
		glm::mat4 rotateNode = glm::rotate(rotation,glm::vec3(0,1,0));
		glm::mat4 transNode = glm::translate(translation);

		glm::mat4 heightTransform;
		if (parent == NULL) {
			heightTransform = glm::mat4(1.f);
		}
		else {
			float moveUP = parent->scale.y * parent->nodeFurniture->height;
			heightTransform = glm::translate(0.f,moveUP,0.f);
		}

		glm::mat4 out = matrix * heightTransform * transNode * rotateNode * scaleNode;

		nodeFurniture->draw(_vbo, _cbo, _ibo, _nbo, positionLocation,colorLocation,normalLocation, u_modelMatrixLocation, out, color, selected);

		if (children != NULL) {
		for (int i = 0; i < children->size(); i++) {
				children->at(i)->traverse(_vbo, _cbo, _ibo, _nbo, positionLocation,colorLocation,normalLocation, u_modelMatrixLocation, out);
			}
		}
}