#pragma once
#include "Date.h"
#include "DauSach.h"


// ..... khoi tao........
void initList_MT(ListMT &l);

// kiem tra rong
bool ListMTIsEmpty(ListDMS l);

// get node
NodeMT* GetNode_MT(MT DATA);

void AddHeadList_MT(ListMT &l, MT data);

void AddTailList_MT(ListMT &l, MT data);
	

void ClearAll_ListMT(ListMT &l);

bool SearchTenSach_MT(ListMT lMT, string tensach);

int SoSachDangMuon(ListMT lMT);

// ham kiem tra doc gia co lam mat sach hay khong? .Co thi tra lai 1, khong thi tra lai 0.
int MatSach(ListMT lMT);

int SoNgayMuon_Max(ListMT lMT);

int SoNgayQuaHan(ListMT lMT);

void Output_MT(NodeMT * p, int i);

void XoaDisplay_MT(int i);

void OutputList_MT(ListMT lMT);

void EffectiveMenu_MT(ListMT lMT, int pos, int flag);

int chonItem_MT(ListMT lMT);

