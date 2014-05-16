// MightyCaslView.cpp : CMightyCaslView クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "MightyCasl.h"

#include "MightyCaslDoc.h"
#include "MightyCaslView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView

IMPLEMENT_DYNCREATE(CMightyCaslView, CView)

BEGIN_MESSAGE_MAP(CMightyCaslView, CView)
	//{{AFX_MSG_MAP(CMightyCaslView)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//    この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView クラスの構築/消滅

CMightyCaslView::CMightyCaslView()
{
	// TODO: この場所に構築用のコードを追加してください。

}

CMightyCaslView::~CMightyCaslView()
{
}

BOOL CMightyCaslView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView クラスの描画

void CMightyCaslView::OnDraw(CDC* pDC)
{
	CMightyCaslDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView クラスの診断

#ifdef _DEBUG
void CMightyCaslView::AssertValid() const
{
	CView::AssertValid();
}

void CMightyCaslView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMightyCaslDoc* CMightyCaslView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMightyCaslDoc)));
	return (CMightyCaslDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMightyCaslView クラスのメッセージ ハンドラ

