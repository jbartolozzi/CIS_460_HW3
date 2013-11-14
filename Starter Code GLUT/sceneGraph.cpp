#include "sceneGraph.h"

sceneGraph::sceneGraph(char* filename) {
	currentMeshNumber = 0;
	ifstream file(filename);
	while (!file.good()) {
		cout << "Invalid File Name Please Try Again: ";
		char* filename = new char[25];
		cin >> filename;
		file.open(filename);
	}

	while(!file.eof()) {
		char line[100];
		file.getline(line,10);
		char* in1 = strtok(line, " ");
		char* in2 = strtok(NULL," ");
		char* in3 = strtok(NULL," ");

		xSize = atof(in1);
		zSize = atof(in2);
		numObjects = atoi(in3);

		char space[100];
		char line2[100];
		char line3[100];
		char line4[100];
		char line5[100];
		char line6[100];
		file.getline(space,100);
		file.getline(line2,100);
		file.getline(line3,100);
		file.getline(line4,100);
		file.getline(line5,100);
		file.getline(line6,100);
		
		if (strcmp(line2,"mesh")==0) {
			char line7[100];
			file.getline(line7,100);
			readMeshBlock(line3,line4,line5,line6,line7);
		}
		else {
			readObjBlock(line2,line3,line4,line5,line6);
		}

		for (int i = 1; i < numObjects; i++) {
			char space2[100];
			char line22[100];
			char line32[100];
			char line42[100];
			char line52[100];
			char line62[100];
			file.getline(space2,100);
			file.getline(line22,100);
			file.getline(line32,100);
			file.getline(line42,100);
			file.getline(line52,100);
			file.getline(line62,100);
			if (strcmp(line22,"mesh")==0) {
				char line72[100];
				file.getline(line72,100);
				readMeshBlock(line32,line42,line52,line62,line72);
			}
			else {
				readObjBlock(line22,line32,line42,line52,line62);
			}
		}
	}
	chair* chair1 = new chair(glm::vec3(0.f,0.6,0.8));
	lamp* lamp1 = new lamp(glm::vec3(0.f,0.6,0.8));
	table* table1 = new table(glm::vec3(0.f,0.6,0.8));
	fileCabinet* fc1 = new fileCabinet(glm::vec3(0.f,0.6,0.8));

	ffloor *floor1 = new ffloor(3*xSize,3*zSize);
	node* rootFloor = new node(NULL,NULL,floor1,0.f,glm::vec3(1.f,1.f,1.f),glm::vec3(3.f,0.f,0.f),glm::vec3(0.7,0.7,0.7));
	root = rootFloor;
	vector<node*>* newChildren = new vector<node*>;
	
	
	for(int i = 0; i < xSize * zSize; i++) {
		indexMap.push_back(NULL);
	}

	for (int i = 0; i < numObjects; i++) {
		if (objectTypes[i] == CHAIR) {
			if (indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] == NULL) {
				node* newNode = new node(rootFloor,NULL,chair1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] = newNode;
				newChildren->push_back(newNode);
			}
			else {
				node* newNode = new node(indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y],NULL,chair1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				handleChildren(i,newNode);
			}
		}
		else if(objectTypes[i] == LAMP) {
			if (indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] == NULL) {
				node* newNode = new node(rootFloor,NULL,lamp1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] = newNode;
				newChildren->push_back(newNode);
			}
			else {
				node* newNode = new node(indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y],NULL,lamp1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				handleChildren(i,newNode);
			}
		}
		else if(objectTypes[i] == TABLE) {
			if (indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] == NULL) {
				node* newNode = new node(rootFloor,NULL,table1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] = newNode;
				newChildren->push_back(newNode);
			}
			else {
				node* newNode = new node(indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y],NULL,table1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				handleChildren(i,newNode);
			}
		}
		else if(objectTypes[i] == FILECABINET) {
			if (indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] == NULL) {
				node* newNode = new node(rootFloor,NULL,fc1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] = newNode;
				newChildren->push_back(newNode);
			}
			else {
				node* newNode = new node(indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y],NULL,fc1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				handleChildren(i,newNode);
			}
		}
		else if(objectTypes[i] == MESH) {
			meshFurniture* mf1 = new meshFurniture(glm::vec3(0.f,0.6,0.8),meshFileNames[currentMeshNumber]);

			currentMeshNumber++;
			if (indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] == NULL) {
				node* newNode = new node(rootFloor,NULL,mf1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y] = newNode;
				newChildren->push_back(newNode);
			}
			else {
				node* newNode = new node(indexMap[objectPositions[i].x + (xSize+1) * objectPositions[i].y],NULL,mf1,objectRotations[i],objectsScales[i],glm::vec3(objectPositions[i].x,0.f,objectPositions[i].y),objectColors[i]);
				handleChildren(i,newNode);
			}
		}
	}

	rootFloor->children = newChildren;
	rootFloor->selected = true;
	currentNode = root;
}

void sceneGraph::handleChildren(int i, node* nodein) {
	int k = objectPositions[i].x + (xSize+1) * objectPositions[i].y;
	node* checker = indexMap[k];
	vector<node*>* childin = new vector<node*>;
	childin->push_back(nodein);
	checker->children = childin;
	indexMap[k] = nodein;
}

