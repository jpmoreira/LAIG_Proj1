//
//  LG_Transform.h
//  LAIG-Proj1
//
//  Created by José Pedro Moreira on 30/09/14.
//  Copyright (c) 2014 José Pedro Moreira. All rights reserved.
//

#ifndef __LAIG_Proj1__LG_Transform__
#define __LAIG_Proj1__LG_Transform__

#include "LG_Parsable_Node.h"



class LG_Transform:public LG_Parsable_Node{
    
    

    static LG_Transform * transform(LG_Node_Map map,TiXmlElement elem);
    
};

#endif /* defined(__LAIG_Proj1__LG_Transform__) */
