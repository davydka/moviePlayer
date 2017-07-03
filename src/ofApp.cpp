#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	vidVar = 0;

	ofDirectory currentVideoDirectory(ofToDataPath("videos", true));
	currentVideoDirectory.allowExt("mov");
	currentVideoDirectory.allowExt("mp4");
	currentVideoDirectory.allowExt("mkv");
	currentVideoDirectory.allowExt("avi");
	if(currentVideoDirectory.exists()){
		currentVideoDirectory.listDir();
		vector<ofFile> files = currentVideoDirectory.getFiles();

		for(int i = 0; i < currentVideoDirectory.size(); i++){
			ofLogNotice(currentVideoDirectory.getPath(i));
			ofVideoPlayer* player = new ofVideoPlayer();
			player->load(currentVideoDirectory.getPath(i));
			player->setLoopState(OF_LOOP_NORMAL);
			player->setVolume(0.0);
			//player->play();
			//player->setPaused(true);
			videosHolder[i] = player;
		}
	} else {
		ofLogError() << "currentVideoDirectory: " << currentVideoDirectory.path() << " MISSING";
	}

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

	//flockingMovie.play();
	//fingerMovie.play();

	//currentPlayer = fingerMovie;
	//currentPlayer.play();
	videosHolder[vidVar]->play();
}


//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(0);

	videosHolder[vidVar]->update();
	pointilize.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	ofClear(0);
	videosHolder[vidVar]->draw(0, 0, 320, 240);
	fbo.end();

	pointilize.draw(0,0);

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
	//std::cout<<vidVar<<std::endl;

	videosHolder[vidVar]->setPaused(true);
	vidVar++;
	if(vidVar > videosHolder.size()-1)
		vidVar = 0;

	videosHolder[vidVar]->play();
}
