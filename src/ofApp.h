#pragma once

#include "ofMain.h"
#include "ofxGui.h"
//#include "ofxGif.h"

class ofApp : public ofBaseApp{
    
public:
    
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	ofxPanel panel;
	ofParameter<int> renderType;
	ofParameter<int> dynamicSize;
	ofParameter<float> borderSize;
	ofParameter<float> radius;

	ofFbo fbo;
	ofVideoPlayer currentPlayer;

	int vidVar;
	map<int, ofVideoPlayer*> videosHolder;

	//map<int, ofxGIF::fiGifLoader*> gifloader;

};

