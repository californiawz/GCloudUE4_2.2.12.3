/*
 * File_Jni.h
 *
 *  Created on: 2011-9-15
 *      Author: vforkkcai
 */

#ifndef __XFILE_H
#define __XFILE_H
#include "ABasePal.h"
#include "AString.h"

namespace ABase
{
	enum FileMode
	{
		modeCreate, modeAppend, modeRead, modeReadWrite, modeWrite, 
	};

	enum FilePosition
	{
		posBegin, posCurrent, posEnd,
	};

	class EXPORT_CLASS CFile
	{
	public:
		CFile();
		virtual ~CFile();

    public:
        static bool Remove(const char* file);
        static bool Exist(const char* file);
        static bool IsDir(const char* file);
        static bool Rename(const char* oldFilename, const char* newFileName);

	public:
		// construction
		bool Open(const char* file, FileMode mode);
		void Close();
		bool Exist();

	public:
		// Input/Output
		int Read(void* buffer, a_uint32 count);
        int Read(void* buffer, int index, a_uint32 count);
		bool Write(const void* buffer, a_uint32 count);
        bool Append(const void* buffer, a_uint32 count);
//        bool Clear();
		bool Remove();

	public:
		// Position
		a_uint32 GetLength();
		a_uint64 Seek(a_uint64 loff, FilePosition pos);
		void SeekToBegin();
		void SeekToEnd();

	private:
		FILE* m_pFile;
		AString _filePath;
	};
}
#endif /* FILE_JNI_H_ */
