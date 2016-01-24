//
//  DynamicBackgroundLayer.cpp
//  CheetahEffectTest
//
//  Created by Jonathan Chu on 19/1/16.
//
//

#include "DynamicBackgroundLayer.h"

#define BOKEH_COUNT 100
#define BOKEH_GEN_GRID_ROW 3.f
#define BOKEH_GEN_GRID_COL 2.f

using namespace cocos2d;

DynamicBackground::DynamicBackground(){
    
}

DynamicBackground::~DynamicBackground(){
    
}

DynamicBackground* DynamicBackground::create()
{
    DynamicBackground* dynamicBackground = new DynamicBackground();
    
    if(dynamicBackground->cocos2d::Node::create()){
        return dynamicBackground;
    }
    
    return NULL;
}

// Setup the Dynamic Background
void DynamicBackground::setup(){
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    
    time = 0.f;
    
    setupBackground();
    
    setupBokehGLState();
    
    //// Generate Bokehs
    // Generate groups of bokeh with settings defined in functions
    // Settings can be easily added by creating similar functions
    // TODO: Generate bokehs by reading external plist / JSON or XML instead of hardcoding value here
    generateBokehsInGrid(18, getStandardSharpBokehSetting());
    generateBokehsInGrid(13, getLargeBluredBokehSetting());
    generateBokehsInGrid(8, getSmallBokehSetting());
    
    this->scheduleUpdate();
}

void DynamicBackground::setupBackground(){
    // Add Background Sprite
    auto backgroundSprite = Sprite::create("background_color.png");
    
    backgroundSprite->setPosition(Vec2(_visibleSize.width/2.f + _origin.x, _visibleSize.height/2.f + _origin.y));
    backgroundSprite->setScale(_visibleSize.width / backgroundSprite->getTextureRect().size.width, _visibleSize.height / backgroundSprite->getTextureRect().size.height);
    
    this->addChild(backgroundSprite, 0);
}

void DynamicBackground::setupBokehGLState(){
    GLProgram *bokehGLProgram = GLProgram::createWithFilenames("bokehShader.vsh", "bokehShader.fsh");
    _bokehGLState = GLProgramState::getOrCreateWithGLProgram(bokehGLProgram);
    GLProgram *bluredbokehGLProgram = GLProgram::createWithFilenames("bokehShader.vsh", "bokehShader.fsh");
    _bluredBokehGLState = GLProgramState::getOrCreateWithGLProgram(bluredbokehGLProgram);
    
    Texture2D* gradientTex = Director::getInstance()->getTextureCache()->addImage("bokeh_gradient.png");
    _bokehGLState->setUniformTexture("u_gradient", gradientTex);
    _bluredBokehGLState->setUniformTexture("u_gradient", gradientTex);
    
    _bokehGLState->setUniformFloat("u_blurAmount", 0.f);
    _bluredBokehGLState->setUniformFloat("u_blurAmount", 1.f);
}

void DynamicBackground::update(float dt){
    time += dt;
//    CCLOG("Time now is %f", time);
    
    for (int i=0; i<_bokehs.size(); i++) {
        _bokehs.at(i)->updateBokeh(dt);
    }
}

void DynamicBackground::generateBokehsInGrid(int count, Bokeh::BokehSetting setting){
    int gridCount = BOKEH_GEN_GRID_ROW * BOKEH_GEN_GRID_COL;
    int bokehPerGrid = floorf((float)count / (float)gridCount);
    int bokehRemainder = gridCount % bokehPerGrid;
    
    float gridWidth = _visibleSize.width / BOKEH_GEN_GRID_COL;
    float gridHeight = _visibleSize.height / BOKEH_GEN_GRID_ROW;
    
    for(int i=0; i<BOKEH_GEN_GRID_ROW; i++){
        for(int j=0; j<BOKEH_GEN_GRID_COL; j++){
            for(int k=0; k<bokehPerGrid; k++){
                auto aBokeh = Bokeh::create();
                
                setting.spawnArea = Rect(_origin.x + gridWidth * j,
                                         _origin.y + gridHeight * i,
                                         gridWidth,
                                         gridHeight);
                
                if(setting.blur == 0.f){
                    aBokeh->setup(_bokehGLState, setting);
                }else{
                    aBokeh->setup(_bluredBokehGLState, setting);
                }
                _bokehs.pushBack(aBokeh);
                this->addChild(aBokeh);
            }
        }
    }
    
    for(int i=0; i<bokehRemainder; i++){
        auto aBokeh = Bokeh::create();
        
        setting.spawnArea = Rect(_origin.x, _origin.y, _visibleSize.width, _visibleSize.height);
        
        aBokeh->setup(_bokehGLState, setting);
        _bokehs.pushBack(aBokeh);
        this->addChild(aBokeh);
    }
}

Bokeh::BokehSetting DynamicBackground::getStandardSharpBokehSetting(){
    Bokeh::BokehSetting settings;
    
    settings.opacityRange.min = 6;
    settings.opacityRange.max = 40;
    
    settings.startSizeRange.min = 1.5f;
    settings.startSizeRange.max = 3.8f;
    
    settings.endSizeRange.min = 2.5f;
    settings.endSizeRange.max = 4.f;
    
    settings.speedRange.min = 3.f;
    settings.speedRange.max = 20.f;
    
    settings.swayRange.min = 10.f;
    settings.swayRange.max = 30.f;
    
    settings.blur = 0.f;
    
    settings.durationRange.min = 3.f;
    settings.durationRange.max = 10.f;
    
    settings.fadeDurationRange.min = 0.5f;
    settings.fadeDurationRange.max = 1.0f;
    
    return settings;
}

Bokeh::BokehSetting DynamicBackground::getLargeBluredBokehSetting(){
    Bokeh::BokehSetting settings;
    
    settings.opacityRange.min = 10;
    settings.opacityRange.max = 30;
    
    settings.startSizeRange.min = 3.5f;
    settings.startSizeRange.max = 8.f;
    
    settings.endSizeRange.min = 4.f;
    settings.endSizeRange.max = 8.5f;
    
    settings.speedRange.min = 6.f;
    settings.speedRange.max = 15.f;
    
    settings.swayRange.min = 0.1f;
    settings.swayRange.max = 0.5f;
    
    settings.blur = 1.f;
    
    settings.durationRange.min = 6.f;
    settings.durationRange.max = 12.f;
    
    settings.fadeDurationRange.min = 1.f;
    settings.fadeDurationRange.max = 2.f;
    
    return settings;
}

Bokeh::BokehSetting DynamicBackground::getSmallBokehSetting(){
    Bokeh::BokehSetting settings;
    
    settings.opacityRange.min = 15;
    settings.opacityRange.max = 35;
    
    settings.startSizeRange.min = 1.5f;
    settings.startSizeRange.max = 3.6f;
    
    settings.endSizeRange.min = 2.f;
    settings.endSizeRange.max = 4.f;
    
    settings.speedRange.min = 3.f;
    settings.speedRange.max = 20.f;
    
    settings.swayRange.min = 0.f;
    settings.swayRange.max = 0.4f;
    
    settings.blur = 1.f;
    
    settings.durationRange.min = 3.f;
    settings.durationRange.max = 10.f;
    
    settings.fadeDurationRange.min = 0.5f;
    settings.fadeDurationRange.max = 1.0f;
    
    return settings;
}

