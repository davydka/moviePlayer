#include "ofApp.h"

int _w = 32;
int _h = 32;

float _elapsedTime;
float _alarm;

int frameIndex = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	vidVar = 4;
	ofSetWindowShape(_w, _h);
	ofSetWindowPosition(0, 0);
	ofSetFrameRate(60);

	/*
	ofDirectory currentVideoDirectory(ofToDataPath("gifs", true));
	currentVideoDirectory.allowExt("gif");

	if(currentVideoDirectory.exists()){
		currentVideoDirectory.listDir();
		vector<ofFile> files = currentVideoDirectory.getFiles();

		for(int i = 0; i < currentVideoDirectory.size(); i++){
			ofLogNotice(currentVideoDirectory.getPath(i));
			ofxGIF::fiGifLoader* player = new ofxGIF::fiGifLoader();
			player->load(currentVideoDirectory.getPath(i));
		}
	} else {
		ofLogError() << "currentVideoDirectory: " << currentVideoDirectory.path() << " MISSING";
	}
	*/

	
	ofDirectory currentVideoDirectory(ofToDataPath("videosSmall", true));
	currentVideoDirectory.allowExt("mp4");
	//currentVideoDirectory.allowExt("mp4");
	//currentVideoDirectory.allowExt("mkv");
	//currentVideoDirectory.allowExt("avi");
	if(currentVideoDirectory.exists()){
		currentVideoDirectory.listDir();
		vector<ofFile> files = currentVideoDirectory.getFiles();

		for(int i = 0; i < currentVideoDirectory.size(); i++){
			ofLogNotice(currentVideoDirectory.getPath(i));
			ofVideoPlayer* player = new ofVideoPlayer();
			player->setPixelFormat(OF_PIXELS_NATIVE);
			player->load(currentVideoDirectory.getPath(i));
			//player->setLoopState(OF_LOOP_NORMAL);
			player->setVolume(0.0);
			player->play();
			player->setPaused(true);
			player->setPosition(0.0);
			videosHolder[i] = player;
		}
	} else {
		ofLogError() << "currentVideoDirectory: " << currentVideoDirectory.path() << " MISSING";
	}
	

	fbo.allocate(_w, _h, GL_RGBA);
	//videosHolder[vidVar]->play();

	_elapsedTime = ofGetElapsedTimef();
	_alarm = _elapsedTime + 5.;
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(0);

	_elapsedTime = ofGetElapsedTimef();
	if(_elapsedTime > _alarm){
		_alarm = _elapsedTime + 5.;

		videosHolder[vidVar]->setPaused(true);
		vidVar++;
		if(vidVar > videosHolder.size()-1)
			vidVar = 0;

		videosHolder[vidVar]->setPosition(0.0);
		videosHolder[vidVar]->setPaused(false);
		//videosHolder[vidVar]->setLoopState(OF_LOOP_NORMAL);
		std::cout<<videosHolder[vidVar]->getMoviePath()<<std::endl;
		std::cout<<videosHolder[vidVar]->isPlaying()<<std::endl;
		std::cout<<videosHolder[vidVar]->isPaused()<<std::endl;
	}
	if(videosHolder[vidVar]->isPaused()){
		std::cout<<"caught pause"<<std::endl;
		videosHolder[vidVar]->setPaused(false);
	}

	videosHolder[vidVar]->update();


}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	ofClear(0);
	videosHolder[vidVar]->draw(0, 0, _w, _h);
	fbo.end();

	fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//std::cout<<vidVar<<std::endl;

	/*
	videosHolder[vidVar]->setPaused(true);
	vidVar++;
	if(vidVar > videosHolder.size()-1)
		vidVar = 0;

	videosHolder[vidVar]->play();
	*/
}
