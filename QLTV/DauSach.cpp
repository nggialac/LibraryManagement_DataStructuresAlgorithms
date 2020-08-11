#include "DauSach.h"

int checkEmpty_DauSach(List_DauSach listDS) {
	return listDS.n == -1;
}

int checkFull_DauSach(List_DauSach listDS) {
	return listDS.n == MAX_LIST_DAUSACH;
}

int themDauSach(List_DauSach &listDS,  pDauSach &pDS) {
	if (checkFull_DauSach(listDS)) {
		return 0;
	}
	listDS.nodesDS[++listDS.n] = pDS;
	return 1;
}

void xoaDauSach_ViTri(List_DauSach &listDS, int viTri) {
	if (viTri > listDS.n  || checkEmpty_DauSach(listDS)  ||  checkFull_DauSach(listDS) || viTri < 0) {
		return;
	}
	// xoa vi tri cuoi mang
	if (viTri == listDS.n) {
		delete listDS.nodesDS[listDS.n];
		listDS.nodesDS[listDS.n--] = NULL; //*
		return;
	}
	// ***NOTE
	delete listDS.nodesDS[viTri];
	for (int temp = viTri + 1; temp <= listDS.n; temp++) {
		listDS.nodesDS[temp - 1] = listDS.nodesDS[temp];
	}
	delete listDS.nodesDS[listDS.n--];//*
	listDS.nodesDS[listDS.n--] = NULL;
	return;
}

bool searchDauSach_ISBN(List_DauSach listDS, string ISBN) {
	for (int i = 0; i < listDS.n; i++) {
		if (listDS.nodesDS[i]->ISBN == ISBN)
			return true;
	}
	return false;
}

pDauSach layDauSach_Ten(List_DauSach listDS, string tenSach) {
	pDauSach temp = NULL;
	for (int i = 0; i <= listDS.n; i++) {
		temp = listDS.nodesDS[i];
		if (temp->tenSach == tenSach)
			return temp;
	}
	return NULL;
}

List_DauSach layDauSach_TheLoai(List_DauSach &listDS, string theLoai) {
	List_DauSach listDSTemp;
	listDSTemp.n = 0;
	for (int i = 0; i < listDS.n; i++) {
		if (listDS.nodesDS[i]->theLoai == theLoai) {
			listDSTemp.nodesDS[listDSTemp.n] = listDS.nodesDS[i];
			listDSTemp.n++;
		}
	}
	return listDSTemp;
}

string getString(string a) {
	for (int i = 0; i < (int)a.length(); i++) {
		if (a[i] == ' ') {
			a.erase(i, 1);
			i--;
		}
	}
	return a;
}

//Sap xep Dau Sach
//COI LAI?
void swap_DS(pDauSach ds1, pDauSach ds2) {
	DauSach temp = *ds1;
	*ds1 = *ds2;
	*ds2 = temp;
}

