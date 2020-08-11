#include "DanhMucSach.h"

void initList_DMS(ListDMS& ldms) {
	ldms.n = 0;
	ldms.headLDMS = ldms.tailLDMS = NULL;
	//ldms.headLDMS = NULL;
}

bool ListDMSIsEmpty(ListDMS ldms) {
	return ldms.headLDMS == NULL;
}

Node_DMS* getNode_DMS(DMS data) {
	Node_DMS *p = new Node_DMS;
	if(p == NULL) {
		return NULL;
	}
	p-> info = data;
	p-> nextNDMS = NULL;
	return (p);
}

//????????????
void addTailList_DMS(ListDMS &ldms, DMS data) {
	Node_DMS *p = getNode_DMS(data);
	if (ldms.headLDMS == NULL) {
		ldms.headLDMS = ldms.tailLDMS = p;
	} else {
		ldms.tailLDMS->nextNDMS = p;
		ldms.tailLDMS = p;
	}
	ldms.n++;
}

int getViTri_Key(Node_DMS *first, string key) {
	int viTri;
	Node_DMS *q;
	q = first;
	viTri = 1;
	if (q == NULL)
		return(-1);
	while (q != NULL && q->info.maSach != key) {
		q = q->nextNDMS;
		viTri++;
	}
	return(viTri);
}

Node_DMS *nodePointer(Node_DMS *first, int i) {
	Node_DMS *p;
	int viTri = 1;
	p = first;
	while (p != NULL && viTri < i) {
		p = p->nextNDMS;
		viTri++;
	}
	return(p);
}

void deleteFirst(Node_DMS *&first) {
	Node_DMS *p;
	if (first == NULL)
		return;
	else {
		p = first;    // nut can xoa la nut dau
		first = first->nextNDMS;
		delete p;
	}
}

void deleteAfter(Node_DMS *p) {
	Node_DMS *q;
	q = p-> nextNDMS;  // q chi nut can xoa
	p->nextNDMS = q-> nextNDMS;
	delete q;
}

int delete_Key(pDauSach &pDS, string key) {
	int viTri;
	viTri = getViTri_Key(pDS->pListDMS.headLDMS, key);
	if (viTri > pDS->pListDMS.n   || viTri == -1) {
		return  -1;
	}
	// truong hop xoa dau
	else if (viTri == 1) {
		deleteFirst(pDS->pListDMS.headLDMS );
		pDS->pListDMS.n--;
		return 1;
	} else {
		//p chi toi nut truoc nut can xoa
		Node_DMS  *p = nodePointer(pDS->pListDMS.headLDMS , viTri - 1);
		deleteAfter(p);

		// truong hop xoa duoi, thi phai cap nhat lai pTail, rat quan trong cho nay.@@
		if (viTri == pDS->pListDMS.n) {
			pDS->pListDMS.tailLDMS = p;
		}
		pDS->pListDMS.n--;
		return 1;
	}
}

bool Check_DMS(Node_DMS* nDMS) {
	for (Node_DMS* p = nDMS; p != NULL; p = p->nextNDMS) {
		// sach da co nguoi muon.
		if (p->info.trangThaiSach == 1) {
			return true;
		}
	}
	return false;
}

Node_DMS* Search_DMS1(pDauSach pDS, string masach) {
	Node_DMS* p;
	p = pDS->pListDMS.headLDMS;
	while (p != NULL && p->info.maSach != masach)
		p = p->nextNDMS;
	return (p);
}

Node_DMS* Search_DMS2(Node_DMS* dms, int pos) {
	int count = -1;
	for (Node_DMS* temp = dms; temp != NULL; temp = temp->nextNDMS) {
		count++;
		if (pos == count) {
			return temp;
		}
	}
	return NULL;
}

