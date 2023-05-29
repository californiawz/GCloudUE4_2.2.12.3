//
//  AValue.hpp
//  AValue
//
//  Created by vforkk on 11/28/16.
//  Copyright © 2016 vforkk. All rights reserved.
//

#ifndef AValue_hpp
#define AValue_hpp
#include "ABasePal.h"
#include "AString.h"

#define ENABLE_DEBUG 0

#if ENABLE_DEBUG
#include <map>
#endif

namespace ABase {
    
    typedef unsigned int ArrayIndex;
        
    enum ValueType
    {
        NullValue = 0, ///< 'null' value
        IntValue,      ///< signed integer value
        UIntValue,     ///< unsigned integer value
        RealValue,     ///< double value
        StringValue,   ///< UTF-8 string value
        BooleanValue,  ///< bool value
        ArrayValue,    ///< array value (ordered list)
        ObjectValue    ///< object value (collection of name/value pairs).
    };
    
    class ValueIteratorBase;
    class ValueIterator;
    class ValueConstIterator;
    
	class EXPORT_CLASS Value
    {
    public:
        typedef ValueIterator iterator;
        typedef ValueConstIterator const_iterator;
        
    public:
        Value( ValueType value = NullValue);
        Value( int value );
        Value( uint32_t value );
        Value( int64_t value );
        Value( uint64_t value );
        Value( double value );
        Value( const char *value );
        Value( bool value );
        Value( const Value &other );
        ~Value();
        
    public:
        int asInt32() const;
        uint32_t asUInt32() const;
        int64_t asInt64() const;
        uint64_t asUInt64() const;
        bool asBool() const;
        float asFloat() const;
        float asDouble() const;
        AString asString() const;
        const char* asCString() const;
        
    public:
        bool isNull() const;
        bool isBool() const;
        bool isInt() const;
        bool isUInt() const;
        bool isIntegral() const;
        bool isDouble() const;
        bool isNumeric() const;
        bool isString() const;
        bool isArray() const;
        bool isObject() const;
        
    public:
        Value& operator[](int i);
        const Value& operator[](int i)const;
        
        Value& operator[](const char*);
        const Value& operator[](const char* key)const;
        
        int Size()const;
        
    public:
        Value &operator=( const Value &other );
        /// Swap values.
        /// \note Currently, comments are intentionally not swapped, for
        /// both logic and efficiency.
        void swap( Value &other );
        
        ValueType type() const;
        
        bool operator <( const Value &other ) const;
        bool operator <=( const Value &other ) const;
        bool operator >=( const Value &other ) const;
        bool operator >( const Value &other ) const;
        
        bool operator ==( const Value &other ) const;
        bool operator !=( const Value &other ) const;
        
    public:
        ValueConstIterator begin() const;
        ValueConstIterator end() const;
        
        iterator begin();
        iterator end();
        
    public:
        static Value Null;
        
    private:
        union ValueHolder
        {
            uint64_t _uint;
            double _real;
            bool _bool;
            char* _string;
#if ENABLE_DEBUG
            std::map<ValueString, Value>* _map;
#else
            void* _map;
#endif
        } _value;
        ValueType _type;
    };
    
    class ValueWrapper;
    class ValueIteratorBase
    {
    public:
        friend class ValueWrapper;
        typedef unsigned int size_t;
        typedef int difference_type;
        typedef ValueIteratorBase SelfType;
        
        ValueIteratorBase();
        virtual ~ValueIteratorBase();
        
        virtual bool operator ==( const SelfType &other ) const
        {
            if (_impl && other._impl) {
                return *_impl == *other._impl;
            }
            return _impl == other._impl;
        }
        
        virtual bool operator !=( const SelfType &other ) const
        {
            if (_impl && other._impl) {
                return *_impl != *other._impl;
            }
            return _impl != other._impl;
        }
        
        virtual difference_type operator -( const SelfType &other ) const
        {
            if (_impl && other._impl) {
                return *_impl - *other._impl;
            }
            // Todo:
            assert(0);
            return 0;
        }
        
        virtual SelfType &operator--()
        {
            assert(0);
            return *this;
        }
        
        virtual SelfType &operator++()
        {
            assert(0);
            return *this;
        }
        
        virtual const Value& operator *() const
        {
            assert(0);
            return Value::Null;
        }
        
        /// Return either the index or the member name of the referenced value as a Value.
        virtual Value key() const
        {
            if (_impl) {
                return _impl->key();
            }
            return Value::Null;
        }
        
        /// Return the index of the referenced Value. -1 if it is not an arrayValue.
        virtual uint32_t index() const
        {
            if (_impl) {
                return _impl->index();
            }
            return 0;
        }
        
        /// Return the member name of the referenced Value. "" if it is not an objectValue.
        virtual const char *memberName() const
        {
            if (_impl) {
                return _impl->memberName();
            }
            return 0;
        }
        
    public:
        virtual ValueIteratorBase* duplicate()const = 0;
        
    protected:
        ValueIteratorBase* _impl;
    };
    
    /** \brief const iterator for object and array value.
     *
     */
    class ValueConstIterator : public ValueIteratorBase
    {
    public:
        typedef ValueConstIterator SelfType;
        
        ValueConstIterator();
        
        
        ValueConstIterator(const ValueConstIterator& other)
        {
            _impl = 0;
            *this =  (const ValueIteratorBase &)other;
        }
        
        ~ValueConstIterator()
        {
        }
        
    public:
        
        ValueConstIterator &operator =( const ValueIteratorBase &other );
        
        virtual ValueConstIterator operator++( int )
        {
            ValueConstIterator temp( *this );
            if (_impl) {
                ++*_impl;
            }
            return temp;
        }
        
        virtual SelfType operator--( int )
        {
            SelfType temp( *this );
            if (_impl) {
                --*_impl;
            }
            return temp;
        }
        
        virtual SelfType &operator--()
        {
            if (_impl) {
                --*_impl;
            }
            return *this;
        }
        
        virtual SelfType &operator++()
        {
            if (_impl) {
                ++*_impl;
            }
            return *this;
        }
        
        virtual const Value& operator *() const
        {
            if (_impl) {
                return *(*_impl);
            }
            return Value::Null;
        }

    protected:
        ValueIteratorBase* duplicate()const;
    };
    
    
    /** \brief Iterator for object and array value.
     */
    class ValueIterator : virtual public ValueIteratorBase
    {
    public:
        typedef ValueIterator SelfType;
        ValueIterator();
        
        ValueIterator(const ValueIterator& other)
        {
            _impl = 0;
            *this = (const ValueIteratorBase &)other;
        }
        
        ~ValueIterator()
        {
            
        }
        
    public:
        
        virtual ValueIterator &operator =( const ValueIteratorBase &other );
        
        virtual ValueIterator operator++( int )
        {
            SelfType temp( *this );
            ++*this;
            return temp;
        }
        
        virtual ValueIterator operator--( int )
        {
            SelfType temp( *this );
            --*this;
            return temp;
        }
        
        virtual ValueIterator &operator--()
        {
            if (_impl) {
                --*_impl;
            }
            return *this;
        }
        
        virtual ValueIterator &operator++()
        {
            if (_impl) {
                ++*_impl;
            }
            return *this;
        }
        
        const Value& operator *() const
        {
            if (_impl) {
                return *(*_impl);
            }
            return Value::Null;
        }
        
    protected:
        ValueIteratorBase* duplicate()const;
    };
        
}

#endif /* AValue_hpp */
