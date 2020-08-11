
#pragma once
#include <iostream>
#include "XuLyTam.h"
#include "MuonTra.h"
#include <string>
#include "GlobalVariable.h"
#include "XuLyInput.h"
#include "Ve_Hinh.h"
#include "mylib.h"

using std::cout;
using std::string;
// khoi tao
void initTREE_DG(TreeTDG &t);

// kiem tra rong
bool IsEmpty(TreeTDG t);

// get node
NodeTDG* GetNode_DG(TDG dg);

//  them node vao tree DG
void InsertDTtoTree(TreeTDG &t, TDG dg);

// dem so luong doc gia
int countDG(TreeTDG tree);

// kiem tra MSDG co ton tai hay khong.
bool Check_MADG(TreeTDG  t, int MADG);

// tra ve 1 so nguyen ngau nhien tu dong;
int Random();

// Ham tra ve  MSDG la so nguyen ngau nhien tu dong va khong trung.
int Random_MADG(TreeTDG t);

// find Min
NodeTDG* FindMin(TreeTDG t);

// tim doc gia bang ma doc gia, co tra ve dia chi , khong tra ve NULL
NodeTDG* Find_DG(TreeTDG t, int MADG);

// neu xoa dc, thuc hien xoa roi tra ve true , khong tra ve false
bool IsDeleted_DG(TreeTDG &t, TDG dg);

//xoa  Output mot doc gia.
void Xoa_OutDG_1line(int locate);

// xoa Output 29 doc gia
void Xoa_OutDg_29lines();

// xuat thong tin cua mot DG ra man hinh console
void Output_DG(NodeTDG* dg);

// lay ten va ho
string Get_TenHO(TDG dg);

//Ap dung duyet theo thu tu Inoder de cac phan tu trong mang theo thu tu tang dan.
void Create_ArrMADG(TreeTDG t, int* arr);

void Create_ArrTenHo(TreeTDG t, TEN_HO* arr);

// tao danh sach tam de xu ly.
void Creat_TEMPLIST(TreeTDG t, LIST_TEMPLIST &l, int &index);

void Swap_TenHo(TEN_HO &a, TEN_HO &b);

void QuicKsort_ARRTenHo(TEN_HO *th, int left, int right);

// ham cap nhat thong tin DG
void Update_DG(TreeTDG &t, TDG &dg, bool isEdited = false);

// output
void OutputDG_PerPage1(TreeTDG t, TEN_HO *arr, int index);

//  ham xuat ds DG theo thu tu ten ho tang dan
void OutputDG_PerPage2(TreeTDG t, int* arr, int index);

// ham xuat danh sach DG theo thu tu MADG tang dan
void Output_ListDG2(TreeTDG t, int *arr);

void OutputDG_PerPage(TreeTDG t, LIST_TEMPLIST l, int index);

int ChooseItems(TreeTDG &t, LIST_TEMPLIST &l, int tttrang, int tongtrang);

// ham xuat thong tin DG
int Output_ListDG(TreeTDG &t, LIST_TEMPLIST &l, TDG &dg, int &tttrang);

void Menu_DocGia(TreeTDG &t);

void InDocGia(TreeTDG t);

// quick sort mang theo thu tu keyword giam dan
void Sort_QuaHan(QuaHan *ArrQuaHan, int q, int r);

//Duyệt cây theo thứ tự NLR (Preorder): Giai thuat khong de quy.
void DanhSachQuaHan(TreeTDG t);

