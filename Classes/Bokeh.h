//
//  Bokeh.h
//  CheetahEffectTest
//
//  Created by Jonathan Chu on 20/1/16.
//
//

#ifndef __CheetahEffectTest__Bokeh__
#define __CheetahEffectTest__Bokeh__

#include "cocos2d.h"

class Bokeh : public cocos2d::Node
{
public:
    Bokeh();
    ~Bokeh();
    
    static Bokeh* create();
    
    struct Range {
        float min, max;
    };
    
    struct BokehSetting {
        cocos2d::Rect spawnArea;
        Range opacityRange;
        Range startSizeRange;
        Range endSizeRange;
        Range swayRange;
        Range speedRange;
        cocos2d::Vec2 dir;
        float blur;
        Range durationRange;
        Range fadeDurationRange;
    };
    
    void setup(cocos2d::GLProgramState* glState);
    
    void setup(cocos2d::GLProgramState* glState, BokehSetting settings);
    
    void updateBokeh(float dt);
    
private:
    cocos2d::Sprite* _bokehSprite;
    
    struct BokehAttr {
        float opacity;
        float startSize;
        float endSize;
        float sway;
        float speed;
        float duration;
        float fadeDuration;
    };
    
    float _lifetime;
    
    BokehSetting _settings;
    BokehAttr _attributes;
    
    cocos2d::Vec2 _basePosition;
    
    void reset();
};

#endif /* defined(__CheetahEffectTest__Bokeh__) */
