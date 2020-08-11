#include "Date.h"

bool isNamNhuan(int year) {
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

int isNgayDung(NTN d) {
	if(d.ngay < 1||d.ngay>31) return 0;
	if(d.thang < 1||d.thang>12) return 1;
	if(d.nam < NAM_MIN || d.nam > NAM_MAX) return 2;
	if((d.thang == 4 || d.thang == 6 || d.thang == 9 || d.thang == 11) && (d.ngay > 30)) {
		return 0;
	}
	if (d.thang == 2) {
		if (isNamNhuan(d.nam)) {
			if (d.ngay > 29)
				return 0;
		} else {
			if (d.ngay > 28) {
				return 0;
			}
		}
	}
	return 3;
}

void xuatNgayThang(NTN dt, int x, int y) {
	gotoxy(x, y);
	cout << dt.ngay << " /";
	gotoxy(x + 4, y);
	cout << dt.thang << " /";
	gotoxy(x + 8, y);
	cout << dt.nam;
}

void layNgayGioHT(NTN &d) {
	//int ngay,thang,nam ;
	tm today;
	time_t ltime;
	time(&ltime);
	//today = localtime( &ltime );
	localtime_s(&today, &ltime);
	d.ngay = today.tm_mday;
	d.thang = today.tm_mon + 1;
	d.nam = today.tm_year + 1900;
}

int layNamHT() {
	tm today;
	time_t ltime;
	time(&ltime);
	//today = localtime( &ltime );
	localtime_s(&today, &ltime);
	return (today.tm_year + 1900);
}

int tinhNgay(NTN dt) {
	if (dt.thang < 3) {
		dt.nam--;
		dt.thang += 12;
	}
	return 365 * dt.nam + dt.nam / 4 - dt.nam / 10 + dt.nam / 400 + (153 * dt.thang - 457) / 5 + dt.ngay - 306;
}

int khoangCachNgay(NTN nt1) {
	NTN nt2;
	layNgayGioHT(nt2);
	return (tinhNgay(nt2) - tinhNgay(nt1));
}

int soSanhNgay(NTN nt1, NTN nt2) {
	return (tinhNgay(nt2) - tinhNgay(nt1));
}

//int main() {
//	NTN d,d1;
//	d1.nam = 2020;
//	d1.ngay = 20;
//	d1.thang = 1;
////	LayNgayGioHT(d);
////	xuatNgayThang(d,10,10);
////	xuatNgayThang(d1,10,30);
//	cout<<khoangCachNgay(d1);
//	return 0;
//}
