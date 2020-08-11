#include "MuonTra.h"

void initList_MT(ListMT &l) {
	l.headLMT = l.tailLMT = NULL;
	l.n = 0;
}

bool ListMTIsEmpty(ListDMS l) {
	return l.headLDMS == NULL;
}

NodeMT* GetNode_MT(MT DATA) {
	NodeMT *p = new NodeMT;
	if (p == NULL) {
		return NULL;
	}
	p->info = DATA;
	p->rightNMT = NULL;
	p->leftNMT = NULL;
	return (p);
}

void AddHeadList_MT(ListMT &l, MT data) {
	// tao Node
	NodeMT *p = GetNode_MT(data);
	if (l.headLMT == NULL) {
		l.headLMT = l.tailLMT = p;
	} else {
		p->rightNMT = l.headLMT;
		l.headLMT->leftNMT = p;
		l.headLMT = p;
	}
	++l.n;
}

void AddTailList_MT(ListMT &l, MT data) {
	// tao Node
	NodeMT *p = GetNode_MT(data);
	if (l.headLMT == NULL) {
		l.headLMT = l.tailLMT = p;
	} else {
		p->leftNMT = l.tailLMT;
		l.tailLMT->rightNMT = p;
		l.tailLMT = p;
	}
	++l.n;
}

void ClearAll_ListMT(ListMT &l) {
	NodeMT * p;
	while (l.headLMT != NULL) {
		p = l.headLMT;
		l.headLMT = l.headLMT->rightNMT;
		delete p;
	}
}

bool SearchTenSach_MT(ListMT lMT, string tensach) {
	for (NodeMT * p = lMT.headLMT; p != NULL; p = p->rightNMT) {
		if ((p->info.tenSach == tensach && p->info.trangThai == 0) || (p->info.tenSach == tensach && p->info.trangThai == 2)) {
			return true;
		}
	}
	return false;
}

int SoSachDangMuon(ListMT lMT) {
	int i = 0;
	for (NodeMT * p = lMT.headLMT; p != NULL; p = p->rightNMT) {
		if (p->info.trangThai == 0 || p->info.trangThai == 2) {
			i++;
		}
	}
	return i;
}

int MatSach(ListMT lMT) {
	for (NodeMT * p = lMT.headLMT; p != NULL; p = p->rightNMT) {
		if ( p->info.trangThai == 2) {
			return 1;
		}
	}
	return 0;
}

int SoNgayMuon_Max(ListMT lMT) {
	int max = 0;
	int nngay;
	for (NodeMT * p = lMT.headLMT; p != NULL; p = p->rightNMT) {
		if ((p->info.trangThai == 0) || (p->info.trangThai == 2)) {
			nngay = khoangCachNgay(p->info.ngayMuon);
			if (max < nngay) {
				max = nngay;
			}
		}
	}
	return max;
}

int SoNgayQuaHan(ListMT lMT) {
	return (SoNgayMuon_Max(lMT) - 7);
}


void Output_MT(NodeMT * p, int i) {
	gotoxy(XDisplayMT[0] + 2, 21 + i);
	cout << p->info.tenSach;
	gotoxy(XDisplayMT[1] + 2, 21 + i);
	cout << p->info.maSach;

	xuatNgayThang(p->info.ngayMuon, XDisplayMT[2] + 2, 21 + i);

	xuatNgayThang(p->info.ngayTra, XDisplayMT[3] + 3, 21 + i);

	gotoxy(XDisplayMT[4] + 9, 21 + i);
	cout << khoangCachNgay(p->info.ngayMuon);
	gotoxy(XDisplayMT[5] + 6, 21 + i);
	cout << p->info.viTriSach;

	gotoxy(XDisplayMT[6] + 2, 21 + i);
	if (p->info.trangThai == 2)
		cout << " Lam Mat Sach";
	else if (khoangCachNgay(p->info.ngayMuon) > 7)
		cout << " M. Qua 7 ngay";
	else if (p->info.trangThai == 0)
		cout << " Dang Muon";
	else if (p->info.trangThai == 1)
		cout << " Da Tra";
}

