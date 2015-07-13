

#import "tinyCocos2DText.h"


namespace tiny
{
    namespace Cocos2D
    {
        namespace Text
        {
            
            void align (vectorCRef(CCSpritePtr) sprites, CCPoint loc, float inbetween, float angle0, float angle1, CCRatio alignment, YMarginRatios ymargins)
            {
                alignment.x ++;
                    //alignment.y ++;
                
                float H = 0;
                float W = 0;
                
                for(auto s:sprites)
                {
                    H = max(H,ccHeightScaled(s));
                    W += ccWidthScaled(s);
                }
                
                W += inbetween * (sprites.size()-1);
                
                float X     = loc.x - W/2. * alignment.x;
                float Y     = loc.y - H/2. * alignment.y;
                float A     = 1 < sprites.size() ? angle0 : (angle0+angle1)/2.;
                float dA    = 1 < sprites.size() ? (angle1 - angle0) / (sprites.size()-1) : 0;
                
                for(auto s:sprites)
                {
                    float w = ccWidthScaled(s)/2.;
                    X += w;
                        //tLog(" X="<<X);
                    float y = 0;
                    switch(ccTag(s))
                    {
                        case ',':
                        case '.':
                        case '_':
                            y = ymargins.bottom*H;
                            break;
                        case '\'':
                            y = ymargins.top*H;
                            break;
                    }
                    ccPosition(s,Vec2(X,Y+y));
                    ccRotation(s,A);
                    X += w + inbetween;
                    A += dA;
                }
            }
            
            string Alphabet::filenameGet(char c) const
            {
                string n;
                switch (c)
                {
                    case '\''   : n = "quote"; break;
                    case '\"'   : n = "doublequote"; break;
                    case '*'    : n = "star"; break;
                    case '.'    : n = "period"; break;
                    case ','    : n = "comma"; break;
                    case '+'    : n = "plus"; break;
                    case '-'    : n = "minus"; break;
                    case '@'    : n = "at"; break;
                    case '`'    : n = "apostrophe"; break;
                    case '~'    : n = "tilde"; break;
                    case '['    : n = "leftsquarebracket"; break;
                    case ']'    : n = "rightsquarebracket"; break;
                    case '<'    : n = "leftanglebracket"; break;
                    case '>'    : n = "rightanglebracket"; break;
                    case '('    : n = "leftparentheses"; break;
                    case ')'    : n = "rightparentheses"; break;
                    case '{'    : n = "leftcurlybrace"; break;
                    case '}'    : n = "rightcurlybrace"; break;
                    case ':'    : n = "colon"; break;
                    case ';'    : n = "semicolon"; break;
                    case '?'    : n = "questionmark"; break;
                    case '/'    : n = "slash"; break;
                    case '\\'   : n = "backslash"; break;
                    case '%'    : n = "percent"; break;
                    case '$'    : n = "dollar"; break;
                    case '#'    : n = "hash"; break;
                    case '!'    : n = "exclamation"; break;
                    case '&'    : n = "ampersand"; break;
                    case '^'    : n = "caret"; break;
                    case '|'    : n = "pipe"; break;
                    case '_'    : n = "underscore"; break;
                    case '='    : n = "equal"; break;
                    default:
                        if ('A' <= c and c <= 'Z')
                        {
                            n += 'a' + (c - 'A');
                            n += "-capital";
                            tLog("capital n: "<<n);
                        }
                        else
                        {
                            n = c;
                        }
                }
                    // format: "image-text-<identifier>-letter[-capital].png"
                    // "image-text-title-w.png"
                    // "image-text-title-W-capital.png"
                string filename = parameters.prefix+'-'+n+parameters.suffix;
                return filename;
            }
            
            vector<CCSpritePtr> Alphabet::spriteFramesCreate(string prefix, string text, float scale)
            {
                vector<CCSpritePtr> r;
                r.reserve(text.length());
                for(char c:text)
                {
                    if (same(c,' '))
                    {
                        auto s = ccFrame(prefix+filenameGet('m'));
                        s -> setScale(scale);
                        s -> setAnchorPoint(Vec2(.5,.5));
                        ccTag(s,c);
                        ccHide(s);
                        r.push_back(s);
                    }
                    else
                    {
                        auto s = ccFrame(prefix+filenameGet(c));
                        s -> setScale(scale);
//                        s -> setFlippedY(true);
                        s -> setAnchorPoint(Vec2(.5,.5));
                        ccTag(s,c);
                        r.push_back(s);
                    }
                }
                return r;
            }
            
            vector<CCSpritePtr> Alphabet::spritesCreate(string text, float scale)
            {
                vector<CCSpritePtr> r;
                r.reserve(text.length());
                for(char c:text)
                {
                    if (same(c,' '))
                    {
                        auto s = ccSprite(filenameGet('m'));
                        ccScale(s,scale);
                        ccTag(s,c);
                        ccHide(s);
                        r.push_back(s);
                    }
                    else
                    {
                        auto s = ccSprite(filenameGet(c));
                        ccScale(s,scale);
                        ccTag(s,c);
                        r.push_back(s);
                    }
                }
                return r;
            }
            
            
            
            vector<string> Alphabet::framesGet(string text) const
            {
                vector<string> r;
                r.reserve(text.length());
                for(char c:text)
                {
                    if (c == ' ')
                        c = 'm';
                    r.push_back(filenameGet(c));
                }
                return r;
            }
            
        } // namespace Text
        
        
    }
}


