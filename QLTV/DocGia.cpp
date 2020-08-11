#include "DocGia.h"

void initTREE_DG(TreeTDG &t) {
	nDG = 0;
	t = NULL;
}

bool IsEmpty(TreeTDG t) {
	return t == NULL;
}

NodeTDG* GetNode_DG(TDG dg) {
	NodeTDG *p = new NodeTDG;
	if (p == NULL) {
		return NULL;
	}
	// khoi tao danh muc sach trong node doc gia
	initList_MT(p->listMT);
	p->info = dg;
	p->leftTDG = p->rightTDG = NULL;
	return (p);
}

void InsertDTtoTree(TreeTDG &t, TDG dg) {
	/// tang doc gia len 1
	if (t == NULL) {
		t = GetNode_DG(dg);
		++nDG;
	} else if (t->info.maThe > dg.maThe) {
		InsertDTtoTree(t->leftTDG, dg);
	} else if (t->info.maThe < dg.maThe) {
		InsertDTtoTree(t->rightTDG, dg);
	}
}

int countDG(TreeTDG tree) {
	int c = 1;             // ban than node duoc dem la 1;
	if (tree == NULL)
		return 0;
	else {
		c += countDG(tree->leftTDG);
		c += countDG(tree->rightTDG);
		return c;
	}
}

bool Check_MADG(TreeTDG  t, int MADG) {
	if (t == NULL) {
		return false;
	} else if (t->info.maThe == MADG) {
		return true;
	} else if (MADG < t->info.maThe) {
		return Check_MADG(t->leftTDG, MADG);
	} else {
		return Check_MADG(t->rightTDG, MADG);
	}
}

int Random() {
	srand((int)time(0));
	int x;
	// bo ham rand() vao vong lap moi khong bi loi tang dan, hay giam dan.
	for (int i = 0; i < 500; i++) {
		x = rand();
	}
	return x;
}

int Random_MADG(TreeTDG t) {
	int temp;
	do {
		temp = Random();
	} while (Check_MADG(t, temp));  // check trung , neu trung thi random lai
	return temp;
}

NodeTDG* FindMin(TreeTDG t) {
	while (t->leftTDG != NULL) t = t->leftTDG;
	return (t);
}

NodeTDG* Find_DG(TreeTDG t, int MADG) {
	while (t != NULL && t->info.maThe != MADG) {
		if (MADG < t->info.maThe) {
			t = t->leftTDG;
		} else t = t->rightTDG;
	}
	return (t);
}

bool IsDeleted_DG(TreeTDG &t, TDG dg) {
	if (t == NULL)
		return false;
	else {
		if (dg.maThe > t->info.maThe)
			return IsDeleted_DG(t->rightTDG, dg);
		else if (dg.maThe < t->info.maThe)
			return IsDeleted_DG(t->leftTDG, dg);
		else { // Wohoo... I found you, Get ready to be deleted
			//case 1: No child
			if (t->leftTDG == NULL && t->rightTDG == NULL) {
				delete t; // dangling pointer
				t = NULL;
				nDG--;
			} else if (t->leftTDG == NULL) { // case 2: One child
				NodeTDG* temp = t;
				t = t->rightTDG;
				delete temp;
				nDG--;
			} else if (t->rightTDG == NULL) {
				NodeTDG* temp = t;
				t = t->leftTDG;
				delete temp;
				nDG--;
			}// Case 3: 2 children
			else {
				NodeTDG* temp = FindMin(t->rightTDG);

				// copy du lieu vao .
				t->info = temp->info;
				t->listMT = temp->listMT;
				return IsDeleted_DG(t->rightTDG, temp->info);
			}
			return true;
		}
	}
}

void Xoa_OutDG_1line(int locate) {
	gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[1] - xDisplayDG[0] - 1) << setfill(' ') << ' ';
	gotoxy(xDisplayDG[1] + 1, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[2] - xDisplayDG[1] - 1) << setfill(' ') << ' ';
	gotoxy(xDisplayDG[2] + 4, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[3] - xDisplayDG[2] - 5) << setfill(' ') << ' ';
	gotoxy(xDisplayDG[3] + 3, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[4] - xDisplayDG[3] - 3) << setfill(' ') << ' ';
	gotoxy(xDisplayDG[4] + 3, yDisplay + 3 + locate);
	cout << setw(xDisplayDG[5] - xDisplayDG[4] - 3) << setfill(' ') << ' ';
}