void quickSortDS(List_DauSach &listDS, int left, int right) {
	dauSach key = *(listDS.nodesDS[(left + right) / 2]);
	dauSach tempDS;
	int i = left, j = right;
	do {
		while ((string)listDS.nodesDS[i]->tenSach < (string)key.tenSach)
			i++;
		while ((string)listDS.nodesDS[j]->tenSach > (string)key.tenSach)
			j--;
		if (i <= j) {
			if (i < j) {
				swap_DS(listDS.nodesDS[i], listDS.nodesDS[j]);
			}
			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) quickSortDS(listDS, left, j);
	if (right > i) quickSortDS(listDS, i, right);
}

void Update_DauSach(List_DauSach &lDS, pDauSach &pDS, bool isEdited) {
	dauSach info;
	// hien con tro nhap
	ShowCur(true);
	normalBGColor();

	int nngang = (int)keyBangNhapDauSach[0].length();
	// cac flag 
	int ordinal = 0;
	bool isSave = false;
	bool isEscape = false;

	// temp
	string tensach = "";
	string ISBN = "";
	string tacgia = "";
	string theloai = "";
	int sotrang = 0;
	int namXB = 0;

	CreateBox(X_NOTIFY + 7, Y_NOTIFY, "NOTI:  ", 52);
	BangNhap(79, yDisplay, nngang, keyBangNhapDauSach, 14);
	BangGuides(79, yDisplay + 20, nngang, keyGuide2, 7);
	if (isEdited) {
		tensach = pDS->tenSach;
		ISBN = pDS->ISBN;
		tacgia = pDS->tacGia;
		theloai = pDS->theLoai;
		sotrang = pDS->soTrang;
		namXB = pDS->namXB;

		gotoxy(80 + (nngang / 3), yDisplay + 3);
		cout << tensach;
		gotoxy(80 + (nngang / 3), yDisplay + 5);
		cout << ISBN;
		gotoxy(80 + (nngang / 3), yDisplay + 7);
		cout << tacgia;
		gotoxy(80 + (nngang / 3), yDisplay + 9);
		cout << theloai;
		gotoxy(80 + (nngang / 3), yDisplay + 11);
		cout << sotrang;
		gotoxy(80 + (nngang / 3), yDisplay + 13);
		cout << namXB;
	}
	while (true) {
		switch (ordinal) {
			case 0:
				gotoxy(80 + (nngang / 3), yDisplay + 3);
				NhapTenSach(tensach, ordinal, isSave, isEscape);
				break;
			case 1:
				gotoxy(80 + (nngang / 3), yDisplay + 5);
				NhapISBN(ISBN, ordinal, isSave, isEscape);
				break;
			case 2:
				gotoxy(80 + (nngang / 3), yDisplay + 7);
				NhapTenTacGia(tacgia, ordinal, isSave, isEscape);
				break;
			case 3:
				gotoxy(80 + (nngang / 3), yDisplay + 9);
				NhapTheLoaiSach(theloai, ordinal, isSave, isEscape);
				break;
			case 4:
				gotoxy(80 + (nngang / 3), yDisplay + 11);
				nhapSoTrang(sotrang, ordinal, isSave, isEscape);
				break;
			case 5:
				gotoxy(80 + (nngang / 3), yDisplay + 13);
				NhapNamXuatBan(namXB, ordinal, isSave, isEscape);
				break;
		}
		// check Save
		if (isSave) {
			// cap nhat lai flag
			isSave = false;
			// check rong;
			if (tensach.length() == 0) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 0;
				continue;
			} else if (ISBN.length() == 0) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 1;
				continue;
			} else if (tacgia.length() == 0) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 2;
				continue;
			} else if (theloai.length() == 0) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 3;
				continue;
			} else if (sotrang == 0) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!! ";
				normalBGColor();
				// quay lai va dien vao truong du lieu do
				ordinal = 4;
				continue;
			} else if (namXB == 0) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CAC TRUONG DU LIEU KHONG DUOC DE TRONG !!!";
				normalBGColor();
				ordinal = 5;
				continue;
			} else if (namXB > (int)layNamHT()) {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "NAM XUAT BAN KHONG LON HON NAM HIEN TAI !!!";
				normalBGColor();
				ordinal = 5;
				continue;
			}
			if (searchDauSach_ISBN(lDS, ISBN)) {
				if (pDS->ISBN != ISBN) {
					gotoxy(X_NOTIFY + 15, Y_NOTIFY);
					SetColor(BLUE);
					cout << "ISBN VUA NHAP VAO TRUNG VOI ISBN DA CO  !!!";
					normalBGColor();
					// quay lai va dien vao truong du lieu do
					ordinal = 1;
					continue;
				}
			}
			// import data vao info
			info.tenSach = ChuanHoaString(tensach);
			info.ISBN = ChuanHoaString(ISBN);
			info.tacGia = ChuanHoaString(tacgia);
			info.theLoai = ChuanHoaString(theloai);
			info.soTrang = sotrang;
			info.namXB = namXB;
			if (isEdited) {
				//	pDS->info = info;//
				pDS->tenSach = info.tenSach;
				pDS->ISBN = info.ISBN;
				pDS->tacGia = info.tacGia;
				pDS->theLoai = info.theLoai;
				pDS->soTrang = info.soTrang;
				pDS->namXB = info.namXB;
				normalBGColor();
				return;
			} else {
				// gan NULL cho con tro trong DS
				initList_DMS(pDS->pListDMS);
				initList_DMS(pDS->pListDMS);
				//pDS->info = info;
				pDS->tenSach = info.tenSach;
				pDS->ISBN = info.ISBN;
				pDS->tacGia = info.tacGia;
				pDS->theLoai = info.theLoai;
				pDS->soTrang = info.soTrang;
				pDS->namXB = info.namXB;
				int temp = themDauSach(lDS, pDS);
				if (temp == 0) {
					// thong bao ra.
					for (int i = 0; i < 5; i++) {
						SetColor(BLUE);
						gotoxy(X_NOTIFY + 15, Y_NOTIFY);
						Sleep(100);
						cout << "BO NHO DA DAY .KHONG THEM DAU SACH MOI VAO DUOC !";
					}
				} else {
					// In dong thong bao .
					for (int i = 0; i < 5; i++) {
						SetColor(BLUE);
						gotoxy(X_NOTIFY + 15, Y_NOTIFY);
						Sleep(100);
						cout << "           SUCCESSFULLY !!! ";
					}
				}
				normalBGColor();
				return;
			}
		}
		// thoat
		if (isEscape) {
			return;
		}
	}
	ShowCur(false);
}

