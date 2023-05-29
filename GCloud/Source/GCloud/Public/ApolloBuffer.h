//
//  CApolloBuffer.h
//  ApolloBuffer
//
//  Created by vforkk on 17/9/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __GCloud__CApolloBuffer__
#define __GCloud__CApolloBuffer__
#include "AString.h"
#include "AArray.h"
#include "ApolloBufferReader.h"
#include "ApolloBufferWriter.h"

namespace GCloud {
        
    typedef struct EXPORT_CLASS _tagApolloBufferBase : public AObject
    {
    protected:
        _tagApolloBufferBase(){}
        virtual ~_tagApolloBufferBase(){}
        
    public:
        
        bool Encode(GCloud::AString& rBuffer)const
        {
            return encode(rBuffer);
        }
        
        int Encode(char *data,int &len) const
        {
            return encode(data,len);
        }

        bool Decode(const char* data, int len)
        {
            return decode(data, len);
        }
        
        bool Decode(const GCloud::AString& data)
        {
            return decode(data);
        }
        
        //_tagApolloBufferBase* operator = (const _tagApolloBufferBase& from);
        
        //_tagApolloBufferBase* operator = (const _tagApolloBufferBase* from);
        
    protected:
        
        virtual bool encode(GCloud::AString& rBuffer)const
        {
            CApolloBufferWriter writer;
            BeforeEncode(writer);
            this->WriteTo(writer);
            
            rBuffer = writer.GetBufferData();
            return true;
        }
        
        virtual bool encode(char *data,int &len) const
        {
            if (!data) {
                return false;
            }
            CApolloBufferWriter writer;
            BeforeEncode(writer);
            this->WriteTo(writer);
            
            GCloud::AString buf = writer.GetBufferData();
            if (buf.size() >= len)
            {
                return false;
            }
            memcpy(data, buf.data(), buf.size());
            len = (int)buf.size();
            return true;
        }
        
        virtual bool decode(const char* data, int len)
        {
            if (data) {
                CApolloBufferReader reader(data, len);
                this->BeforeDecode(reader);
                
                this->ReadFrom(reader);
                return true;
            }
            return false;
        }
        
        virtual bool decode(const GCloud::AString& data)
        {
            CApolloBufferReader reader(data);
            this->BeforeDecode(reader);
            this->ReadFrom(reader);
            return true;
        }
        
    public:
        virtual AObject* Clone()const = 0;
        virtual void WriteTo(CApolloBufferWriter& writer)const = 0;
        virtual void ReadFrom(CApolloBufferReader& reader) = 0;
        
    public:
        virtual void BeforeEncode(CApolloBufferWriter& writer)const{}
        virtual void BeforeDecode(CApolloBufferReader& reader){}
        
    }ApolloBufferBase;
    
    
    typedef struct _tagApolloBufferBuffer : public ApolloBufferBase
    {
        
    public:
        _tagApolloBufferBuffer()
        {
            m_pBuffer = NULL;
            m_nBufferLen = 0;
        }
        
        ~_tagApolloBufferBuffer();
        
        _tagApolloBufferBuffer(const GCloud::AString& data)
        {
            decode(data);
        }
        
        _tagApolloBufferBuffer(const char* pbuf, int len)
        {
            decode(pbuf, len);
        }
        
    public:
        int GetBufferLen() const
        {
            return m_nBufferLen;
        }
        
        const char* GetBuffer()const
        {
            return m_pBuffer;
        }
        
    protected:
        
        virtual bool encode(GCloud::AString& rBuffer)const
        {
            //GCloudLogInfo("_tagApolloBufferBuffer encode:%p, len:%d", m_pBuffer, m_nBufferLen);
            if (m_pBuffer && m_nBufferLen > 0) {
                rBuffer.assign(m_pBuffer, m_nBufferLen);
                return true;
            }
            return false;
        }
        
        virtual bool encode(char *data,int &len) const
        {
            if (!data) {
                return false;
            }
            
            if (m_nBufferLen >= len)
            {
                return false;
            }
            if (m_pBuffer)
            {
                memcpy(data, m_pBuffer, m_nBufferLen);
                len = m_nBufferLen;
            }
            else
            {
                len  = 0;
            }
            return true;
        }
        
        virtual bool decode(const char* data, int len);
        
        virtual bool decode(const GCloud::AString& data);
        
    private:
        virtual AObject* Clone()const;
        
        virtual void WriteTo(CApolloBufferWriter& writer)const
        {
            
        }
        
        virtual void ReadFrom(CApolloBufferReader& reader)
        {
            
        }
        
    private:
        char* m_pBuffer;
        int m_nBufferLen;
        
    }ApolloBufferBuffer;
    
    //bool ConvertFromApolloBuffer(const ApolloBufferBase* from, ApolloBufferBase* to);
    bool Convert(const ApolloBufferBase* from, ApolloBufferBase* to);
    
    
    typedef struct _tagApolloActionBufferBase : public ApolloBufferBase
    {
    private:
        int Action;
        
    public:
        _tagApolloActionBufferBase()
        : Action(0)
        {
            
        }
        
    protected:
        _tagApolloActionBufferBase(int act)
        : Action(act)
        {
        }
        virtual ~_tagApolloActionBufferBase(){}
        
    public:
        int GetAction()
        {
            return Action;
        }
        
    protected:
        virtual void BeforeEncode(CApolloBufferWriter& writer)const
        {
            writer.Write(Action);
        }
        
        virtual void BeforeDecode(CApolloBufferReader& reader)
        {
            reader.Read(Action);
        }
        
    }ApolloActionBufferBase;
    
    typedef struct _tagApolloAction : public ApolloActionBufferBase
    {
        
    public:
        _tagApolloAction()
        :ApolloActionBufferBase(0)
        {
            
        }
        
    protected:
        virtual AObject* Clone()const;
        
        virtual void WriteTo(CApolloBufferWriter& writer)const
        {
            
        }
        
        virtual void ReadFrom(CApolloBufferReader& reader)
        {
            
        }
        
    }ApolloAction;
    
}


#endif /* defined(__GCloud__CApolloBuffer__) */