void Xoa_OutDg_29lines() {
	for (int i = 0; i <NUMBER_LINES; i++) {
		Xoa_OutDG_1line(i);
	}
}

void Output_DG(NodeTDG* dg) {
	Xoa_OutDG_1line(locate);
	gotoxy(xDisplayDG[0] + 3, yDisplay + 3 + locate);
	cout << dg->info.maThe;
	gotoxy(xDisplayDG[1] + 1, yDisplay + 3 + locate);
	cout << dg->info.ho;
	gotoxy(xDisplayDG[2] + 4, yDisplay + 3 + locate);
	cout << dg->info.ten;
	gotoxy(xDisplayDG[3] + 3, yDisplay + 3 + locate);
	(dg->info.phai == 0) ? cout << "NAM" : cout << "NU";

	gotoxy(xDisplayDG[4] + 3, yDisplay + 3 + locate);
	(dg->info.trangThaiThe == 0) ? cout << "KHOA" : cout << "HOAT DONG";
	locate++;
}


// loai bo khoang cach.
string Get_TenHO(TDG dg) {
	int i = 0;
	string token;
	token = dg.ten;
	while (dg.ho[i] != ' ') {
		token += dg.ho[i++];
	}
	return token;
}

void Create_ArrMADG(TreeTDG t, int* arr) {
	if (t == NULL)
		return;
	Create_ArrMADG(t->leftTDG, arr); // visit left subtree
	arr[index++] = t->info.maThe;
	Create_ArrMADG(t->rightTDG, arr);// visit right subtree
}

void Create_ArrTenHo(TreeTDG t, TEN_HO* arr) {
	if (t == NULL)
		return;
	Create_ArrTenHo(t->leftTDG, arr); // visit left subtree
	arr[index].hoten = Get_TenHO(t->info);
	arr[index++].MADG = t->info.maThe;
	Create_ArrTenHo(t->rightTDG, arr);// visti right subtree
}

void Creat_TEMPLIST(TreeTDG t, LIST_TEMPLIST &l, int &index) {
	if (t == NULL)
		return;
	Creat_TEMPLIST(t->leftTDG, l, index);
	AddTailList_TEMPLIST(l, index++, t->info.maThe);
	Creat_TEMPLIST(t->rightTDG, l, index);
}

void Swap_TenHo(TEN_HO &a, TEN_HO &b) {
	TEN_HO temp;
	temp = a;
	a = b;
	b = temp;
}

