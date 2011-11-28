#pragma once

#include "ofMain.h"

#define CHARGE_THRESHOLD 2.5

class MetaBall2D {
public:
    float x,y;
    float radius;
    float charge;
    
    ofVec2f pos;
    ofVec2f vel;
    
    MetaBall2D(float _x,float _y,float _r) {
        radius = _r;
        
        charge = ofRandom(20);
        
        pos = ofVec2f(_x,_y);
        
        vel = ofVec2f(ofRandomf(),ofRandomf());
        vel.normalize();
    }
    
    float calcFunction(float X,float Y) {
        return radius / sqrt(pow((pos.x-X),2) + pow((pos.y-Y),2));
    }
    
    float calcDonutFunction(float X, float Y,float radius2) {
        return radius / abs(radius2 - sqrt(pow((pos.x-X),2) + pow((pos.y-Y),2)));
    }
                      
    void update() {
        pos += vel;
    }
    
    void bounds(float w,float h) {
        if(pos.x < 0) {
            pos.x += w;
        }
        
        if(pos.x > w) {
            pos.x -= w;
        }
        
        if(pos.y < 0) {
            pos.y += h;
        }
        
        if(pos.y > h) {
            pos.y -= h;
        }
    }
};

class MetaBallGrid {
private:	
    vector<MetaBall2D*> balls;
    int gridWidth;
    int gridHeight;
    int gridResX;
    int gridResY;
    
    int optResX; // optimization grid resolution
    int optResY;
    
    float *gridValues;
public:
    
    MetaBallGrid(int _gW,int _gH,int _gRX,int _gRY) {
        gridWidth = _gW;
        gridHeight = _gH;
        gridResX = _gRX;
        gridResY = _gRY;
        
        optResY = 10;
        optResX = 10;
        
        gridValues = new float[gridWidth*gridHeight];
    }
    
    MetaBall2D* getBall(int i) {
        return balls[i];
    }
    
    void update() {
        
        for(int i=0;i<balls.size();i++) {
            balls[i]->update();
            balls[i]->bounds(gridWidth,gridHeight);
            
        }
      //  initGrid();
       // calcGrid2();
        
    }

    
    void calcGrid() {
        int numBalls = balls.size();
       
        for(int y=0;y<gridHeight;y+=gridResY) {
            for(int x=0;x<gridWidth;x+=gridResX) {
                int gInd = x + y * gridWidth;
                gridValues[gInd] = 0;            
                for(int i=0;i<numBalls;i++) {
                    gridValues[gInd] += balls[i]->calcFunction(x,y);
                }
                        
                   
            }
        }
    }
    
    void calcGrid2() {
        
        int calcs = 0;
        int numBalls = balls.size();
        
        for(int y=0;y < gridHeight; y+=optResY) {
            for(int x = 0;x < gridWidth; x += optResX) {
                    // get center charge
                int centerX = x+optResX/2;
                int centerY = y+optResY/2;
                
                float charge = 0;
                int numBalls = balls.size();
                
                for(int i=0;i<numBalls;i++) {
                    charge += balls[i]->calcFunction(centerX,centerY);
                    calcs++;
                }
                                                
                if(charge > CHARGE_THRESHOLD) {
                    // calc the full grid
                   
                    for(int yy = y;yy < y+optResY;yy += gridResY) {
                        for(int xx=x;xx < x+optResX;xx += gridResX) {
                                                      
                            int grid_index = xx + yy * gridWidth;
                            for(int i=0;i<numBalls;i++) {
                                gridValues[grid_index] += balls[i]->calcFunction(xx,yy);
                                calcs++;
                            }
                        }
                    }
                   
                    ofSetColor(255,255,255);
                    ofNoFill();
                   // ofRect(x, y, optResX, optResY);
                    
                }
                
            }
        }
        
        
        
    }
    
    void initGrid() {
        for(int y=0;y<gridHeight;y+=gridResY) {
            for(int x=0;x<gridWidth;x+=gridResX) {
                int gInd = x + y * gridWidth;
                gridValues[gInd] = 0;
                
            }
        }         
    }
    
    void descGrid() {
        for(int y=0;y<gridHeight;y+=gridResY) {
            for(int x=0;x<gridWidth;x+=gridResX) {
               int gInd = x + y * gridWidth;
                ofLog() << "X:"<<x<<", Y:"<<y<<" - " << gridValues[gInd] << endl;
                
            }
        }        
    }
    
    void drawGrid(float minTh,float maxTh) {
        
        ofMesh points;
        points.setMode(OF_PRIMITIVE_POINTS);
        for(int y=0;y<gridHeight;y+=gridResY) {
            for(int x=0;x<gridWidth;x+=gridResX) {
                int gInd = x + y * gridWidth;
                if(gridValues[gInd] > minTh && gridValues[gInd] < maxTh) {
                    points.addVertex(ofVec2f(x,y));
                    float g = ofMap(gridValues[gInd],0,maxTh,0,255);
                    ofColor c = ofColor(g,g,g,g);
                    points.addColor(c);
                    
                }
                
            }
        }
        
        points.drawFaces();
        
    }
    
    void addBall(float _x,float _y,float _r) {
        MetaBall2D *b = new MetaBall2D(_x,_y,_r);
        
        balls.push_back(b);
    }
    

    
};


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    MetaBallGrid* grid;
    
    float threshold;
    
    ofFbo ballTex;
    
    ofImage img;
    
    ofFbo renderTex;
	

};

