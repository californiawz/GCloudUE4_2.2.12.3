//
//  ApolloBufferWriter.h
//  ApolloBuffer
//
//  Created by vforkk on 17/9/14.
//  Copyright (c) 2014 TSF4G. All rights reserved.
//

#ifndef __ApolloBuffer__ApolloBufferWriter__
#define __ApolloBuffer__ApolloBufferWriter__

#include "ABasePal.h"
#include "AData.h"
#include "AArray.h"
#include "ADictionary.h"
#include <vector>
#include <map>

namespace ABase {
    
    struct _tagApolloBufferBase;
    
    class EXPORT_CLASS CApolloBufferWriter
    {
    public:
        void Write(a_bool b)
        {
            m_Buffer.append((char*)&b, sizeof(b));
        }
        
        void Write(a_uint8 c)
        {
            m_Buffer.append((char*)&c, sizeof(c));
        }
        
        void Write(a_int8 c)
        {
            m_Buffer.append((char*)&c, sizeof(c));
        }
        
        void Write(a_int16 s)
        {
            s = a_hton16(s);
            m_Buffer.append((char*)&s, sizeof(s));
        }
        
        void Write(a_uint16 s)
        {
            s = a_hton16(s);
            m_Buffer.append((char*)&s, sizeof(s));
        }
        
        void Write(a_int32 i)
        {
            i = a_hton32(i);
            m_Buffer.append((char*)&i, sizeof(i));
        }
        
        void Write(a_uint32 i)
        {
            i = a_hton32(i);
            m_Buffer.append((char*)&i, sizeof(i));
        }
        
        void Write(a_int64 l)
        {
            l = a_hton64(l);
            m_Buffer.append((char*)&l, sizeof(l));
        }
        
        void Write(a_uint64 l)
        {
            l = a_hton64(l);
            m_Buffer.append((char*)&l, sizeof(l));
        }

        void Write(const unsigned char* buffer, int len)
        {
            Write(len);
            m_Buffer.append((char*)buffer, len);
        }
        
        void Write(const char* s)
        {
            int len = (int)strlen(s);
            if (len > 0) {
                Write(len+1);
                m_Buffer.append((char*)s, len+1);
            }
            else
            {
                Write(len);
            }
        }
        
        void Write(const AString& s)
        {
            int len = (int)s.size();
            Write(len);
            if (len > 0) {
                m_Buffer.append(s.data(), len);
            }
        }
        
        void Write(const AArray& v)
        {
            int size = (int)v.Count();
            Write(size);
            
            for (int i = 0; i<v.Count(); i++) {
                Write(v.ObjectAtIndex(i));
            }
        }
        
        void Write(const ADictionary& m)
        {
            int size = m.Count();
            Write(size);
            
            for (int i = 0; i < m.Count(); i++) {
                
                AObject* key = m.KeyAt(i);
                Write(key);
                Write(m.ObjectForKey(key));
            }
        }
        
        /*
        template<typename T, typename Alloc>
        void Write(const std::vector<T, Alloc>& v)
        {
            int size = (int)v.size();
            Write(size);
            
            typedef typename std::vector<T, Alloc>::const_iterator IT;
            for (IT iter = v.begin(); iter != v.end(); iter++) {
                Write(*iter);
            }
        }
        
        
        template<typename K, typename V, typename Alloc>
        void Write(const std::map<K, V, Alloc>& m)
        {
            int size = m.size();
            Write(size);
            
            typedef typename std::map<K, V, Alloc>::const_iterator IT;
            for (IT iter = m.begin(); iter != m.end(); iter++) {
                Write(iter->first);
                Write(iter->second);
            }
        }*/
        
        void Write(const AObject* o);
        void Write(const _tagApolloBufferBase& rStruct);
        void Write(const _tagApolloBufferBase* pStruct);
        void Write(_tagApolloBufferBase& rStruct);
        void Write(_tagApolloBufferBase* pStruct);
        
    public:
        const AString& GetBufferData()
        {
            return m_Buffer;
        }
        
    private:
        AString m_Buffer;
    };
}

#endif /* defined(__ApolloBuffer__ApolloBufferWriter__) */
