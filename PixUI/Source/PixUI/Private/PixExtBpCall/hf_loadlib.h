/**************************************************

**** @file:     hf_loadlib.h

**** @brief:    

**** @author:   tianzelei

**** @date:     2020/05/28

**** @group:    PixUI

**** @copyright: Copyright 2020 PixUI. All Rights Reserved.

***************************************************/

#pragma once

//PixUI lib header file version
#define DF_PXLIB_LOADLIB_VERSION "0.1.3"

#include <string.h>
#include <cassert>

#if (defined(_DEBUG) && _DEBUG) || (defined(DEBUG) && DEBUG)
#define PX_DEBUG 1
#else
#define PX_DEBUG 0
#endif //(defined(_DEBUG) && _DEBUG) || (defined(DEBUG) && DEBUG)

namespace pixui
{
	typedef long long		PxLong;
	typedef unsigned char	PxByte;
	struct PxArray
	{
		PxArray()
			:p_Buffer_(nullptr), un_len_(0)
		{

		}
		PxArray(int val)
			:PxArray()
		{

		}
		PxArray(void* val)
			:PxArray()
		{

		}
		PxArray(unsigned char* pBuff, unsigned int len)
			: PxArray()
		{
			Set(pBuff, len);
		}
		PxArray(void* pBuff, unsigned int len)
			: PxArray((unsigned char*)pBuff,len)
		{

		}
		PxArray(const PxArray& ary)
			: PxArray(ary.Buffer(), ary.Len())
		{

		}
		~PxArray()
		{
			Free();
		}
		PxArray& operator=(const PxArray& ary)
		{
			Set(ary.Buffer(), ary.Len());
			return *this;
		}
		void Free()
		{
			if (p_Buffer_ && Len()>0)
			{
				delete[]p_Buffer_;
			}
			p_Buffer_ = nullptr;
			un_len_ = 0;
		}
		void Set(unsigned char* p_buffer, unsigned int un_len)
		{
			Free();
			if (un_len > 0 && p_buffer)
			{
				un_len_ = un_len;
				p_Buffer_ = new unsigned char[un_len_];
				memcpy(p_Buffer_, p_buffer, un_len_);
			}
		}
		void Set(void* p_buffer, unsigned int un_len)
		{
			Set((unsigned char*)p_buffer, un_len);
		}
		unsigned char* Buffer() const
		{
			return p_Buffer_;
		}
		unsigned int Len() const
		{
			return un_len_;
		}
		unsigned char At(unsigned int un_index)
		{
			if (un_index < Len())
			{
				return p_Buffer_[un_index];
			}
			return 0;
		}

		unsigned char*	p_Buffer_;
		unsigned int	un_len_;
	};

	typedef unsigned int*	PxLibContextPtr;

	enum EPxLibValueType
	{
		em_pxlib_value_void,
		em_pxlib_value_bool,
		em_pxlib_value_byte,
		em_pxlib_value_char,
		em_pxlib_value_short,
		em_pxlib_value_int,
		em_pxlib_value_float,
		em_pxlib_value_long,
		em_pxlib_value_double,
		em_pxlib_value_string,
		em_pxlib_value_array,
		em_pxlib_value_context,
		em_pxlib_value_args,	//

		em_param_count
	};

	struct PxLibParams;

	static void* NewLibParmasCopy(const void* pParams);
	static void DeleteLibParmas(const void* pParams);

	struct PxLibValue
	{
		PxLibValue()
		{
			e_type_ = em_pxlib_value_void;
			p_buff_ = nullptr;
			l_len_ = 0;
			b_new_arg_buff = false;
		}
		~PxLibValue()
		{
			Free();
		}

		PxLibValue(const PxLibValue &val)
			: PxLibValue()
		{
			e_type_ = val.e_type_;
			{
				if (e_type_ == em_pxlib_value_args)
				{//new by self
					CopyArgs((PxLibParams*)val.Buff());
				}
				else if (e_type_ == em_pxlib_value_context)
				{
					p_buff_ = (char *)val.Buff();
				}
				else
				{
					if (val.Buff() && val.l_len_ > 0)
					{
						l_len_ = val.l_len_;
						p_buff_ = new char[l_len_ + 1];
						p_buff_[l_len_] = 0;
						memcpy(p_buff_, val.Buff(), val.l_len_);
					}
				}
				
			}
		}


		PxLibValue(const EPxLibValueType e_type)
			: PxLibValue()
		{
			Set(e_type, nullptr);
		}

		PxLibValue(const EPxLibValueType e_type, void* p_buff)
			: PxLibValue()
		{
			Set(e_type, p_buff);
		}

#define DF_PXLIB_VALUE_TYPE(type_)  \
	b_new_arg_buff = false;			\
	l_len_ = sizeof(type_);         \
	p_buff_ = new char[l_len_ + 1]; \
	p_buff_[l_len_] = 0;            \
	*((type_ *) p_buff_) = val;

		PxLibValue(const bool val)
		{
			DF_PXLIB_VALUE_TYPE(bool);
			e_type_ = em_pxlib_value_bool;
		}

		PxLibValue(const PxByte val)
		{
			DF_PXLIB_VALUE_TYPE(PxByte);
			e_type_ = em_pxlib_value_byte;
		}

