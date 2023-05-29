//
//  IOperation.h
//  OperationQueue
//
//  Created by vforkk on 5/17/16.
//  Copyright © 2016 vforkk. All rights reserved.
//

#ifndef ABase_IOperation_h
#define ABase_IOperation_h

#include "ABasePal.h"

namespace ABase {
    
    class EXPORT_CLASS Operation
    {
    public:
        bool Repeat;
    public:
        long long OperationId;
        long long SleepStamp;
        
        
    public:
        void Sleep(int ms);
        void Cancel();
        
    public:
        virtual void Run() = 0;
        virtual Operation* Duplicate()const = 0;
        
    public:
        Operation();
        virtual ~Operation();
    };
    
    
    typedef void (*StaticOperator) (Operation* op, void* param);
    class StaticOperation : public Operation
    {
    private:
        StaticOperator _operator;
        void* _param;
        
    public:
        StaticOperation(StaticOperator op, void* param = NULL, bool repeat = true)
        : _operator(op),_param(NULL)
        {
            Repeat = repeat;
            _param = param;
        }
        
        StaticOperation(const StaticOperation* op)
        {
            *this = *op;
        }
        
    public:
        virtual void Run();
        virtual Operation* Duplicate()const;
    };
    
    class ObjectOperation;
    
	class EXPORT_CLASS OperationTargetBase
    {
    public:
        OperationTargetBase();
        virtual ~OperationTargetBase();
        
    public:
        void Sleep(int ms);
        void Cancel(bool destroyThis);
        
        
    public:
        virtual void DoOperation(ObjectOperation* op, void* param);
        
    private:
        bool _running;
        ObjectOperation* _operation;
        friend class ObjectOperation;
    };
    
    typedef void (OperationTargetBase::*ObjectOperator) (ObjectOperation* op, void* param);
	class EXPORT_CLASS ObjectOperation : public Operation
    {
        
    public:
        ObjectOperation(OperationTargetBase* target, ObjectOperator op, void* param = NULL, bool repeat = true);
        
        ObjectOperation(const ObjectOperation* op);
        
        ~ObjectOperation();
        
    public:
        void Cancel(bool destroyTarget);
        void ClearTarget();
        
    public:
        virtual void Run();
        virtual Operation* Duplicate()const;
        
    private:
        OperationTargetBase* _target;
        ObjectOperator _operator;
        bool _destroyTarget;
        void* _param;
    };
    
}

#endif /* IOperation_h */
