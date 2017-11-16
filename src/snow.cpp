#include "snow.h"		// Referencia al header donde los siguientes métodos están
							//declarados
	Snow::Snow(){
		int x = ofRandom( ofGetWindowWidth() );
		//int y = ofRandom( ofGetWindowHeight() );
    //int x = ofGetWindowWidth()/2;
		int y = 0;
    int vx = ofRandom( -3,3);
    int vy = ofRandom( 10);
    int acx = 0;
    int acy = 0.8;
    pos.set(x,y);
    vec.set(vx,vy);
    ac.set(acx,acy);
		color.set(255,255,255);
    radio = 1.5;

    //color.set( ofRandom(255), ofRandom(255), ofRandom(255));

	}

	void Snow::setup(float g){
		ac.set(0,g);
	};



	void Snow::update(){

		if(pos.y >= 400){

		} else {
    vec = vec + ac;
    pos = pos + vec;
	}

	}

	void Snow::draw(){
		ofSetColor(color);
		ofFill();
		ofCircle(pos.x, pos.y, radio);
	}
