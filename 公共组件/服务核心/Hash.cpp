// Hash.cpp: implementation of the CHash class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "hash.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHash::CHash()
{
	m_lSlots = 100;
	m_pHash = 0;

}

CHash::~CHash()
{
	Destroy();

}
/*!构造函数
 *
 *lSlot：表示哈希数组的长度
*/
CHash::CHash(unsigned long lSlot)
{
	if(lSlot <100)
		m_lSlots = 100;
	else
		m_lSlots = lSlot;
	//
	m_pHash = 0;

	m_iCurrentPos = 0;
	m_pCurrentHashItem = NULL;

}
/*!初始化参数
 *返回值:1:初始化成功；0：初始化失败
 *
*/
int CHash::InitParam()
{
	int nResult = 0;
	//安全性检查
	if(m_pHash)
		Destroy();
	//
	try
	{
		m_nLenth = 0;
		m_pHash = new CHashItem *[m_lSlots];
		for(unsigned long i=0;i<m_lSlots;i++)
			m_pHash[i] = NULL;
		//
		nResult = 1;
	}
	catch (...)
	{
		strcpy(m_chrErrorInfo,"分配内存失败!");
		nResult = 0;
		
	}
	//
	return nResult;
}
/*!清空哈希表
 *
 *
*/
void CHash::Destroy()
{
	if(m_pHash)
	{
		CHashItem* pHashItem, *pTempItem;
		for(unsigned long i=0;i<m_lSlots;i++)
		{
			pHashItem = m_pHash[i];
			while(pHashItem)
			{
				pTempItem = pHashItem;
				pHashItem = pTempItem->pNextItem;
				delete pTempItem;
			}
		}
		//
		delete [] m_pHash;
		m_pHash = 0;
	}

}
/*!哈希函数
 *key:表示用来做关键字的字符
 *lKey:返回的关键字值
 *返回值:该关键字所确定的哈希元素在哈希数组中的位置
*/
unsigned long CHash::HashFun(const char *key, unsigned long &lKey)
{
	if(0!=key && 0!=key[0] )
	{
		for(;*key;++key)
			lKey = lKey*5 + *key;
	}
	else
	{
		strcpy(m_chrErrorInfo,"关键字不能为空!");
	}
	//
	return lKey % m_lSlots;
}

unsigned long CHash::HashFun(const long key, unsigned long &lKey)
{
	if(0!=key)
	{
		lKey = key * key;// << 5;
	}
	else
	{
		strcpy(m_chrErrorInfo,"关键字不能为空!");
	}
	//
	return lKey % m_lSlots;
}
/*!添加一个哈希元素
 *key:要添加的关键字
 *hahsItemValue:USER_LIST结构体的引用,作为哈希元素的值
 *返回值：1:插入成功;0:插入失败
*/
int CHash::InsertItem(const char *key, void *pHashItemValue)
{
	int nResult=0;
	//
	if(0!=key && 0!=key[0])
	{
		try
		{
			unsigned long lPos;
			unsigned long lKey;
			lPos = 0;
			lKey = 0;
			lPos = HashFun(key,lKey);
			if(lPos>=0 && lKey!=0)
			{			
				if(m_pHash[lPos])
				{
					CHashItem* pHashItem;
					CHashItem* pNextItem;
					pHashItem = m_pHash[lPos];
					while (pHashItem->pNextItem)
					{
						pHashItem = pHashItem->pNextItem;
					}
					//
					pNextItem = new CHashItem();
					strcpy(pNextItem->sKey, key);
					pNextItem->pObject = pHashItemValue;

					pHashItem->pNextItem = pNextItem;
					//
					nResult = 1;
					m_nLenth++;
				}
				else
				{
					m_pHash[lPos] = new CHashItem();
					strcpy(m_pHash[lPos]->sKey, key);
					m_pHash[lPos]->pObject = pHashItemValue;
					//
					nResult = 1;
					m_nLenth++;
					
				}
			}
		}
		catch(...)
		{
			nResult = 0;
			strcpy(m_chrErrorInfo,"添加哈希元素失败!");
		}
	}
	else
	{
		strcpy(m_chrErrorInfo,"关键字不能为空!");
	}
	//
	return nResult;
}

