#ifndef QQ_DEFINITION_H
#define QQ_DEFINITION_H

#include "precompiled.h"

// 8.2
#define CheckVideoMsg_Symbol "?CheckVideoMsg@Msg@Util@@YAXHKKPAUITXMsgPack@@@Z"
// 9.2.3 (26595)
//#define CheckVideoMsg_Symbol "?CheckVideoMsg@Msg@Util@@YAXHKKKPAUITXMsgPack@@@Z"
#define GetMsgAbstract_Symbol "?GetMsgAbstract@Msg@Util@@YA?AVCTXStringW@@PAUITXMsgPack@@@Z"
#define GetMsgTime_Symbol "?GetMsgTime@Msg@Util@@YA_JPAUITXMsgPack@@@Z"
#define GetMsgDumpString_Symbol "?GetMsgDumpString@Msg@Util@@YA?AVCTXStringW@@PAUITXMsgPack@@@Z"
#define GetNickname_Symbol "?GetNickname@Contact@Util@@YA?AVCTXStringW@@K@Z"
#define GetSelfUin_Symbol "?GetSelfUin@Contact@Util@@YAKXZ"

//void __cdecl Util::Msg::CheckVideoMsg(int,unsigned long,unsigned long,struct ITXMsgPack *)
 typedef void (__cdecl* CheckVideoMsg_t)(int, unsigned long, unsigned long, unsigned long *);
//typedef void (__cdecl* CheckVideoMsg_t)(int, unsigned long, unsigned long, unsigned long, unsigned long *);
//__int64 __cdecl Util::Msg::GetMsgTime(struct ITXMsgPack *)
typedef __int64 (__cdecl* GetMsgTime_t)(unsigned long *);
//class CTXStringW __cdecl Util::Msg::GetMsgAbstract(struct ITXMsgPack *)
typedef void (__cdecl* GetMsgAbstract_t)(void *, unsigned long *);
//class CTXStringW __cdecl Util::Contact::GetNickname(unsigned long)
typedef void (__cdecl* GetNickname_t)(void *, unsigned long);

typedef unsigned long (__cdecl* GetSelfUin_t)(void);

// 初始化Hook函数指针
bool InitQQPtr();

extern ULONG_PTR CheckVideoMsgPtr;
//
extern CheckVideoMsg_t CheckVideoMsg;
// 获取消息时间
extern GetMsgTime_t GetMsgTime;
// 获取消息内容
extern GetMsgAbstract_t GetMsgAbstract;
// 通过QQ获取昵称
extern GetNickname_t GetNickname;

extern GetSelfUin_t GetSelfUin;

#endif // QQ_DEFINITION_H
