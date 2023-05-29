//
//  TDirPublicDefine.h
//  TDirSample
//
//  Created by vforkk on 10/16/15.
//  Copyright © 2015 vforkk. All rights reserved.
//

#ifndef TDirPublicDefine_h
#define TDirPublicDefine_h
#include "ApolloBuffer.h"
#include "GCloudPublicDefine.h"

namespace GCloud {
    
    typedef struct _tagTDirInitInfo : public GCloud::ApolloBufferBase
    {
    public:
        GCloud::AString OpenID; //OpenId of player
        GCloud::AString Url;    //The Url of the Tdir server can pass in multiple domain names/IPs, separated by ",".
        bool EnableManualUpdate;//Whether the callback of the navigation module is driven by the game itself, currently only true
        int MaxIdleTime;        //The maximum idle time is connected, and the timeout is disconnected.
        GCloud::AString IPs;    //[optional] The ips of the Tdir server, separated by ",". instead of url.
        int TDirType;           //[optional] TDir Type: Pebble or UA
        
    public:
        _tagTDirInitInfo()
        {
            EnableManualUpdate = false;
            MaxIdleTime = 3;
            TDirType = 0;   // TDirTypeNone
        }
        
    public:
        virtual AObject* Clone()const
        {
            _tagTDirInitInfo* clone = new _tagTDirInitInfo(*this);
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& write)const
        {
            write.Write(OpenID);
            write.Write(Url);
            write.Write(EnableManualUpdate);
            write.Write(MaxIdleTime);
            write.Write(IPs);
            write.Write(TDirType);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(OpenID);
            reader.Read(Url);
            reader.Read(EnableManualUpdate);
            reader.Read(MaxIdleTime);
            reader.Read(IPs);
            reader.Read(TDirType);
        }
        
    }TDirInitInfo;
    
    enum TreeNodeType
    {
        TnTypeCategory,
        TnTypeLeaf,
    };
    
    enum TreeNodeFlag
    {
        TnFLagHeavy = 0x10,
        TnFlagCrown = 0x20,
        TnFlagFine = 0x40,
        TnFlagUnavailable = 0x80,
    };
    
    enum TreeNodeTag
    {
        TnTagHot = 0x01,
        TnTagRecommend = 0x02,
        TnTagNew = 0x04,
        TnTagLimited = 0x08,
        TnTagExperience = 0x10,
    };
    
    enum TDirConnectionType
    {
        TDirTypeNone    = 0,
        TDirTypePebble  = 1,
        TDirTypeUA      = 2,
    };
    
    struct TDirRoleInfo : public GCloud::ApolloBufferBase
    {
        GCloud::AString OpenId;//OpenId of player
        int32_t TreeId;//Service id
        int32_t LeafId;//Id of leaf node
        int64_t LastLoginTime;//Last login time
        int64_t RoleId;//Id of role
        int32_t RoleLevel;//Level of role
        GCloud::AString RoleName;//Name of role
        GCloud::AString UserData;//Custom data
        
        
    public:
        virtual AObject* Clone()const
        {
            TDirRoleInfo* clone = new TDirRoleInfo();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(OpenId);
            writer.Write(TreeId);
            writer.Write(LeafId);
            writer.Write(LastLoginTime);
            writer.Write(RoleId);
            writer.Write(RoleLevel);
            writer.Write(RoleName);
            writer.Write(UserData);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(OpenId);
            reader.Read(TreeId);
            reader.Read(LeafId);
            reader.Read(LastLoginTime);
            reader.Read(RoleId);
            reader.Read(RoleLevel);
            reader.Read(RoleName);
            reader.Read(UserData);
        }
    };
    
    
    
    struct TDirRoleCollection : public GCloud::ApolloBufferBase
    {
        GCloud::AArray/*TDirRoleInfo**/ RoleInfos;
        
        
    public:
        virtual AObject* Clone()const
        {
            TDirRoleCollection* clone = new TDirRoleCollection();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(RoleInfos);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read<TDirRoleInfo>(RoleInfos);
        }
    };
    
    
    struct TdirCustomData : public GCloud::ApolloBufferBase
    {
        int Attr1;//Corresponding backend custom value 1
        int Attr2;//Corresponding backend custom value 2
        GCloud::AString UserData;//Corresponding backend custom data
        
