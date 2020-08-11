/*Thu vien:
	-Dau sach: DSTT 1 mang con tro (ISBN C6, Ten sach, So trang, Tac gia, Nam xuat ban, The loai, Con tro dms):
		+con tro tro den cac sach thuoc dau sach tuong ung
	-Danh muc sach: DSLK don (Ma sach, Trang thai, Vi tri)
		+Moi sach co 1 ma sach duy nhat
		+Trang thai sach:
			0: Cho muon duoc
			1: Da co doc gia muon
			2: Sach da thanh ly
	-Danh sach the doc gia: Cay NPTK (Ma the(so nguyen ngau nhien tu dong), Ho, Ten, Phai, Trang thai cua the, Con tro)
		+Con tro tro den danh sach cac cuon sach da va dang muon
	-Danh sach muon tra: DSLK kep (Ma sach, Ngay muon, Ngay tra, trang thai)
		+0: Sach dang muon (chua tra)
		+1: Da tra
		+2: Lam mat sach
*/
#pragma once
#include <iostream>

#define MAX_LIST_DAUSACH 10000

using namespace std;

//-----------------------------------------------o0o------------------------------------------
struct Ntn {
	int ngay;
	int thang;
	int nam;
};
typedef struct Ntn NTN;
//**************************************************
struct DMSach {
	string maSach;
	int trangThaiSach;
	string viTri;
};
typedef struct DMSach DMS;
struct NodeDMSach {
	DMS info;
	NodeDMSach *nextNDMS;
};
typedef struct NodeDMSach Node_DMS;
struct ListDMSach {
	int n;
	Node_DMS *headLDMS, *tailLDMS;
};
typedef struct ListDMSach ListDMS;
//**************************************************
struct DauSach {
	string ISBN;
	string tenSach;
	string tacGia;
	string theLoai;
	int namXB;
	int soTrang;
	ListDMS pListDMS;
	int soLanMuon;
};
typedef struct DauSach dauSach;
typedef struct DauSach *pDauSach;
//**************************************************
struct ListDauSach {
	int n=-1;
	DauSach *nodesDS[MAX_LIST_DAUSACH];
};
typedef struct ListDauSach List_DauSach;
//**************************************************
struct MuonTra {
	string maSach;
	int trangThai;
	NTN ngayMuon;
	NTN ngayTra;
	//
	string tenSach;
	string viTriSach;
};
typedef struct MuonTra MT;
struct NodeMuonTra {
	MuonTra info;
	NodeMuonTra *leftNMT, *rightNMT;
};
typedef struct NodeMuonTra NodeMT;
struct ListMuonTra {
	int n;
	NodeMuonTra *headLMT, *tailLMT;
};
typedef struct ListMuonTra ListMT;
//**************************************************
struct TheDocGia {
	int maThe; //int maThe;
	string ho;
	string ten;
	bool phai;
	int trangThaiThe;

};
typedef struct TheDocGia TDG;
struct NodeTheDocGia {
	ListMT listMT;
	TheDocGia info;
	NodeTheDocGia *leftTDG, *rightTDG;
};
typedef struct NodeTheDocGia NodeTDG;
typedef struct NodeTheDocGia *TreeTDG;
//**************************************************
struct Top {
	string tenSach;
	int soSachMuon;
};

struct QuaHan {
	uint MADG;
	int songayquahan;
};


