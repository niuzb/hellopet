LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame
LOCAL_CPP_EXTENSION := .cc .cpp
LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/Client/BoneAniManager/AnimABBoxDataCenter.cpp \
../../Classes/Client/BoneAniManager/SkeletonAnimRcsManager.cpp \
../../Classes/Client/GameManager/BattleManger.cpp \
../../Classes/Client/GameManager/CommonLookUpUtils.cpp \
../../Classes/Client/GameManager/XLogicManager.cpp \
../../Classes/Client/Layers/Game/BattleLayer.cpp \
../../Classes/Client/Layers/Game/BattleLayerMoveController.cpp \
../../Classes/Client/Layers/UI/BattleUILayer.cpp \
../../Classes/Client/Layers/UI/LoginUILayer.cpp \
../../Classes/Client/Layers/UI/MainMenuLayer.cpp \
../../Classes/Client/Layers/UI/UIManager.cpp \
../../Classes/Client/Layers/UI/MessageBox.cpp \
../../Classes/Client/Layers/UI/LayerAutoAdaptiveBase.cpp \
../../Classes/Client/Layers/UI/BattleUIArmyHeadIconPanel.cpp \
../../Classes/Client/Layers/UI/BattleUISkillIconPanel.cpp \
../../Classes/Client/Layers/Game/LoadingLayer.cpp \
../../Classes/Client/Layers/Game/BattleLoadingLayer.cpp \
../../Classes/Client/Map/MapDataCenter.cpp \
../../Classes/Client/Map/MapPhysicalLayer.cpp \
../../Classes/Client/Particle/BoneAniParticle/BoneParticle.cpp \
../../Classes/Client/Particle/ParticleManager.cpp \
../../Classes/Client/Props/PropsDataCenter.cpp \
../../Classes/Client/Props/PropsTriggerManager.cpp \
../../Classes/Client/Props/PropsTriggerSprite.cpp \
../../Classes/Client/Props/PropsTriggerBase.cpp \
../../Classes/Client/Props/FlySingleBombProp.cpp \
../../Classes/Client/Props/LocalExplosionProp.cpp \
../../Classes/Client/Props/WithHeroProtectProp.cpp \
../../Classes/Client/Props/RoundFlyBombProp.cpp \
../../Classes/Client/Props/AutoFighterProp.cpp \
../../Classes/Client/Props/HeroDeformProp.cpp \
../../Classes/Client/Props/AwayExplosionProp.cpp \
../../Classes/Client/Props/PropBase.cpp \
../../Classes/Client/Props/PropManager.cpp \
../../Classes/Client/Lua/lua_tinker.cpp \
../../Classes/Client/Lua/LuaTinkerManager.cpp \
../../Classes/Client/Sprite/BoneAnimSprite.cpp \
../../Classes/Client/Sprite/RoleActorBase.cpp \
../../Classes/Client/Sprite/SpriteBase.cpp \
../../Classes/Client/Sprite/SpriteBaseNode.cpp \
../../Classes/Client/Sprite/SpriteCreatorFactory.cpp \
../../Classes/Client/Sprite/SpriteHero.cpp \
../../Classes/Client/Sprite/SpriteOthHero.cpp \
../../Classes/Client/Sprite/UserData.cpp \
../../Classes/Client/Sprite/SpriteArmyPool.cpp \
../../Classes/Client/Sprite/SpriteHeroBase.cpp \
../../Classes/Client/Sprite/SpriteDecorationBatchNode.cpp \
../../Classes/Client/SpriteBehavior/BehaviorDefine.cpp \
../../Classes/Client/SpriteBehavior/HeroBehavior/HeroRunState.cpp \
../../Classes/Client/SpriteBehavior/RoleState/BaseAttackState.cpp \
../../Classes/Client/SpriteBehavior/RoleState/DieState.cpp \
../../Classes/Client/SpriteBehavior/RoleState/IdleState.cpp \
../../Classes/Client/SpriteBehavior/RoleState/RunState.cpp \
../../Classes/Client/SpriteBehavior/RoleState/NormalAttackState.cpp \
../../Classes/Client/SpriteBehavior/RoleState/SkillDispMgr.cpp \
../../Classes/Client/SpriteBehavior/RoleState/AttackChecker.cpp \
../../Classes/Client/StateMachine/FStateMachine.cpp \
../../Classes/Client/Timer/TimeSynchronizer.cpp \
../../Classes/Client/Timer/HeartbeatPackageSender.cpp \
../../Classes/Client/GraphicShape/Painter.cpp \
../../Classes/Engine/CameraController.cpp \
../../Classes/Engine/CommonUtils.cpp \
../../Classes/Engine/Flash2Cocos2d-X/ArmatureSpritePool.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CAnimation.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CArmature.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CArmatureAniData.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CBaseNode.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CBone.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CBoneAniData.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CConnectionData.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CEventFrame.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CFrameNode.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CFrameNodeList.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CMathHelper.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CProcessBase.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CTween.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CTweenNode.cpp \
../../Classes/Engine/Flash2Cocos2d-X/CXLog.cpp \
../../Classes/Engine/Illusion_Particle/ParticleAnimation.cpp \
../../Classes/Engine/Illusion_Particle/ParticleFactory.cpp \
../../Classes/Engine/Illusion_Particle/SpriteParticle.cpp \
../../Classes/Engine/NetWork/BaseMsgHandler.cpp \
../../Classes/Engine/NetWork/LuaNetwork.cpp \
../../Classes/Engine/NetWork/MessageCache.cpp \
../../Classes/Engine/NetWork/MessageHandler.cpp \
../../Classes/Engine/NetWork/MessageLog.cpp \
../../Classes/Engine/NetWork/MessageUtil.cpp \
../../Classes/Engine/NetWork/NetStateChecker.cpp \
../../Classes/Engine/NetWork/NetWorkUtil.cpp \
../../Classes/Engine/NetWork/cs_basic.pb.cc \
../../Classes/Engine/NetWork/cs_core.pb.cc \
../../Classes/Engine/NetWork/head.pb.cc \
../../Classes/Engine/NetWork/cs_battle.pb.cc \
../../Classes/Engine/NetWork/db.pb.cc \
../../Classes/Engine/NetWork/errcode.pb.cc \
../../Classes/Engine/NetWork/cs_config.pb.cc \
../../Classes/Engine/NetWork/OnlineNetworkManager.cpp \
../../Classes/Engine/Sound/GameAudioManager.cpp \
../../Classes/Engine/Sound/SoundConfigDataCenter.cpp \
../../Classes/Engine/XmlParser/TinyXml/tinystr.cpp \
../../Classes/Engine/XmlParser/TinyXml/tinyxml.cpp \
../../Classes/Engine/XmlParser/TinyXml/tinyxmlerror.cpp \
../../Classes/Engine/XmlParser/TinyXml/tinyxmlparser.cpp \
../../Classes/HelloWorldScene.cpp \
../../libs/CrossPlatform/AES.cpp \
../../libs/CrossPlatform/CSocketUtil.cpp \
../../libs/CrossPlatform/CrossXOS.cpp \
../../libs/CrossPlatform/FileUtils.cpp \
../../libs/CrossPlatform/ImageUtil.cpp \
../../libs/CrossPlatform/Thread.cpp \
../../libs/CrossPlatform/md5.cpp \
../../libs/CrossPlatform/util.cpp \
../../libs/PageManager/CCFileData.cpp \
../../libs/PageManager/GameResourceManager.cpp \
../../libs/PageManager/Resource/ResourcePlistArray.cpp \
../../libs/PageManager/Resource/ResourcePlistDictionary.cpp \
../../libs/PageManager/Resource/ResourceTexture.cpp \
../../libs/PageManager/ResourceCache.cpp \
../../libs/PageManager/ResourcePage.cpp \
../../libs/PageManager/ResourcePageManager.cpp \


