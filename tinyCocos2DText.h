    //
    //  tinyCocos2DText.h
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 3/25/14.
    //
    //

#pragma once

#import "tinyCocos2D.h"

namespace tiny
{
    namespace Cocos2D
    {
        namespace Text
        {
            typedef struct {
                float bottom;
                float top;
            } YMarginRatios;
            
            extern void align (vectorCRef(CCSpritePtr) sprites, CCPoint loc, float inbetween = 1, float angle0 = 0, float angle1 = 0, CCRatio alignment = {0,0}, YMarginRatios ymargins = {-.4,.4} );
            
            STRUCT (Alphabet)
            {
                STRUCT (Parameters)
                {
                    string prefix;
                    string suffix = ".png";
                    
                    Parameters() {}
                    Parameters(string p, string s = ".png") : prefix(p), suffix(s) {}
                } parameters;
                
                Alphabet() {}
                Alphabet(ParametersCRef p) : parameters(p) {}
                
                string filenameGet(char c) const;
                
                vector<CCSpritePtr> spriteFramesCreate(string prefix, string text, float scale = 1);
                vector<CCSpritePtr> spritesCreate(string text, float scale = 1);
                vector<string> framesGet(string text) const;
            };
        }
    }
}