		PxLibValue(const char val)
		{
			DF_PXLIB_VALUE_TYPE(char);
			e_type_ = em_pxlib_value_char;
		}

		PxLibValue(const short val)
		{
			DF_PXLIB_VALUE_TYPE(short);
			e_type_ = em_pxlib_value_short;
		}

		PxLibValue(const int val)
		{
			DF_PXLIB_VALUE_TYPE(int);
			e_type_ = em_pxlib_value_int;
		}

		PxLibValue(const float val)
		{
			DF_PXLIB_VALUE_TYPE(float);
			e_type_ = em_pxlib_value_float;
		}
		PxLibValue(const long val)
		{
			if (sizeof(long) == sizeof(int))
			{
				DF_PXLIB_VALUE_TYPE(int);
				e_type_ = em_pxlib_value_int;
			}
			else
			{
				DF_PXLIB_VALUE_TYPE(PxLong);
				e_type_ = em_pxlib_value_long;
			}
		}
		PxLibValue(const PxLong val)
		{
			DF_PXLIB_VALUE_TYPE(PxLong);
			e_type_ = em_pxlib_value_long;
		}

		PxLibValue(const double val)
		{
			DF_PXLIB_VALUE_TYPE(double);
			e_type_ = em_pxlib_value_double;
		}
		PxLibValue(char *val)
			: PxLibValue()
		{
			if (val)
			{
				l_len_ = strlen(val);
				if (l_len_ > 0)
				{
					p_buff_ = new char[l_len_ + 1];
					p_buff_[l_len_] = 0;
					memcpy(p_buff_, val, l_len_);
				}
			}
			e_type_ = em_pxlib_value_string;
		}
		PxLibValue(const char *val)
			: PxLibValue()
		{
			if (val)
			{
				l_len_ = strlen(val);
				if (l_len_ > 0)
				{
					p_buff_ = new char[l_len_ + 1];
					p_buff_[l_len_] = 0;
					memcpy(p_buff_, val, l_len_);
				}
			}
			e_type_ = em_pxlib_value_string;
		}
		PxLibValue(PxArray& ary)
			: PxLibValue()
		{
			l_len_ = ary.Len();
			if (l_len_ > 0)
			{
				p_buff_ = new char[l_len_];
				memcpy(p_buff_, ary.Buffer(), l_len_);
			}
			e_type_ = em_pxlib_value_array;
		}
		PxLibValue(const PxArray& ary)
			: PxLibValue()
		{
			l_len_ = ary.Len();
			if (l_len_ > 0)
			{
				p_buff_ = new char[l_len_];
				memcpy(p_buff_, ary.Buffer(), l_len_);
			}
			e_type_ = em_pxlib_value_array;
		}
		PxLibValue(const PxLibContextPtr ctx)
			: PxLibValue()
		{
			p_buff_ = (char *)ctx;
			e_type_ = em_pxlib_value_context;
		}
		PxLibValue(PxLibParams *args)
			: PxLibValue()
		{
			CopyArgs(args);
		}
		PxLibValue(const PxLibParams *args)
			: PxLibValue()
		{
			CopyArgs(args);
		}

		static void TryToValue(PxLibValue &dst, PxLibValue &src)
		{
			if (dst.Type() == src.Type())
			{
				dst = src;
			}
			else
			{
				double d_val = 0.0f;
				switch (src.Type())
				{
				case em_pxlib_value_bool:
					d_val = static_cast<double>(src.GetVal<bool>());
					break;
				case em_pxlib_value_char:
					d_val = static_cast<double>(src.GetVal<char>());
					break;
				case em_pxlib_value_byte:
					d_val = static_cast<double>(src.GetVal<PxByte>());
					break;
				case em_pxlib_value_int:
					d_val = static_cast<double>(src.GetVal<int>());
					break;
				case em_pxlib_value_float:
					d_val = static_cast<double>(src.GetVal<float>());
					break;
				case em_pxlib_value_long:
					d_val = static_cast<double>(src.GetVal<PxLong>());
					break;
				case em_pxlib_value_double:
					d_val = static_cast<double>(src.GetVal<double>());
					break;
				default:
					break;
				}

				switch (dst.Type())
				{
				case em_pxlib_value_bool:
					dst.Set(d_val > 0);
					break;
				case em_pxlib_value_byte:
					dst.Set(static_cast<PxByte>(d_val));
					break;
				case em_pxlib_value_char:
					dst.Set(static_cast<char>(d_val));
					break;
				case em_pxlib_value_short:
					dst.Set(static_cast<short>(d_val));
					break;
				case em_pxlib_value_float:
					dst.Set(static_cast<float>(d_val));
					break;
				case em_pxlib_value_int:
					dst.Set(static_cast<int>(d_val));
					break;
				case em_pxlib_value_long:
					dst.Set(static_cast<PxLong>(d_val));
					break;
				case em_pxlib_value_double:
					dst.Set(d_val);
					break;
				default:
					break;
				}
			}
		}

		void CopyArgs(const PxLibParams* pSrcParms)
		{
			if (pSrcParms)
			{
				l_len_ = 0;
				e_type_ = em_pxlib_value_args;
				b_new_arg_buff = true;
				p_buff_ = (char*)NewLibParmasCopy(pSrcParms);
			}
		}

