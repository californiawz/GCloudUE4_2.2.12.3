//
//  ApolloBufferReader.h
//  ApolloBuffer
//
//  Created by vforkk on 17/9/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __GCloud__ApolloBufferReader__
#define __GCloud__ApolloBufferReader__

#include "GCloudPal.h"
#include "AString.h"
#include "AArray.h"
#include "ADictionary.h"
#include <vector>
#include <map>

namespace GCloud {
    
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
        
        CApolloBufferReader(const GCloud::AString& data)
        {
            m_nIndex = 0;
            m_Data = data;
        }
        
        void Reset()
        {
            m_nIndex = 0;
        }
        
    public:
        void Read(bool& b)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            b = m_Data.at(m_nIndex) ? true : false;
            m_nIndex++;
        }
        
        void Read(int8_t& c)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            c = m_Data.at(m_nIndex);
            m_nIndex++;
        }
        
        void Read(uint8_t& c)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            c = m_Data.at(m_nIndex);
            m_nIndex++;
        }
        
        void Read(int16_t& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            int16_t t;
            memcpy(&t, p, sizeof(t));
            v = g_ntoh16(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(uint16_t& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            uint16_t t;
            memcpy(&t, p, sizeof(t));
            v = g_ntoh16(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(int32_t& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            int32_t t;
            memcpy(&t, p, sizeof(t));
            v = g_ntoh32(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(uint32_t& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            uint32_t t;
            memcpy(&t, p, sizeof(t));
            v = g_ntoh32(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(int64_t& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            int64_t t;
            memcpy(&t, p, sizeof(t));
            v = g_ntoh64(t);
            
            m_nIndex += sizeof(v);
        }
        
        void Read(uint64_t& v)
        {
            if (m_nIndex >= m_Data.size()) {
                return;
            }
            const char* p = (m_Data.data() + m_nIndex);
            uint64_t t;
            memcpy(&t, p, sizeof(t));
            v = g_ntoh64(t);
            
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
        
        void Read(GCloud::AString& buffer)
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
        GCloud::AString m_Data;
    };
}

#endif /* defined(__GCloud__ApolloBufferReader__) */
