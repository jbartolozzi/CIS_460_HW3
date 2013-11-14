#include "mesh.h"

mesh::mesh(char* filename) {
	meshColor = glm::vec3(0.f,0.4,0.6);
	readFile(filename);
	constructBuffers();
}

void mesh::constructBuffers() {
	for (int i = 0; i < faces.size(); i++) {
		vbo.push_back(faces[i].ind1.x);
		vbo.push_back(faces[i].ind1.y);
		vbo.push_back(faces[i].ind1.z);
		vbo.push_back(1.f);

		vbo.push_back(faces[i].ind2.x);
		vbo.push_back(faces[i].ind2.y);
		vbo.push_back(faces[i].ind2.z);
		vbo.push_back(1.f);

		vbo.push_back(faces[i].ind3.x);
		vbo.push_back(faces[i].ind3.y);
		vbo.push_back(faces[i].ind3.z);
		vbo.push_back(1.f);

		nbo.push_back(faces[i].faceNormal.x);
		nbo.push_back(faces[i].faceNormal.y);
		nbo.push_back(faces[i].faceNormal.z);
		nbo.push_back(0.f);

		nbo.push_back(faces[i].faceNormal.x);
		nbo.push_back(faces[i].faceNormal.y);
		nbo.push_back(faces[i].faceNormal.z);
		nbo.push_back(0.f);

		nbo.push_back(faces[i].faceNormal.x);
		nbo.push_back(faces[i].faceNormal.y);
		nbo.push_back(faces[i].faceNormal.z);
		nbo.push_back(0.f);

		cbo.push_back(meshColor.r);
		cbo.push_back(meshColor.g);
		cbo.push_back(meshColor.b);

		cbo.push_back(meshColor.r);
		cbo.push_back(meshColor.g);
		cbo.push_back(meshColor.b);

		cbo.push_back(meshColor.r);
		cbo.push_back(meshColor.g);
		cbo.push_back(meshColor.b);
	}

	for (int i = 0; i < faces.size() * 3; i++) {
		indices.push_back(i);
	}
}

void mesh::readFile(char* filename) {
	ifstream file(filename);
	while (!file.good()) {
		cout << "Invalid File Name Please Try Again: ";
		char* filename = new char[25];
		cin >> filename;
		file.open(filename);
	}
	
	char line[100];
	file.getline(line,10);
	char* token1 = strtok(line," ");
	if (strcmp(token1,"extrusion") == 0) {
		isExtrusion = true;
		// get the height of the extrusion
		char line2[10];
		file.getline(line2,10);
		char* extrusionH = strtok(line2," ");
		extrusionLength = atof(extrusionH);
			
		char line3[10];
		file.getline(line3,10);
		char* numPoints = strtok(line3," ");
		numVerts = atof(numPoints);

		for (int i = 0; i < numVerts; i++) {
			char currentLine[20];
			file.getline(currentLine,20);
			char* xString = strtok(currentLine," ");
			char* zString = strtok(NULL," ");
			glm::vec3 newVertex = glm::vec3(atof(xString), 0.f, atof(zString));
			vertices.push_back(newVertex);
		}
		constructExtrusion();
	}

	else if (strcmp(token1,"surfrev")==0){
		isExtrusion = false;
		// get the number of radial slices
		char line2[10];
		file.getline(line2,10);
		char* slicS = strtok(line2," ");
		numSlices = atoi(slicS);

		if (numSlices < 3) {
			int newInput;
			cout << "The number of radial slices is less than 3." << endl;
		}
		else {
			char line3[10];
			file.getline(line3,10);
			char* numPoints = strtok(line3," ");
			numVerts = atof(numPoints);

			hasCaps = true;
			float checkX;
			for (int i = 0; i < numVerts; i++) {
				char currentLine[20];
				file.getline(currentLine,20);
				char* xString = strtok(currentLine," ");
				char* zString = strtok(NULL," ");
				glm::vec3 newVertex = glm::vec3(atof(xString), atof(zString), 0.f);
				
				glm::vec3 check;
				if (i == 0) {
					check = newVertex;
					//vertices.push_back(glm::vec3(0.f,newVertex.y,0.f)); 
				}
				vertices.push_back(newVertex);

				if (i == numVerts - 1 && newVertex != check) {
					//vertices.push_back(check); 
				}
			}
			constructRevolution();
		}
	}
	else {
		cout << "The input file is not configured correctly. Please retry." << endl;
	}
}

void mesh::draw(unsigned int _vbo, unsigned int _cbo, unsigned int _ibo, unsigned int _nbo, unsigned int positionLocation,
		unsigned int colorLocation, unsigned int normalLocation, unsigned int u_modelMatrixLocation, glm::mat4 transform) {
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vbo.size() * sizeof(float), &vbo[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	//always make sure you are telling OpenGL the right size to make the buffer, color data doesn't have as much data!
	glBufferData(GL_ARRAY_BUFFER, cbo.size() * sizeof(float), &cbo[0], GL_STREAM_DRAW);	//the color is going to change every frame

	glBindBuffer(GL_ARRAY_BUFFER, _nbo);
	glBufferData(GL_ARRAY_BUFFER, nbo.size() * sizeof(float), &nbo[0], GL_STATIC_DRAW); //the square normals don't need to change, ever,

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);
	
	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//now use color data, remember we're not using 4 at a time anymore
	glBindBuffer(GL_ARRAY_BUFFER, _cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));
	
	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, _nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &transform[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, indices.size() * sizeof(unsigned short), GL_UNSIGNED_SHORT, 0);
	
	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}

