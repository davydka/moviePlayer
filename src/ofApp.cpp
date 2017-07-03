#include "ofApp.h"

bool vidVar;

//--------------------------------------------------------------
void ofApp::setup(){
	vidVar = 0;

	flockingMovie.load("movies/flocking.mp4");
	flockingMovie.setLoopState(OF_LOOP_NORMAL);

	fingerMovie.load("movies/moon.mp4");
	fingerMovie.setLoopState(OF_LOOP_NORMAL);

	fbo.allocate(320, 240, GL_RGBA);

	//init ornament
	pointilize.setup(1024,768);

	//assign video input to ornament
	pointilize.loadTexture(fbo.getTexture());

	//setup gui
	renderType.set("renderType", 0, 0, 1);
	renderType.addListener(this, &ofApp::onRenderTypeChanged);
	dynamicSize.set("dynamic Size", 0, 0, 2);
	dynamicSize.addListener(this, &ofApp::onDynamicSizeChanged);
	borderSize.set("border size", 0, 0, 1.0);
	borderSize.addListener(this, &ofApp::onBorderSizeChanged);
	radius.set("radius", 0, 0, 1.0);
	radius.addListener(this, &ofApp::onRadiusChanged);

	panel.setup();
	panel.add(renderType);
	panel.add(dynamicSize);
	panel.add(borderSize);
	panel.add(radius);

	flockingMovie.play();
	fingerMovie.play();

	currentPlayer = fingerMovie;
}


//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(0);

	flockingMovie.update();
	fingerMovie.update();

	//update filter
	//if (fingerMovie.isFrameNew()){
		pointilize.update();
	//}

}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	ofClear(0);
	currentPlayer.draw(0, 0, 320, 240);
	fbo.end();

	//draw filter
	pointilize.draw(0,0);

	//draw gui
	panel.draw();
}

void ofApp::onRenderTypeChanged(int& t){
	pointilize.setRenderType(t);
}

void ofApp::onDynamicSizeChanged(int& t){
	pointilize.setDynamicSizeMode(t);
}

void ofApp::onScaleModeChanged(int& t){
	pointilize.setScaleMode(t);
}

void ofApp::onBorderSizeChanged(float& t){
	pointilize.setBorderSize(t);
}

void ofApp::onRadiusChanged(float& t){
	pointilize.setRadius(t);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	vidVar = !vidVar;
	
	if(vidVar){
		currentPlayer = flockingMovie;
	} else {
		currentPlayer = fingerMovie;
	}
}
