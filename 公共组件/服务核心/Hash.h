/*!
*	模块名:CHash
*  功能:实现哈希表,能添加,删除,查找
*  时间:
*/
//
#ifndef HASH_H
#define HASH_H

#ifndef NULL
#define NULL 0
#endif

#ifndef HASHPOINT
#define HASHPOINT	void*
#endif
#include "ServiceCoreHead.h"
class SERVICE_CORE_CLASS CHash  
{
public:
	int GetCurrentPos();
	void * FindNext(char **sKey);
	unsigned long GetHashArrayNum();
	int GetHashItemNum();
	void *DeleteItem(const char* key);
	void *DeleteItem(const long key);
	void* QueryItem(const char* key);
	void* QueryItem(const long key);
	int InsertItem(const long key, void* hashItemValue);
	int InsertItem(const char* key, void* hashItemValue);
	int InitParam();
	CHash(unsigned long lSlot);
	CHash();

	void FindFirst(int pos = 0);
	void *FindNext();

	virtual ~CHash();
	void Destroy();
//  add by cress
	HASHPOINT GetFirst(int nPos, int &nCurrentPos, int nMaxPos = 0);
	HASHPOINT GetFirst(int nPos);
	void * GetNext(HASHPOINT *hashPoint, int &nCurrentPos, int nMaxPos = 0);
//  end
	
protected:
	class CHashItem
	{
		public:
			CHashItem()
			{
				sKey[0] = '\0';
				lKey = -1;
				pNextItem = NULL;
				pObject = NULL;
			}
			char sKey[100];
			long lKey;
			void *pObject;
			CHashItem *pNextItem;
	};
	
	unsigned long m_nLenth;/*!<哈希表中元素个数*/
	unsigned long m_lSlots;/*!<哈希数组的长度*/
	CHashItem **m_pHash;/*!<指向哈希数组的指针*/
	char m_chrErrorInfo[1024];/*!<错误信息*/
	unsigned long  m_iCurrentPos;
	CHashItem *m_pCurrentHashItem;
	
protected:
	unsigned long HashFun(const char* key,unsigned long &lKey);
	unsigned long HashFun(const long key,unsigned long &lKey);
};
#endif