		PxLibValue &operator=(const PxLibValue &val)
		{
			Free();
			e_type_ = val.e_type_;
			{
				if (e_type_ == em_pxlib_value_args)
				{//new by self
					CopyArgs((PxLibParams*)val.Buff());
				}
				else if (e_type_ == em_pxlib_value_context)
				{
					p_buff_ = (char*)val.Buff();
				}
				else
				{
					if (val.Buff() && val.l_len_ > 0)
					{
						l_len_ = val.l_len_;
						p_buff_ = new char[l_len_ + 1];
						p_buff_[l_len_] = 0;
						memcpy(p_buff_, val.Buff(), val.l_len_);
					}
				}

			}
			return *this;
		}
		PxLibValue &operator=(const PxByte val)
		{
			Set(val);
			return *this;
		}
        PxLibValue &operator=(const char val)
        {
            Set(val);
            return *this;
        }
		PxLibValue &operator=(const bool val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const short val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const int val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const float val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const double val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const long val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const PxLong val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(char *val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const char *val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(PxArray& val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const PxArray& val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const PxLibContextPtr val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(PxLibParams *val)
		{
			Set(val);
			return *this;
		}
		PxLibValue &operator=(const PxLibParams *val)
		{
			Set(val);
			return *this;
		}


#define DF_PXLIB_VAL_Get(type_) val = *((type_ *) p_buff_)

#define DF_PXLIB_VAL_TRT_GET( val_ ) PxLibValue dst(val_);	\
		TryToValue(dst, *this);								\
		dst.Get(val_);

		void Get(char &val)
		{
			if (e_type_ == em_pxlib_value_char)
			{
				DF_PXLIB_VAL_Get(char);
			}
			else
			{
				DF_PXLIB_VAL_TRT_GET(val);
			}
		}
		void Get(PxByte &val)
		{
			if (e_type_ == em_pxlib_value_byte)
			{
				DF_PXLIB_VAL_Get(unsigned char);
			}
			else
			{
				DF_PXLIB_VAL_TRT_GET(val);
			}
		}
		void Get(bool &val)
		{
			if (e_type_ == em_pxlib_value_bool)
			{
				DF_PXLIB_VAL_Get(bool);
			}
			else
			{
				DF_PXLIB_VAL_TRT_GET(val);
			}
		}
		void Get(short &val)
		{
			if (e_type_ == em_pxlib_value_short)
			{
				DF_PXLIB_VAL_Get(short);
			}
			else
			{
				DF_PXLIB_VAL_TRT_GET(val);
			}
		}
		void Get(int &val)
		{
			if (e_type_ == em_pxlib_value_int)
			{
				DF_PXLIB_VAL_Get(int);
			}
			else
			{
				DF_PXLIB_VAL_TRT_GET(val);
			}
		}
		void Get(float &val)
		{
			if (e_type_ == em_pxlib_value_float)
			{
				DF_PXLIB_VAL_Get(float);
			}
			else
			{
				DF_PXLIB_VAL_TRT_GET(val);
			}
		}
		void Get(double &val)
		{
			if (e_type_ == em_pxlib_value_double)
			{
				DF_PXLIB_VAL_Get(double);
			}
			else
			{
				DF_PXLIB_VAL_TRT_GET(val);
			}
		}
		void Get(long &val)
		{
			if (sizeof(long) == sizeof(int))
			{
				if (e_type_ == em_pxlib_value_int)
				{
					DF_PXLIB_VAL_Get(int);
				}
				else
				{
					int tmp = 0;
					DF_PXLIB_VAL_TRT_GET(tmp);
					val = tmp;
				}
			}
			else
			{
				if (e_type_ == em_pxlib_value_long)
				{
					DF_PXLIB_VAL_Get(long);
				}
				else
				{
					DF_PXLIB_VAL_TRT_GET(val);
				}
			}
		}
		void Get(PxLong &val)
		{
			if (e_type_ == em_pxlib_value_long)
			{
				DF_PXLIB_VAL_Get(PxLong);
			}
			else
			{
				DF_PXLIB_VAL_TRT_GET(val);
			}
		}
		void Get(char *&val)
		{
			if (e_type_ == em_pxlib_value_string)
			{
				val = p_buff_ ? p_buff_ : GetEmpty();
			}
		}
		void Get(const char *&val)
		{
			if (e_type_ == em_pxlib_value_string)
			{
				val = p_buff_ ? p_buff_ : GetEmpty();
			}
		}
		void Get(PxArray &val)
		{
			if (e_type_ == em_pxlib_value_array)
			{
				val.Set(p_buff_, (unsigned int)l_len_);
			}
		}
		void Get(PxLibContextPtr &val)
		{
			if (e_type_ == em_pxlib_value_context)
			{
				val = (PxLibContextPtr)p_buff_;
			}
		}
		void Get(PxLibParams* &val)
		{
			if (e_type_ == em_pxlib_value_args)
			{
				val = (PxLibParams*)p_buff_;
			}
		}
		void Get(const PxLibParams* &val)
		{
			if (e_type_ == em_pxlib_value_args)
			{
				val = (PxLibParams*)p_buff_;
			}
		}
		void Get(PxLibValue &val)
		{
			val = *this;
		}


		template<typename T>
		T GetVal()
		{
			T val = 0;
			Get(val);
			return val;
		}

		char* GetEmpty()
		{
			static char s_empty[1] = {0};
			return s_empty;
		}

		void Set(const PxLibValue &val)
		{
			Free();
			e_type_ = val.e_type_;
			if (e_type_ == em_pxlib_value_args)
			{
				CopyArgs((PxLibParams*)val.Buff());
			}
			else if (e_type_ == em_pxlib_value_context)
			{
				p_buff_ = (char *)val.Buff();
			}
			else
			{
				if (val.Buff() && val.l_len_ > 0)
				{
					l_len_ = val.l_len_;
					p_buff_ = new char[l_len_ + 1];
					p_buff_[l_len_] = 0;
					memcpy(p_buff_, val.Buff(), val.l_len_);
				}
			}
		}
#define DF_PXLIB_VAL_SET(type_) \
	Free();                     \
	DF_PXLIB_VALUE_TYPE(type_);
		void Set(const char val)
		{
			DF_PXLIB_VAL_SET(char);
			e_type_ = em_pxlib_value_char;
		}
		void Set(const PxByte val)
		{
			DF_PXLIB_VAL_SET(unsigned char);
			e_type_ = em_pxlib_value_byte;
		}
		void Set(const bool val)
		{
			DF_PXLIB_VAL_SET(bool);
			e_type_ = em_pxlib_value_bool;
		}
		void Set(const short val)
		{
			DF_PXLIB_VAL_SET(short);
			e_type_ = em_pxlib_value_short;
		}
		void Set(const int val)
		{
			DF_PXLIB_VAL_SET(int);
			e_type_ = em_pxlib_value_int;
		}
		void Set(const float val)
		{
			DF_PXLIB_VAL_SET(float);
			e_type_ = em_pxlib_value_float;
		}
		void Set(const double val)
		{
			DF_PXLIB_VAL_SET(double);
			e_type_ = em_pxlib_value_double;
		}
		void Set(const long val)
		{
			if (sizeof(long) == sizeof(int))
			{
				DF_PXLIB_VAL_SET(int);
				e_type_ = em_pxlib_value_int;
			}
			else
			{
				DF_PXLIB_VAL_SET(PxLong);
				e_type_ = em_pxlib_value_long;
			}
		}
		void Set(const PxLong val)
		{
			DF_PXLIB_VAL_SET(PxLong);
			e_type_ = em_pxlib_value_long;
		}
		void Set(char *val)
		{
			Free();
			if (val)
			{
				l_len_ = strlen(val);
				if (l_len_ > 0)
				{
					p_buff_ = new char[l_len_ + 1];
					p_buff_[l_len_] = 0;
					memcpy(p_buff_, val, l_len_);
				}
			}
			e_type_ = em_pxlib_value_string;
		}
		void Set(const char *val)
		{
			Free();
			if (val)
			{
				l_len_ = strlen(val);
				if (l_len_ > 0)
				{
					p_buff_ = new char[l_len_ + 1];
					p_buff_[l_len_] = 0;
					memcpy(p_buff_, val, l_len_);
				}
			}
			e_type_ = em_pxlib_value_string;
		}
		void Set(PxArray& val)
		{
			Free();
			l_len_ = val.Len();
			if (l_len_ > 0)
			{
				p_buff_ = new char[l_len_];
				memcpy(p_buff_, val.Buffer(), l_len_);
			}
			e_type_ = em_pxlib_value_array;
		}
		void Set(const PxArray& val)
		{
			Free();
			l_len_ = val.Len();
			if (l_len_ > 0)
			{
				p_buff_ = new char[l_len_];
				memcpy(p_buff_, val.Buffer(), l_len_);
			}
			e_type_ = em_pxlib_value_array;
		}
		void Set(const PxLibContextPtr val)
		{
			Free();
			p_buff_ = (char*)val;
			e_type_ = em_pxlib_value_context;
		}
		void Set(PxLibParams *val)
		{
			Free();
			CopyArgs(val);
		}
		void Set(const PxLibParams *val)
		{
			Free();
			CopyArgs(val);
		}

#define DF_PX_LIB_VALUE_TYPE_SET(type_) \
	l_len_ = sizeof(type_);             \
	p_buff_ = new char[l_len_ + 1];     \
	p_buff_[l_len_] = 0;                \
	memcpy(p_buff_, val, l_len_);
		void Set(EPxLibValueType e_type,const void *val)
		{
			Free();
			e_type_ = e_type;
			if (val)
			{
				switch (e_type_)
				{
				case pixui::em_pxlib_value_bool:
					DF_PX_LIB_VALUE_TYPE_SET(bool);
					break;
				case pixui::em_pxlib_value_byte:
					DF_PX_LIB_VALUE_TYPE_SET(pixui::PxByte);
					break;
				case pixui::em_pxlib_value_char:
					DF_PX_LIB_VALUE_TYPE_SET(char);
					break;
				case pixui::em_pxlib_value_short:
					DF_PX_LIB_VALUE_TYPE_SET(short);
					break;
				case pixui::em_pxlib_value_int:
					DF_PX_LIB_VALUE_TYPE_SET(int);
					break;
				case pixui::em_pxlib_value_float:
					DF_PX_LIB_VALUE_TYPE_SET(float);
					break;
				case pixui::em_pxlib_value_long:
					DF_PX_LIB_VALUE_TYPE_SET(pixui::PxLong);
					break;
				case pixui::em_pxlib_value_double:
					DF_PX_LIB_VALUE_TYPE_SET(double);
					break;
				case pixui::em_pxlib_value_string:
					l_len_ = strlen((char *)val);
					if (l_len_ > 0)
					{
						p_buff_ = new char[l_len_ + 1];
						p_buff_[l_len_] = 0;
						memcpy(p_buff_, val, l_len_);
					}
					break;
				case pixui::em_pxlib_value_array:
					//unknown length
					break;
				case pixui::em_pxlib_value_context:
					p_buff_ = (char*)(val);
					break;
				case  pixui::em_pxlib_value_args:
					CopyArgs((PxLibParams*)val);
					break;
				default:
					break;
				}
			}
		}

		void Free()
		{
			if (e_type_ == em_pxlib_value_args)
			{
				if (b_new_arg_buff)
				{
					DeleteLibParmas((PxLibParams*)p_buff_);
				}
			}
			else
			{
				if (p_buff_ && l_len_ > 0)
				{
					delete p_buff_;
				}
			}
			e_type_ = em_pxlib_value_void;
			p_buff_ = nullptr;
			l_len_ = 0;
			b_new_arg_buff = false;
		}

		void *Buff() const
		{
			return (void *) p_buff_;
		}

		EPxLibValueType Type()
		{
			return e_type_;
		}

		EPxLibValueType e_type_;
		char *p_buff_;
		size_t l_len_;
		bool b_new_arg_buff;
	};

	struct PxLibParams {
		PxLibParams()
		{
			n_count_ = 0;
			n_push_index = 0;
			p_values = nullptr;
		}

		PxLibParams(int n_count)
			: PxLibParams()
		{
			ResetCount(n_count);
		}

		PxLibParams(const PxLibParams &val)
			: PxLibParams()
		{
			n_count_ = val.n_count_;
			if (n_count_ > 0)
			{
				p_values = new PxLibValue[n_count_];

				for (int i = 0; i < n_count_; i++)
				{
					p_values[i] = val.p_values[i];
				}
			}
		}
		~PxLibParams()
		{
			Free();
		}

		PxLibValue* GetValue(int n_index)
		{
			if (p_values && n_index >= 0 && n_index < n_count_)
			{
				return &(p_values[n_index]);
			}
			return nullptr;
		}

		void Free()
		{
			if (p_values)
			{
				delete[] p_values;
			}
			n_push_index = 0;
			n_count_ = 0;
			p_values = nullptr;
		}

		void ResetCount(int n_count)
		{
			Free();
			n_count_ = n_count;
			if (n_count > 0)
			{
				p_values = new PxLibValue[n_count];
			}
		}

		PxLibParams &operator=(const PxLibParams val)
		{
			Free();
			n_count_ = val.n_count_;
			if (n_count_ > 0)
			{
				p_values = new PxLibValue[n_count_];

				for (int i = 0; i < n_count_; i++)
				{
					p_values[i] = val.p_values[i];
				}
			}
			return *this;
		}

		int ParamCount()
		{
			return n_count_;
		}

		EPxLibValueType ParamType(int n_index)
		{
			EPxLibValueType e_type = em_pxlib_value_void;
			if (0 <= n_index && n_index < n_count_)
			{
				e_type = p_values[n_index].Type();
			}
			return e_type;
		}

		void PushReset()
		{
			n_push_index = 0;
		}

		template<typename... ARGS>
		void PushArgs(ARGS... args)
		{
			PushReset();
			ResetCount(sizeof...(ARGS));
			Push(args...);
		}

		template<typename T, typename... Ts>
		void Push(T x, Ts... xs)
		{
#if PX_DEBUG
			assert(0 <= n_push_index && n_push_index < n_count_);
#endif //PX_DEBUG
			if (0 <= n_push_index && n_push_index < n_count_)
			{
				Push(x);
				n_push_index++;
				if (sizeof...(Ts) > 0)
				{
					Push(xs...);
				}
			}
		}

		template<typename T>
		void Push(T x)
		{
			static_assert(sizeof(x) != 0, "Unsupported argument type");
		}

		template<typename T>
		void AutoPush(T x)
		{
#if PX_DEBUG
			assert(0 <= n_push_index && n_push_index < n_count_);
#endif //PX_DEBUG
			if (0 <= n_push_index && n_push_index < n_count_)
			{
				Push(x);
				n_push_index++;
			}
			
		}

		void Push()
		{
			//no argument
		}
		void Push(const char val)
		{
			Set(n_push_index, val);
		}
		void Push(const PxByte val)
		{
			Set(n_push_index, val);
		}
		void Push(const bool val)
		{
			Set(n_push_index, val);
		}
		void Push(const short val)
		{
			Set(n_push_index, val);
		}
		void Push(const int val)
		{
			Set(n_push_index, val);
		}
		void Push(const float val)
		{
			Set(n_push_index, val);
		}
		void Push(const double val)
		{
			Set(n_push_index, val);
		}
		void Push(const long val)
		{
			Set(n_push_index, val);
		}
		void Push(const PxLong val)
		{
			Set(n_push_index, val);
		}
		void Push(char *val)
		{
			Set(n_push_index, val);
		}
		void Push(const char *val)
		{
			Set(n_push_index, val);
		}
		void Push(PxArray& val)
		{
			Set(n_push_index, val);
		}
		void Push(const PxArray& val)
		{
			Set(n_push_index, val);
		}
		void Push(const PxLibContextPtr val)
		{
			Set(n_push_index, val);
		}
		void Push(PxLibParams *val)
		{
			Set(n_push_index, val);
		}
		void Push(const PxLibParams *val)
		{
			Set(n_push_index, val);
		}

#define DF_PXLIB_PARAM_SET(index_, val_)  \
	if (0 <= index_ && index_ < n_count_) \
	{                                     \
		p_values[n_index].Set(val_);      \
	}

		void Set(int n_index, const  char val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const PxByte val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const bool val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const short val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const int val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const float val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const double val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const long val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const PxLong val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const char *val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, char *val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, PxArray& val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const PxArray& val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const PxLibContextPtr val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, PxLibParams *val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}
		void Set(int n_index, const PxLibParams *val)
		{
			DF_PXLIB_PARAM_SET(n_index, val);
		}

#define DF_PXLIB_PARAM_GET(index_, val_)  \
	if (0 <= index_ && index_ < n_count_) \
	{                                     \
		p_values[n_index].Get(val_);      \
	}

		void Get(int n_index, char &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, PxByte &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, bool &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, short &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, int &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, float &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, double &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, long &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, PxLong &val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, char *&val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, const char *&val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, PxArray& val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, PxLibContextPtr& val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, PxLibParams *&val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		void Get(int n_index, const PxLibParams *&val)
		{
			DF_PXLIB_PARAM_GET(n_index, val);
		}
		template<typename T>
		T GetVal(int n_index)
		{
			T val = 0;
			Get(n_index, val);
			return val;
		}
		int n_count_;
		int n_push_index;
		PxLibValue *p_values;
	};


	static void* NewLibParmasCopy(const void* pParams)
	{
		PxLibParams* p_lib_params = (PxLibParams*)pParams;
		if (p_lib_params)
		{
			return new PxLibParams(*p_lib_params);
		}
		return nullptr;
	}
	static void DeleteLibParmas(const void* pParams)
	{
		PxLibParams* p_lib_params = (PxLibParams*)pParams;
		if (p_lib_params)
		{
			delete p_lib_params;
		}
	}

	struct PxLibFunc {
		PxLibFunc(char *name, int n_count)
			: p_name_(nullptr), n_param_count_(n_count)
		{
			param_type_ = nullptr;

			if (name)
			{
				auto len = strlen(name);
				if (len > 0)
				{
					p_name_ = new char[len + 1];
					p_name_[len] = 0;
					memcpy(p_name_, name, len);
				}
			}

			if (n_param_count_ > 0)
			{
				param_type_ = new EPxLibValueType[n_param_count_];
				for (auto i = 0; i < n_param_count_; i++)
				{
					param_type_[i] = em_pxlib_value_void;
				}
			}

			p_next_ = nullptr;
		}

		PxLibFunc(const char *name, int n_count)
			: p_name_(nullptr), n_param_count_(n_count)
		{
			param_type_ = nullptr;

			if (name)
			{
				auto len = strlen(name);
				if (len > 0)
				{
					p_name_ = new char[len + 1];
					p_name_[len] = 0;
					memcpy(p_name_, name, len);
				}
			}

			if (n_param_count_ > 0)
			{
				param_type_ = new EPxLibValueType[n_param_count_];
				for (auto i = 0; i < n_param_count_; i++)
				{
					param_type_[i] = em_pxlib_value_void;
				}
			}

			p_next_ = nullptr;
		}

		PxLibFunc(char *name)
			: PxLibFunc(name, 0)
		{
		}

		PxLibFunc(const char *name)
			: PxLibFunc(name, 0)
		{
		}

		~PxLibFunc()
		{
			if (p_name_)
			{
				delete p_name_;
			}

			if (param_type_)
			{
				delete[] param_type_;
			}

			if (p_next_)
			{
				delete p_next_;
			}
			param_type_ = nullptr;
			n_param_count_ = 0;
			p_name_ = nullptr;
			p_next_ = nullptr;
		}

		char *Name()
		{
			return p_name_;
		}

		int ParamCount()
		{
			return n_param_count_;
		}

		void ResetParamCount(int n_count)
		{
			if (param_type_)
			{
				delete[] param_type_;
				param_type_ = nullptr;
			}
			n_param_count_ = n_count;

			if (n_param_count_ > 0)
			{
				param_type_ = new EPxLibValueType[n_param_count_];
				for (auto i = 0; i < n_param_count_; i++)
				{
					param_type_[i] = em_pxlib_value_void;
				}
			}
		}

		EPxLibValueType ParamType(int n_index)
		{
			if (0 <= n_index && n_index < n_param_count_)
			{
				return param_type_[n_index];
			}
			return em_pxlib_value_void;
		}

		PxLibFunc *Next()
		{
			return p_next_;
		}
		void SetNext(PxLibFunc *p_next)
		{
			p_next_ = p_next;
		}

		template<typename T>
		void SetParams(int n_index, T x)
		{
			if (0 <= n_index && n_index < ParamCount())
			{
				SetParam(n_index, x);
			}
		}

		template<typename... Ts>
		void Push(Ts... xs)
		{
			//Push(x);
			//Push(xs...);
		}

	private:
		void SetParam(int n_index, EPxLibValueType e_type)
		{
			param_type_[n_index] = e_type;
		}

		void SetParam(int n_index,const char val)
		{
			SetParam(n_index, em_pxlib_value_char);
		}
		void SetParam(int n_index, const PxByte val)
		{
			SetParam(n_index, em_pxlib_value_byte);
		}
		void SetParam(int n_index, const bool val)
		{
			SetParam(n_index, em_pxlib_value_bool);
		}
		void SetParam(int n_index, const short val)
		{
			SetParam(n_index, em_pxlib_value_short);
		}
		void SetParam(int n_index, const int val)
		{
			SetParam(n_index, em_pxlib_value_int);
		}
		void SetParam(int n_index, const long val)
		{
			if (sizeof(int) == sizeof(long))
			{
				SetParam(n_index, em_pxlib_value_int);
			}
			else
			{
				SetParam(n_index, em_pxlib_value_long);
			}
		}
		void SetParam(int n_index, const PxLong val)
		{
			SetParam(n_index, em_pxlib_value_long);
		}
		void SetParam(int n_index, const float val)
		{
			SetParam(n_index, em_pxlib_value_float);
		}
		void SetParam(int n_index, const double val)
		{
			SetParam(n_index, em_pxlib_value_double);
		}
		void SetParam(int n_index, const char *val)
		{
			SetParam(n_index, em_pxlib_value_string);
		}
		void SetParam(int n_index, char* val)
		{
			SetParam(n_index, em_pxlib_value_string);
		}
		void SetParam(int n_index, PxArray& val)
		{
			SetParam(n_index, em_pxlib_value_array);
		}
		void SetParam(int n_index, const PxArray& val)
		{
			SetParam(n_index, em_pxlib_value_array);
		}
		void SetParam(int n_index, const PxLibContextPtr val)
		{
			SetParam(n_index, em_pxlib_value_context);
		}
		void SetParam(int n_index, PxLibParams* val)
		{
			SetParam(n_index, em_pxlib_value_args);
		}
		void SetParam(int n_index, const PxLibParams* val)
		{
			SetParam(n_index, em_pxlib_value_args);
		}

		char *p_name_;
		EPxLibValueType *param_type_;
		int n_param_count_;

		PxLibFunc *p_next_;
	};

	struct PxLibInfor;

	typedef PxLibValue *(*PFun_PxLib_Delegate)(unsigned int un_context, PxLibParams &in_param);
	typedef void (*PFun_PxLib_Listener)(unsigned int un_context, const char* psz_event_name, PxLibParams &in_param);
	typedef PxLibInfor *(*PFun_PxLib_Register)();
	typedef PxLibValue *(*PFun_PxLib_OnCallFun)(const char *psz_FunName, PxLibParams &in_param);
	typedef void (*PFun_PxLib_OnSetDelegate)(const char *psz_DelegateName, PFun_PxLib_Delegate FunDelegate, unsigned int un_context);
	typedef void (*PFun_PxLib_OnSetListener)(PFun_PxLib_Listener FunListener, unsigned int un_context);
	typedef void (*PFun_PxLib_UnRegister)();
	typedef const char *(*PFun_PxLib_strvalue)();
	typedef void (*PFun_PxLib_OnScriptInit)(void *state);
	typedef void (*PFun_PxLib_OnScriptDone)(void *state);
	typedef void (*PFun_PxLib_OnTick)();
	typedef void (*PFun_PxLib_OnCtx_GC)(PxLibContextPtr ctx_);

	class PxLibPFunEx
	{
	public:
		PxLibPFunEx() {
			n_size_ = sizeof(PxLibPFunEx);
		}
		virtual ~PxLibPFunEx() {

		}

		int n_size_ = 0;
		int n_keep_ = 0;

		/////////////////add external function information here//////////////////
		virtual void* GetProcess(const char* psz_name) {
			return nullptr;
		}
	};

	struct PxLibSlot {
		PxLibSlot(){
			size = sizeof(PxLibSlot);
			pfOnScriptInit = nullptr;
			pfOnScriptDone = nullptr;
			pfOnTick = nullptr;
		}
		int size;
		PFun_PxLib_OnScriptInit pfOnScriptInit;
		PFun_PxLib_OnScriptDone pfOnScriptDone;
		PFun_PxLib_OnTick pfOnTick;
	};

	struct PxLibInfor {
		PxLibInfor()
		{
			n_v_size_ = sizeof(PxLibInfor);

			un_FunNums_ = 0;
			p_Functions_ = nullptr;

			un_DelegateNums_ = 0;
			p_Delegates_ = nullptr;

			pfun_register_ = nullptr;
			pfun_callfun_ = nullptr;
			pfun_setdelegate_ = nullptr;
			pfun_setListener_ = nullptr;
			pfun_un_register_ = nullptr;

			pfun_hd_version_ = nullptr;
			pfun_tp_version_ = nullptr;
			pfun_version_ = nullptr;
			pfun_complime_timer_ = nullptr;
			pfun_lib_name_ = nullptr;

			slot_ = nullptr;

			pfun_onctx_gc_ = nullptr;

			p_lib_ex_ = nullptr;

			n_keep_size_ = 0;
		}

		~PxLibInfor()
		{
			Free();
		}

		void Free()
		{
			if (p_Functions_)
			{
				delete p_Functions_;
			}

			if (p_Delegates_)
			{
				delete p_Delegates_;
			}

			un_FunNums_ = 0;
			p_Functions_ = nullptr;

			un_DelegateNums_ = 0;
			p_Delegates_ = nullptr;

			pfun_register_ = nullptr;
			pfun_callfun_ = nullptr;
			pfun_setdelegate_ = nullptr;
			pfun_setListener_ = nullptr;
			pfun_un_register_ = nullptr;

			pfun_hd_version_ = nullptr;
			pfun_tp_version_ = nullptr;
			pfun_version_ = nullptr;
			pfun_complime_timer_ = nullptr;
			pfun_lib_name_ = nullptr;

			pfun_onctx_gc_ = nullptr;

			p_lib_ex_ = nullptr;
		}

		int FunNums()
		{
			return un_FunNums_;
		}

		PxLibFunc *PushFun(const char *sz_Name)
		{
			if (GetFunByName(sz_Name))
			{
#if PX_DEBUG
				assert(0);//Same name already exists...
#endif //PX_DEBUG
				return nullptr;
			}

			PxLibFunc *p_Fun = new PxLibFunc(sz_Name);
			return PushFunBack(p_Fun);
		}

		PxLibFunc *GetFunByName(const char *sz_Name)
		{
			PxLibFunc *p_Temp = p_Functions_;
			for (unsigned int i = 0; i < un_FunNums_; i++)
			{
				if (p_Temp && strcmp(p_Temp->Name(), sz_Name) == 0)
				{
					return p_Temp;
				}
				else
				{
					p_Temp = p_Temp->Next();
				}
			}
			return nullptr;
		}

		PxLibFunc *GetFunByIndex(unsigned int n_index)
		{
			if (n_index < un_FunNums_)
			{
				PxLibFunc *p_Temp = p_Functions_;
				for (unsigned int i = 0; i < n_index; i++)
				{
					if (p_Temp)
					{
						p_Temp = p_Temp->Next();
					}
				}
				return p_Temp;
			}
			return nullptr;
		}

		PxLibFunc *PushFunBack(PxLibFunc *p_Fun)
		{
			un_FunNums_++;
			if (p_Functions_ == nullptr)
			{
				p_Functions_ = p_Fun;
			}
			else
			{
				PxLibFunc *p_Tmp = p_Functions_;
				while (p_Tmp->Next())
				{
					p_Tmp = p_Tmp->Next();
				}
				p_Tmp->SetNext(p_Fun);
			}
			return p_Fun;
		}


		//delegate
		int DelegateNums()
		{
			return un_DelegateNums_;
		}

		PxLibFunc *PushDelegate(const char *sz_Name)
		{
			if (GetDelegateByName(sz_Name))
			{
#if PX_DEBUG
				assert(0);//Same name already exists...
#endif //PX_DEBUG
				return nullptr;
			}

			PxLibFunc *p_Fun = new PxLibFunc(sz_Name);
			return PushDelegateBack(p_Fun);
		}

		PxLibFunc *GetDelegateByName(const char *sz_Name)
		{
			PxLibFunc *p_Temp = p_Delegates_;
			for (unsigned int i = 0; i < un_DelegateNums_; i++)
			{
				if (p_Temp && strcmp(p_Temp->Name(), sz_Name) == 0)
				{
					return p_Temp;
				}
				else
				{
					p_Temp = p_Temp->Next();
				}
			}
			return nullptr;
		}

		PxLibFunc *GetDelegateByIndex(unsigned int un_index)
		{
			if (un_index < un_DelegateNums_)
			{
				PxLibFunc *p_Temp = p_Delegates_;
				for (unsigned int i = 0; i < un_index; i++)
				{
					if (p_Temp)
					{
						p_Temp = p_Temp->Next();
					}
				}
				return p_Temp;
			}
			return nullptr;
		}

		PxLibFunc *PushDelegateBack(PxLibFunc *p_Fun)
		{
			un_DelegateNums_++;
			if (p_Delegates_ == nullptr)
			{
				p_Delegates_ = p_Fun;
			}
			else
			{
				PxLibFunc *p_Tmp = p_Delegates_;
				while (p_Tmp->Next())
				{
					p_Tmp = p_Tmp->Next();
				}
				p_Tmp->SetNext(p_Fun);
			}
			return p_Fun;
		}

		int n_v_size_;
		int n_keep_size_;

		unsigned int un_FunNums_;
		unsigned int un_DelegateNums_;

		PxLibFunc *p_Functions_;
		PxLibFunc *p_Delegates_;

		PFun_PxLib_Register pfun_register_;
		PFun_PxLib_OnCallFun pfun_callfun_;
		PFun_PxLib_OnSetDelegate pfun_setdelegate_;
		PFun_PxLib_OnSetListener pfun_setListener_;
		PFun_PxLib_UnRegister pfun_un_register_;

		PFun_PxLib_strvalue pfun_hd_version_;
		PFun_PxLib_strvalue pfun_tp_version_;
		PFun_PxLib_strvalue pfun_version_;
		PFun_PxLib_strvalue pfun_complime_timer_;
		PFun_PxLib_strvalue pfun_lib_name_;

		PxLibSlot *slot_;

		PFun_PxLib_OnCtx_GC pfun_onctx_gc_;

		PxLibPFunEx* p_lib_ex_;
	};
}// namespace pixui
