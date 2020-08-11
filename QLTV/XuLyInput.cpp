#include "XuLyInput.h"

void xoa(char* s, int vitrixoa) {
	int n = strlen(s);
	for (int i = vitrixoa; i < n; i++)
		s[i] = s[i + 1];
	s[n - 1] = '\0';
}

char* ChuanHoaChar(char* result) {
	for (int i = 0; i < strlen(result); i++)
		if (result[i] == ' '&& result[i + 1] == ' ') {
			xoa(result, i);
			i--;
		}
	if (result[0] == ' ')
		xoa(result, 0);
	if (result[strlen(result) - 1] == ' ')
		xoa(result, strlen(result) - 1);
	return result;
}

char* toCharArray(string str) {
	char* c = new char(str.size() + 1);
	for (int i = 0; i < str.size() + 1; i++)
		c[i] = str[i];
	return c;
}

//CHARACTER
string ChuanHoaString(string result) {
	for (size_t i = 1; i < result.length(); i++) {
		if (result[0] == ' ') {
			result.erase(0, 1);
			i--;
		} else if (result[i - 1] == ' ' && result[i] == ' ') {
			result.erase(i - 1, 1);
			i--;
		} else if (result[result.length() - 1] == ' ') {
			result.erase(result.length() - 1, 1);
		}
	}
	return result;
}

void Nhap(int &result, int choice, int &ordinal, bool &isSave, bool &isEscape) {
	//cout << result;
	int count = 0;
	// giu lai vi tri ban dau
	int x = wherex() - 1, y = wherey() - 1;
	if (choice == 1 && result == 3) {
		result = 1;
		gotoxy(x, y);
		cout << result << ":  HOAT DONG ";
	}
	while (true) {
		while (_kbhit()) {
			int kb_hit = _getch();
			if ((kb_hit == 48 || kb_hit == 49) && count < 1) {
				count++;
				result = kb_hit - 48;
				if (choice == 0) {
					// xoa dong thong bao
					gotoxy(X_NOTIFY + 15, Y_NOTIFY);
					cout << setw(42) << setfill(' ') << " ";
					gotoxy(x, y);
					(result == 0) ? cout << result << ":  NAM" : cout << result << ":  NU    ";
				} else if (choice == 1) {
					// xoa dong thong bao
					gotoxy(X_NOTIFY + 15, Y_NOTIFY);
					cout << setw(42) << setfill(' ') << " ";
					gotoxy(x, y);
					(result == 0) ? cout << result << ":  KHOA      " : cout << result << ":  HOAT DONG ";
				}
			} else if (kb_hit == 224) {
				kb_hit = _getch();
				// cho nay xay ra hai truong hop
				if (choice == 0) {
					if (kb_hit == KEY_UP) {
						ordinal = 1;
						return;
					} else {
						ordinal = 3;
						return;
					}
				} else if (choice == 1) {
					if (kb_hit == KEY_UP) {
						ordinal = 2;
						return;
					} else {
						ordinal = 0;
						return;
					}
				}
			} else if (kb_hit == ENTER) {
				if (choice == 0) {
					ordinal = 3;
					return;
				} else if (choice == 1) {
					ordinal = 0;
					return;
				}
			} else if (kb_hit == BACKSPACE && count > 0) {
				gotoxy(x, y);
				result = 3;
				cout << " " << setw(15) << setfill(' ') << " ";
				count--;
				// chuyen ve vi tri ban dau.
				gotoxy(x, y);
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "BAN HAY NHAP 0 HOAC 1,Backspace DE XOA !!!";
				//normalBGColor();
				SetColor(LIGHT_YELLOW);
				gotoxy(x, y);
			}
		}
	}
}