int NhapSach(pDauSach &pDS) {
	DMSach info;
	// hien con tro nhap
	ShowCur(true);
	normalBGColor();
	int nngang = (int)keyBangNhapDanhMucSach[0].length();
	CreateBox(40, Y_NOTIFY + 2, "NOTIFICATIONS:  ", 66);
	BangNhap(38, yDisplay + 2, nngang, keyBangNhapDanhMucSach, 8);
	BangGuides(38, yDisplay + 22, nngang, keyGuide3, 4);

	// cac flag dieu khien qua trinh cap nhat
	int ordinal = 1;
	bool isSave = false;
	bool isEscape = false;

	// cac bien luu tru tam thoi
	// ma sach = isbn + stt;   aaaa1..aaaa2....aaaa3....aaaa4
	// to_string(++pDS->dms.n)  chuyen kieu int thanh kieu nguyen.
	int stt = pDS->pListDMS.n;
	string maSach = pDS->ISBN + to_string(++stt);
	// neu maSach co trung thi tang ma sach len.
	while (Search_DMS1(pDS, maSach) != NULL) {
		stt++;
		maSach = pDS->ISBN + to_string(stt);
	}
	int ttSach = 3;
	string viTri = "";

	gotoxy(40 + (nngang / 3), yDisplay + 5);
	cout << maSach;
	while (true) {
		switch (ordinal) {
			case 1:
				NhapTrangThaiSach(ttSach, ordinal, isSave, isEscape, 40 + (nngang / 3), yDisplay + 7);
				break;
			case 2:
				NhapViTri(viTri, ordinal, isSave, isEscape, 40 + (nngang / 3), yDisplay + 9);
				break;
		}
		// check Save
		if (isSave) {
			// cap nhat lai flag
			isSave = false;
			// check rong;
			if (ttSach == 3) {
				gotoxy(55, Y_NOTIFY + 2);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 1;
				continue;
			}
			if (viTri.length() == 0) {
				gotoxy(55, Y_NOTIFY + 2);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 2;
				continue;
			}
			// import data vao info
			info.maSach = maSach;
			info.trangThaiSach = ttSach;
			info.viTri = viTri;
			addTailList_DMS(pDS->pListDMS, info);
			return 0;
		}
		if (isEscape) {
			return -1;
		}
	}
}

int SuaDanhMucSach(pDauSach &pDS, Node_DMS* dms) {
	DMS info;
	// kiem tra dieu kien.
	if (dms->info.trangThaiSach == 1)
		return 2;
	// hien con tro nhap
	ShowCur(true);
	normalBGColor();

	int nngang = (int)keyBangNhapDanhMucSach[0].length();

	CreateBox(67, Y_NOTIFY + 2, "NOTIFICATIONS:  ", 66);
	BangNhap(65, yDisplay + 6, nngang, keyBangNhapDanhMucSach, 8);
	BangGuides(65, yDisplay + 22, nngang, keyGuide3, 4);

	// cac flag dieu khien qua trinh cap nhat
	int ordinal = 1;
	bool isSave = false;
	bool isEscape = false;

	string maSach = dms->info.maSach;

	int ttSach = dms->info.trangThaiSach ;
	string viTri = dms->info.viTri;

	gotoxy(67 + (nngang / 3), yDisplay + 9);
	cout << maSach;

	gotoxy(89, yDisplay + 11);
	if (ttSach == 0)
		cout << ttSach << ":   CHO MUON DUOC  ";
	else if (ttSach == 1)
		cout << ttSach << ":   DA DUOC MUON   ";
	else if (ttSach == 2)
		cout << ttSach << ":   DA THANH LY    ";

	gotoxy(89, yDisplay + 13);
	cout << viTri;
	while (true) {
		switch (ordinal) {
			case 1:
				NhapTrangThaiSach(ttSach, ordinal, isSave, isEscape, 89,  yDisplay + 11);
				break;
			case 2:
				NhapViTri(viTri, ordinal, isSave, isEscape, 89, yDisplay + 13);
				break;
		}
		// check Save
		if (isSave) {
			// cap nhat lai flag
			isSave = false;
			// check rong;
			if (ttSach == 3) {
				gotoxy(67, Y_NOTIFY + 2);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 1;
				continue;
			}
			if (viTri.length() == 0) {
				gotoxy(67, Y_NOTIFY + 2);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 2;
				continue;
			}
			// import data vao info
			info.maSach = maSach;
			info.trangThaiSach = ttSach;
			info.viTri = viTri;
			dms->info = info;
			return 1;
		}
		if (isEscape) {
			return -1;
		}
	}
}