void QuicKsort_ARRTenHo(TEN_HO *th, int left, int right) {
	TEN_HO key = th[(left + right) / 2];
	int i = left, j = right;
	do {
		while (th[i].hoten < key.hoten)
			i++;
		while (th[j].hoten > key.hoten)
			j--;
		if (i <= j) {
			if (i < j) Swap_TenHo(th[i], th[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) QuicKsort_ARRTenHo(th, left, j);
	if (right > i) QuicKsort_ARRTenHo(th, i, right);
}

void Update_DG(TreeTDG &t, TDG &dg, bool isEdited) {
	// hien con tro nhap
	ShowCur(true);
	normalBGColor();

	// cac flag dieu khien qua trinh cap nhat
	int ordinal = 0;
	bool isSave = false;
	bool isEscape = false;

	// chieu dai bang nhap
	int nngang = (int)keyBangNhapDG[0].length();

	// cac bien luu tru tam thoi
	string ho = "";
	string ten = "";
	int phai = 3, ttthe = 3;
	int MADG;

	CreateBox(X_NOTIFY, Y_NOTIFY, "NOTIFICATIONS:  ", 59);
	BangNhap(xDisplayDG[5] + 7, yDisplay, nngang, keyBangNhapDG, 12);
	BangGuides(xDisplayDG[5] + 7, yDisplay + 20, nngang, keyGuide1, 6);

	if (isEdited) {
		ho = dg.ho;
		ten = dg.ten;
		phai = dg.phai;
		ttthe = dg.trangThaiThe;
		MADG = dg.maThe;
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 3);
		cout << MADG;
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 5);
		cout << ho;
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 7);
		cout << ten;
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 9);
		(phai == 0) ? cout << phai << ":  NAM" : cout << phai << ":  NU";
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 11);
		(ttthe == 0) ? cout << ttthe << ":  KHOA" : cout << ttthe << ":  HOAT DONG";
	}
	if (!isEdited) {
		gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 3);
		MADG = Random_MADG(t);
		cout << MADG;
	}

	while (true) {

		switch (ordinal) {
			case 0:
				gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 5);
				NhapHo(ho, ordinal, isSave, isEscape);
				break;
			case 1:
				gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 7);
				NhapTen(ten, ordinal, isSave, isEscape);
				break;
			case 2:
				gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 9);
				Nhap(phai, NHAP_PHAI, ordinal, isSave, isEscape);
				break;
			case 3:
				gotoxy((xDisplayDG[5] + 7 + nngang / 2), yDisplay + 11);
				Nhap(ttthe, NHAP_TRANG_THAI, ordinal, isSave, isEscape);
				break;
		}
		// check Save
		if (isSave) {
			// cap nhat lai flag
			isSave = false;

			// check rong;
			if (ho.length() == 0) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();

				// quay lai va dien vao truong du lieu do
				ordinal = 0;
				continue;
			} else if (ten.length() == 0) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();

				// quay lai va dien vao truong du lieu do
				ordinal = 1;
				continue;
			} else if (phai == 3) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 2;
				continue;
			} else if (ttthe == 3) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				ordinal = 3;
				continue;
			}

			dg.maThe = MADG;
			dg.ho = ChuanHoaString(ho);
			dg.ten = ChuanHoaString(ten);
			dg.phai = phai;
			dg.trangThaiThe = ttthe;

			if (isEdited) {
				NodeTDG* p;

				// ma doc gia khong doi
				p = Find_DG(t, MADG);
				p->info = dg;
			} else {
				InsertDTtoTree(t, dg);
			}

			// In dong thong bao .
			for (int i = 0; i < 5; i++) {
				SetColor(BLUE);
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				Sleep(100);
				cout << "           SUCCESSFULLY !!! ";
			}
			normalBGColor();
			XoaMotVung(xDisplayDG[5] + 7, yDisplay, 30, 60);
			return;
		}

		if (isEscape) {
			XoaMotVung(xDisplayDG[5] + 7, yDisplay, 30, 60);
			return;
		}
	}
	ShowCur(false);
}

void OutputDG_PerPage1(TreeTDG t, TEN_HO *arr, int index) {
	Xoa_OutDg_29lines();
	locate = 0;
	index--;
	NodeTDG* temp = NULL;

	if (t == NULL)
		return;
	else {
		for (int i =  NUMBER_LINES * index; i < NUMBER_LINES*( 1 +  index) && i < nDG; i++) {
			temp = Find_DG(t, arr[i].MADG);
			Output_DG(temp);
		}
	}
}

void Output_ListDG1(TreeTDG t, TEN_HO *arr) {
	ShowCur(false);
	nDG = countDG(t);

	// thu tu trang
	int tttrang, tongtrang;
	tttrang = 1;
	tongtrang = (nDG / NUMBER_LINES) + 1;
	OutputDG_PerPage1(t, arr, tttrang);

	int kb_hit;
	do {
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit) {
				case PAGE_UP:

					(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
					OutputDG_PerPage1(t, arr, tttrang);
					break;
				case PAGE_DOWN:

					(tttrang < tongtrang) ? tttrang++ : tttrang = 1;
					OutputDG_PerPage1(t, arr, tttrang);
					break;

				case ESC:
					return;
			}
		}
		gotoxy(3, 35);
		cout << "HotKey: PgUp, PgDn, ESC, KEYUP, KEYDOWN ";
		gotoxy(55, 35);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}

void OutputDG_PerPage2(TreeTDG t, int* arr, int index) {
	Xoa_OutDg_29lines();
	locate = 0;
	NodeTDG* temp = NULL;
	index--;
	for (int i = 0 + NUMBER_LINES * index; i < (NUMBER_LINES + NUMBER_LINES * index) && i < nDG; i++) {
		temp = Find_DG(t, arr[i]);
		Output_DG(temp);
	}
}