void NhapTen(string &result, int &ordinal, bool &isSave, bool &isEscape) {
	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	int count = (int)result.length();
	int x, y;
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;

		while (_kbhit()) {
			int kb_hit = _getch();
			// chi nhan chu thuong hoac  chu in hoa.
			// chi nhap ten toi da 7 ky tu, vi tu dai nhat tieng viet chi la 7.
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122)) && count < MAX_TEN) {
				count++;
				// xoa dong thong bao
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				cout << setw(42) << setfill(' ') << " ";
				gotoxy(x, y);
				// chuyen qua in hoa
				kb_hit = toupper((char)kb_hit);
				cout << (char)kb_hit;
				result += (char)kb_hit;
			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 0;
					return;
				} else {
					ordinal = 2;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 2;
				return;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);

			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "TOI DA 7 KY TU, CHI LAY KY TU CHU !!!";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}


void NhapHo(string &result, int &ordinal, bool &isSave, bool &isEscape) {

	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	int count = (int)result.length();
	int x, y;
	// bien co hieu
	int nSpace = 0;
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;
		while (_kbhit()) {
			int kb_hit = _getch();
			// chi nhan chu thuong hoac  chu in hoa va dau cach
			// chi nhap ho toi da 15 ky tu.
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122) || kb_hit == SPACE)
			        && count < MAX_HO && count >= 0) {
				// xoa dong thong bao
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				cout << setw(42) << setfill(' ') << " ";
				gotoxy(x, y);

				if (nSpace == 1 && kb_hit == SPACE) {
					count++;
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 0;
				} else if (kb_hit != SPACE) {
					count++;
					kb_hit = toupper((char)kb_hit);
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 1;
				}

			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 3;
					return;
				} else {
					ordinal = 1;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 1;
				return;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << " TOI DA 16 KY TU, CHI LAY KY TU CHU !!!";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

void NhapTenSach(string &result, int &ordinal, bool &isSave, bool &isEscape) {
	ShowCur(true);
	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	int count = (int)result.length();
	int x, y;
	// bien co hieu
	int nSpace = 0;
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;
		while (_kbhit()) {
			int kb_hit = _getch();

			// chi nhan chu thuong hoac  chu in hoa va dau cach va so
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122)
			        || (kb_hit >=  48 && kb_hit <= 57) || kb_hit == SPACE) && count < MAX_TENSACH && count >= 0) {
				// xoa dong thong bao
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				cout << setw(42) << setfill(' ') << " ";
				gotoxy(x, y);

				if (nSpace == 1 && kb_hit == SPACE) {
					count++;
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 0;
				} else if (kb_hit != SPACE) {
					count++;
					kb_hit = toupper((char)kb_hit);
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 1;
				}

			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 5;
					return;
				} else {
					ordinal = 1;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 1;
				return;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "TOI DA 24 KY TU, GOM KY TU CHU VA SO !!!";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

void NhapTenTacGia(string &result, int &ordinal, bool &isSave, bool &isEscape) {
	ShowCur(true);
	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	int count = (int)result.length();
	int x, y;
	// bien co hieu
	int nSpace = 0;
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;
		while (_kbhit()) {
			int kb_hit = _getch();
			// chi nhan chu thuong hoac  chu in hoa va dau cach
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122) || kb_hit == SPACE)
			        && count < MAX_TENTG && count >= 0) {
				// xoa dong thong bao
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				cout << setw(42) << setfill(' ') << " ";
				gotoxy(x, y);
				if (nSpace == 1 && kb_hit == SPACE) {
					count++;
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 0;
				} else if (kb_hit != SPACE) {
					count++;
					kb_hit = toupper((char)kb_hit);
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 1;
				}
			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 1;
					return;
				} else {
					ordinal = 3;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 3;
				return;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "TOI DA 17 KY TU, CHI LAY KY TU CHU !!!";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

void NhapTheLoaiSach(string &result, int &ordinal, bool &isSave, bool &isEscape) {
	ShowCur(true);
	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	int count = (int)result.length();
	int x, y;
	// bien co hieu
	int nSpace = 0;
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;
		while (_kbhit()) {
			int kb_hit = _getch();
			// chi nhan chu thuong hoac  chu in hoa va dau cach
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122) || kb_hit == SPACE)
			        && count < MAX_THELOAISACH && count >= 0) {
				// xoa dong thong bao
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				cout << setw(42) << setfill(' ') << " ";
				gotoxy(x, y);
				if (nSpace == 1 && kb_hit == SPACE) {
					count++;
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 0;
				} else if (kb_hit != SPACE) {
					count++;
					kb_hit = toupper((char)kb_hit);
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 1;
				}
			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 2;
					return;
				} else {
					ordinal = 4;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 4;
				return;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "TOI DA 11 KY TU, CHI LAY KY TU CHU !!!";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

void nhapSoTrang(int &nTrang, int &ordinal, bool &isSave, bool &isEscape) {
	ShowCur(true);
	// dem so chu so
	// cout << nTrang;
	uint temp = nTrang;
	int count = 0;
	int x, y;
	while (temp != 0) {
		count++;
		temp /= 10;
	}
	if (count) {
		cout << nTrang;
	}
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;
		while (_kbhit()) {
			int kb_hit = _getch();
			if (kb_hit >= 48 && kb_hit <= 57 && count < 6) {

				// xoa dong thong bao
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				cout << setw(42) << setfill(' ') << " ";
				gotoxy(x, y);


				int f = kb_hit - 48;
				cout << f;
				nTrang = nTrang * 10 + (f);
				count++;
			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 3;
					return;
				} else {
					ordinal = 5;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 5;
				return;
			} else if (kb_hit == BACKSPACE && count >0) {
				cout << "\b" << " " << "\b";
				count--;
				nTrang /= 10;
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CHI CHAP NHAN KY TU SO VA CHIEU DAI <= 6 ";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

void NhapNamXuatBan(int &nam, int &ordinal, bool &isSave, bool &isEscape) {
	ShowCur(true);
	// dem so chu so
	uint temp = nam;
	int count =  0;
	int x, y;
	while (temp != 0) {
		count++;
		temp /= 10;
	}
	if (count) {
		cout << nam;
	}
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;
		while (_kbhit()) {
			int kb_hit = _getch();
			if (kb_hit >= 48 && kb_hit <= 57 && count <= 3) {
				// xoa dong thong bao
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				cout << setw(42) << setfill(' ') << " ";
				gotoxy(x, y);
				int f = kb_hit - 48;
				cout << f;
				nam = nam * 10 + (f);
				count++;
			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {

					ordinal = 4;
					return;
				} else {
					ordinal = 0;
					return;
				}
			} else if (kb_hit == ENTER) {

				ordinal = 0;
				return;
			} else if (kb_hit == BACKSPACE && count >0) {
				cout << "\b" << " " << "\b";
				count--;
				nam /= 10;
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "CHI CHAP NHAN KY TU SO VA CHIEU DAI <= 4";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

void NhapISBN(string &result, int &ordinal, bool &isSave, bool &isEscape) {
	ShowCur(true);
	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	int count = (int)result.length();
	int x, y;
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;
		while (_kbhit()) {
			int kb_hit = _getch();
			// chi nhan chu thuong hoac  chu in hoa.
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122)) && count < MAX_ISBN) {
				count++;
				// xoa dong thong bao
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				cout << setw(42) << setfill(' ') << " ";
				gotoxy(x, y);

				// chuyen qua in hoa
				kb_hit = toupper((char)kb_hit);
				cout << (char)kb_hit;
				result += (char)kb_hit;
			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 0;
					return;
				} else {
					ordinal = 2;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 2;
				return;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);

			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(X_NOTIFY + 15, Y_NOTIFY);
				SetColor(BLUE);
				cout << "TOI DA 6 KY TU, CHI LAY KY TU CHU !!!";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

int  ChonSoSachNhap() {
	int soluong = 3;
	gotoxy(104, 5);
	cout << soluong;

	SetBGColor(4);

	SetColor(BRIGHT_WHITE);
	gotoxy(88, 3);
	cout << "SO LUONG SACH CAN NHAP HIEN TAI  ";
	gotoxy(81, 7);

	SetColor(LIGHT_GREEN);
	cout << "<- Left arrow (-)             ";
	SetColor(LIGHT_GREEN);
	cout << "(+) Right arrow ->";
	SetBGColor(BLUE);
	gotoxy(88, 9);
	cout << "    (Press ENTER to continue)    ";
	normalBGColor();
	while (true) {
		while (_kbhit()) {
			int kb_hit = _getch();
			if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_RIGHT) {
					soluong++;
					gotoxy(104, 5);
					cout << "                    ";
					SetColor(BRIGHT_WHITE);
					gotoxy(104, 5);
					cout << soluong ;

				} else if (kb_hit == KEY_LEFT) {

					if (soluong >= 2) {
						soluong--;
						gotoxy(104, 5);
						cout << "                    ";
						SetColor(BRIGHT_WHITE);
						gotoxy(104, 5);
						cout << soluong;
					}
				}

			} else if (kb_hit == ENTER) {
				return soluong;
			} else if (kb_hit == ESC) {
				return -1;
			}
		}
	}
}

void NhapTrangThaiSach(int &result, int &ordinal, bool &isSave, bool &isEscape, int a, int b) {
	gotoxy(a, b);
	ShowCur(true);
	int count = 0;

	int x = wherex() - 1, y = wherey() - 1;
	if ( result == 3) {
		result = 0;
		gotoxy(x, y);
		cout << result << ":  CHO MUON DUOC ";
	}
	while (true) {
		while (_kbhit()) {
			int kb_hit = _getch();
			if ((kb_hit == 48 || kb_hit == 49 || kb_hit == 50) && count < 1) {
				count++;
				result = kb_hit - 48;
				// xoa dong thong bao
				gotoxy(a - 7, Y_NOTIFY + 2);
				cout << setw(49) << setfill(' ') << " ";
				gotoxy(x, y);
				if (result == 0)
					cout << result << ":   CHO MUON DUOC ";
				else if (result == 1)
					cout << result << ":   DA DUOC MUON  ";
				else if (result == 2)
					cout << result << ":   DA THANH LY   ";

			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 2;
					return;
				} else {
					ordinal = 2;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 2;
				return;
			} else if (kb_hit == BACKSPACE && count > 0) {
				gotoxy(x, y);
				result = 3;
				cout << " " << setw(17) << setfill(' ') << " ";
				count--;
				// chuyen ve vi tri ban dau.
				gotoxy(x, y);
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else {
				gotoxy(a - 7, Y_NOTIFY + 2);
				SetColor(BLUE);
				cout << "BAN HAY NHAP 0, 1, 2, HOAC Backspace DE XOA !!!";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

void NhapViTri(string &result, int &ordinal, bool &isSave, bool &isEscape, int a, int b) {
	gotoxy(a, b);
	ShowCur(true);
	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	int count = (int)result.length();
	int x, y;
	// bien co hieu
	int nSpace = 0;
	while (true) {
		x = wherex() - 1;
		y = wherey() - 1;
		while (_kbhit()) {
			int kb_hit = _getch();
			// chi nhan chu thuong hoac  chu in hoa va dau cach, dau phay, va so.
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122) || (kb_hit >= 48 && kb_hit <= 57 )
			        || kb_hit == SPACE || kb_hit == 44) && count < MAX_TENTG && count >= 0) {
				// xoa dong thong bao
				gotoxy(a - 7, Y_NOTIFY + 2);
				cout << setw(48) << setfill(' ') << " ";
				gotoxy(x, y);
				// chuan hoa khoang trong
				if (nSpace == 1 && kb_hit == SPACE) {
					count++;
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 0;
				} else if (kb_hit != SPACE) {
					count++;
					kb_hit = toupper((char)kb_hit);
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 1;
				}
			} else if (kb_hit == 224) {
				kb_hit = _getch();
				if (kb_hit == KEY_UP) {
					ordinal = 1;
					return;
				} else {
					ordinal = 1;
					return;
				}
			} else if (kb_hit == ENTER) {
				ordinal = 1;
				return;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {
					isSave = true;
					return;
				}
			} else if (kb_hit == ESC) {
				isEscape = true;
				return;
			} else { // check vi tri a ne.
				gotoxy(a - 7 , Y_NOTIFY + 2);
				SetColor(BLUE);
				cout << "TOI DA 17  KY TU, BAO GOM CHU, SO VA DAU PHAY !";
				normalBGColor();
				gotoxy(x, y);
			}
		}
	}
}

int  NhapMaDauSach(string &result) {
	ShowCur(true);
	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	int count = (int)result.length();
	while (true) {
		while (_kbhit()) {
			int kb_hit = _getch();
			// chi nhan chu thuong hoac  chu in hoa va so
			// chi nhap ten toi da 7 ky tu, vi tu dai nhat tieng viet chi la 7.
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122) || (kb_hit >= 48 && kb_hit <= 57)
			        || kb_hit == 44) && count <= 10 && count >= 0) {
				count++;
				// chuyen qua in hoa
				kb_hit = toupper((char)kb_hit);
				cout << (char)kb_hit;
				result += (char)kb_hit;
			} else if (kb_hit == ENTER) {
				return 1 ;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);

			} else if (kb_hit == ESC) {
				return  -1;
			}
		}
	}
}

int  NhapTenSachTimKiem(string &result) {
	ShowCur(true);
	// bien dem so chu da duoc nhap vao cho result
	cout << result;
	// bien co hieu
	int nSpace = 0;
	int count = (int)result.length();
	while (true) {
		while (_kbhit()) {
			int kb_hit = _getch();
			// chi nhan chu thuong hoac  chu in hoa va dau cach va so
			if (((kb_hit >= 65 && kb_hit <= 90) || (kb_hit >= 97 && kb_hit <= 122)
			        || (kb_hit >= 48 && kb_hit <= 57) || kb_hit == SPACE) && count < 35 && count >= 0) {
				if (nSpace == 1 && kb_hit == SPACE) {
					count++;
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 0;
				} else if (kb_hit != SPACE) {
					count++;
					kb_hit = toupper((char)kb_hit);
					cout << (char)kb_hit;
					result += (char)kb_hit;
					nSpace = 1;
				}
			} else if (kb_hit == ENTER) {
				return 1;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				result.erase(result.length() - 1, 1);

			} else if (kb_hit == ESC) {
				return  -1;
			}
		}
	}
}

int NhapMaDocGia(int &msdg) {
	ShowCur(true);
	int temp = msdg;
	int count = 0;
	while (temp != 0) {
		count++;
		temp /= 10;
	}
	if (count) {
		cout << msdg;
	}
	while (true) {
		while (_kbhit()) {
			int kb_hit = _getch();
			if ((kb_hit >= 48 && kb_hit <= 57) 	&& ( count <= 9 && count >= 0)) {
				int f = kb_hit - 48;
				cout << f;
				msdg = msdg * 10 + (f);
				count++;
			} else if (kb_hit == ENTER) {
				return 1;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				msdg /= 10;
			} else if (kb_hit == ESC) {
				return  -1;
			}
		}
	}
}


int InputMaThe(int &maThe) {
	ShowCur(true);
	int temp = maThe;
	int count = 0;
	// kiem tra maThe da duoc nhap chua
	while (temp != 0) {
		count++;
		temp /= 10;
	}
	if (count) {
		cout << maThe;
	}
	while (true) {
		while (_kbhit()) {
			int kb_hit = _getch();
			if ((kb_hit >= 48 && kb_hit <= 57) && (count <= 9 && count >= 0)) {
				int f = kb_hit - 48;
				cout << f;
				maThe = maThe * 10 + (f);
				count++;
			} else if (kb_hit == ENTER) {
				return 1;
			} else if (kb_hit == BACKSPACE && count > 0) {
				cout << "\b" << " " << "\b";
				count--;
				maThe /= 10;
			} else if (kb_hit == ESC) {
				return  -1;
			}
		}
	}
}

int InputNgayThang(NTN &date, int x, int y) {
	ShowCur(true);
	int flag = 2;
	layNgayGioHT(date);
	NTN tempDate;
	tempDate.ngay = date.ngay;
	tempDate.thang = date.thang;
	tempDate.nam = date.nam;

	gotoxy(123, 37);
	gotoxy(x, y);
	cout << date.ngay << " /" << date.thang << " /" << date.nam;

	while (true) {
		while (_kbhit()) {
			int kb_hit = _getch();
			if (kb_hit >= 48 && kb_hit <= 57) {
				if (flag == 0) {
					int f = kb_hit - 48;
					tempDate.ngay = tempDate.ngay * 10 + (f);
					if (tempDate.ngay > 31) {
						tempDate.ngay /= 10;
						continue;
					}
					gotoxy(x, y);
					cout << tempDate.ngay;
				} else if (flag == 1) {

					int f = kb_hit - 48;
					tempDate.thang = tempDate.thang * 10 + (f);
					if (tempDate.thang > 12) {
						tempDate.thang /= 10;
						continue;
					}
					gotoxy(x + 4, y);
					cout << tempDate.thang;
				} else if (flag == 2) {

					int f = kb_hit - 48;
					tempDate.nam = tempDate.nam * 10 + (f);
					if (tempDate.nam > 9999) {
						tempDate.nam /= 10;
						continue;
					}
					gotoxy(x + 7, y);
					cout << tempDate.nam;
				}
			} else if (kb_hit == ENTER) {
				if (flag == 0) {

					gotoxy(x + 4, y);
					cout << tempDate.thang;
					flag = 1;
				} else if (flag == 1) {

					gotoxy(x + 7, y);
					cout << tempDate.nam;
					flag = 2;
				} else if (flag == 2) {

					gotoxy(x, y);
					cout << tempDate.ngay;
					flag = 0;
				}
			} else if (kb_hit == BACKSPACE && tempDate.ngay > 0 && tempDate.thang > 0 && tempDate.nam > 0) {
				cout << "\b" << " " << "\b";
				if (flag == 0) {
					tempDate.ngay /= 10;
				} else if (flag == 1) {
					tempDate.thang /= 10;
				} else if (flag == 2) {
					tempDate.nam /= 10;
				}
			} else if (kb_hit == 0) {
				kb_hit = _getch();
				if (kb_hit == KEY_F10) {

					flag = isNgayDung(tempDate);
					if (flag == 3) {
						// xoa nhung noi dung khong duoc su dung
						gotoxy(x - 19, y - 2);
						cout << "                                                  ";
						gotoxy(x, y);
						cout << "                     ";
						gotoxy(x - 3, y + 2);
						cout << "                     ";

						// kiem tra ngay nhap lon hon ngay hien tai
						if (khoangCachNgay(tempDate) < 0) {
							return 1;
						} else {
							date = tempDate;
							return 2;
						}
					} else if (flag == 0) {
						gotoxy(x - 3, y + 2);
						cout << "Sai ngay. Nhap lai!";
						gotoxy(x, y);
						cout << tempDate.ngay;
						continue;
					} else if (flag == 1) {
						gotoxy(x - 3, y + 2);
						cout << "Sai thang. Nhap lai!";
						gotoxy(x + 4, y);
						cout << tempDate.thang;
						continue;
					} else if (flag == 2) {
						gotoxy(x - 3, y + 2);
						cout << "Sai nam. Nhap lai!";
						gotoxy(x + 7, y);
						cout << tempDate.nam;
						continue;
					}
				}
			} else if (kb_hit == ESC) {
				// xoa nhung noi dung khong duoc su dung
				gotoxy(x - 19, y - 2);
				cout << "                                                  ";
				gotoxy(x, y);
				cout << "                     ";
				gotoxy(x - 3, y + 2);
				cout << "                     ";
				return -1;
			}
		}
	}
}

//int main() {
//	string m = "             h e          llo w    orld  %";
//	string n = ChuanHoaString(m);
//	cout<<n;
////	int maThe = 2;
////	InputMaThe(maThe);
////	InputNgayThang(d,10,10);
//	return 0;
//}