void Xoa_OutDMS_1line(int locate) {
	gotoxy(xDisplayDMS[0] + 1, yDisplay + 3 + locate);
	cout << setw(11) << setfill(' ') << ' ';
	gotoxy(xDisplayDMS[1] + 1, yDisplay + 3 + locate);
	cout << setw(13) << setfill(' ') << ' ';
	gotoxy(xDisplayDMS[2] + 1, yDisplay + 3 + locate);
	cout << setw(34) << setfill(' ') << ' ';
}

void Xoa_OutDMS_29lines() {
	for (int i = 0; i <NUMBER_LINES; i++) {
		Xoa_OutDMS_1line(i);
	}
}

int ChooseItems(List_DauSach &lDS, int &tttrang, int tongtrang) {
	int pos = 0;
	int kb_hit;
	pos = 0;
	SetColor(LIGHT_GREEN);
	gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
	cout << "<<";
	gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
	cout << ">>";
	while (true) {
		// mau me, hoa la he...
		gotoxy(20, 1);
		cout << "~~~";
		gotoxy(20, 1);
		Sleep(50);
		cout << "   ";
		gotoxy(62, 1);
		cout << "~~~";
		gotoxy(62, 1);
		Sleep(50);
		cout << "   ";
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit) {
				case KEY_UP:
					// xoa muc truoc
					gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
					cout << "  ";
					gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
					cout << "  ";
					(pos > 0) ? pos-- : pos = 28;
					// to mau muc moi
					gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
					cout << ">>";
					break;
				case KEY_DOWN:
					// xoa muc truoc
					gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
					cout << "  ";
					gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
					cout << "  ";
					(pos < 28) ? pos++ : pos = 0;
					// to mau muc moi
					gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
					cout << ">>";
					break;
				case PAGE_UP:
					if (tttrang > 1) {
						tttrang--;
					} else {
						tttrang = tongtrang;
					}
					OutputDS_PerPage(lDS, tttrang);
					// hight light dong dau.
					pos = 0;
					SetColor(LIGHT_GREEN);
					gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
					cout << ">>";
					break;
				case PAGE_DOWN:
					if (tttrang <  tongtrang) {
						tttrang++;
					} else {
						tttrang = 1;

					}
					OutputDS_PerPage(lDS, tttrang);
					// high light dong dau.
					pos = 0;
					SetColor(LIGHT_GREEN);
					gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
					cout << ">>";
					break;
				case ENTER:
					return (pos == 0 && tttrang == 1) ? pos : pos + (tttrang - 1)* NUMBER_LINES;

				case ESC:
					return -1;
			}
		}
		ShowCur(false);
		gotoxy(33, 35);
		cout << "Trang " << tttrang << " / " << tongtrang;
	}

}

int ChooseItems1(pDauSach &pDS, int &tttrang, int tongtrang) {
	int pos = 0;
	int kb_hit;
	pos = 0;
	SetColor(LIGHT_GREEN);
	gotoxy(xDisplayDMS[0] + 1, yDisplay + 3 + pos);
	cout << "<<";
	gotoxy(xDisplayDMS[0] + 10, yDisplay + 3 + pos);
	cout << ">>";

	while (true) {
		// mau me, hoa la he...
		gotoxy(12, 1);
		cout << "~~~";
		gotoxy(12, 1);
		Sleep(50);
		cout << "   ";
		gotoxy(54, 1);
		cout << "~~~";
		gotoxy(54, 1);
		Sleep(50);
		cout << "   ";

		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();

			switch (kb_hit) {
				case KEY_UP:
					// xoa muc truoc
					gotoxy(xDisplayDMS[0] + 1, yDisplay + 3 + pos);
					cout << "  ";
					gotoxy(xDisplayDMS[0] + 10, yDisplay + 3 + pos);
					cout << "  ";
					(pos > 0) ? pos-- : pos = 28;

					// to mau muc moi
					gotoxy(xDisplayDMS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDMS[0] + 10, yDisplay + 3 + pos);
					cout << ">>";
					break;

				case KEY_DOWN:

					// xoa muc truoc
					gotoxy(xDisplayDMS[0] + 1, yDisplay + 3 + pos);
					cout << "  ";
					gotoxy(xDisplayDMS[0] + 10, yDisplay + 3 + pos);
					cout << "  ";
					(pos < 28) ? pos++ : pos = 0;

					// to mau muc moi
					gotoxy(xDisplayDMS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDMS[0] + 10, yDisplay + 3 + pos);
					cout << ">>";
					break;

				case PAGE_UP:
					if (tttrang > 1) {
						tttrang--;
					} else {
						tttrang = tongtrang;
					}
					Xoa_OutDMS_29lines();
					OutputDMS_PerPage(pDS, tttrang);

					pos = 0;
					SetColor(LIGHT_GREEN);
					gotoxy(xDisplayDMS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDMS[0] + 10, yDisplay + 3 + pos);
					cout << ">>";
					break;

				case PAGE_DOWN:
					if (tttrang <  tongtrang) {
						tttrang++;
					} else {
						tttrang = 1;
					}
					Xoa_OutDMS_29lines();
					OutputDMS_PerPage(pDS, tttrang);
					pos = 0;
					SetColor(LIGHT_GREEN);
					gotoxy(xDisplayDMS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDMS[0] + 10, yDisplay + 3 + pos);
					cout << ">>";
					break;

				case ENTER:
					return (pos == 0 && tttrang == 1) ? pos : pos + (tttrang - 1)* NUMBER_LINES;

				case ESC:
					return -1;
			}
		}
		ShowCur(false);
		gotoxy(33, 35);
		cout << "Trang " << tttrang << " / " << tongtrang;
	}
}

