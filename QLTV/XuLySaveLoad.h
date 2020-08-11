#pragma once
#include <tchar.h>
#include "DocGia.h"
#include "DauSach.h"
#include <fstream>
#include "DanhMucSach.h"

void ManHinhChinh();
void Save_DS(List_DauSach listDS);
void Load_DS(List_DauSach &listDS);
void Save(TreeTDG t, fstream &file);
void OutFile_DG(TreeTDG t, fstream &file);
void Save_DG(TreeTDG t);
void Load_DG(TreeTDG &t);
int Menu_MuonSach(List_DauSach &lDS, NodeTDG* nDG);
void XuLyMuonSach(TreeTDG &t, List_DauSach &lDS);
void XuLyTraSach(TreeTDG &t, List_DauSach &lDS);
void XuLyMainMenu(TreeTDG &t, List_DauSach &lDS);
