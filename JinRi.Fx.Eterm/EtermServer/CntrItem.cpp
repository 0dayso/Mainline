
// CntrItem.cpp : CEtermServerCntrItem ���ʵ��
//

#include "stdafx.h"
#include "EtermServer.h"

#include "EtermServerDoc.h"
#include "EtermServerView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEtermServerCntrItem ��ʵ��

IMPLEMENT_SERIAL(CEtermServerCntrItem, CRichEditCntrItem, 0)

CEtermServerCntrItem::CEtermServerCntrItem(REOBJECT* preo, CEtermServerDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO:  �ڴ����һ���Թ������
}

CEtermServerCntrItem::~CEtermServerCntrItem()
{
	// TODO:  �ڴ˴�����������
}


// CEtermServerCntrItem ���

#ifdef _DEBUG
void CEtermServerCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CEtermServerCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

