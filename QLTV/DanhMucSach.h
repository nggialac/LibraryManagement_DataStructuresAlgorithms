#pragma once

#include "mylib.h"
#include "DauSach.h"
#include <string>

// ..... khoi tao........
void initList_DMS(ListDMS& ldms);
// kiem tra rong
bool ListDMSIsEmpty(ListDMS ldms);
// get node
Node_DMS* GetNode_DMS(DMS data);
// them vao cuoi
void addTailList_DMS(ListDMS &ldms, DMS data);
// xac dinh vi tri cua nut co gia tri ma sach bang keySearch trong danh sach lien ket
int getViTri_Key(Node_DMS *First, string keySearch);
// xac dinh con tro cua nut thu i trong danh sach lien ket
Node_DMS * nodePointer(Node_DMS *First, int i);
// Phep toan Delete_first: xoa nut o dau danh sach lien ket
void deleteFirst(Node_DMS *&First);
// xoa nut sau nut p
void deleteAfter(Node_DMS *p);
// xoa 1 node bat ky trong danh sach lien ket.
int delete_Key(pDauSach &pDS, string keySearch);
// ham kiem tra sach co ai muon hay chua, co thi tra ve true, ko thi false.
bool Check_DMS(Node_DMS* nDMS);
// tim kiem tra ve con tro nut 1
Node_DMS* Search_DMS1(pDauSach pDS, string masach);
// tim kiem tra ve con tro nut 2
Node_DMS* Search_DMS2(Node_DMS* dms, int pos);

//
int ChooseItems1(pDauSach &pDS, int &tttrang, int tongtrang);
int ChooseItems(List_DauSach &lDS, int &tttrang, int tongtrang);
void Xoa_OutDMS_29lines();
void Xoa_OutDMS_1line(int locate);
int SuaDanhMucSach(pDauSach &pDS, Node_DMS* dms) ;
int NhapSach(pDauSach &pDS);
void NhapDanhMucSach(pDauSach &pDS, int sosach);
void Output_ListDMS(pDauSach &pDS);
void OutputDMS_PerPage(pDauSach pDS, int index) ;
void Output_DMS(DMS dms);
void Top10Sach(List_DauSach lDS);
void Sort_Top10(Top *top10, int q, int r);
int TongSoSachDuocMuon(ListDMS dms);
void Menu_DMS(List_DauSach &lDS);



