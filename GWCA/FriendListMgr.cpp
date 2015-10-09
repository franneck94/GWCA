#include "FriendListMgr.h"
#include "PatternScanner.h"

GWAPI::FriendListMgr::FriendListMgr(GWAPIMgr* parent) : parent_(parent)
{
	FindList();
}

void GWAPI::FriendListMgr::FindList()
{
	/*
	  All function that directly use the adresse of friend list are really small or make no sense to scan.
	  So we scan a function that call one of this function then follow by transforming rel adr to abs adr.
	*/

	PatternScanner scanner(0x401000, 0x4FF000);
	DWORD call = scanner.FindPattern("\x85\xC0\x74\x19\x6A\xFF\x8D\x50\x08\x8D\x4E\x08", "xxxxxxxxxxxx", -0x18);
	call = *(DWORD*)call + (call + 5 - 1) + 2;
	fList_ = &(*(GWAPI::GW::FriendList*)*(DWORD*)call);
}
