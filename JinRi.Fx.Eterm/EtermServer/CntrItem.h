
// CntrItem.h : CEtermServerCntrItem ��Ľӿ�
//

#pragma once

class CEtermServerDoc;
class CEtermServerView;

class CEtermServerCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CEtermServerCntrItem)

// ���캯��
public:
	CEtermServerCntrItem(REOBJECT* preo = NULL, CEtermServerDoc* pContainer = NULL);
		// ע��:  ���� pContainer Ϊ NULL ������ IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE Ҫ������д���
		//  �����Ĺ��캯����  OLE ��ͨ������
		//  �� NULL �ĵ�ָ�빹���

// ����
public:
	CEtermServerDoc* GetDocument()
		{ return reinterpret_cast<CEtermServerDoc*>(CRichEditCntrItem::GetDocument()); }
	CEtermServerView* GetActiveView()
		{ return reinterpret_cast<CEtermServerView*>(CRichEditCntrItem::GetActiveView()); }
	
// ʵ��
public:
	~CEtermServerCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

