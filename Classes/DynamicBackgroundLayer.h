//
//  DynamicBackgroundLayer.h
//  CheetahEffectTest
//
//  Created by Jonathan Chu on 19/1/16.
//
//

#ifndef __CheetahEffectTest__DynamicBackgroundLayer__
#define __CheetahEffectTest__DynamicBackgroundLayer__

#include "cocos2d.h"

#include "Bokeh.h"

class DynamicBackground : public cocos2d::Node
{
public:
    DynamicBackground();
    ~DynamicBackground();
    
    static DynamicBackground* create();
    
    void setup();

    float time;
    
private:    
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _origin;
    
    cocos2d::Vector<Bokeh*> _bokehs;
    
    cocos2d::GLProgramState* _bokehGLState;
    cocos2d::GLProgramState* _bluredBokehGLState;
    
    void setupBackground();
    
    void setupBokehGLState();
    
    void update(float dt);
    
    void generateBokehsInGrid(int count, Bokeh::BokehSetting setting);
    
    Bokeh::BokehSetting getStandardSharpBokehSetting();
    Bokeh::BokehSetting getLargeBluredBokehSetting();
    Bokeh::BokehSetting getSmallBokehSetting();
};

#endif /* defined(__CheetahEffectTest__DynamicBackgroundLayer__) */
