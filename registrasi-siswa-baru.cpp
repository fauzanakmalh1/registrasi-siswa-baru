/*
Nama Program    : Registrasi Siswa Baru
Nama            : Fauzan Akmal Hariz dan Alvin
NPM             : 140810180005 dan 140810180013
Tanggal Buat    : 26 Mei 2019
Deskripsi       : Program ini dibuat menggunakan Double Linked List, Struct, dan Pointer
*/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct ElemtList {
    int nomor_regis;
    char nama_siswa[100];
    char jenis_kelamin[2];
    char asal_sekolah[100];
    char alamat[100];
    char kontak[14];
    ElemtList* next;
    ElemtList* prev;
};

typedef ElemtList* pointer;
typedef pointer List;

void createList(List& First) {
    First=NULL;
}

void createElement(pointer& pBaru) {
    pBaru=new ElemtList;
    cout<<"Nomor Registrasi\t: "; cin>>pBaru->nomor_regis;
    cin.ignore();
    cout<<"Nama Siswa\t\t: "; cin.getline(pBaru->nama_siswa,100);
    cout<<"Jenis Kelamin\t\t: "; cin.getline(pBaru->jenis_kelamin, 2);
    cout<<"Asal Sekolah\t\t: "; cin.getline(pBaru->asal_sekolah,100);
    cout<<"Alamat\t\t\t: "; cin.getline(pBaru->alamat,100);
    cout<<"Kontak\t\t\t: "; cin.getline(pBaru->kontak,14);
    pBaru->next=NULL;
    pBaru->prev=NULL;
}

void insertFirstDoubly(List& First, pointer pBaru) {
    if (First==NULL) {
        First=pBaru;
    }
    else {
        pBaru->next=First;
        First->prev=pBaru;
        First=pBaru;
    }
}

void insertLastDoubly(List& First, pointer pBaru) {
    pointer last;
    if(First==NULL) {
        First=pBaru;
    }
    else {
        last=First;
        while(last->next!=NULL) {
            last=last->next;
        }
        last->next=pBaru;
        pBaru->prev=last;
    }
}

void traversal(List First) {
    pointer pBantu;
    int i=1;

    if (First==NULL) {
        cout<<"List Kosong"<<endl;
    }
    else {
        pBantu=First;
        cout<<"============================================================================================================"<<endl;
        cout<<"                                          DATA REGISTRASI SISWA BARU                                        "<<endl;
        cout<<"============================================================================================================"<<endl;
        cout<<"No."<<"\t"<<"No. Reg"<<"\t\t"<<"Nama Siswa"<<"\t\t"<<"L/P"<<"\t"<<"Asal Sekolah"<<"\t\t"<<"Alamat"<<"\t\t"<<"Kontak"<<endl;
        cout<<"============================================================================================================"<<endl;
        do {
            cout <<i<<"\t"<< pBantu->nomor_regis<<"\t\t"<<pBantu->nama_siswa<<"\t\t"<<pBantu->jenis_kelamin<<"\t"<<pBantu->asal_sekolah<<"\t\t"<<pBantu->alamat<<"\t"<<pBantu->kontak<<endl;
            pBantu=pBantu->next;
            i++;
        } while(pBantu!=NULL);
    }
    cout<<endl;
}

void linearSearch(List First, char kunci[100], int& found, pointer& pCari) {
    found=0;
    pCari=First;
    while (found==0 && pCari!=NULL) {
        if (strcmp(pCari->nama_siswa,kunci)==0) {
            found=1;
        }
        else {
            pCari=pCari->next;
        }
    }
}

void insertAfterDoubly(List& First, pointer pCari, pointer pBaru) {
    if(pCari->next==NULL) {
        pCari->next=pBaru;
    }
    else {
        pBaru->next=pCari->next;
        pBaru->prev=pCari;
        pBaru->next->prev=pBaru;
        pCari->next=pBaru;
    }
}

void insertBeforeDoubly(List& First, pointer pCari, pointer pBaru) {
    if(pCari->prev==NULL) {
        pBaru->next=First;
        First->prev=pBaru;
        First=pBaru;
    }
    else {
        pBaru->next=pCari;
        pBaru->prev=pCari->prev;
        pCari->prev->next=pBaru;
        pCari->prev=pBaru;
    }
}

void deleteFirstDoubly(List& First, pointer& pHapus) {
    if(First==NULL) {
        pHapus=NULL;
        cout<<"List Kosong, Tidak Ada yang Dihapus"<<endl;
    }
    else if(First->next==NULL) {
        pHapus=First;
        First=NULL;
    }
    else {
        pHapus=First;
        First=First->next;
        pHapus->next=NULL;
        First->prev=NULL;
    }
}

