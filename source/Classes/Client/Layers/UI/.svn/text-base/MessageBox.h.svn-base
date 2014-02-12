#ifndef _MESSAGE_BOX_H_
#define _MESSAGE_BOX_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Singleton_t.h"
#include "LayerAutoAdaptiveBase.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace GUI
{
	class MessageBox: public CCNode, public TSingleton<MessageBox> , public LayerAutoAdaptiveBase
	{
	public:
		MessageBox();
		~MessageBox();

		void Show(const char* content,const char* okBtnContent = "",
			const char* cancelBtnContent = "",
			CCObject* handler = NULL,
			SEL_ReleaseEvent ok_selector = NULL,
			SEL_ReleaseEvent cancel_selector = NULL);

		virtual void AdjustWidgetForScreen(Layout* pLayout);

		void Destory();
	protected:
		CCNode* GetParentNode();

		void onOkButtonClick(CCObject* pSender);
		void onCancelLoginClick(CCObject* pSender);
	private:
		UILayer* s_layer;
		CCObject* s_handler;
		SEL_ReleaseEvent s_ok_selector;
		SEL_ReleaseEvent s_cancel_selector;
	};
}

#endif	//_MESSAGE_BOX_H_