int CHash::InsertItem(const long key, void *pHashItemValue)
{
	int nResult=0;
	//
	if(0!=key)
	{
		try
		{
			unsigned long lPos;
			unsigned long lKey;
			lPos = 0;
			lKey = 0;
			lPos = HashFun(key,lKey);
			if(lPos>=0 && lKey!=0)
			{			
				if(m_pHash[lPos])
				{
					CHashItem* pHashItem;
					CHashItem* pNextItem;
					pHashItem = m_pHash[lPos];
					while (pHashItem->pNextItem)
					{
						pHashItem = pHashItem->pNextItem;
					}
					//
					pNextItem = new CHashItem();
					pNextItem->lKey = key;
					pNextItem->pObject = pHashItemValue;

					pHashItem->pNextItem = pNextItem;
					//
					nResult = 1;
					m_nLenth++;
				}
				else
				{
					m_pHash[lPos] = new CHashItem();
					m_pHash[lPos]->lKey = key;
					m_pHash[lPos]->pObject = pHashItemValue;
					//
					nResult = 1;
					m_nLenth++;
					
				}
			}
		}
		catch(...)
		{
			nResult = 0;
			strcpy(m_chrErrorInfo,"添加哈希元素失败!");
		}
	}
	else
	{
		strcpy(m_chrErrorInfo,"关键字不能为空!");
	}
	//
	return nResult;
}
/*!查询一个哈希元素
 *key:查询的关键字
 *返回值:返回一个指向USER_LIST结构体的指针
*/
void* CHash::QueryItem(const char *key)
{
	//
	if(0!=key && 0!=key[0])
	{
		try
		{
			unsigned long lPos;
			unsigned long lKey;
			lPos = 0;
			lKey = 0;
			lPos = HashFun(key,lKey);
			if(lPos>=0 && lKey!=0)
			{
				CHashItem* pHashItem;
				pHashItem = m_pHash[lPos];
				while(pHashItem)
				{
					if(strcmp(pHashItem->sKey, key) == 0)
					{
						return pHashItem->pObject;
					}
					//
					pHashItem = pHashItem->pNextItem;					
				}
			}
		}
		catch(...)
		{
			strcpy(m_chrErrorInfo,"查询数据发生异常!");

		}
	}
	else
	{
		strcpy(m_chrErrorInfo,"关键字不能为空!");
	}
	//
	return NULL;
}

void* CHash::QueryItem(const long key)
{
	//
	if(0!=key)
	{
		try
		{
			unsigned long lPos;
			unsigned long lKey;
			lPos = 0;
			lKey = 0;
			lPos = HashFun(key,lKey);
			if(lPos>=0 && lKey!=0)
			{
				CHashItem* pHashItem;
				pHashItem = m_pHash[lPos];
				while(pHashItem)
				{
					if(pHashItem->lKey == key)
					{
						return pHashItem->pObject;
					}
					//
					pHashItem = pHashItem->pNextItem;					
				}
			}
		}
		catch(...)
		{
			strcpy(m_chrErrorInfo,"查询数据发生异常!");

		}
	}
	else
	{
		strcpy(m_chrErrorInfo,"关键字不能为空!");
	}
	//
	return NULL;
}
/*!删除一个哈希元素
 *key:关键字
 *返回值:1:删除成功；0：删除失败
*/
void *CHash::DeleteItem(const char *key)
{
	int nResult =0;
	void *pVoid;
	//
	if(0!=key && 0!=key[0])
	{
		try
		{
			unsigned long lPos;
			unsigned long lKey;
			lPos = 0;
			lKey = 0;
			lPos = HashFun(key,lKey);
			if(lPos>=0 && lKey!=0)
			{
				CHashItem* pHashItem;
				CHashItem* pParentItem = NULL;
				pHashItem = m_pHash[lPos];

				while (pHashItem)
				{
					if(strcmp(pHashItem->sKey, key) == 0)
					{
						//
						pVoid = pHashItem->pObject;
						if (pParentItem != NULL)
						{
							pParentItem->pNextItem = pHashItem->pNextItem;
						}
						else
						{
							m_pHash[lPos] = pHashItem->pNextItem;
						}
						delete pHashItem;
						m_nLenth --;
						return pVoid;
					}
					//
					pParentItem = pHashItem;
					pHashItem = pHashItem->pNextItem;
				}
			}
		}
		catch (...)
		{
			strcpy(m_chrErrorInfo,"删除数据发生异常!");	
			return NULL;
		}
	}
	
	return NULL;	
}