        TdirCustomData()
        : Attr1(0)
        , Attr2(0)
        {
        }
        
        
    public:
        virtual AObject* Clone()const
        {
            TdirCustomData* clone = new TdirCustomData();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(Attr1);
            writer.Write(Attr2);
            writer.Write(UserData);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(Attr1);
            reader.Read(Attr2);
            reader.Read(UserData);
        }
    };
    
    struct CategoryNode;
    struct LeafNode;
    struct TreeNodeBase: public GCloud::ApolloBufferBase
    {
        int Id;//Id of node
        int ParentId;//Id of parent
        GCloud::AString Name;//Name of node
        int Tag;//Tag of node,such hot and new
        TdirCustomData CustomData;
        
        TreeNodeBase(TreeNodeType t)
        {
            Id = 0;
            ParentId = 0;
            Tag = 0;
            type = t;
        }
        
        virtual ~TreeNodeBase()
        {
        }
        
    public:
        TreeNodeType GetType()const
        {
            return type;
        }
        
        bool IsCategory()const
        {
            return type == TnTypeCategory;
        }
        
        bool IsLeaf()const
        {
            return type == TnTypeLeaf;
        }
        
        bool IsRoot()const
        {
            if (IsCategory()) {
                return ParentId == -1;
            }
            return false;
        }
        
    protected:
        virtual void BeforeEncode(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write((int)type);
            
            writer.Write(Id);
            writer.Write(ParentId);
            writer.Write(Name);
            writer.Write(Tag);
            writer.Write(CustomData);
        }
        
        virtual void BeforeDecode(GCloud::CApolloBufferReader& reader)
        {
            int enumValue = 0;
            reader.Read(enumValue);
            type = (TreeNodeType)enumValue;
            
            reader.Read(Id);
            reader.Read(ParentId);
            reader.Read(Name);
            reader.Read(Tag);
            reader.Read(CustomData);
        }
        
    private:
        TreeNodeType type;
    };
    
    struct CategoryNode : public TreeNodeBase
    {
        CategoryNode()
        : TreeNodeBase(TnTypeCategory)
        {
        }
        
        ~CategoryNode()
        {
        }
        
    public:
        virtual AObject* Clone()const
        {
            CategoryNode* clone = new CategoryNode();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& write)const
        {
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
        }
    };
    
    struct LeafNode : public TreeNodeBase
    {
    public:
        unsigned int Flag;//Flag to show the Congestion
        GCloud::AString Url;//Url of game service
        TDirRoleCollection RoleCollection;//information of role
    public:
        LeafNode()
        : TreeNodeBase(TnTypeLeaf)
        , Flag(0)
        {
        }
        
        ~LeafNode()
        {
        }
        
    public:
        virtual AObject* Clone()const
        {
            LeafNode* clone = new LeafNode();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(Flag);
            writer.Write(Url);
            writer.Write(RoleCollection);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(Flag);
            reader.Read(Url);
            reader.Read(RoleCollection);
        }
    };
    
    struct NodeWrapper : public GCloud::ApolloBufferBase
    {
        TreeNodeType Type;//Type of node
        CategoryNode Category;//Data of non-leaf
        LeafNode Leaf;//Data of leaf
        
    public:
        TreeNodeBase* GetNode()
        {
            if (IsCategory()) {
                return &Category;
            }
            else if (IsLeaf())
            {
                return &Leaf;
            }
            return 0;
        }
        
    public:
        bool IsCategory()const
        {
            return Type == TnTypeCategory;
        }
        
        bool IsLeaf()const
        {
            return Type == TnTypeLeaf;
        }
        
        bool IsRoot()const
        {
            if (IsCategory()) {
                return Category.IsRoot();
            }
            return false;
        }
        