int ChooseItems_DS(List_DauSach &lDS, int &tttrang, int tongtrang) {
	int pos = 0;
	int kb_hit;
	pos = 0;
	SetColor(LIGHT_GREEN);
	gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
	cout << "<<";
	gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
	cout << ">>";
	while (true) {
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
					Xoa_OutDS_29lines();
					OutputDS_PerPage(lDS, tttrang);
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
					Xoa_OutDS_29lines();
					OutputDS_PerPage(lDS, tttrang);
					pos = 0;
					SetColor(LIGHT_GREEN);
					gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + pos);
					cout << "<<";
					gotoxy(xDisplayDS[0] + 26, yDisplay + 3 + pos);
					cout << ">>";
					break;
				case ENTER:
					return (pos == 0 && tttrang == 1) ? pos : pos + (tttrang - 1)* NUMBER_LINES;
			}
		}
		ShowCur(false);
		SetColor(WHITE);
		gotoxy(33, 36);
		cout << "Trang " << tttrang << " / " << tongtrang;
		normalBGColor();
	}
}

void Xoa_OutDS_1line(int locate) {
	gotoxy(xDisplayDS[0] + 1, yDisplay + 3 + locate);
	cout << setw(27) << setfill(' ') << ' ';
	gotoxy(xDisplayDS[1] + 1, yDisplay + 3 + locate);
	cout << setw(6) << setfill(' ') << ' ';
	gotoxy(xDisplayDS[2] + 1, yDisplay + 3 + locate);
	cout << setw(18) << setfill(' ') << ' ';
	gotoxy(xDisplayDS[3] + 1, yDisplay + 3 + locate);
	cout << setw(11) << setfill(' ') << ' ';
	gotoxy(xDisplayDS[4] + 1, yDisplay + 3 + locate);
	cout << setw(6) << setfill(' ') << ' ';
	gotoxy(xDisplayDS[5] + 1, yDisplay + 3 + locate);
	cout << setw(4) << setfill(' ') << ' ';
}

void Xoa_OutDS_29lines() {
	for (int i = 0; i <NUMBER_LINES; i++) {
		Xoa_OutDS_1line(i);
	}
}

void Output_DS(string tenSach, string ISBN, string tacGia, string theLoai, int soTrang, int namXB) {
	ShowCur(false);
	Xoa_OutDS_1line(locate);
	gotoxy(xDisplayDS[0] + 3, yDisplay + 3 + locate);
	cout << tenSach;
	gotoxy(xDisplayDS[1] + 1, yDisplay + 3 + locate);
	cout << ISBN;
	gotoxy(xDisplayDS[2] + 1, yDisplay + 3 + locate);
	cout << tacGia;
	gotoxy(xDisplayDS[3] + 1, yDisplay + 3 + locate);
	cout << theLoai;
	gotoxy(xDisplayDS[4] + 1, yDisplay + 3 + locate);
	cout << soTrang;
	gotoxy(xDisplayDS[5] + 1, yDisplay + 3 + locate);
	cout << namXB;
	locate++;
}

