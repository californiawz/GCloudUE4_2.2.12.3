/*
 * Critical.h
 *
 *  Created on: 2011-7-28
 *      Author: vforkkcai
 */

#ifndef CRITICAL_H_
#define CRITICAL_H_

#include "AMutex.h"

namespace ABase
{
	class EXPORT_CLASS CCritical
	{
	public:
		CCritical(CMutex* pMutex)
		{

			m_pMutex = pMutex;
			if (m_pMutex != NULL)
			{
				m_pMutex->Lock();
			}

		}
		~CCritical()
		{

			if (m_pMutex != NULL)
			{
				m_pMutex->Unlock();
			}

		}


	private:
		CMutex* m_pMutex;

	};
}


#endif /* CRITICAL_H_ */