    public:
        virtual AObject* Clone()const
        {
            NodeWrapper* clone = new NodeWrapper();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write((int)Type);
            
            switch (Type) {
                case TnTypeCategory:
                {
                    writer.Write(Category);
                    break;
                }
                case TnTypeLeaf:
                {
                    writer.Write(Leaf);
                    break;
                }
                default:
                    return;
                    break;
            }
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            int tmp = 0;
            reader.Read(tmp);
            Type = (TreeNodeType)tmp;
            switch (Type) {
                case TnTypeCategory:
                {
                    reader.Read(Category);
                }
                    break;
                case TnTypeLeaf:
                {
                    reader.Read(Leaf);
                    break;
                }
                default:
                    return;
                    break;
            }
        }
        
    };
    
    struct TreeInfo : public GCloud::ApolloBufferBase
    {
        GCloud::AArray/* <NodeWrapper*> */ NodeList;
        
    public:
        const int GetTreeId()const
        {
            if (NodeList.Count() > 0) {
                for (int i = 0; i<NodeList.Count(); i++) {
                    NodeWrapper* node = (NodeWrapper*)NodeList.ObjectAtIndex(i);
                    if (node) {
                        if (node->IsRoot()) {
                            TreeNodeBase* nd = node->GetNode();
                            if (nd) {
                                return nd->Id;
                            }
                        }
                    }
                }
            }
            return 0;
        }
    public:
        virtual AObject* Clone()const
        {
            TreeInfo* clone = new TreeInfo();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(NodeList);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read<NodeWrapper>(NodeList);
        }
        
    };
    
    
    struct TreeCollection : public GCloud::ApolloBufferBase
    {
        AArray/* <TreeInfo*> */ TreeList;
        
    public:
        virtual AObject* Clone()const
        {
            TreeCollection* clone = new TreeCollection();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(TreeList);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read<TreeInfo>(TreeList);
        }
        
    };
    
    struct DirAccountInfo: public GCloud::ApolloBufferBase
    {
        GCloud::AString openid;                          // userid
        int32_t tree_id = 0;                          // platform id
        int32_t leaf_id = 0;                          //
        int64_t login_time = 0;                       // last login time
        int64_t role_id = 0;                          // role id
        int32_t role_level = 0;                       // role level
        GCloud::AString role_name;                       // role name
        GCloud::AString user_data;                       // custom string
        
    public:
        virtual AObject* Clone()const
        {
            DirAccountInfo* clone = new DirAccountInfo();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(openid);
            writer.Write(tree_id);
            writer.Write(leaf_id);
            writer.Write(login_time);
            writer.Write(role_id);
            writer.Write(role_level);
            writer.Write(role_name);
            writer.Write(user_data);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read(openid);
            reader.Read(tree_id);
            reader.Read(leaf_id);
            reader.Read(login_time);
            reader.Read(role_id);
            reader.Read(role_level);
            reader.Read(role_name);
            reader.Read(user_data);
        }
    };
    
    struct DirAccountInfoList : public GCloud::ApolloBufferBase
    {
        GCloud::AArray/* <DirAccountInfo*> */ InfoList;
        
    public:
        virtual AObject* Clone()const
        {
            DirAccountInfoList* clone = new DirAccountInfoList();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(InfoList);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read<DirAccountInfo>(InfoList);
        }
        
    };

    struct OpenIdList : public GCloud::ApolloBufferBase
    {
        GCloud::AArray/* <AString*> */ list;
        
    public:
        virtual AObject* Clone()const
        {
            OpenIdList* clone = new OpenIdList();
            *clone = *this;
            return clone;
        }
        
        virtual void WriteTo(GCloud::CApolloBufferWriter& writer)const
        {
            writer.Write(list);
        }
        
        virtual void ReadFrom(GCloud::CApolloBufferReader& reader)
        {
            reader.Read<AString>(list);
        }
        
    };
}

#endif /* TDirPublicDefine_h */