void deleteLastDoubly(List& First, pointer& pHapus) {
    pointer last;
    if(First==NULL) {
        pHapus=NULL;
        cout<<"List Kosong, Tidak Ada yang Dihapus";
    }
    else if(First->next==NULL) {
        pHapus=First;
        First=NULL;
    }
    else {
        last=First;
        while(last->next!=NULL) {
            last=last->next;
        }
        pHapus=last;
        last->prev->next=NULL;
        pHapus->prev=NULL;
    }
}

void deleteAfterDoubly(List& First, pointer pCari, pointer& pHapus) {
    if(pCari->next==NULL) {
        pHapus=NULL;
        cout<<"List Setelahnya Kosong" <<endl;
    }
    else if(pCari->next->next==NULL) {
        deleteLastDoubly(First, pHapus);
    }
    else {
        pHapus=pCari->next;
        pCari->next=pHapus->next;
        pHapus->next->prev=pCari;
        pHapus->next=NULL;
        pHapus->prev=NULL;
    }
}

void deleteBeforeDoubly(List& First, pointer pCari, pointer& pHapus) {
    if(pCari->prev==NULL) {
        pHapus=NULL;
        cout<<"List Setelahnya Kosong"<<endl;
    }
    else if(pCari->prev->prev==NULL) {
        deleteFirstDoubly(First, pHapus);
    }
    else {
        pHapus=pCari->prev;
		pCari->prev=pHapus->prev;
        pHapus->prev->next=pCari;
		pHapus->next=NULL;
		pHapus->prev=NULL;
    }
}

void deletepCari(List& First, pointer pCari, pointer& pHapus) {
    if(pCari==First) {
        deleteFirstDoubly(First, pHapus);
    }
    else if(pCari->next==NULL) {
        deleteLastDoubly(First,pHapus);
    }
    else {
        pHapus=pCari;
        pCari->prev->next=pCari->next;
        pCari->next->prev=pCari->prev;
        pCari->next=NULL;
        pCari->prev=NULL;
    }
}

void cetakTxt(List First) {
    ofstream input;
    input.open("cetakTXT.txt");
    pointer pBantu;
    int i=1;

    if (First==NULL) {
        input<<"List Kosong"<<endl;
    }
    else {
        pBantu=First;

        input<<"============================================================================================================" <<endl;
        input<<"                                       DATA REGISTRASI SISWA BARU                                           " <<endl;
        input<<"============================================================================================================" <<endl <<endl;

        input<<"No."<<"\t"<<"No. Reg"<<"\t\t"<<"Nama Siswa"<<"\t\t"<<"L/P"<<"\t"<<"Asal Sekolah"<<"\t\t"<<"Alamat"<<"\t\t"<<"Kontak"<<endl;
        input<<"============================================================================================================"<<endl;
        do {
            input <<i<<"\t"<< pBantu->nomor_regis<<"\t\t"<<pBantu->nama_siswa<<"\t\t"<<pBantu->jenis_kelamin<<"\t"<<pBantu->asal_sekolah<<"\t\t"<<pBantu->alamat<<"\t"<<pBantu->kontak<<endl;
            pBantu = pBantu->next;
            i++;
        } while(pBantu != NULL);
    } input<<endl;

    input.close();
}