void Output_ListDG2(TreeTDG t, int *arr) {
	ShowCur(false);
	nDG = countDG(t);
	// thu tu trang
	int tttrang, tongtrang;
	tttrang = 1;
	tongtrang = (nDG / NUMBER_LINES) + 1;
	OutputDG_PerPage2(t, arr, tttrang);

	int kb_hit;
	do {
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit) {

				case PAGE_UP:
					(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
					OutputDG_PerPage2(t, arr, tttrang);
					break;

				case PAGE_DOWN:
					(tttrang < tongtrang) ? tttrang++ : tttrang = 1;
					OutputDG_PerPage2(t, arr, tttrang);
					break;

				case  ESC:
					return;
			}
		}
		gotoxy(3, 35);
		cout << "HotKey: PgUp, PgDn, ESC, KEYUP, KEYDOWN ";
		gotoxy(55, 35);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}

void OutputDG_PerPage(TreeTDG t, LIST_TEMPLIST l, int index) {
	Xoa_OutDg_29lines();
	SetColor(WHITE);
	locate = 0;
	NODE_TEMPLIST * temp1 = NULL;
	NodeTDG* temp2 = NULL;
	index--;
	for (int i = NUMBER_LINES * index; i < NUMBER_LINES * (index + 1) ; i++) {
		temp1 = BinarySearch_TEMPLIST(l, i);
		if (temp1 == NULL) {
			return;
		}
		temp2 = Find_DG(t, temp1->tl.MADG);
		Output_DG(temp2);
	}
}

int ChooseItems(TreeTDG &t, LIST_TEMPLIST &l, int tttrang, int tongtrang) {
	int pos = 0;
	int kb_hit;
	pos = 0;
	SetColor(LIGHT_GREEN);
	gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + pos);
	cout << "<<";
	gotoxy(xDisplayDG[0] + 2 + 6, yDisplay + 3 + pos);
	cout << ">>";
	while (true) {
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();

			switch (kb_hit) {
				case KEY_UP:
					// xoa muc truoc
					gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + pos);
					cout << "  ";
					gotoxy(xDisplayDG[0] + 2 + 6, yDisplay + 3 + pos);
					cout << "  ";

					(pos > 0) ? pos-- : pos = 28;

					// to mau muc moi
					gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDG[0] + 2 + 6, yDisplay + 3 + pos);
					cout << ">>";
					break;

				case KEY_DOWN:
					// xoa muc truoc
					gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + pos);
					cout << "  ";
					gotoxy(xDisplayDG[0] + 2 + 6, yDisplay + 3 + pos);
					cout << "  ";

					(pos < NUMBER_LINES - 1) ? pos++ : pos = 0;

					// to mau muc moi
					gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDG[0] + 2 + 6, yDisplay + 3 + pos);
					cout << ">>";
					break;

				case PAGE_UP:
					if (tttrang > 1) {
						tttrang--;
					} else {
						tttrang = tongtrang;
					}
					OutputDG_PerPage(t, l, tttrang);

					// high light hang dau.
					pos = 0;
					SetColor(LIGHT_GREEN);
					gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDG[0] + 2 + 6, yDisplay + 3 + pos);
					cout << ">>";
					break;

				case PAGE_DOWN:
					if (tttrang <  tongtrang) {
						tttrang++;
					} else {
						tttrang = 1;

					}

					OutputDG_PerPage(t, l, tttrang);

					// high light hang dau.
					pos = 0;
					SetColor(LIGHT_GREEN);
					gotoxy(xDisplayDG[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDG[0] + 2 + 6, yDisplay + 3 + pos);
					cout << ">>";
					break;

				case ENTER:

					// tra ve vi tri pos.
					return (pos == 0 && tttrang == 1) ? pos : pos + (tttrang - 1)* NUMBER_LINES;
			}
		}
		ShowCur(false);
		SetColor(WHITE);
		gotoxy(30, 36);
		cout << "Trang " << tttrang << " / " << tongtrang;
		normalBGColor();
	}
}

