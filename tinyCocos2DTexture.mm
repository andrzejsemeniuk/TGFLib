
#import "tinyCocos2DTexture.h"

#import "tinyApplication.h"

#import "tinyCocos2D.h"

#import "tinyCocos2Dgl.h"


namespace tiny
{
    namespace Cocos2D
    {
        namespace Texture
        {
            
            
            using namespace tiny::Cocos2D;
            
            
            
            
            
            
            std::ostream& operator << (std::ostream& o, DescriptionCRef p)
            {
                return o << '[' << "t=" << p.type << " o=" << p.operators.operators.size() << ']';
            }
            
            
            
            std::ostream& operator << (std::ostream& o, DescriptionsCRef p)
            {
                o << "(descriptions=";
                o << '[' << p.descriptions.size() << '/';
                for(const auto & i : p.descriptions) o << '\n' << i;
                return o << '\n' << ']' << ')';
            }
            
            
            
            
            
            
            
            
            Description::Description (CCOperators o)
            {
                relative    = {CCRelative::ToRoot,true};
                operators   = o;
            }
            
            Description::Description (int t)
            {
                type        = t;
                relative    = {CCRelative::ToRoot,true};
            }
            
            Description::Description (int t, CCOperators o)
            {
                type        = t;
                relative    = {CCRelative::ToRoot,true};
                operators   = o;
            }
            
            Description::Description (int t, CCRelative rel, CCOperators o)
            {
                type        = t;
                relative    = {rel,true};
                operators   = o;
            }
            
            
            
            
            Description Description::afterAddFluctuation (Fluctuation f) const
            {
                Description r = *this;
                
                r.operators.add(f);
                
                return r;
            }
            
            
            
            
            void Description::apply (CCSpritePtr s)
            {
//                s->blending = {CCBlending::Default};
                
                tAssert(operators.applyToSprite(s,false));
            }
            
            
            
            
            
            
            
            
            std::vector<Description> Description::createByAngle(CCAngle angle0, CCAngle angle1, CCAngle angleDelta, CCOperators o)
            {
                return createByAngle(CCAngle::generateFromToBy(angle0,angle1,angleDelta),o);
            }
            
            
            
            
            
            std::vector<Description> Description::createByAngle(vector<CCAngle> angles, CCOperators o)
            {
                tAssert(angles.size());
                
                int count = (int)angles.size();
                
                std_vectorWithCapacity(v,Description,count);
                
                for(auto angle:angles)
                {
                    Description data;
                    data.add(o);
                    data.add(oAddRotation(angle));
                    v.push_back(data);
                }
                
                return v;
            }
            
            
            
            
            
            
            
            
            
            
            std::vector<Description> Description::createWithTexture (CCTexture2DPtr t, vectorCRef(Description) p)
            {
                auto r = p;
                for(autoRef e:r)
                {
                    tAssert(e.sprite = ccSprite(t));
                }
                return r;
            }
            
            std::vector<Description> Description::createWithTextures (vectorCRef(pair<CCTexture2DPtr,Description>) p)
            {
                std_vectorWithCapacity(r,Description,p.size());
                for(auto e:p)
                {
                    r.push_back(e.second);
                    tAssert(r.back().sprite = ccSprite(e.first));
                }
                return r;
            }
            
            std::vector<Description> Description::createWithFunction (std::function<CCSpritePtr (DescriptionCRef)> functionCreatesSprite, vector<Description> descriptions)
            {
                auto r = descriptions;
                
                for(autoRef description:r)
                {
                    tAssert(description.sprite = functionCreatesSprite(description));
                }
                return r;
            }
            
            
            
            
            
            
            