void OutputDS_PerPage(List_DauSach &lDS, int index) {
	Xoa_OutDS_29lines();
	SetColor(WHITE);
	locate = 0;
	index--;
	if (lDS.n == -1)
		return;
	for (int i =  NUMBER_LINES * index;  i < NUMBER_LINES*( 1 + index)  && i <= lDS.n ; i++) {
		Output_DS(lDS.nodesDS[i]->tenSach, lDS.nodesDS[i]->ISBN, lDS.nodesDS[i]->tacGia, lDS.nodesDS[i]->theLoai, lDS.nodesDS[i]->soTrang, lDS.nodesDS[i]->namXB);
	}
}

void Output_ListDStheoTT(List_DauSach lDS) {
	system("color 0");
	clrscr();
	normalBGColor();
	//selectionSort_DS(lDS);
	quickSortDS(lDS, 0, lDS.n);
	DisplayDS(keyDisplayDS, 6, xDisplayDS);
	normalBGColor();
	gotoxy(10, 1);
	cout << "BANG THONG TIN CAC DAU SACH THEO THU TU TEN SACH TANG DAN";
	int nDS = lDS.n + 1;
	int tttrang, tongtrang;
	tttrang = 1;
	tongtrang = (nDS / NUMBER_LINES) + 1;
	OutputDS_PerPage(lDS, tttrang);

	int check;
	pDauSach temp;
	string tensach = "";

	int kb_hit;
	do {
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit) {
				case PAGE_UP:
					(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
					OutputDS_PerPage(lDS, tttrang);
					break;
				case PAGE_DOWN:
					(tttrang <  tongtrang) ? tttrang++ : tttrang = 1;
					OutputDS_PerPage(lDS, tttrang);
					break;
				case KEY_F9:
					VeHinhBangNhap(82, 3,50, "         HAY NHAP VAO TEN SACH CAN TRA CUU");
					gotoxy(92, 5);
					check = NhapTenSachTimKiem(tensach);
					// kiem tra dieu kien tra ve .....
					if (check == -1) {
						gotoxy(92, 10);
						cout << "BAN VUA HUY TAC VU TRA CUU !!!";
						_getch();
						return;
					} else if (check == 1) {
						temp = layDauSach_Ten(lDS, tensach);
						if (temp == NULL) {
							gotoxy(86, 10);
							cout << "TEN SACH VUA NHAP KHONG CO TRONG THU VIEN !!!";
							_getch();
							XoaMotVung(82, 1, 35, 50);
						} else {
							SetBGColor(2);
							gotoxy(93, 8);
							cout << "THONG TIN TRA CUU DUOC !";
							gotoxy(82, 10);
							cout << setw(50) << setfill('-') << "-";
							gotoxy(82, 12);
							cout << setw(50) << setfill('-') << "-";
							gotoxy(82, 14);
							cout << setw(50) << setfill('-') << "-";
							gotoxy(82, 16);
							cout << setw(50) << setfill('-') << "-";
							gotoxy(82, 18);
							cout << setw(50) << setfill('-') << "-";
							gotoxy(82, 20);
							cout << setw(50) << setfill('-') << "-";
							gotoxy(82, 22);
							cout << setw(50) << setfill('-') << "-";
							gotoxy(82, 24);
							cout << setw(50) << setfill('-') << "-";
							normalBGColor();
							gotoxy(82, 11);
							cout << "TEN SACH: " << temp->tenSach;
							gotoxy(82, 13);
							cout << "TAC GIA: " << temp->tacGia;
							gotoxy(82, 15);
							cout << "THE LOAI: " << temp->theLoai;
							gotoxy(82, 17);
							cout << "NAM XUAT BAN: " << temp->namXB;
							gotoxy(82, 19);
							cout << "ISBN: " << temp->ISBN;
							gotoxy(82 ,21);
							cout << "TONG SO SACH CUA DAU SACH: " << temp->pListDMS.n;
							gotoxy(82, 23);
							cout << "SO SACH CON TRONG THU VIEN:  " << temp->pListDMS.n - TongSoSachDuocMuon(temp->pListDMS);
							gotoxy(82, 25);
							cout << "CAC MA SACH CON CO TRONG THU VIEN: ";
							// thuc hien in ma sach ra theo dung format.
							int i = 0, j = 0, count = 0;
							for (Node_DMS* p = temp->pListDMS.headLDMS; p != NULL; p = p->nextNDMS) {
								gotoxy(82 + i, 26 + j);
								if (p->info.trangThaiSach == 0) {
									cout << p->info.maSach;
									i += 10;
									count++;
									if (count == 5) {
										j++;
										i = 0;
										count = 0;
									}
								}
							}
							_getch();
							XoaMotVung(82, 1, 35, 50);
						}
					}
					break;
					// thoat
				case ESC:
					return ;
			}
		}
		ShowCur(false);
		gotoxy(2, 35);
		cout << "HotKey: PgUp, PgDn, ESC,      F9  -  TIM THONG TIN SACH ";
		gotoxy(68, 35);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}