int Output_ListDG(TreeTDG &t, LIST_TEMPLIST &l, TDG &dg,  int &tttrang) {
	NODE_TEMPLIST * temp1 = NULL;
	NodeTDG* temp2 = NULL;
	int choose;
	bool check;

	// nDG la so DG hien co trong cay
	nDG = countDG(t);

	// thu tu trang
	int  tongtrang;
	tongtrang = (nDG / NUMBER_LINES) + 1;
	OutputDG_PerPage(t, l, tttrang);

	int kb_hit;
	do {
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit) {
				case PAGE_UP:

					(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
					OutputDG_PerPage(t, l, tttrang);
					break;

				case PAGE_DOWN:
					(tttrang <  tongtrang) ? tttrang++ : tttrang = 1;
					OutputDG_PerPage(t, l, tttrang);
					break;

					// them
				case KEY_F2:
					Beep(600, 100);
					Update_DG(t, dg, false);
					ClearAll_TEMPLIST(l);
					return 1;

					// hieu chinh
				case  KEY_F3:
					Beep(600, 100);
					choose = ChooseItems(t, l, tttrang, tongtrang);
					temp1 = BinarySearch_TEMPLIST(l, choose);

					// check cac truong hop.
					if (temp1 == NULL) {
						return 1;
					} else {
						temp2 = Find_DG(t, temp1->tl.MADG);
						Update_DG(t, temp2->info, true);
						ClearAll_TEMPLIST(l);
						return 1;
					}

					// xoa
				case KEY_F4:
					Beep(600, 100);
					choose = ChooseItems(t, l, tttrang, tongtrang);
					temp1 = BinarySearch_TEMPLIST(l, choose);

					// truong hop khong chon doc gia nao.
					if (temp1 == NULL) {
						return 1;
					} else {
						temp2 = Find_DG(t, temp1->tl.MADG);
						if (SoSachDangMuon(temp2->listMT) > 0) {
							gotoxy(75, 20);
							cout << "Doc Gia da muon sach nen khong duoc phep xoa !";
							_getch();
							gotoxy(75, 20);
							cout << "                                                      ";
							return 1;
						} else {
							// chỗ biến check này để thông báo là check thành công.....
							check = IsDeleted_DG(t, temp2->info);
							ClearAll_TEMPLIST(l);
							return 1;
						}
					}

				case ESC:
					Beep(600, 100);
					ClearAll_TEMPLIST(l);
					return 0;
			}
		}
		ShowCur(false);
		gotoxy(30, 36);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}

void Menu_DocGia(TreeTDG &t) {
	clrscr();
	normalBGColor();
	int tttrang = 1;
	int esc = 1;

	do {
		clrscr();
		gotoxy(26, 1);
		cout << "CAP NHAT DOC GIA ";

		gotoxy(3, yHotkey );
		SetColor(WHITE);
		cout << "ESC-Thoat, F2 - Them, F3 - Sua, F4 - Xoa, F10 - Luu, PgUP, PgDn";

		normalBGColor();
		TDG dg;
		int index = 0;

		// cho nay thay doi cau truc DSLK TEMPLIST bang Mang cap phat dong hay hon...
		LIST_TEMPLIST l;
		initList_TEMPLIST(l);
		Creat_TEMPLIST(t, l, index);
		DisplayDG(keyDisplayDG, 5, xDisplayDG);
		esc = Output_ListDG(t, l, dg, tttrang);
	} while (esc );
}

void InDocGia(TreeTDG t) {
	clrscr();
	normalBGColor();
	ShowCur(false);

	int c = 0;
	int chosen = 0;
	while (c != ESC) {
		clrscr();
		SetColor(BRIGHT_WHITE);
		gotoxy(xINDOCGIA, yINDOCGIA);
		cout << " THEO THU TU TEN_HO TANG DAN ";
		gotoxy(xINDOCGIA, yINDOCGIA + 2);
		cout << " THEO THU TU MA_DG TANG DAN  ";
		while (c != ENTER) {
			SetColor(LIGHT_GREEN);
			gotoxy(xINDOCGIA - 3, yINDOCGIA + chosen);
			cout << "->";
			gotoxy(xINDOCGIA + 30, yINDOCGIA + chosen);
			cout << "<-";
			c = _getch();

			if (c == KEY_UP || c == KEY_DOWN) {
				gotoxy(xINDOCGIA - 3, yINDOCGIA + chosen);
				cout << "   ";
				gotoxy(xINDOCGIA + 30, yINDOCGIA + chosen);
				cout << "   ";

				if (chosen == 0) {
					chosen = 2;
				} else if (chosen == 2) {
					chosen = 0;
				}
			} else if (c == ESC) {
				return;
			}
		}
		if (chosen == 0) {
			index = 0;
			TEN_HO* ArrTenHo = new TEN_HO[nDG];
			Create_ArrTenHo(t, ArrTenHo);
			DisplayDG(keyDisplayDG, 5, xDisplayDG);
			QuicKsort_ARRTenHo(ArrTenHo, 0, nDG - 1);
			Output_ListDG1(t, ArrTenHo);

			// xoa vung nho
			delete[] ArrTenHo;
		} else if (chosen == 2) {
			index = 0;

			// su dung cap phat dong.
			int* arrMADG = new int[nDG];
			DisplayDG(keyDisplayDG, 5, xDisplayDG);
			Create_ArrMADG(t, arrMADG);
			Output_ListDG2(t, arrMADG);

			// xoa vung nho
			delete[]arrMADG;
		}
		c = 0;
		chosen = 0;
	}
}

