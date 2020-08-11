#pragma once
#include "mylib.h"
#include "Ve_Hinh.h"
#include "XuLyInput.h"
#include "GlobalVariable.h"
#include "Date.h"
#include "Marcro.h"
#include "DanhMucSach.h"



//Dau Sach
int checkEmpty_DauSach(List_DauSach listDS);
int checkFull_DauSach(List_DauSach listDS);
int themDauSach(List_DauSach &listDS,  pDauSach &pDS);
void xoaDauSach_ViTri(List_DauSach &listDS, int viTri);
bool searchDauSach_ISBN(List_DauSach listDS, string ISBN);
pDauSach layDauSach_Ten(List_DauSach listDS, string tenSach);
List_DauSach layDauSach_TheLoai(List_DauSach &listDS, string theLoai);
//Ham xu ly Dau Sach
void Menu_DauSach(List_DauSach &lDS);
void Output_ListDStheoTT(List_DauSach lDS);
void OutputDS_PerPage(List_DauSach &lDS, int index);
void Output_DS(string tenSach, string ISBN, string tacGia, string theLoai, int soTrang, int namXB);
void Xoa_OutDS_29lines();
void Xoa_OutDS_1line(int locate) ;
int ChooseItems_DS(List_DauSach &lDS, int &tttrang, int tongtrang);
void Update_DauSach(List_DauSach &lDS, pDauSach &pDS, bool isEdited);

//
string getString(string a);
void swap_DS(pDauSach ds1, pDauSach ds2);

void quickSortDS(List_DauSach &listDS, int left, int right);



//update info
