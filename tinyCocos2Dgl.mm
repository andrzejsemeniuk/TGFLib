

#import "tinyCocos2Dgl.h"

namespace tiny
{
    namespace Cocos2D
    {
        namespace gl
        {
            namespace blend
            {
                
                string   name        (int code)
                {
                    static std::map<int,std::string> codes =
                    {
                        {0,             "GL_ZERO"},
                        {1,             "GL_ONE"},
                        {0X0300,        "GL_SRC_COLOR"},
                        {0X0301,        "GL_ONE_MINUS_SRC_COLOR"},
                        {0X0302,        "GL_SRC_ALPHA"},
                        {0X0303,        "GL_ONE_MINUS_SRC_ALPHA"},
                        {0X0304,        "GL_DST_ALPHA"},
                        {0X0305,        "GL_ONE_MINUS_DST_ALPHA"},
                        {0X0306,        "GL_DST_COLOR"},
                        {0X0307,        "GL_ONE_MINUS_DST_COLOR"},
                        {0X0308,        "GL_SRC_ALPHA_SATURATE"},
                    };
                    
                    return codes[code];
                }

                
            }
        }
    }
}

