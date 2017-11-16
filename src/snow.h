#ifndef SNOW
#define	SNOW

#include "ofMain.h"

class Snow {
  public:

  	Snow();	// Constructor indispensable en toda clase

  	void update();
    void setup(float g);
  	void draw();

  	ofColor	color;
  	ofVec2f pos;
    ofVec2f vec;
    ofVec2f ac;
    float radio;

};

#endif
