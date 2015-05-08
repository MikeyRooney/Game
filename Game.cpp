#include <Resources\Game.h>

Game::Game(){
	model = new Model();
}

/* initialise everything needed to run the game */
bool Game::init(){

	
	if (!initOpenGL()){
		printf("Error in creating OpenGL instance\n");
		return false;
	}
	
	shader = new Shader();
	if (!shader->createShader()){
		printf("Error creating shader\n");
		getchar();
		return false;
	}



	player = new Player();
	input = new Input();
	camera = new Camera();
	light = new Light();

	map = new Map();
	if (!map->createMap()){
		printf("Error creating map\n");
		return false;
	}

	modelMatrix = glm::mat4(1.0f);

	return true;

}

bool Game::initOpenGL(){
	
	window = NULL;

	const GLubyte* renderer;
	const GLubyte* version;

	if (!glfwInit()){
		return 1;
	}

	window = glfwCreateWindow(xRes, yRes, "Cube Game", NULL, NULL);

	if (!window){
		return 1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	renderer = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}

void Game::runTick(){

	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwPollEvents();

	shader->setActive();

	input->update();
	camera->update();
	light->update();

	map->drawBlocks();
	player->updateAndDraw();

	glUniformMatrix4fv(shader->shaderIDs.at("model"), 1, GL_FALSE, &modelMatrix[0][0]);

	glfwSwapBuffers(window);

}