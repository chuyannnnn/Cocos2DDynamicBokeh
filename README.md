# Cocos2DDynamicBokeh

Cocos2DDynamicBokeh is a small test I did for a company interview.  Project contains a **DynamicBackgroundLayer** node that generates **Bokeh** according to settings.  All bokehs are batched into 2 draw calls for blurred and sharp variants to create fake depth of field effect while maintaining performance. Bokeh lifetime colour can be customize by modifying *bokeh_gradient.png* in the resources folder.


## Cocos2D-x Version

This project is created using *cocos2d-x 3.5*.  Please include dependency library accordingly.  Note that I made a small change to `cocos2d/cocos/renderer/CCQuadCommand.cpp` to allow sprites with custom shaders and uniforms to be batched.  Please replace the original `CCQuadCommand` to enable batching.


## Platform Support

This project supports iOS and Android

### iOS Project
Path: `proj.ios_mac/Cocos2DDynamicBokeh.xcodeproj/project.pbxproj`

### Android Build
Path: `proj.android/build_native.py`
