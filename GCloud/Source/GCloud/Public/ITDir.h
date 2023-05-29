//
//  ITDir.h
//  TDirSample
//
//  Created by vforkk on 10/16/15.
//  Copyright © 2015 vforkk. All rights reserved.
//
// Tree
//  |
//  -- Category
//         |
//         -- Leaf

#ifndef ITDir_h
#define ITDir_h
#include "TDirPublicDefine.h"

namespace GCloud
{
    
    class EXPORT_CLASS TDirObserver
    {
    public:
        /// <summary>
        /// Callback of QueryAll
        /// </summary>
        virtual void OnQueryAllProc(const Result& result, const TreeCollection* treeList) = 0;
        
        /// <summary>
        /// Callback of QueryTree
        /// </summary>
        virtual void OnQueryTreeProc(const Result& result, const TreeInfo* nodeList) = 0;
        
        /// <summary>
        /// Callback of QueryLeaf
        /// </summary>
        virtual void OnQueryLeafProc(const Result& result, const NodeWrapper* node) = 0;
        
        virtual void OnGetAccountBatch(const Result& result, const DirAccountInfoList* node) = 0;
    };
    class EXPORT_CLASS ITDir
    {
        //
        // Constrution & Instance Functions
        //
    protected:
        ITDir();
        virtual ~ITDir();
    public:
        static ITDir& GetInstance();
        
        virtual void AddObserver(const TDirObserver* observer) = 0;
        virtual void RemoveObserver(const TDirObserver* observer) = 0;
        
        //
        // Main Operations
        //
    public:
        /// <summary>
        /// Initialize tdir
        /// </summary>
        /// <returns>Result of Initialization data</returns>
        /// <param name="initInfo">Information to initialize tdir</param>
        virtual bool Initialize(const TDirInitInfo& initInfo) = 0;
        
        /// <summary>
        /// 拉取全部目录树,已弃用
        /// Queries all trees (Deprecated)
        /// </summary>
        /// <returns>The SeqId of receive data,return -1 means QueryTree failed</returns>
        virtual SeqId QueryAll() = 0;
        
        /// <summary>
        /// 通过treeId拉取目录树
        /// Queries the tree by treeId.
        /// </summary>
        /// <returns>The SeqId of receive data,return -1 means QueryTree failed</returns>
        /// <param name="treeId">TreeId == PlatformId</param>
        virtual SeqId QueryTree(int treeId) = 0;
        
        /// <summary>
        /// 通过treeId和leafId拉取节点信息
        /// Queries the leaf by treeId and leafId.
        /// </summary>
        /// <returns>The SeqId of receive data,return -1 means QueryLeaf failed</returns>
        /// <param name="treeId">TreeId == PlatformId</param>
        /// <param name="leafId">LeafId == ZoneId</param>
        virtual SeqId QueryLeaf(int treeId, int leafId) = 0;
        
        
        virtual SeqId GetAccountBatch(int treeId, GCloud::AArray openid_list) = 0;
    public:
        /// <summary>
        /// GCloudSDK2.0.6之前用于查询当前连接是否正常。只有成功连接上服务器后，才能进行后续的其它操作。
        /// GCloudSDK2.0.6之后已经弃用
        /// GCloudSDK2.0.6 was used to query whether the current connection is normal.
        /// After the successful connection to the server, other subsequent operations can be performed.
        /// Deprecated after GCloudSDK 2.0.6
        /// </summary>
        /// <returns>is Connect</returns>
        virtual bool IsConnected() = 0;
        
        /// <summary>
        /// 是否由游戏自己驱动区服导航模块的回调
        /// Whether the callback of the navigation module is driven by the game itself
        /// </summary>
        virtual void EnableManualUpdate(bool enable = false) = 0;
        
        /// <summary>
        /// 驱动Tdir底层模块进行收发数据
        /// Drive the Tdir underlying module to send and receive data
        /// </summary>
        virtual void UpdateByManual() = 0;
        
        virtual void Close() = 0;
    };
    
// #if defined(_WIN32) || defined(_WIN64)
    // inline ITDir* GetITDirInstance(HMODULE hDll)
    // {
        // typedef ITDir*( *CreateFunction)();
        // CreateFunction pFunc = NULL;
// #pragma warning(push)
// #pragma warning(disable:4191)
        // pFunc = (CreateFunction)GetProcAddress(hDll, "gcloud_tdir_getinstance");	
// #pragma warning(pop)
		// if(pFunc == NULL)
		// {
		    // return NULL;
		// }
        // return pFunc();
    // }
// #endif
    
}

#endif /* ITDir_h */
