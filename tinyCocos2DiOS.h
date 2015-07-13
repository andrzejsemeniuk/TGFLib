    //
    //  tinyCocos2DiOS.h
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 7/29/14.
    //
    //

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "tinyCocos2D.h"

@interface tinyCocos2DiOS : NSObject

@end

namespace tiny
{
    namespace Cocos2D
    {
        
        
        using namespace std;
        
        
        
        ______ UIImage *        UIImageForSprite        (CCSpritePtr p, string filename = "tmp-uiimage.png", bool purge = false, bool useTemporaryDirectory = false);
        
        
    }
    
}