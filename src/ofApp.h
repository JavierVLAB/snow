#pragma once

#include "ofMain.h"
#include "snow.h"
#include "ofxImGui.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"

//#define _USE_LIVE_VIDEO
//#define _USE_KINECT

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();


		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		vector<Snow> snow;

		int screenWidth;
		int screenHeight;
		float gravity;
		int updateSnowRate;
		ofMesh      myMesh;

	//--------- ofxImGui ------------

	void drawGui();
	void setupGui();

	ofxImGui::Gui gui;
	bool     showGui;


	//------

	// ----------- ofxOpenCv -----------

		#ifdef _USE_LIVE_VIDEO
			ofVideoGrabber 		vidGrabber;
		#else
			ofVideoPlayer 		vidPlayer;
		#endif

		ofxCvColorImage			colorImg;

		ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

		ofxCvContourFinder 	contourFinder;

		int 				openCvThreshold;
		bool				bLearnBakground;

		//--------- ConmplexPolygon ------------
		vector <ofPoint> loadPoints(string file);
		ofPolyline                          shape;


		//--------- ofxKinect ------

		ofxKinect kinect;

	bool bThreshWithOpenCV;
	bool bDrawPointCloud;

	int nearThreshold;
	int farThreshold;

	int angle;

		//---------  ------------

	ofFbo fbo;
	ofMesh mesh;

	float scale;



};