void sceneGraph::readObjBlock(char* line1, char* line2, char* line3, char* line4, char* line5) {
	if (strcmp(line1, "table") == 0) {
		objectTypes.push_back(objTypes::TABLE);
	}
	else if (strcmp(line1, "chair") == 0) {
		objectTypes.push_back(objTypes::CHAIR);
	}
	else if (strcmp(line1, "filecabinet") == 0) {
		objectTypes.push_back(objTypes::FILECABINET);
	}
	else if (strcmp(line1, "lamp") == 0) {
		objectTypes.push_back(objTypes::LAMP);
	}

	char* r = strtok(line2, " ");
	char* g = strtok(NULL, " ");
	char* b = strtok(NULL, " ");

	objectColors.push_back(glm::vec3(atof(r),atof(g),atof(b)));

	char* xInd = strtok(line3, " ");
	char* zInd = strtok(NULL, " ");

	objectPositions.push_back(glm::vec2(atof(xInd),atof(zInd)));

	char* rot = strtok(line4, " ");

	objectRotations.push_back(atof(rot));

	char* xSca = strtok(line5, " ");
	char* ySca = strtok(NULL," ");
	char* zSca = strtok(NULL," ");

	objectsScales.push_back(glm::vec3(atof(xSca),atof(ySca),atof(zSca)));
}

char* sceneGraph::readNextCharToken() {
	char* token = strtok(NULL, " ");
	return token;
}

int sceneGraph::readNextIntToken(){
	return atoi(readNextCharToken());
}

float sceneGraph::readNextFloatToken(){
	return (float) atof(readNextCharToken());
}

glm::vec3 sceneGraph::readNextVecToken() {
	glm::vec3 newVec;
	newVec.x = readNextFloatToken();
	newVec.y = readNextFloatToken();
	newVec.z = readNextFloatToken();
	return newVec;
}

void sceneGraph::goToNextNode() {
	currentNode->selected = false;
	if (currentNode->children != NULL) {
		for(int i = 0; i < currentNode->children->size(); i++) {
			childStack.push(currentNode->children->at(i));
		}
		currentNode = childStack.top();
		currentNode->selected = true;
		childStack.pop();
	}
	else if (!childStack.empty()) {
		currentNode = childStack.top();
		currentNode->selected = true;
		childStack.pop();
	}
	else {
		currentNode = root;
		currentNode->selected = true;
	}
}

void sceneGraph::pressA() {
	glm::vec3 pos = glm::vec3(currentNode->translation.x - 0.5f, currentNode->translation.y, currentNode->translation.z);
	currentNode->translation = pos;
}

void sceneGraph::pressD() {
	glm::vec3 pos = glm::vec3(currentNode->translation.x + 0.5f, currentNode->translation.y, currentNode->translation.z);
	currentNode->translation = pos;
}
	
void sceneGraph::pressW() {
	glm::vec3 pos = glm::vec3(currentNode->translation.x, currentNode->translation.y, currentNode->translation.z + 0.5f);
	currentNode->translation = pos;
}

void sceneGraph::pressS() {
	glm::vec3 pos = glm::vec3(currentNode->translation.x, currentNode->translation.y, currentNode->translation.z - 0.5f);
	currentNode->translation = pos;
}

void sceneGraph::pressLittleX() {
	glm::vec3 sca = glm::vec3(currentNode->scale.x + 0.5f, currentNode->scale.y, currentNode->scale.z);
	currentNode->scale = sca;
}

void sceneGraph::pressBigX() {
	glm::vec3 sca = glm::vec3(currentNode->scale.x - 0.5f, currentNode->scale.y, currentNode->scale.z);
	currentNode->scale = sca;
}

void sceneGraph::pressLittleY() {
	glm::vec3 sca = glm::vec3(currentNode->scale.x, currentNode->scale.y + 0.5f, currentNode->scale.z);
	currentNode->scale = sca;
}

void sceneGraph::pressBigY() {
	glm::vec3 sca = glm::vec3(currentNode->scale.x, currentNode->scale.y - 0.5f, currentNode->scale.z);
	currentNode->scale = sca;
}

void sceneGraph::pressLittleZ() {
	glm::vec3 sca = glm::vec3(currentNode->scale.x, currentNode->scale.y, currentNode->scale.z + 0.5f);
	currentNode->scale = sca;
}

void sceneGraph::pressBigZ() {
	glm::vec3 sca = glm::vec3(currentNode->scale.x, currentNode->scale.y, currentNode->scale.z - 0.5f);
	currentNode->scale = sca;
}

void sceneGraph::pressLittleR() {
	currentNode->rotation += 10.f;
}
void sceneGraph::pressBigR() {
	currentNode->rotation -= 10.f;
}
void sceneGraph::pressE() {
	
}

void sceneGraph::readMeshBlock(char* line1, char* line2, char* line3, char* line4, char* line5) {
	objectTypes.push_back(objTypes::MESH);

	char* filen = strtok(line1, " ");
	char* test = new char;
	strcpy(test,filen);
	meshFileNames.push_back(test);

	char* imagen = strtok(line2, " ");
	meshImages.push_back(imagen);

	objectColors.push_back(glm::vec3(0.f,1.f,1.f));

	char* xInd = strtok(line3," ");
	char* zInd = strtok(NULL, " ");

	objectPositions.push_back(glm::vec2(atof(xInd),atof(zInd)));

	char* rot = strtok(line4, " ");

	objectRotations.push_back(atof(rot));

	char* xSca = strtok(line5, " ");
	char* ySca = strtok(NULL," ");
	char* zSca = strtok(NULL," ");

	objectsScales.push_back(glm::vec3(atof(xSca),atof(ySca),atof(zSca)));
	// filename
	// image
	// xindex zindex
	// rotation
	// x y z scale
}