/*
 * File_Jni.h
 *
 *  Created on: 2011-9-15
 *      Author: vforkkcai
 */

#ifndef _GCLOUD_FILE_H_
#define _GCLOUD_FILE_H_

#include "GCloudPal.h"
#include "AString.h"

namespace GCloud
{
	enum FileMode
	{
		modeCreate, modeAppend, modeRead, modeReadWrite, modeWrite, modeReadWriteDestroyed,
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
        static bool GetFileSize(const char* file, int32_t& fileSize);
        static bool GetFileSize64(const char* file, int64_t& fileSize);
        static bool Exist2(const char* file);
        static bool Remove2(const char* file);
        static FILE* Open2(const char* file, FileMode mode);
        static int FSeek64(FILE* stream, int64_t offset, int origin);

	public:
		// construction
		bool Open(const char* file, FileMode mode);
		void Close();
		bool Exist();

	public:
		// Input/Output
		int Read(void* buffer, uint32_t count);
		int Read(void* buffer, int index, uint32_t count);
		bool Write(const void* buffer, uint32_t count);
		bool Append(const void* buffer, uint32_t count);
		//bool Clear();
		bool Remove();

	public:
		// Position
		uint32_t GetLength();
		uint64_t Seek(uint64_t loff, FilePosition pos);
		void SeekToBegin();
		void SeekToEnd();

	private:
		FILE* m_pFile;
		GCloud::AString _filePath;
	};
}
#endif /* _GCLOUD_FILE_H_ */
