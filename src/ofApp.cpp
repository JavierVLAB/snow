#include "ofApp.h"

static bool removeShapeOffScreen(Snow ss) {
    if (!ofRectangle(0, -400, 1024,768+400).inside(ss.pos)) {
        return true;
    }
    return false;
}

//--------------------------------------------------------------
void ofApp::setup(){

  ofSetFrameRate(30);

  glPointSize(3);

  screenWidth = ofGetWidth();
  screenHeight = ofGetHeight();

  gravity = 0.082;
  updateSnowRate = 5;
  myMesh.setMode(OF_PRIMITIVE_POINTS);

  for(int i = 0; i < 100; i++){
    Snow s;
    s.setup(gravity);
    snow.push_back(s);
  }

  setupGui();
  scale = 1.5;

  #ifdef _USE_LIVE_VIDEO
    #ifdef _USE_KINECT
      kinect.setRegistration(true);
      kinect.init();
      kinect.open();
      kinect.setCameraTiltAngle(0);
    #else
        vidGrabber.setVerbose(true);
        vidGrabber.setup(640,480);
    #endif
	#else
        vidPlayer.load("fingers.mov");
        vidPlayer.play();
        vidPlayer.setLoopState(OF_LOOP_NORMAL);
	#endif

  colorImg.allocate(640,480);
  grayImage.allocate(640,480);
  grayBg.allocate(640,480);
  grayDiff.allocate(640,480);

  bLearnBakground = true;
  openCvThreshold = 30;
  nearThreshold = 255;
  farThreshold = 235;


}

//--------------------------------------------------------------
void ofApp::update(){

  ofRemove(snow, removeShapeOffScreen);

  bool bNewFrame = false;

#ifdef _USE_LIVE_VIDEO
    #ifdef _USE_KINECT
      kinect.update();
      bNewFrame = kinect.isFrameNew();
    #else
      vidGrabber.update();
      bNewFrame = vidGrabber.isFrameNew();
    #endif
  #else
      vidPlayer.update();
      bNewFrame = vidPlayer.isFrameNew();
#endif

if (bNewFrame){

  #ifdef _USE_LIVE_VIDEO
      #ifdef _USE_KINECT
        colorImg.setFromPixels(kinect.getPixels());
        grayImage.setFromPixels(kinect.getDepthPixels());

        ofPixels & pix = grayImage.getPixels();
        int numPixels = pix.size();
        for(int i = 0; i < numPixels; i++) {
          if(pix[i] < nearThreshold && pix[i] > farThreshold) {
            pix[i] = 255;
          } else {
            pix[i] = 0;
          }
        }

        grayImage.flagImageChanged();

        contourFinder.findContours(grayImage, 20, (640*480)/10, 10, true);

      #else
        colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg;

        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(openCvThreshold);

        contourFinder.findContours(grayDiff, 20, (640*480)/10, 10, true);
      #endif
  #else
        ofImage img;
        img.setFromPixels(vidPlayer.getPixels());
        img.resize(640,480);
        colorImg.setFromPixels(img.getPixels());
        grayImage = colorImg;

        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(openCvThreshold);

        contourFinder.findContours(grayDiff, 20, (640*480)/10, 10, true);
  #endif


  if (bLearnBakground == true){
    grayBg = grayImage;
    bLearnBakground = false;
  }



  if(contourFinder.nBlobs > 0){
    //vector <ofPoint> pts = loadPoints("shape.dat");
    //shared_ptr<ofxBox2dPolygon> poly = shared_ptr<ofxBox2dPolygon>(new ofxBox2dPolygon);
    //vector<ofPoint> vec;
    //vec.resize(contourFinder.blobs[0].nPts);

    //for(int i = 0; i < vec.size(); i++){
    //  vec[i] = contourFinder.blobs[0].pts[i]*scale;
    //}
      //vec.simplify(
  }


}

  for(int i = 0; i < snow.size(); i++){
    snow[i].update();
  }

  for(int i = 0; i < updateSnowRate; i++){
    Snow s;
    s.setup(gravity);
    snow.push_back(s);
  }

  myMesh.clear();

  for (int i = 0; i < snow.size(); i++){
      myMesh.addVertex(snow[i].pos);
  }




}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  //for(int i = 0; i < snow.size(); i++){
  //  snow[i].draw();
  //}

  // draw my own blob

for (int i = 0; i < contourFinder.nBlobs; i++){
  for (int j = 0; j < contourFinder.blobs[i].nPts - 1; j++){
    ofSetHexColor(0xffffff);
    ofDrawLine(contourFinder.blobs[i].pts[j]*scale,
               contourFinder.blobs[i].pts[j+1]*scale);
  }

}
  myMesh.draw();
  drawGui();

}

//-------------
//---------
void ofApp::setupGui(){

  gui.setup();

  showGui = false;
}

//----------
void ofApp::drawGui(){

  if(showGui){
    gui.begin();
      ImGui::Separator();
      ImGui::Text("Application average frame rate = %.1f FPS", ImGui::GetIO().Framerate);
      ImGui::Separator();
      ImGui::Text("Press 'g' to show de Gui");
      ImGui::Separator();
      ImGui::SliderFloat("Gravity", &gravity, 0.05, 2.0);
      ImGui::SliderInt("Update Rate", &updateSnowRate, 1, 20);
      //ImGui::SliderInt("Near threshold", &nearThreshold, 0, 255);
      //ImGui::SliderInt("Far threshold", &farThreshold, 0, 255);
      //ImGui::SliderInt("OpenCV threshold", &openCvThreshold, 0, 255);
      //ImGui::Separator();
      //ImGui::Separator();
      //ImGui::SliderFloat("Density", &density, 0, 10.0);
      //ImGui::SliderFloat("Bounce", &bounce, 0, 1.0);
      //ImGui::SliderFloat("Friction", &friction, 0, 10.0);
      vidPlayer.setPaused(!ImGui::Button("Test Window"));
    gui.end();
  }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  switch (key){
    case 'g':
      showGui = !showGui;
      break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
