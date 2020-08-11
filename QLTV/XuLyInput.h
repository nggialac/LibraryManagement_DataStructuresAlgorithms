#pragma once


#include "Marcro.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include "mylib.h"
#include "Date.h"
using namespace std;
using namespace std;

void xoa(char* s, int vitrixoa);
char* ChuanHoaChar(char* result);
char* toCharArray(string str);
string ChuanHoaString(string result);// bo space
void Nhap(int &result, int choice, int &ordinal, bool &isSave, bool &isEscape);
void NhapISBN(string &result, int &ordinal, bool &isSave, bool &isEscape);
void NhapNamXuatBan(int &nam, int &ordinal, bool &isSave, bool &isEscape);//
void nhapSoTrang(int &nTrang, int &ordinal, bool &isSave, bool &isEscape);//
void NhapTheLoaiSach(string &result, int &ordinal, bool &isSave, bool &isEscape);
void NhapTenTacGia(string &result, int &ordinal, bool &isSave, bool &isEscape);
void NhapTenSach(string &result, int &ordinal, bool &isSave, bool &isEscape);
void NhapHo(string &result, int &ordinal, bool &isSave, bool &isEscape);
void NhapTen(string &result, int &ordinal, bool &isSave, bool &isEscape);
//
int ChonSoSachNhap();
//
int  NhapMaDauSach(string &result);
void NhapViTri(string &result, int &ordinal, bool &isSave, bool &isEscape, int a, int b);
void NhapTrangThaiSach(int &result, int &ordinal, bool &isSave, bool &isEscape, int a, int b);
int  NhapMaDocGia(int &msdg);
//
int InputMaThe(int &maThe);
int InputNgayThang(NTN &date, int x, int y);
int NhapTenSachTimKiem(string &result);






