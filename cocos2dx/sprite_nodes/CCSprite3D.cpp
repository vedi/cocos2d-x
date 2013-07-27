/****************************************************************************

Copyright (c) 2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCSprite3D.h"
#include "CCDirector.h"
#include "3d_model_support/model.h"
#include "kazmath/GL/matrix.h"
#include "shaders/CCShaderCache.h"
#include "effects/CCGrid.h"
#include "3d_model_support/md2.h"
#include "support/CCPointExtension.h"
#include "CCTextureCache.h"

NS_CC_BEGIN

CCSprite3D* CCSprite3D::create(CCModel* pModel)
{
    CCSprite3D* pRet = new CCSprite3D();
    if (pRet && pRet->init()) {
        pRet->setModel(pModel);
        pRet->autorelease();
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

CCSprite3D::CCSprite3D()
: m_pModel(NULL)
, m_modelRotation(0.0f)
{
    kmVec3Fill(&m_modelPosition, 0, 0, 0);
    kmVec3Fill(&m_modelScale, 1.0f, 1.0f, 1.0f);
    mCustSkin = CCTextureCache::sharedTextureCache()->addImage("images/main.png");
    mCustSkin->retain();
}

CCSprite3D::~CCSprite3D()
{
    CC_SAFE_RELEASE(m_pModel);
}

void CCSprite3D::setModel(CCModel* pModel)
{
    CC_SAFE_RETAIN(pModel);
    CC_SAFE_RELEASE(m_pModel);
    m_pModel = pModel;
}

CCModel* CCSprite3D::getModel()
{
    return m_pModel;
}

bool CCSprite3D::init()
{
    CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
    setShaderProgram(program);

    return true;
}

void CCSprite3D::setPosition(float x,float y,float z)
{
    kmVec3Fill(&m_modelPosition, x, y, z);
}

void CCSprite3D::setPosition(const CCPoint &position)
{
    m_modelPosition.x = position.x;
    m_modelPosition.y = position.y;
    CCNode::setPosition(position);
}

const CCPoint& CCSprite3D::getPosition()
{
    return CCNode::getPosition();
    return ccp(m_modelPosition.x, m_modelPosition.y);
}

kmVec3 CCSprite3D::getPosition() const
{
    return m_modelPosition;
}

float CCSprite3D::getRotation()
{
    return CCNode::getRotation();
}

void CCSprite3D::setRotation(float fRotation)
{
    CCNode::setRotation(fRotation);
}

void CCSprite3D::setScale(float x,float y,float z)
{
    kmVec3Fill(&m_modelScale, x, y, z);
}

kmVec3 CCSprite3D::getScale() const
{
    return m_modelScale;
}

void CCSprite3D::setVisible(bool visible)
{
    CCNode::setVisible(visible);
}

bool CCSprite3D::isVisible()
{
    return CCNode::isVisible();
}

void CCSprite3D::showBoundingBox(bool show)
{
    // TODO
}

void CCSprite3D::draw()
{
//    m_bDepthTestEnabled = 0 == glIsEnabled(GL_DEPTH_TEST) ? false : true;
//
//    CCDirector::sharedDirector()->setDepthTest(true);
//
    CC_NODE_DRAW_SETUP();

//    getShaderProgram()->use();
//    getShaderProgram()->setUniformsForBuiltins();

    CCPoint const & origin = ccp(0, 0);
    CCPoint const & destination = ccp(100, 100);

    ccVertex3F vertices[3] = {
//        {origin.x, origin.y, 100},
            {destination.x, origin.y, 200},
            {destination.x, destination.y, 100},
            {origin.x, destination.y, 200}
    };

    ccTex2F uv[3] = {
//        {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f}
    };

    ccColor4B colors[3] = {
//        {255, 255, 255, 255},
            {128, 128, 128, 128},
            {128, 128, 128, 128},
            {255, 255, 255, 255}
    };

    ccGLBindTexture2D(mCustSkin->getName());

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, uv);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    CHECK_GL_ERROR_DEBUG();

    CC_INCREMENT_GL_DRAWS(1);

//    m_pModel->draw();
//    static unsigned int uiStartFrame = 0, uiEndFrame = 182;
//    static float fAnimSpeed = 16.5f;
//   ((CCModelMd2*)m_pModel)->animate(fAnimSpeed, uiStartFrame, uiEndFrame, true);
//   CCDirector::sharedDirector()->setDepthTest(m_bDepthTestEnabled);
}

void CCSprite3D::transform(void)
{
    CCNode::transform();
//    kmGLTranslatef(m_modelPosition.x, m_modelPosition.y, m_modelPosition.z);
//    kmGLScalef(m_modelScale.x, m_modelScale.y, m_modelScale.z);
//    kmGLRotatef(getRotation(), 0, 0, 1.0f);
}

NS_CC_END
