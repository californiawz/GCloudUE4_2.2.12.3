//
//  ApolloBufferReader.h
//  ApolloBuffer
//
//  Created by vforkk on 17/9/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __ApolloBuffer__ApolloBufferReader__
#define __ApolloBuffer__ApolloBufferReader__

#include "ABasePal.h"
#include "AString.h"
#include "AArray.h"
#include "ADictionary.h"
#include <vector>
#include <map>

namespace ABase {
    
    struct _tagApolloBufferBase;
    
    class EXPORT_CLASS CApolloBufferReader
    {
    public:
        CApolloBufferReader(const char* pszData, int size)
        {
            m_nIndex = 0;
            if(pszData)
            {
                m_Data.assign(pszData, size);
            }
        }
        
        CApolloBufferReader(const AString& data)
        {
            m_nIndex = 0;
            m_Data = data;
        }
        
        void Reset()
        {
            m_nIndex = 0;
        }
        
    public:
        void Read(a_bool& b)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            b = m_Data.at(m_nIndex) ? true : false;
            m_nIndex++;
        }
        
        void Read(a_int8& c)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            c = m_Data.at(m_nIndex);
            m_nIndex++;
        }
        
        void Read(a_uint8& c)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            c = m_Data.at(m_nIndex);
            m_nIndex++;
        }
        
        void Read(a_int16& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            a_int16 t;
            memcpy(&t, p, sizeof(t));
            v = a_ntoh16(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(a_uint16& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            a_uint16 t;
            memcpy(&t, p, sizeof(t));
            v = a_ntoh16(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(a_int32& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            a_int32 t;
            memcpy(&t, p, sizeof(t));
            v = a_ntoh32(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(a_uint32& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            a_uint32 t;
            memcpy(&t, p, sizeof(t));
            v = a_ntoh32(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(a_int64& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            a_int64 t;
            memcpy(&t, p, sizeof(t));
            v = a_ntoh64(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(a_uint64& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            a_uint64 t;
            memcpy(&t, p, sizeof(t));
            v = a_ntoh64(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(char* buffer, int size)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            if (buffer) {
                memset(buffer, 0, size);
                int len = 0;
                Read(len);
                if (len < size && len > 0) {
                    const char* p = (m_Data.data() + m_nIndex);
                    memcpy(buffer, p, len);
                    m_nIndex += len;
                }
            }
        }
        
        void Read(AString& buffer)
        {
            buffer.clear();
            int len = 0;
            Read(len);
            
            if (m_nIndex >= m_Data.size() || (m_nIndex + len) >m_Data.size()) {
                return;
            }
            
            if(len > 0)
            {
                const char* p = (m_Data.data() + m_nIndex);
                buffer.assign(p, len);
                m_nIndex += len;
            }
        }
        
        
        template<typename T>
        void Read(AArray& v)
        {
            int count = 0;
            Read(count);
            
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            
            v.RemoveAll();
            for (int i = 0; i<count; i++) {
                T t;
                Read(t);
                v.Add(t);
            }
        }
        
        template<typename K, typename V>
        void Read(ADictionary& dict)
        {
            int count = 0;
            Read(count);
            
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            
            dict.RemoveAll();
            for (int i = 0; i<count; i++) {
                K k;
                V v;
                Read(k);
                Read(v);
                dict.Set(k, v);
            }
        }
        /*
        template<typename T, typename Alloc>
        void Read(std::vector<T, Alloc>& v)
        {
            int count = 0;
            Read(count);
            
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            
            v.clear();
            for (int i = 0; i<count; i++) {
                T t;
                Read(t);
                v.push_back(t);
            }
        }
        
        template<typename K, typename V, typename Alloc>
        void Read(std::map<K, V, Alloc>& v)
        {
            int count = 0;
            Read(count);
            
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            
            v.clear();
            for (int i = 0; i<count; i++) {
                std::pair<K, V> pair;
                
                Read(pair.first);
                Read(pair.second);
                
                v.insert(pair);
            }
        }*/
        
        void Read(_tagApolloBufferBase& rStruct);
        void Read(_tagApolloBufferBase* pStruct);
        
    private:
        int m_nIndex;
        AString m_Data;
    };
}

#endif /* defined(__ApolloBuffer__ApolloBufferReader__) */
