//
//  StoreManager.h
//  idou
//
//  Created by razer tong on 11-11-3.
//  Copyright 2011�� __MyCompanyName__. All rights reserved.
//

#ifndef idou_StoreManager_h
#define idou_StoreManager_h

// Disable
//#include "GameDataManager.h"

typedef enum
{
    KProductA=0,//com.taomee.seer.vipgold1 
    KProductB,
    KProductC,
    KProductD,
    KProductE,
    KProductF,
    KProductUnknow,
}KProductType;

typedef  struct  
{
    KProductType type;
    int num;//�����𶹵�����
    float cost;
}KProductInfo;

namespace CocosIAP 
{
class  ProductManager
    {
 
    public:
        ProductManager();
        ~ProductManager();
		static ProductManager *sharedManager();
        
        //�����
		void buyProduct(KProductType type);
       
        //�����û��ѹ��򵽵Ľ�
		void addVipGolds();
        
        //���������������
		void requesetProductData();
        
        //���ػ��۸�
        const char *getFormattedPriceAtIndex(int index);
    };
}

#endif