void Menu_DauSach(List_DauSach &lDS) {
	system("color 0");
	clrscr();
	gotoxy(35, 1);
	cout << "CAP NHAT DAU SACH ";
	// nDG la so DG hien co trong danh sach tuyen tinh
	int nDS = lDS.n + 1;
	int choose;
	pDauSach pDS;
	gotoxy(3, yHotkey);
	SetColor(WHITE);
	cout << "HotKey:  ESC - Thoat, F2 - Them, F3 - Sua, F4 - Xoa, F10 - Luu, PgUP, PgDn";
	normalBGColor();
	// thu tu trang
	int tttrang, tongtrang;
	tttrang = 1;
	tongtrang = (nDS / NUMBER_LINES) + 1;
label1:
	XoaMotVung(79, yDisplay, 30, 53);
	DisplayDS(keyDisplayDS, 6, xDisplayDS);
	OutputDS_PerPage(lDS, tttrang);
	int kb_hit;
	do {
		if (_kbhit()) {
			kb_hit = _getch();
			if (kb_hit == 224 || kb_hit == 0)
				kb_hit = _getch();
			switch (kb_hit) {
				case PAGE_UP:
					(tttrang > 1) ? tttrang-- : tttrang = tongtrang;
					OutputDS_PerPage(lDS, tttrang);
					break;
				case PAGE_DOWN:
					(tttrang <  tongtrang) ? tttrang++ : tttrang = 1;
					OutputDS_PerPage(lDS, tttrang);
					break;
				case KEY_F2:
					Beep(600, 100);
					pDS = new dauSach;
					if (pDS == NULL)
						goto label1;
					Update_DauSach(lDS, pDS, false);
					goto label1 ;
				case  KEY_F3:
					Beep(600, 100);
					choose = ChooseItems_DS(lDS, tttrang, tongtrang);
					if (choose > lDS.n)
						goto label1;
					Update_DauSach(lDS, lDS.nodesDS[choose], true);
					goto label1;
				case KEY_F4:
					Beep(600, 100);
					choose = ChooseItems_DS(lDS, tttrang, tongtrang);
					if (choose > lDS.n)
						goto label1;
					// neu co nguoi muon thi se khong duoc phep xoa .
					if (Check_DMS(lDS.nodesDS[choose]->pListDMS.headLDMS)) {
						gotoxy(79,20);
						cout << " Dau Sach da co Doc Gia muon nen khong duoc phep xoa !";
						_getch();
						gotoxy(79, 20);
						cout << "                                                      ";
						goto label1;
					}
					xoaDauSach_ViTri(lDS, choose);
					goto label1;
					// thoat
				case ESC:
					Beep(600, 100);
					return ;
			}
		}
		ShowCur(false);
		gotoxy(33, 36);
		cout << "Trang " << tttrang << " / " << tongtrang;
	} while (true);
}



