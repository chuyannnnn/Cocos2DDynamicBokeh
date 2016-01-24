//
//  Bokeh.cpp
//  CheetahEffectTest
//
//  Created by Jonathan Chu on 20/1/16.
//
//

#include "Bokeh.h"

using namespace cocos2d;

Bokeh::Bokeh(){
    
}

Bokeh::~Bokeh(){
    
}

Bokeh* Bokeh::create()
{
    Bokeh* bokeh = new Bokeh();
    
    if(bokeh->cocos2d::Node::create()){
        return bokeh;
    }
    
    return NULL;
}


// Setup the Dynamic Background
void Bokeh::setup(GLProgramState* glState)
{
    // Setup Bokeh with default values
    BokehSetting settings;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    settings.spawnArea = Rect(origin.x, origin.y, visibleSize.width, visibleSize.height);
    
    settings.opacityRange.min = 50;
    settings.opacityRange.max = 150;
    
    settings.startSizeRange.min = 1.f;
    settings.startSizeRange.max = 3.f;
    
    settings.endSizeRange.min = 0.15f;
    settings.endSizeRange.max = 0.4f;
    
    settings.speedRange.min = 5.f;
    settings.speedRange.max = 30.f;
    
    settings.swayRange.min = 0.f;
    settings.swayRange.max = 0.3f;
    
    settings.blur = CCRANDOM_0_1() > 0.5f ? 0.f : 1.f;
    settings.dir = Vec2(CCRANDOM_0_1() * 2.f - 1.f, CCRANDOM_0_1() * 2.f - 1.f);
    settings.dir.normalize();
    
    settings.durationRange.min = 4.f;
    settings.durationRange.max = 8.f;
    
    settings.fadeDurationRange.min = 1.f;
    settings.fadeDurationRange.max = 1.5f;
    
    setup(glState, settings);
}

void Bokeh::setup(GLProgramState* glState, Bokeh::BokehSetting settings)
{
    _settings = settings;
    
    // Set state
    _lifetime = 0.f;
    
    // Setup Bokeh with settings
//    _bokehSprite = Sprite::create("bokeh_small.png");
    _bokehSprite = Sprite::create("bokeh_solid.png");
    
    _bokehSprite->setScaleX(0.5f);
    
    _bokehSprite->setBlendFunc(BlendFunc::ADDITIVE);
    
    // Use same glProgramState to batch rendering and reduce draw call to one
//    GLProgram *bokehGLProgram = GLProgram::createWithFilenames("bokehShader.vsh", "bokehShader.fsh");
//    GLProgramState *bokehGLState = GLProgramState::getOrCreateWithGLProgram(bokehGLProgram);
//    _bokehSprite->setGLProgramState(bokehGLState);
    
    reset();
    
    _bokehSprite->setGLProgramState(glState);
    
    this->addChild(_bokehSprite);
}

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

void Bokeh::updateBokeh(float dt)
{
    _lifetime += dt;
    
    // Linear Movement
    Vec2 moveVector = _settings.dir * _attributes.speed * dt;
    Vec2 swayVector = Vec2();
    swayVector.x = _settings.dir.y;
    swayVector.y = - _settings.dir.x;
    swayVector = swayVector * sinf(_lifetime / 2.f + _attributes.startSize) * _attributes.sway;
    
    _basePosition += moveVector;
    this->setPosition(_basePosition + swayVector);
    
//    this->setPosition(this->getPosition() + moveVector + swayVector);
    
    float scale = lerp(_attributes.startSize, _attributes.endSize, _lifetime/_attributes.duration);
    this->setScale(scale);
    
    // Timed Movement
    if(_lifetime <= _attributes.fadeDuration){
        // Bokeh Spawn
        _bokehSprite->setOpacity(_attributes.opacity * (_lifetime / _attributes.fadeDuration));
        
    }else{
        if(_lifetime < _attributes.duration - _attributes.fadeDuration){
            // Bokeh Moving
            
        }else if(_lifetime < _attributes.duration){
            // Bokeh Dying
            _bokehSprite->setOpacity(_attributes.opacity * ((_attributes.duration - _lifetime) / _attributes.fadeDuration));
        }else{
            // Bokeh Dead
            reset();
        }
    }
}

void Bokeh::reset(){
//    this->setScale(_settings.startSize);
    _bokehSprite->setOpacity(0);
    _lifetime = 0.f;
    
    // Randomize Attributes
    _attributes.opacity = random(_settings.opacityRange.min, _settings.opacityRange.max);
    _attributes.startSize = random(_settings.startSizeRange.min, _settings.startSizeRange.max);
    _attributes.endSize = random(_settings.endSizeRange.min, _settings.endSizeRange.max);
    _attributes.sway = random(_settings.swayRange.min, _settings.swayRange.max);
    _attributes.speed = random(_settings.speedRange.min, _settings.speedRange.max);
    _attributes.duration = random(_settings.durationRange.min, _settings.durationRange.max);
    _attributes.fadeDuration = random(_settings.fadeDurationRange.min, _settings.fadeDurationRange.max);
    
    _settings.dir = Vec2(CCRANDOM_0_1() * 2.f - 1.f, CCRANDOM_0_1() * 2.f - 1.f);
    _settings.dir.normalize();
    
    // Randomize Position within spawnArea
    this->setPositionX(_settings.spawnArea.origin.x + _settings.spawnArea.size.width * CCRANDOM_0_1());
    this->setPositionY(_settings.spawnArea.origin.y + _settings.spawnArea.size.height * CCRANDOM_0_1());
    
    _basePosition = this->getPosition();
    
    // Set start scale
    this->setScale(_attributes.startSize);
}