void XoaDisplay_MT(int i) {
	gotoxy(XDisplayMT[0] + 1, 21 + i);
	cout << setw(XDisplayMT[1] - XDisplayMT[0] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[1] + 1, 21 + i);
	cout << setw(XDisplayMT[2] - XDisplayMT[1] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[2] + 1, 21 + i);
	cout << setw(XDisplayMT[3] - XDisplayMT[2] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[3] + 1, 21 + i);
	cout << setw(XDisplayMT[4] - XDisplayMT[3] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[4] + 1, 21 + i);
	cout << setw(XDisplayMT[5] - XDisplayMT[4] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[5] + 1, 21 + i);
	cout << setw(XDisplayMT[6] - XDisplayMT[5] - 1) << setfill(' ') << " ";
	gotoxy(XDisplayMT[6] + 1, 21 + i);
	cout << setw(XDisplayMT[7] - XDisplayMT[6] - 1) << setfill(' ') << " ";
}

void OutputList_MT(ListMT lMT) {
	int i = 0;
	// xoa display dau sach
	for (int j = 0; j < 3; j++) {
		XoaDisplay_MT(j);
	}
	// thuc hien ouput
	for (NodeMT * p = lMT.headLMT; p != NULL; p = p->rightNMT) {
		if ( p->info.trangThai == 0 || p->info.trangThai == 2) {
			Output_MT(p, i);
			i++;
		}
	}
}

void EffectiveMenu_MT(ListMT lMT, int pos, int flag) {
	int i = 0;
	ShowCur(false);
	// get so sach dang muon trong danh sach.
	int n = SoSachDangMuon(lMT);
	// 0 --> 2;  2---> 1;  1---> 0
	if (flag == 1) {
		for (NodeMT * p = lMT.headLMT; p != NULL; p = p->rightNMT) {
			if (p->info.trangThai == 0 || p->info.trangThai == 2) {
				if (i == pos) {
					SetBGColor(GREEN);
					SetColor(BLACK);
					Output_MT(p, i);
					normalBGColor();
				}
				if (i == (pos + n - 1) % n) {
					SetColor(WHITE);
					Output_MT(p, i);
				}
				i++;
			}
		}
	} else if (flag == 2) {
		// 0 ---> 1; 1 ---> 2; 2 ---> 0
		for (NodeMT * p = lMT.headLMT; p != NULL; p = p->rightNMT) {
			if (p->info.trangThai == 0 || p->info.trangThai == 2) {
				if (i == pos) {
					SetBGColor(GREEN);
					SetColor(BLACK);
					Output_MT(p, i);
					normalBGColor();
				}
				if (i == (pos + 1) % n) {
					SetColor(WHITE);
					Output_MT(p, i);
				}
				i++;
			}
		}
	}
}

int chonItem_MT(ListMT lMT) {
	int currpos = 0;
	ShowCur(false);
	// get so sach dang muon trong danh sach.
	int n = SoSachDangMuon(lMT);

	if (n == 0)
		return -1;
	// high light muc dau.
	int i = 0;
	for (NodeMT * p = lMT.headLMT; p != NULL, i != 1; p = p->rightNMT) {
		if (p->info.trangThai == 0 || p->info.trangThai == 2) {
			if (i == 0) {
				SetBGColor(GREEN);
				SetColor(BLACK);
				Output_MT(p, i);
				normalBGColor();
				i++;
			}
		}
	}
	// xu ly.
	int kb_hit;
	while (true) {
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0) {
				kb_hit = _getch();
			}
			switch (kb_hit) {
				case KEY_UP:
					if (currpos > 0) {
						currpos = currpos - 1;
					} else {
						currpos = n - 1;  // vi tri hien tai bang so so sach muon.
					}
					EffectiveMenu_MT(lMT, currpos, 2);
					break;
				case KEY_DOWN:
					if (currpos <  n - 1) {
						currpos = currpos + 1;
					} else {
						currpos = 0;
					}
					EffectiveMenu_MT(lMT, currpos, 1);
					break;
				case ENTER: //enter
					return currpos;
			}
		}
	}
}