void Output_DMS(DMS dms) {
	Xoa_OutDMS_1line(locate);
	gotoxy(xDisplayDMS[0] + 3, yDisplay + 3 + locate);
	cout << dms.maSach;
	gotoxy(xDisplayDMS[1] + 1, yDisplay + 3 + locate);
	if (dms.trangThaiSach == 0) {
		cout << "Cho Muon Duoc";
	} else if (dms.trangThaiSach == 1) {
		cout << "Da Cho Muon";
	} else if (dms.trangThaiSach == 2) {
		cout << "Da Thanh Ly";
	}
	gotoxy(xDisplayDMS[2] + 10, yDisplay + 3 + locate);
	cout << dms.viTri;
	locate++;
}

void OutputDMS_PerPage(pDauSach pDS, int index) {
	Xoa_OutDMS_29lines();
	locate = 0;
	if (pDS->pListDMS.headLDMS == NULL && pDS->pListDMS.tailLDMS == NULL)
		return;
	index--;
	index *= NUMBER_LINES;
	int count = 0;
	Node_DMS * temp = NULL;
	for ( temp = pDS->pListDMS.headLDMS ; temp != NULL  && count < index ; temp = temp->nextNDMS) {
		count++;
	}
	for (int i = 0; i < NUMBER_LINES && temp != NULL; i++) {
		Output_DMS(temp->info);
		temp = temp->nextNDMS;
	}
	return;
}

