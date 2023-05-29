//
//  Copyright © 2022-2023 MSDK team. All rights reserved.
//

#ifndef MSDK_OBSERVER_MANAGER_H
#define MSDK_OBSERVER_MANAGER_H

#include "MSDKMacros.h"
#include "MSDKMutex.h"

NS_MSDK_BEGIN

        class IObserver {
        public:
            virtual void Change(const std::string &tag) = 0;
        };

        class MSDKObserverManager {
        public:
            void AddObserver(IObserver *observer);

            void RemoveObserver(IObserver *observer);

            void Update(const std::string &tag);
        private:
            static std::set<IObserver *> mObserverQueue;
            MSDKMutex m_observerMutex;
        };

NS_MSDK_END

#endif //MSDK_OBSERVER_MANAGER_H