#	../../Classes/AppDelegate.cpp \
#	../../Classes/HelloWorldScene.cpp 
#APP_SUBDIRS := $(patsubst $(LOCAL_PATH)/%, %, $(shell find $(LOCAL_PATH)/$(APPDIR) -path '*/.svn' -prune -o -type d -print))
#APP_SUBDIRS := $(patsubst $(LOCAL_PATH)/%, %, $(shell find $(LOCAL_PATH)/../../Classes -path '*/.svn' -prune -o -type d -print))
#LOCAL_SRC_FILES := $(filter %.c %.cpp, $(APP_SUBDIRS))
#APP_SUBDIRS := $(filter-out %.c %.cpp, $(APP_SUBDIRS))
#LOCAL_SRC_FILES += $(foreach F, $(APP_SUBDIRS), $(addprefix $(F)/,$(notdir $(wildcard $(LOCAL_PATH)/$(F)/*.cpp))))
#LOCAL_SRC_FILES += $(foreach F, $(APP_SUBDIRS), $(addprefix $(F)/,$(notdir $(wildcard $(LOCAL_PATH)/$(F)/*.c))))
#LOCAL_SRC_FILES += hellocpp/main.cpp       

           
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes  \
$(LOCAL_PATH)/../../Classes/Engine  \
$(LOCAL_PATH)/../../Classes/Client  \
$(LOCAL_PATH)/../../cocos2dx/external/Box2D  \
$(LOCAL_PATH)/../../cocos2dx/cocos2dx/platform  \
$(LOCAL_PATH)/../../cocos2dx/cocos2dx/include  \
$(LOCAL_PATH)/../../cocos2dx/cocos2dx/kazmath/include  \
$(LOCAL_PATH)/../../cocos2dx/cocos2dx/include  \
$(LOCAL_PATH)/../../cocos2dx/cocos2dx/platform/android  \
$(LOCAL_PATH)/../../cocos2dx/cocos2dx/platform/third_party/android \
$(LOCAL_PATH)/../../cocos2dx/cocos2dx/platform/third_party/android/prebuilt/libxml2/include \
$(LOCAL_PATH)/../../libs \
$(LOCAL_PATH)/../../libs/PageManager \
$(LOCAL_PATH)/../../libs/PageManager/Resource \
$(LOCAL_PATH)/../../libs/TXGUI \
$(LOCAL_PATH)/../../libs/TXGUI/Common \
$(LOCAL_PATH)/../../libs/CrossPlatform \
$(LOCAL_PATH)/../../libs/ProtoBuf/include \
$(LOCAL_PATH)/../../Classes/Engine/Flash2Cocos2d-X \
$(LOCAL_PATH)/../../Classes/Engine/XmlParser/TinyXml \
$(LOCAL_PATH)/../../Classes/Client/BoneAniManager\
$(LOCAL_PATH)/../../Classes/Client/GameManager/     \
$(LOCAL_PATH)/../../Classes/Client/Map       \
$(LOCAL_PATH)/../../Classes/Client/SpriteBehavior \
$(LOCAL_PATH)/../../Classes/Client/Common          \
$(LOCAL_PATH)/../../Classes/Client/GraphicShape  \
$(LOCAL_PATH)/../../Classes/Client/Layers    \
$(LOCAL_PATH)/../../Classes/Client/Layers/Game    \
$(LOCAL_PATH)/../../Classes/Client/Layers/UI    \
$(LOCAL_PATH)/../../Classes/Client/Particle  \
$(LOCAL_PATH)/../../Classes/Client/Sprite  \
$(LOCAL_PATH)/../../Classes/Client/StateMachine \
$(LOCAL_PATH)/../../Classes/Engine/ATLTileMap \
$(LOCAL_PATH)/../../Classes/Engine/NetWork \
$(LOCAL_PATH)/../../Classes/Engine/Illusion_Particle \



LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static cocos_lua_static box2d_static protobuf_static
            
include $(BUILD_SHARED_LIBRARY)
$(call import-add-path,  $(LOCAL_PATH)/../../cocos2dx)
$(call import-add-path,  $(LOCAL_PATH)/../../libs)
$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android) 
 
$(call import-module,extensions)
$(call import-module,scripting/lua/proj.android)
$(call import-module,external/Box2D)
$(call import-module,ProtoBuf/android)