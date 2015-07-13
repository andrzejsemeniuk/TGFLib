    //
    //  tinyCocos2DiOS.m
    //  productFlowerz
    //
    //  Created by andrzej semeniuk on 7/29/14.
    //
    //

#import "tinyCocos2DiOS.h"

#import "tinyApplication.h"

@implementation tinyCocos2DiOS

@end


namespace tiny
{
    namespace Cocos2D
    {
        
        using namespace std;
        
        
        
        UIImage *       UIImageForSprite            (CCSpritePtr p, string filename, bool purge, bool useTemporaryDirectory)
        {
            NSString * path1 = 0;
            
            if (useTemporaryDirectory)
            {
                    // use NSTemporaryDirectory();
                path1 = [NSTemporaryDirectory() stringByAppendingPathComponent:tiny::Application::toNSString(filename)];
                NSLog(@"UIImageForSprite: path1: %@",path1);
                    // WON'T WORK - SAVES IMAGE UNDER OWN PATH THEN PARAMETER
                io::saveToFilePNG(p,tiny::Application::fromNSString(path1));
            }
            else
            {
                    //auto path = tiny::Application::IO::pathInDocumentsFolder(filename);
                    //NSString * path1 = tiny::Application::toNSString(path);
                
                    // THIS IS THE PATH WHERE COCOS2D SAVES THE PNG FILE
                std::string fullpath = CCFileUtils::getInstance()->getWritablePath() + filename;
                tLog( "io::saveToFilePNG: "<<filename<<"="<<fullpath );
                
                path1 = tiny::Application::toNSString(fullpath);
                NSLog(@"UIImageForSprite: path1: %@",path1);
                    // PROVIDE THE FILENAME, NOT THE PATH
                io::saveToFilePNG(p,filename);
            }
            
            UIImage * image = [UIImage imageWithContentsOfFile:path1];
            
            auto size = [image size];
            tLog("UIImageForSprite: image width="<<size.width<<" height="<<size.height);

            if (purge)
            {
                tiny::Application::IO::removeFilenameInDocumentsFolder(filename);
//                tiny::Application::IO::writeToFilenameInDocumentsFolder(filename,"");
            }
            
            if (0)
            {
                NSString * filePath = Application::toNSString(Application::IO::pathInDocumentsFolder(filename));
                NSLog(@"UIImageForSprite: filePath: %@",filePath);
                [UIImagePNGRepresentation(image) writeToFile:filePath atomically:YES];
                image = [[[UIImage alloc] initWithContentsOfFile:filePath] autorelease];
            }
            return image;
        };
        
        
    }
}