            Factory::Parameters::Parameters ()
            {
                blending.applicant = {GL_ONE,GL_ONE_MINUS_SRC_ALPHA};
            }
            
            
            
            
            
            
            Factory::Factory (bool frames)
            {
                if (frames)
                {
                    parameters.blending.applicant   = {GL_ONE,GL_ONE_MINUS_SRC_ALPHA};
                    parameters.blending.applyToRoot = false;
                    parameters.blending.applyToAll  = false;
                }
                else
                {
                    parameters.blending.applicant   = {GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
                    parameters.blending.applyToRoot = false;
                    parameters.blending.applyToAll  = false;
                }
            }
            
            
            
            
            
            
            void Factory::textureCreateStepHierarchy (CCSpritePtr sprite, CCNodePtr root, CCNodePtr previous, CCNodePtr first, DescriptionCRef description, vectorCRef(Description) descriptions, int count)
            {
                bool valid = description.relative.valid();
                auto value = description.relative.value();
                
                if (valid and first and value.isRelativeToFirst())
                {
                    first->addChild(sprite);
                }
                else if (valid and previous and value.isRelativeToPrevious())
                {
                    previous->addChild(sprite);
                }
                else if (valid and previous and value.value <= count)
                {
                    if (0 < value.value)
                    {
                        auto parent = descriptions.at(value.value-1).sprite;
                        
                        parent->addChild(sprite);
                    }
                    else
                    {
                        root->addChild(sprite);
                    }
                }
                else
                {
                    root->addChild(sprite);
                }
            }
            
            
            
            
            
            
            
            Factory::Formation Factory::textureCreateStepFormation (int type, vectorCRef(Description) descriptions, Color4F fill, bool symmetric)
            {
                static int counter = 0;
                
                counter++;
                
                    //tiny::Cocos2D::gl::blend::separate::state blending;
                
                CCSpritePtr root        = ccSpriteEmpty();
                
                if (parameters.blending.applyToRoot)
                {
                    ccBlending  (root,parameters.blending.applicant);
                }
                ccAnchor    (root,Vec2(.5,.5));
                ccTag       (root,type);
                
                CCNodePtr   first       = 0;
                CCNodePtr   previous    = 0;
                
                int         count       = 0;
                
                AABB        aabb;
                
                for(auto description:descriptions)
                {
                        // DESCRIPTION IS A TEMPORARY
                    
                        // DESCRIPTION SPRITE ALREADY EXISTS
                    auto sprite = description.sprite;
                    
                    tAssert(sprite);
                    
                        //tLog("textureCreateStepFormation: counter="<<counter<<" count="<<count<<" texture is PMA="<<sprite->getTexture()->hasPremultipliedAlpha());

                    ccTag       (sprite,description.type);
                        //tDebug( io::saveToFilePNG(sprite,to_string("factory-textureCreate-sprite-",counter,"-",count,"-before.png")); );
                    
                        // COMPOSE SPRITE TREE, IE LAYER THE SPRITES
#if 1
                    bool valid = description.relative.valid();
                    auto value = description.relative.value();
                    
                    if (valid and first and value.isRelativeToFirst())
                    {
                        first->addChild(sprite);
                    }
                    else if (valid and previous and value.isRelativeToPrevious())
                    {
                        previous->addChild(sprite);
                    }
                    else if (valid and previous and value.value <= count)
                    {
                        if (0 < value.value)
                        {
                            auto parent = descriptions.at(value.value-1).sprite;
                            
                            parent->addChild(sprite);
                        }
                        else
                        {
                            root->addChild(sprite);
                        }
                    }
                    else
                    {
                        root->addChild(sprite);
                    }
#else
                    textureCreateStepHierarchy(sprite,root,previous,first,description,descriptions,count);
#endif
                    
                        // CALCULATE BOUNDING BOX
                    
                        // NOTE: NEED TO TAKE BOUNDING BOX OF SPRITE >BEFORE< AND >AFTER< APPLICATION, DUE TO POSITION/ALIGNMENT
                        //       ISSUES.  BBOX AFTER WILL DIFFER FROM BBOX BEFORE IF SPRITE IS POSITIONED OR ALIGNED IN NON DEFAULT
                        //       WAY (IE (0,0) / (.5,.5))
                    
                    aabb.add(bbox2w(sprite));
                    
                        // APPLY CUSTOM BLENDING TO SPRITE (OPTIONAL)
                    if (parameters.blending.applyToAll)
                    {
                        description.add(oBlending(parameters.blending.applicant));
                    }
                    
                        // FINALLY, APPLY OPERATORS ON SPRITE
                    description.apply(sprite);

                        // CALCULATE RESULTING BBOX
                    aabb.add(bbox2w(sprite));
                    
                        //tDebug( io::saveToFilePNG(sprite,to_string("factory-textureCreate-sprite-",counter,"-",count,"-after.png")); );
                    
                    if (not first)
                    {
                        first = sprite;
                    }
                    
                    previous = sprite;
                    
                    count++;
                }
                
                if (symmetric)
                {
                    aabb.size.width = aabb.size.height = max(aabb.size.width,aabb.size.height);
                }
                
                return {root,aabb.size};
            }
            
            
            
            
            
            
            
            CCSpritePtr Factory::textureCreateStepRender (CCNodePtr root, CCSize size, Color4F fill)
            {
                CCSpritePtr r = 0;
                
                if (parameters.render.function)
                {
                    r = parameters.render.function(root,size,fill);
                }
                else
                {
                    r = ccRender(root,size,fill);
                }
                
                return r;
            }
            
            
            
            
            
            
            
            CCTexture2DPtr Factory::textureCreateFromDescriptions (int type, vectorCRef(Description) descriptions, Color4F fill, bool symmetric)
            {
                auto formation = textureCreateStepFormation(type,descriptions,fill,symmetric);
                
                    // REMEMBER TO HAVE ROOT SIZE BE 0x0
                
                CCSpritePtr sprite = textureCreateStepRender(formation.root,formation.size,fill);
                
                    //tDebug( io::saveToFilePNG(sprite,to_string("factory-textureCreate-result-",counter,"-",aabb.size.width,"x",aabb.size.height,".png")); );
                
                if (1)
                {
                        //blending.restore();
                    glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
                }
                
                return sprite->getTexture();
            }
            
            
            
            
            
            
            
            
            
            
            
            
            CCTexture2DPtr Factory::textureCreateFromComposition (Composition composition, vectorCRef(Description) arrangements, std::function<CCSpritePtr (DescriptionCRef)> producerOfSprite)
            {
                    // ALGORITHM:
                    //  1 COMPOSE SPRITE TO BE RENDERED (1)
                    //    1 CREATE TOP SPRITE (1-1)
                    //    2 FOR EACH ARRANGEMENT (1-2)
                    //      1 CREATE ROOT SPRITE (1-2-1)
                    //      2 FOR EACH LAYER (1-2-2)
                    //        1 CREATE LAYER SPRITE FROM DESCRIPTION (IE PROVIDED FUNCTION) (1-2-2-1)
                    //        2 ATTACH SPRITE TO SPRITE HIERARCHY ON ROOT (IE ARRANGEMENT) (1-2-2-2)
                    //        3 APPLY OPERATORS ON SPRITE (1-2-2-3)
                    //      3 APPLY OPERATORS ON ROOT (1-2-3)
                    //    3 APPLY OPERATORS ON TOP (1-3)
                    //  2 RENDER SPRITE (2)
                
                static int counter = 0;
                
                counter++;
                
                AABB topAABB;
                
                    // CREATING TOP SPRITE
                
                auto top = ccSpriteEmpty();
                
                if (parameters.blending.applyToRoot)
                {
                    ccBlending  (top,parameters.blending.applicant);
                }
                
                ccTag       (top,composition.description.type);
                
                    // THINK OF TOP AS THE CORONA SPRITE, IE TOP=CORONA
                    // THINK OF AN ARRANGEMENT AS A SINGLE PETAL OF A CORONA, IE ROOT=PETAL
                    // THINK OF A LAYER AS A SINGLE LAYER OF A PETAL, IE LAYER=PETAL OVERLAY
                
                for(auto arrangement:arrangements)
                {
                    int count = 0;
                    
                        // CREATE ROOT SPRITE
                    
                    CCSpritePtr root = arrangement.sprite = ccSpriteEmpty();
                    
                    if (parameters.blending.applyToRoot)
                    {
                        ccBlending  (root,parameters.blending.applicant);
                    }
                    ccAnchor    (root,Vec2(.5,.5));
                    ccTag       (root,composition.description.type);
                    
                    CCNodePtr   first     = 0;
                    CCNodePtr   previous  = 0;
                    
                    AABB        rootAABB;
                    
                    auto        LAYERS = composition.layers;
                    
                    for(autoRef LAYER:LAYERS)
                    {
                        autoRef DESCRIPTION = LAYER.description;
                        
                            // CREATE DESCRIPTION SPRITE
                        
                        auto sprite = DESCRIPTION.sprite = producerOfSprite(DESCRIPTION);
                        
                        if (not sprite)
                        {
                            continue; // ????
                        }
                        
                        tAssert(sprite);
                        
                            //tLog("textureCreateFromComposition: counter="<<counter<<" count="<<count<<" texture is PMA="<<sprite->getTexture()->hasPremultipliedAlpha());

                            //ccBlending  (sprite,blending);
                        ccTag       (sprite,DESCRIPTION.type);
                        
                            //tDebug( io::saveToFilePNG(sprite,to_string("factory-textureCreate-sprite-",counter,"-",count,"-before.png")); );
#if 1
                        bool valid = DESCRIPTION.relative.valid();
                        auto value = DESCRIPTION.relative.value();
                        
                        if (valid and first and value.isRelativeToFirst())
                        {
                            first->addChild(sprite);
                        }
                        else if (valid and previous and value.isRelativeToPrevious())
                        {
                            previous->addChild(sprite);
                        }
                        else if (valid and previous and value.value <= count)
                        {
                            if (0 < value.value)
                            {
                                auto parent = LAYERS[value.value-1].description.sprite;
                                
                                parent->addChild(sprite);
                            }
                            else
                            {
                                root->addChild(sprite);
                            }
                        }
                        else
                        {
                            root->addChild(sprite);
                        }
#else
                        textureCreateStepHierarchy(sprite,root,previous,first,DESCRIPTION,LAYERS,count);
#endif
                        
                        {
                            if (parameters.blending.applyToAll)
                            {
                                DESCRIPTION.add(oBlending(parameters.blending.applicant));
                            }
                            
                            DESCRIPTION.apply(sprite);
                            
                            rootAABB.add(bbox2w(sprite));
                        }
                        
                            //tDebug( io::saveToFilePNG(sprite,to_string("factory-textureCreate-sprite-",counter,"-",count,"-after.png")); );
                        
                        if (not first)
                        {
                            first = sprite;
                        }
                        
                        previous = sprite;
                        
                        count++;
                    }
                    
                    top -> addChild(root);
                    
                    {
                        ccResize(root,rootAABB.size);
                        
                            // -ALL CHILDREN OF ROOT HAVE BEEN ALIGNED RELATIVE TO ITS CENTER
                            // -NOW THAT THE ROOT HAS CHANGED ITS SIZE FROM 1X1 TO WxH WE NEED TO REPOSITION ITS IMMEDIATE CHILDREN BY HALF-THAT
                        
                        CCPoint vector = s2p(rootAABB.size)/2.;
                        
                        for(auto child:ccChildren(root))
                        {
                            ccMoveBy(child,vector);
                        }
                    }
                    
                        //tDebug( io::saveToFilePNG(root,to_string("factory-textureCreate-root-",counter,"-a.png")); );
                    
                        // PREPEND BLENDING ONTO ROOT SPRITE
                    if (parameters.blending.applyToAll)
                    {
                        arrangement.add(oBlending(parameters.blending.applicant));
                    }
                    
                        //tDebug( io::saveToFilePNG(root,to_string("factory-textureCreate-root-",counter,"-b.png")); );
                    arrangement.apply(root);
                        //tDebug( io::saveToFilePNG(root,to_string("factory-textureCreate-root-",counter,"-c.png")); );
                    
                    for(autoRef LAYER:LAYERS)
                    {
                        topAABB.add(bbox2w(LAYER.description.sprite));
                    }
                }
                
                if (composition.symmetric)
                {
                    topAABB.size.width = topAABB.size.height = max(topAABB.size.width,topAABB.size.height);
                }
                    // REMEMBER TO HAVE ROOT SIZE BE 0x0
                
//                auto sprite = ccRender(top,topAABB.size,fill);
                
                auto sprite = textureCreateStepRender(top,topAABB.size,composition.fill);
                
                    //tDebug( io::saveToFilePNG(sprite,to_string("factory-textureCreate-result-",counter,"-",aabb.size.width,"x",aabb.size.height,".png")); );
                
                if (1)
                {
                    glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
                }

                return sprite->getTexture();
            }
            
            
            
            
            
            
            Composition::Composition    ()
            {
                fill = {1,1,1,0};
            }
            
            
            
            
            
            vector<Description>             Composition::layersGetAsDescriptions () const
            {
                vector<Description> r;
                r.reserve(layers.size());
                
                for(autoCRef layer:layers)
                {
                    r.push_back(layer.description);
                }
                
                return r;
            }

            

            
            
        } // namespace Texture
    }
}