void *CHash::DeleteItem(const long key)
{
	int nResult =0;
	void *pVoid;
	//
	if(0!=key)
	{
		try
		{
			unsigned long lPos;
			unsigned long lKey;
			lPos = 0;
			lKey = 0;
			lPos = HashFun(key,lKey);
			if(lPos>=0 && lKey!=0)
			{
				CHashItem* pHashItem;
				CHashItem* pParentItem = NULL;
				pHashItem = m_pHash[lPos];

				while (pHashItem)
				{
					if(pHashItem->lKey == key)
					{
						//
						pVoid = pHashItem->pObject;
						if (pParentItem != NULL)
						{
							pParentItem->pNextItem = pHashItem->pNextItem;
						}
						else
						{
							m_pHash[lPos] = pHashItem->pNextItem;
						}
						delete pHashItem;
						m_nLenth --;
						return pVoid;
					}
					//
					pParentItem = pHashItem;
					pHashItem = pHashItem->pNextItem;
				}
			}
		}
		catch (...)
		{
			strcpy(m_chrErrorInfo,"删除数据发生异常!");	
			return NULL;
		}
	}
	return NULL;

	//
	
}
/*!得到哈希表中哈希元素的个数
 *返回值:哈希元素的个数
 */
int CHash::GetHashItemNum()
{
	return m_nLenth;
}
/*!得到哈希表中哈希数组的大小
 *返回值:哈希数组的大小	
 */
unsigned long CHash::GetHashArrayNum()
{
	return m_lSlots;
}

void CHash::FindFirst(int pos)
{
	m_iCurrentPos = pos + 1;
	m_pCurrentHashItem = m_pHash[pos];
}

void * CHash::FindNext(char **sKey)
{
	CHashItem *pItem;
	if (GetHashItemNum() == 0)
		return NULL;
	if (m_pCurrentHashItem != NULL)
	{
		pItem = m_pCurrentHashItem;
		m_pCurrentHashItem = m_pCurrentHashItem->pNextItem;
		*sKey = pItem->sKey;
		return pItem->pObject;
	}
	else if (m_iCurrentPos >= m_lSlots)
	{
		*sKey = NULL;
		return NULL;
	}
	else
	{
		while(m_pCurrentHashItem == NULL && m_iCurrentPos < m_lSlots)
		{
			m_pCurrentHashItem = m_pHash[m_iCurrentPos ++];
		}
		if (m_pCurrentHashItem == NULL)
		{
			*sKey = NULL;
			return NULL;
		}
		pItem = m_pCurrentHashItem;
		m_pCurrentHashItem = m_pCurrentHashItem->pNextItem;
		*sKey = pItem->sKey;
		return pItem->pObject;
	}
}

void *CHash::FindNext()
{
	char *pTemp = NULL;
	return FindNext(&pTemp);
}

int CHash::GetCurrentPos()
{
	return m_iCurrentPos;
}

// add by cress
HASHPOINT CHash::GetFirst(int nPos)
{
	return NULL;
}

HASHPOINT CHash::GetFirst(int nPos, int &nCurrentPos, int nMaxPos)
{
	nCurrentPos = 0;
	if (nMaxPos == 0)
		nMaxPos = m_lSlots;
	
	if (GetHashItemNum() == 0)
		return NULL;

	CHashItem *pHashItem;
	if (nPos >= nMaxPos)
	{
		return NULL;
	}

	nCurrentPos = nPos;
	pHashItem = m_pHash[nCurrentPos ++];
	
	if (pHashItem != NULL)
	{
		return (HASHPOINT)pHashItem;
	}
	else
	{
		while(pHashItem == NULL && nCurrentPos < nMaxPos)
		{
			pHashItem = m_pHash[nCurrentPos ++];
		}
		return pHashItem;
	}
}

void * CHash::GetNext(HASHPOINT *hashPoint, int &nCurrentPos, int nMaxPos)
{
	if (nMaxPos == 0)
		nMaxPos = nMaxPos;
	if (nMaxPos < nCurrentPos)
		return NULL;
	
	CHashItem *pHashItem = (CHashItem *)*hashPoint;
	if (pHashItem == NULL)
		return NULL;
	void *pObject = pHashItem->pObject;
	*hashPoint = pHashItem->pNextItem;
	while(*hashPoint == NULL && nCurrentPos < nMaxPos)
	{
		*hashPoint = (HASHPOINT)m_pHash[nCurrentPos ++];
	}
	return pObject;
}
