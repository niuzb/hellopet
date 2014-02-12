//
//  IPlatform.h
//  iSeer
//
//  Created by b a on 12-5-11.
//  Copyright (c) 2012�� __MyCompanyName__. All rights reserved.
//

#ifndef iSeer_IPlatform_h
#define iSeer_IPlatform_h


///
// enum  language of device
//
enum
{
    LANGUAGE_HS,//��������
    LANGUAGE_HT,//��������
    LANGUAGE_EN,//Ӣ��
};


///
// enum  UIUserInterfaceType
//
typedef  enum
{
    UIUserInterfacePhone,           // iPhone and iPod touch style UI
    UIUserInterfaceRetinaPhone,
    UIUserInterfacePad     // iPad style UI
}UIUserInterfaceType;


///
// interface of platform
// 
class IPlatform
{
public :
    
    virtual ~IPlatform() {}
    
    ///
    //  InitPlatform
    //  init all the devices that needed!
    //
    virtual void InitPlatform() = 0;
    
    
    ///
    //  ShutDown
    //  clean up all context used  
    //
    virtual void ShutDown() = 0;
    
    ///
    //  @prototype, playAudioEffect
    //
    //  @param 
    //         name,  audio file's name
    //  @param
    //         delay, delay a time to play sound
    //
	virtual void PlayAudioEffect(const char*name, float delay) = 0;

	///
	//  @prototype, UTF8Length
	//
	//  @param
	//         str,   source string
	//
	virtual int UTF8Length(const char* str) = 0;

	///
	//  @prototype, UTF8SubString
	//
	//  @param  inStr,  source string
	//  @param  length, sub-string length
	//  @param  outStr, destination string
	virtual void UTF8SubString(const char* inStr, int length, char* outStr) = 0;
    
    
    ///
    //  @prototype, getCurLanguage
    //
    //  @param 
    //         void
    //  @note, get current lanaguage from the device
    virtual int getCurLanguage() = 0;
    
    ///
    //  @prototype, getDeviceUUID
    //  @param 
    //         void
    // ��ȡ�豸��UUID
    virtual const char *getDeviceUUID() = 0;
    
    ///
    //  @prototype, getVersion
    //  @param 
    //         void
    //��0.0.1.6 ��Ϸ�汾ת��Ϊ16����
    virtual unsigned int getVersion() = 0;
    
    ///
    //  @prototype, getVersionA
    //  @param 
    //         void
    //��ȡinfo.plist�е�bundle version
    //��ʽ0.0.1.6
    virtual const char *getVersionA() = 0;
    
    ///
    //  @prototype, getSystemVersion
    //  @param 
    //         void
    //��ȡios����ϵͳ��version
    virtual float getSystemVersion() = 0;
    
    ///
    //  @prototype, isConnected
    //  @param 
    //         bool, connected ture, otherwise false
    //�ж��豸����������״̬
    virtual bool IsConnected() = 0;
    
    ///
    //  @prototype, getUserInterface
    //  @param 
    //         UIUserInterfaceType
    //�ж��豸��iphone��or��ipad
    virtual UIUserInterfaceType getUserInterface() = 0;
    
    ///
    //  @prototype, isRetinaDisplay
    //  @param 
    //         bool, ture for retina display, otherwise false
    virtual bool IsRetinaDisplay() = 0;
    
    ///
    //  @prototype, isRetinaDisplay
    //  @param 
    //         bool, ture for retina display, otherwise false
    virtual void initUserInterface() = 0;
    
    ///
    //  @prototype, isRetinaDisplay
    //  @param 
    //         bool, ture for retina display, otherwise false
    virtual bool IsIpad() = 0;
    
    virtual const char *CCLocalizedString(const char *key,const char *comment) = 0;
    
    //kechain
    virtual const char* getPasswordForUsername(const char* username,const char* serviceName) = 0;
    
    virtual bool storeUsername(const char* username ,const char* password,const char* serviceName ,bool updateExisting ) =0;
    
};

#endif
