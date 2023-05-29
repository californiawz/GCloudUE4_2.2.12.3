//
//  OperationQueue.h
//  TaskPool
//
//  Created by vforkk on 5/17/16.
//  Copyright © 2016 vforkk. All rights reserved.
//

#ifndef ABase_OperationQueue_h
#define ABase_OperationQueue_h

#include "Operation.h"

namespace ABase {
    class EXPORT_CLASS OperationQueue
    {
    public:
        static OperationQueue* GetInstance();
    public:
        virtual void AddOperation(OperationTargetBase* target, ObjectOperator op, void* param = NULL, bool repeat = true) = 0;
        virtual void AddOperation(StaticOperator op, void* param = NULL, bool repeat = true) = 0;
        //virtual void AddOperation(const Operation& operation) = 0;
        
    };
}

#endif /* ABase_OperationQueue_h */