void Output_ListDMS(pDauSach &pDS) {
	// thu tu trang
	clrscr();
	int check1;
	int check2;
	int check3;
	int tttrang, tongtrang;
	tttrang = 1;
	tongtrang = ((pDS->pListDMS.n + 1 ) / NUMBER_LINES) + 1;
	Node_DMS* temp = NULL, *temp1 = NULL;
	gotoxy(8, 1);
	cout << " BANG DANH MUC SACH CUA DAU SACH : " << pDS->tenSach;
label:
	DisplayDMS(keyDisplayDMS, 3, xDisplayDMS);
	OutputDMS_PerPage(pDS, tttrang);
	string keySearch = "";
	int kb_hit;
	do {
		XoaMotVung(65,2,  30, 67);
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit) {
				case PAGE_UP:
					(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
					OutputDMS_PerPage(pDS, tttrang);
					break;
				case PAGE_DOWN:
					(tttrang <  tongtrang) ? tttrang++ : tttrang = 1;
					OutputDMS_PerPage(pDS, tttrang);
					break;
				case  KEY_F3:
					Beep(600, 100);
					VeHinhBangNhap(82, 3, 38, " HAY NHAP VAO MA SACH CAN HIEU CHINH");
					gotoxy(96, 5);
					check1 = NhapMaDauSach(keySearch);
					// kiem tra dieu kien tra ve .....
					if (check1 == -1) {
						gotoxy(84, Y_NOTIFY + 12);
						cout << "BAN VUA HUY TAC VU HIEU CHINH !!!";
						_getch();
					} else if (check1 == 1) {
						temp = Search_DMS1(pDS, keySearch);
						if (temp == NULL) {
							gotoxy(77, Y_NOTIFY + 12);
							cout << "BAN VUA NHAP MA SACH " << "'" << keySearch << "'" << " KHONG CO TRONG DU LIEU";
							_getch();
						} else {
							check3 = SuaDanhMucSach(pDS, temp);
							// kiem tra cac truong hop.
							if (check3 == 1) {
								gotoxy(73, Y_NOTIFY + 12);
								cout << "BAN VUA HIEU CHINH THONG TIN SACH CO MA SACH LA: " << keySearch;
								_getch();
							} else if (check3 == 2) {
								gotoxy(73, Y_NOTIFY + 12);
								cout << "Sach da co Doc Gia muon nen khong duoc phep hieu chinh !";
								_getch();
								gotoxy(73, Y_NOTIFY + 12);
								cout << "                                                        ";
							} else {
								gotoxy(82, Y_NOTIFY + 12);
								cout << "BAN VUA HUY TAC VU HIEU CHINH !!!";
								_getch();
							}
						}
					}
					goto label;
				case KEY_F4:
					Beep(600, 100);
					VeHinhBangNhap(82, 3, 35,  "     HAY NHAP VAO MA SACH DE XOA   ");
					gotoxy(96, 5);
					check1 = NhapMaDauSach(keySearch);
					// kiem tra dieu kien tra ve .....
					if (check1 == -1) {
						gotoxy(88, 10);
						cout << "BAN VUA HUY TAC VU XOA !!!";
						_getch();
					} else if (check1 == 1) {
						temp1 = Search_DMS1(pDS, keySearch);
						// da co doc gia muon.
						if (temp1->info.trangThaiSach == 1) {
							gotoxy(78, 20);
							cout << "Sach da co Doc Gia muon nen khong duoc phep xoa !";
							_getch();
							gotoxy(78, 20);
							cout << "                                                      ";
						} else {
							check2 = delete_Key(pDS, keySearch);
							if (check2 == -1) {
								gotoxy(75, 10);
								cout << "BAN VUA NHAP MA SACH " << "'" << keySearch << "'" << " KHONG CO TRONG DU LIEU";
								_getch();
							} else if (check2 == 1) {
								gotoxy(82, 10);
								cout << "BAN VUA XOA SACH CO MA SACH LA: " << keySearch;
								_getch();
							}
						}
					}
					goto label;
				case ESC:
					Beep(600, 100);
					return;
			}
		}
		ShowCur(false);
		gotoxy(3, 35);
		cout << "HotKey:  F3 - Hieu chinh , F4 - Xoa , ESC - Thoat";
		gotoxy(54, 35);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}

void NhapDanhMucSach(pDauSach &pDS, int sosach) {
	clrscr();
	system("color 3E");;
	int check1 = 0 ;
	gotoxy(39, 2);
	cout << "BAN DANG NHAP THONG TIN VAO DANH MUC SACH CUA DAU SACH : " << pDS->tenSach;
	gotoxy(60, 16);
	cout << "SO SACH CAN NHAP: " << sosach << endl;
	gotoxy(51, 17);
	cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	gotoxy(52, 31);
	cout << " HotKey:   F10 - Luu ,  ESC - Thoat ";
	// nhap sach theo so sach da cho truoc
	for (int i = 0; i < sosach && check1 != -1; i++) {
		// nhap sach
		check1 = NhapSach(pDS);
		XoaMotVung(38, yDisplay + 2, 10, (int)keyBangNhapDanhMucSach[0].length());
		gotoxy(60, 18);
		cout << "SO SACH DA NHAP : " << i + 1;
	}
	Output_ListDMS(pDS);
}

