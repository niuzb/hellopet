// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//

#ifndef iSeer_UICreator_h
#define iSeer_UICreator_h

#include "TXGUI.h"

namespace TXGUI {
    class UILayerBase;
    class CustomScene;
    class UILayout;
    
	/**
     * @brief ����resource.h�����л�ȡ������Դ���ֵı���ֵ 
     * @param name, ��Դ��
     * @return int, ��Դ����ֵ
     * @
     */ 
    int getResourceIDByName(const char* name);

	void resetReloadResourceID();

    class UICreator
    {
    public: 
        /**
         * @brief ����һ��UIͼ��
         * @param SceneType, 
         * @param pCustomScene, ��ͼ��
         * @return UILayerBase, UILayer�Ķ���
         * @
         */
        static UILayerBase* CreateUILayer(SceneType _sceneType, CustomScene* pCustomScene);   
        
		/**
         * @brief ���ļ��д���һ��UIͼ��
         * @param file, ����plist�ļ����ڵ�λ��
         * @param pParent, ��ͼ��
         * @return bShow, �Ƿ�Ĭ��Ϊ��ʾ
         * @
         */
        static UILayout*  CreateUILayoutFromFile(const char* file,  cocos2d::CCNode *pParent,
                                                     bool bShow = false); 

		/**
         * @brief ���ļ��д���һ��UIͼ��,�Ӳ��뵽UIϵͳ��Ĭ�ϵĽڵ���
         * @param file, ����plist�ļ����ڵ�λ��
         * @return bShow, �Ƿ�Ĭ��Ϊ��ʾ
         * @
         */
        static UILayout*  CreateUILayoutFromFile(const char* file, bool bShow = false); 
    };
    
    class TXMainSDM
    {
    public:
        static void Init();
        static void ShutDown();
    };
    
    
#define dispatchMenuEvent(pfn, pObject) (UIManager::sharedManager()->DispatchMenuEvent(this, pfn, pObject)) 
#define RegisterMenuEvent(layerout, pfn) (layerout->RegisterMenuHandler(
}




#endif