int main () {
    pointer pBaru, pCari, pHapus;
    List first;
    int n, pilih, ketemu;
    char kunci[100];

    cout<<"=========================================================" <<endl;
    cout<<"    SELAMAT DATANG DI PROGRAM REGISTRASI SISWA BARU      " <<endl;
    cout<<"=========================================================" <<endl <<endl;

    awal:
	cout<<"Silahkan Masukan Banyak Data Siswa : "; cin>>n; cout<<endl;
	cout<<"=========================================================" <<endl <<endl;


	createList(first);

	for(int i=0; i<n; i++) {
		createElement(pBaru);
		insertLastDoubly(first, pBaru);
		cout<<endl <<"=========================================================" <<endl <<endl;
	}

	do {
        system("cls");
        cout<<"|=======================================================|" <<endl;
        cout<<"|                       PILIHAN MENU                    |" <<endl;
        cout<<"|=======================================================|" <<endl;
        cout<<"|                                                       |" <<endl;
		cout<<"|          1.  Masukan Data ke Data Pertama             |" <<endl;
		cout<<"|          2.  Masukan Data ke Data Terakhir            |" <<endl;
		cout<<"|          3.  Masukan Data Sebelum Data                |" <<endl;
		cout<<"|          4.  Masukan Data Setelah Data                |" <<endl;
		cout<<"|          5.  Hapus Data Pertama                       |" <<endl;
		cout<<"|          6.  Hapus Data Terakhir                      |" <<endl;
		cout<<"|          7.  Hapus Data Sebelum Data                  |" <<endl;
		cout<<"|          8.  Hapus Data Setelah Data                  |" <<endl;
		cout<<"|          9.  Hapus Data yang Dicari                   |" <<endl;
        cout<<"|          10. Tampilkan Data                           |" <<endl;
		cout<<"|          11. Update Data                              |" <<endl;
		cout<<"|          12. Cetak Data di Format TXT (.txt)          |" <<endl;
		cout<<"|          13. Keluar Program                           |" <<endl;
        cout<<"|=======================================================|" <<endl <<endl;
		cout<<"Silahkan Masukan Pilihan : "; cin>>pilih;
		cout<<"=========================================================" <<endl <<endl;
        switch (pilih) {
            case 1:
                createElement(pBaru);
                insertFirstDoubly (first, pBaru);
                break;
            case 2:
                createElement(pBaru);
                insertLastDoubly (first, pBaru);
                break;
            case 3:
                traversal(first);
                cin.ignore();
                cout<<"Masukan Sebelum Nama Siswa\t: "; cin.getline(kunci,100);
                linearSearch(first, kunci, ketemu, pCari);
                if (ketemu) {
                    createElement(pBaru);
                    insertBeforeDoubly(first, pCari, pBaru);
                }
                else {
                    cout<<"Tidak Ditemukan" <<endl;
                }
                break;
            case 4:
                traversal(first);
                cin.ignore();
                cout<<"Masukan Setelah Nama Siswa\t: ";cin.getline(kunci,100);
                linearSearch(first, kunci, ketemu, pCari);
                if (ketemu) {
                    createElement(pBaru);
                    insertAfterDoubly(first, pCari, pBaru);
                }
                else {
                    cout<<"Tidak Ditemukan" <<endl;
                }
                break;
            case 5:
                deleteFirstDoubly(first, pHapus);
				cout<<"Data Berhasil Terhapus" <<endl;
				break;
            case 6:
                deleteLastDoubly(first, pHapus);
				cout<<"Data Berhasil Terhapus" <<endl;
				break;
            case 7:
                traversal(first);
                cin.ignore();
                cout<<"Masukan Nama Siswa\t: "; cin.getline(kunci,100);
                linearSearch(first, kunci, ketemu, pCari);
                if (ketemu) {
                    deleteBeforeDoubly(first, pCari, pBaru);
                    cout<<"Data Berhasil Terhapus" <<endl;
                }
                else {
                    cout<<"Tidak Ditemukan" <<endl;
                }
                break;
            case 8:
                traversal(first);
                cin.ignore();
                cout<<"Masukan Nama Siswa\t: "; cin.getline(kunci,100);
                linearSearch(first, kunci, ketemu, pCari);
                if (ketemu) {
                    deleteAfterDoubly(first, pCari, pBaru);
                    cout<<"Data Berhasil Terhapus" <<endl;
                }
                else {
                    cout<<"Tidak Ditemukan" <<endl;
                }
                break;
            case 9:
                traversal(first);
                cin.ignore();
                cout<<"Masukan Nama Siswa yang Akan Dihapus\t: "; cin.getline(kunci,100);
                linearSearch(first, kunci, ketemu, pCari);
                if (ketemu) {
                    deletepCari(first, pCari, pBaru);
                    cout<<"Data Berhasil Terhapus" <<endl;
                }
                else {
                    cout<<"Tidak Ditemukan" <<endl;
                }
                break;
            case 10 :
				traversal(first);
				break;
            case 11:
                traversal(first);
                cin.ignore();
                cout<<"Update Data Nama Siswa : "; cin.getline(kunci,100);
                linearSearch(first, kunci, ketemu, pCari);
                if (ketemu) {
                    createElement(pBaru);
                    insertAfterDoubly(first, pCari, pBaru);
                    deletepCari(first, pCari, pHapus);
                    cout<<"Data Berhasil Terupdate" <<endl;
                }
                else {
                    cout<<"Tidak ditemukan" <<endl;
                }
                break;
            case 12:
                cetakTxt(first);
                cout<<"Data Berhasil Dicetak Dalam Format TXT (.txt)" <<endl;
				break;
            case 13:
				cout<<"Terima Kasih Telah Menggunakan Program Ini" <<endl;
                return 0;
                break;
			default :
				cout<<"Maaf Pilihan Anda Tidak Tersedia" <<endl;
				goto awal;
			}
			cout<<endl;
            system("pause");
		}while(pilih!=13);
	return 0;
}
