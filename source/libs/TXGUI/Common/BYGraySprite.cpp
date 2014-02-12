//
// BYGraySprite.cpp
//

#include "BYGraySprite.h"

BYGraySprite::BYGraySprite()
{
}


BYGraySprite::~BYGraySprite()
{
}


BYGraySprite* BYGraySprite::create( const char* pszFileName ){
	BYGraySprite* graySprite = new BYGraySprite;
	if (graySprite && graySprite->initWithFile(pszFileName)){
		graySprite->autorelease();
		return graySprite;
	}else{
		CC_SAFE_RELEASE(graySprite);
		return NULL;
	}
}

BYGraySprite* BYGraySprite::create()
{
	BYGraySprite *pSprite = new BYGraySprite();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

BYGraySprite* BYGraySprite::createWithTexture(CCTexture2D *pTexture)
{
	BYGraySprite *pobSprite = new BYGraySprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

bool BYGraySprite::initWithTexture(CCTexture2D *pTexture)
{
	return CCSprite::initWithTexture(pTexture);
}

bool BYGraySprite::initWithTexture(CCTexture2D* pTexture, const CCRect& tRect ){
	do{
		CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, tRect));


		GLchar* pszFragSource =
			"#ifdef GL_ES \n \
			precision mediump float; \n \
			#endif \n \
			uniform sampler2D u_texture; \n \
			varying vec2 v_texCoord; \n \
			varying vec4 v_fragmentColor; \n \
			void main(void) \n \
			{ \n \
			// Convert to greyscale using NTSC weightings \n \
			//calculate the fragment color based on the texture and the vertex colour \n \
			vec4 basecolor = texture2D(u_texture, v_texCoord); \n \
			vec4 frameColor = basecolor; \n \
			frameColor.r = (basecolor.r + basecolor.g + basecolor.b) / 3.0; \n \
			frameColor.g = (basecolor.r + basecolor.g + basecolor.b) / 3.0; \n \
			frameColor.b = (basecolor.r + basecolor.g + basecolor.b) / 3.0; \n \
			if(basecolor.a == 0.0) \n \
			{ \n \
			//throw this fragment away \n \
			discard; \n \
			} \n \
			gl_FragColor = frameColor; \n \
			}";


		CCGLProgram* pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
		this->setShaderProgram(pProgram);
		pProgram->release();
		CHECK_GL_ERROR_DEBUG();


		this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();


		this->getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();


		this->getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();


		return true;
	} while (0);
	return false;
}


void BYGraySprite::draw(){
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );


	this->getShaderProgram()->use();
	this->getShaderProgram()->setUniformForModelViewProjectionMatrix();


	ccGLBindTexture2D( this->getTexture()->getName() );


#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;


	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));


	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));


	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWS(1);
}