void mesh::constructExtrusion() {
	//convexity test
	extrusionIsConvex = true;
	int firstIsPositive = 0;
	for (int i = 0; i < vertices.size(); i++) {
		if ( i < vertices.size() - 2) {
			glm::vec3 a = vertices[i+1] - vertices[i];
			glm::vec3 b = vertices[i+2] - vertices[i+1];
			glm::vec3 cross = glm::normalize(glm::cross(a,b));
			if (cross.y > 0) {
				if (firstIsPositive == 0) {
					firstIsPositive = 1;
				}
				else {
					if (firstIsPositive < 0) {
						extrusionIsConvex = false;
					}
				}
			}
			else {
				if (firstIsPositive == 0) {
					firstIsPositive = -1;
				}
				else {
					if (firstIsPositive > 0) {
						extrusionIsConvex = false;
					}
				}
			}
		}
		else if (i == vertices.size() - 2) {
			glm::vec3 a = vertices[i+1] - vertices[i];
			glm::vec3 b = vertices[0] - vertices[i+1];
			glm::vec3 cross = glm::normalize(glm::cross(a,b));
			if ((cross.y > 0 && firstIsPositive < 0) || (cross.y < 0 && firstIsPositive > 0)){
				extrusionIsConvex = false;
			}
		}
		else {
			glm::vec3 a = vertices[0] - vertices[i];
			glm::vec3 b = vertices[1] - vertices[0];
			glm::vec3 cross = glm::normalize(glm::cross(a,b));
			if ((cross.y > 0 && firstIsPositive < 0) || (cross.y < 0 && firstIsPositive > 0)){
				extrusionIsConvex = false;
			}
		}
	}
	if (extrusionIsConvex) {
		cout << "it is convex" << endl;
	}
	else {
		cout << "it is not convex" << endl;
	}
	// add the top polygon
	for (int i = 0; i < numVerts; i++) {
			vertices.push_back(glm::vec3(vertices[i].x,extrusionLength,vertices[i].z));
	}

	// if extrusion is convex make the caps
	if (extrusionIsConvex) {
		//make the bottom cap
		for(int i = 0; i < numVerts - 3; i++) {
			faces.push_back(face(vertices[0],vertices[i+1],vertices[i+2],glm::vec3(0,-1,0)));
		}
		//make the top cap
		for(int i = 0; i < numVerts - 3; i++) {
			faces.push_back(face(vertices[numVerts],vertices[numVerts+i+1],vertices[numVerts+i+2],glm::vec3(0,1,0)));
		}
		//make the walls
		for(int i = 0; i < numVerts - 1; i++) {
			glm::vec3 a = vertices[i+1] - vertices[i];
			glm::vec3 b = vertices[i+numVerts+1] - vertices[i];
			glm::vec3 norm = glm::normalize(glm::cross(a,b));
			faces.push_back(face(vertices[i],vertices[i+1],vertices[i+numVerts+1],norm));
			faces.push_back(face(vertices[i],vertices[i+numVerts],vertices[i+numVerts+1],norm));
		}
	}
	else {
		//dont make the caps
		//make the walls
		for(int i = 0; i < numVerts - 1; i++) {
			glm::vec3 a = vertices[i+1] - vertices[i];
			glm::vec3 b = vertices[i+numVerts+1] - vertices[i];
			glm::vec3 norm = glm::normalize(glm::cross(a,b));
			faces.push_back(face(vertices[i],vertices[i+1],vertices[i+numVerts+1],norm));
			faces.push_back(face(vertices[i],vertices[i+numVerts],vertices[i+numVerts+1],norm));
		}
	}
}

void mesh::constructRevolution() {
	vector<glm::vec3> current = vertices;
	// set the current points to the original non cap points

	for (int i = 0; i < numSlices; i++) {
		vector<glm::vec3> next;
		float theta = 360.f / float(numSlices);//get the current angle 
		
		for (int j = 0; j < current.size(); j++) {
			glm::vec4 newP = glm::rotate(theta,glm::vec3(0,1,0)) * glm::vec4(current[j],0.f);
			next.push_back(glm::vec3(newP.x,newP.y,newP.z));
		}

		// bottom cap slice
		glm::vec3 a = current[1] - current[0];
		glm::vec3 b = next[0] - current[0];
		glm::vec3 norm = -glm::normalize(glm::cross(a,b));
		faces.push_back(face(current[0],current[1],next[1],norm));
		faces.push_back(face(next[0],next[1],current[0],norm));

		// make in between faces
		for (int k = 0; k < current.size() - 1; k++) {
			//current[i] current[i+1] next[i]
			//next[i] next[i+1] current[i+1]
			a = current[k+1] - current[k];
			b = next[k] - current[k];
			norm = -glm::normalize(glm::cross(a,b));
			faces.push_back(face(current[k],current[k+1],next[k],norm));
			faces.push_back(face(next[k],next[k+1],current[k+1],norm));
		}

		// top cap slice
		a = current[current.size()-2] - current[current.size() -1];
		b = next[next.size()-1] - current[current.size() - 1];
		norm = glm::normalize(glm::cross(a,b));
		faces.push_back(face(current[current.size() - 1], current[current.size() - 2],next[next.size() - 2],norm));
		faces.push_back(face(next[next.size() - 1],next[next.size() - 2],current[current.size() -1],norm));

		current = next;
	}
}