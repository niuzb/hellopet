//
//  ImageUtil.h
//  iSeer
//
//  Created by b a on 12-5-14.
//  Copyright (c) 2012�� __MyCompanyName__. All rights reserved.
//

#ifndef iSeer_ImageUtil_h
#define iSeer_ImageUtil_h



//�Ѳ�ɫͼת��Ϊ�Ҷ�ͼ
void convertToGray(unsigned char *imgPixel,const int &width,const int &height);

//����ת��
void convertToLight(unsigned char *imgPixel,const int &width,const int &height,int value);


#endif