void Sort_QuaHan(QuaHan *ArrQuaHan, int q, int r) {
	QuaHan temp;
	int i = q;
	int j = r;
	//Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
	int x = ArrQuaHan[(q + r) / 2].songayquahan;
	do {
		// Phân đoạn dãy con a[q],..., a[r]
		while (ArrQuaHan[i].songayquahan > x)
			i++; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x
		while (ArrQuaHan[j].songayquahan < x)
			j--;   //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

		if (i <= j) { // Hoan vi
			temp = ArrQuaHan[i];
			ArrQuaHan[i] = ArrQuaHan[j];
			ArrQuaHan[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (q<j) 	// phần thứ nhất có từ 2 phần tử trở lên
		Sort_QuaHan(ArrQuaHan, q, j);
	if (i < r)   	// phần thứ ba có từ 2 phần tử trở lên
		Sort_QuaHan(ArrQuaHan, i, r);
}


void DanhSachQuaHan(TreeTDG t) {
	system("color 0");
	clrscr();
	int nDG_MAX = countDG(t);

	// tao mang phu de xu ly.
	QuaHan *ArrQuaHan = new QuaHan[nDG_MAX];

	int ndg = 0;

	//Duyệt cây theo thứ tự NLR (Preorder): Giai thuat khong de quy.
	const int STACKSIZE = 500;
	NodeTDG* Stack[STACKSIZE];
	int sp = -1;	// Khoi tao Stack rong
	NodeTDG* p = t;
	while (p != NULL) {
		// cap nhat du lieu vao mang.
		ArrQuaHan[ndg].MADG = p->info.maThe;
		ArrQuaHan[ndg].songayquahan = SoNgayQuaHan(p->listMT);
		ndg++;

		if (p->rightTDG != NULL)
			Stack[++sp] = p->rightTDG;
		if (p->leftTDG != NULL)
			p = p->leftTDG;
		else if (sp == -1)
			break;
		else p = Stack[sp--];
	}

	// quicksort ArrQuaHan theo thu tu giam dan.
	Sort_QuaHan(ArrQuaHan, 0, ndg - 1);

	// in thong tin ra ngoai man hinh.
	string text = "DANH SACH DOC GIA MUON QUA HAN ";
	CreateBox(48, 2, text, (int)text.length());
	SetBGColor(GREEN);

	gotoxy(47, 2);
	cout << "DANH SACH DOC GIA MUON QUA HAN ";
	gotoxy(3, 5);
	cout << "STT";
	gotoxy(10, 5);
	cout << "MA DOC GIA";
	gotoxy(25, 5);
	cout << "HO DOC GIA";
	gotoxy(48, 5);
	cout << "TEN DOC GIA";
	gotoxy(65, 5);
	cout << "MA SACH";
	gotoxy(80, 5);
	cout << "TEN SACH";
	gotoxy(100, 5);
	cout << "TONG SO NGAY QUA HAN";
	normalBGColor();
	SetColor(WHITE);

	// in danh sach doc gia muon qua han theo thoi gian giam dan.
	int j = 0;
	for (int i = 0; i < ndg; i++) {
		if (ArrQuaHan[i].songayquahan > 0) {
			NodeTDG* p = Find_DG(t, ArrQuaHan[i].MADG);
			gotoxy(12, 6 + j);
			cout << p->info.maThe;
			gotoxy(25, 6 + j);
			cout << p->info.ho;
			gotoxy(50, 6 + j);
			cout << p->info.ten;
			gotoxy(67, 6 + j);
			cout << p->listMT.headLMT->info.maSach;
			gotoxy(82, 6 + j);
			cout << p->listMT.headLMT->info.tenSach;
			gotoxy(108, 6 + j);
			cout << SoNgayQuaHan(p->listMT);
			gotoxy(4, 6 + j);
			j++;
			cout << j;
		}
	}
	_getch();
	delete[] ArrQuaHan;
}