void Menu_DMS(List_DauSach &lDS) {
	system("color 3E");
	int choose;
	int nDS = lDS.n + 1;
	int tttrang, tongtrang;
	tttrang = 1;
	tongtrang = (nDS / NUMBER_LINES) + 1;
	int temp = 1;

	do {
		clrscr();

		// hien thi bang chua thong tin dau sach
		DisplayDS(keyDisplayDS, 6, xDisplayDS);
		OutputDS_PerPage(lDS, tttrang);

		gotoxy(23, 1);
		SetBGColor(GREEN);
		cout << "CHON DAU SACH DE CAP NHAT DANH MUC SACH";
		normalBGColor();

		// chon dau sach muon nhap sach vao
		choose = ChooseItems(lDS, tttrang, tongtrang);

		// check cac truong hop ...
		if (choose == -1) {
			return ;
		} else if (choose > lDS.n) {

			// xem thử chỗ đầu sách có quay lại ngay cái trang hầu nảy luôn kko
			gotoxy( 2 , yDisplay + 3 + choose % NUMBER_LINES);
			cout << setw(27) << setfill(' ') << ' ';
			continue;
		}

		if (lDS.nodesDS[choose]->pListDMS.headLDMS != NULL   && lDS.nodesDS[choose]->pListDMS.n == - 1) {
			continue;
		}

		// chon so sach nhap
		int sosach = ChonSoSachNhap();
		if (sosach == -1) {
			XoaMotVung(81, 3, 20, 50);
			continue ;
		} else {
			// bat dau nhap thong tin sach
			NhapDanhMucSach(lDS.nodesDS[choose], sosach);
		}
	} while (true);
}

int TongSoSachDuocMuon(ListDMS dms) {
	int dem = 0;
	Node_DMS *temp = NULL;
	for (temp = dms.headLDMS; temp != NULL; temp = temp->nextNDMS) {
		//  tinh ca sach da muon va da muon nhung lam mat.
		if (temp->info.trangThaiSach == 1   ||  temp->info.trangThaiSach == 2) {
			dem++;
		}
	}
	return dem;
}

void Sort_Top10(Top *top10, int q, int r) {
	Top temp;
	int i = q;
	int j = r;
	//Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
	int x = top10[(q + r) / 2].soSachMuon;

	do {
		// Phân đoạn dãy con a[q],..., a[r]
		while (top10[i].soSachMuon > x)
			i++; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x
		while (top10[j].soSachMuon < x)
			j--; //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

		if (i <= j) { // Hoan vi
			temp = top10[i];
			top10[i] = top10[j];
			top10[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (q<j) 	// phần thứ nhất có từ 2 phần tử trở lên
		Sort_Top10(top10, q, j);
	if (i < r)   	// phần thứ ba có từ 2 phần tử trở lên
		Sort_Top10(top10, i, r);
}

void Top10Sach(List_DauSach lDS) {
	system("color 3E");
	clrscr();
	int count = 0;
	Top *top10 = new Top[lDS.n + 1];

	// nhap thong tin vao mang.
	for (int i = 0; i <= lDS.n; i++) {
		top10[i].tenSach = lDS.nodesDS[i]->tenSach;
		top10[i].soSachMuon = TongSoSachDuocMuon(lDS.nodesDS[i]->pListDMS);
	}
	Sort_Top10(top10, 0, lDS.n);
	// in thong tin ra  console
	gotoxy(50, 2);
	SetBGColor(GREEN);
	cout << "TOP 10 DAU SACH CO SO LUOC MUON NHIEU NHAT ";
	normalBGColor();
	int j = 0;
	while (top10[j].soSachMuon != 0 && j < 10   ||  top10[j].soSachMuon == top10[j + 1].soSachMuon  && top10[j].soSachMuon != 0) {
		SetColor(WHITE);
		gotoxy(xDisplayTop10[1] + 3, yDisplayTop10 + 2 + j);
		cout << top10[j].tenSach;
		gotoxy(xDisplayTop10[2] + 16, yDisplayTop10 + 2 + j);
		cout << top10[j].soSachMuon;
		gotoxy(xDisplayTop10[0] + 7, yDisplayTop10 + 2 + j);
		j++;
		cout << j;
	}
	DisplayTop10(keyDisplayTop10, 3, xDisplayTop10, j + 2);
	_getch();
	// xoa vung nho....
	delete[] top10;
}
