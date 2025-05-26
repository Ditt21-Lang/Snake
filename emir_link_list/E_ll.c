/* File        : bodyNRSL.c */ 
/* Deskripsi   : Body prototype ADT Non Restricted Single Linked/Linear list yang hanya dikenali First(L) */
/* Dibuat oleh : Ade Chandra Nugraha */
/* Tanggal     : 24-10-2001 */
//test test

//uhum
#include <limits.h>
#include <malloc.h>
#include "E_LL.h"
#include <stdlib.h>
#include <stdio.h>

/********** BODY SUB PROGRAM ***********/
/**** Predikat untuk test keadaan LIST  ****/
boolean ListEmpty (List L)
// /* Mengirim true jika List Kosong *//
{
	//saya mencek headnya saja 
	if(First(L) == NULL ){
	return true;
	}
	else{
	return false;
	}
}

/**** Konstruktor/Kreator List Kosong ****/
void CreateList (List * L)
/* IS : L sembarang */
/* FS : Terbentuk List Kosong */
{
	//mencreate node untuk head dan menull kan
	 First(*L) = (address)malloc(sizeof(ElmtList));
	 First(*L)->next=NULL;
}

/**** Manajemen Memory ****/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address != Nil, 	   */
/*	dan misalnya menghasilkan P, maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	
	 /* Kamus Lokal */
	 address P;
	 /* Algoritma */
	 P = (address) malloc (sizeof (ElmtList));
	 if (P != Nil)		/* Alokasi berhasil */
	 {
	Info(P) = X;
	Next(P) = Nil;
	 }
	 return (P);
}

void DeAlokasi (address P)
/* IS : P terdefinisi */
/* FS : P dikembalikan ke sistem */
/* Melakukan dealokasi / pengembalian address P ke system */
{
	 if (P != Nil)
	 {
	free (P);
	 }
}

/**** Pencarian sebuah elemen List ****/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address elemen tsb. */
/* Jika tidak ada, mengirimkan Nil */
/* Menggunakan variabel bertype boolean */
{
	 /* Kamus Lokal */
	 address P;
	 boolean found =  false;
	 /* algoritma */
	 P = First(L);
	 while ((P != Nil) && (!found))
	 {
		if (Info(P) == X)
		{	found = true; 	}
		else
		{	P = Next(P);	}
	 }	/* P = Nil atau Ketemu */
	
	 return (P);
}

boolean FSearch (List L, address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
	 /* Kamus Lokal */
	 boolean found=false;
	 address PSearch;
	 /* Algortima */
	 PSearch = First(L);
	 while ((PSearch != Nil) && (!found))
	 {
		if (PSearch == P)
		{	found = true; 	}
		else
		{	PSearch = Next(PSearch);	}
	 }	/* PSearch = Nil atau Ketemu */
	 
	 return (found);
}

address SearchPrec (List L, infotype X)
/* Mengirimkan address elemen sebelum elemen yang nilainya = X */
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec) = P dan Info(P) = X */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec = Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
	 /* Kamus Lokal */
	address Prec, P;
	boolean found=false;
	 /* Algoritma */
	Prec = Nil;
	P = First(L);
	while ((P != Nil) && (!found))
	{
		 if (Info(P) == X)
		 {	found = true;	}
		 else
		 {
			Prec = P;
			P = Next(P);
		 }
	}    /* P = Nil atau Ketemu */
	if (found)
	{	return (Prec);		}
	else
	{	return (Nil);		}
}

/**** PRIMITIF BERDASARKAN NILAI ****/
/**** Penambahan Elemen ****/
void InsVFirst (List * L, infotype X)
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	 /* Kamus Lokal */
	address P;
	 /* Algoritma */
	P=Alokasi(X);
	if(P != NULL){
		InsertFirst(L,P);
	}else{
		printf("memory penuh -_-");
	}
}

void InsVLast (List * L, infotype X)
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir (elemen terakhir adalah yang baru) */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal IS = FS */
{
	 /* Kamus Lokal */
	address P,search;
	
	 /* Algoritma */
	if(First(*L) == NULL){
		P=(address)malloc(sizeof(ElmtList));
		Info(P)=X;
		Next(P)=NULL;
		First(*L)=P;
	}else
	search=First(*L);
	while(search->next != NULL){
		search=search->next;
	}
	P=(address)malloc(sizeof(ElmtList));
	Info(P)=X;
	Next(P)=NULL;
	search->next=P;
}
	 //Buatkan algoritma sesuai spesifikasi modul ini

/**** Penghapusan Elemen ****/
void DelVFirst (List * L, infotype * X)//yang ini masih salah bu perlu perbaikan;
/* IS : L TIDAK Kosong */
/* FS : Elemen pertama List dihapus, nilai info disimpan ke X */
/* 	dan alamat elemen pertama di dealokasi */
{
	 /* Kamus Lokal */
	address P;
	 /* Algoritma */
	if( First(*L)->next != NULL){
	P=(address)malloc(sizeof(ElmtList));
	*X=First(*L)->info;
	Next(P)=First(*L);
	First(*L)=First(*L)->next;
	free(First(*L));
	free(P);
	}
	else{
		P=First(*L);
		*X = Info(P);
		free(P);
		First(*L)=NULL;

	}
	}
	 //Buatkan algoritma sesuai spesifikasi modul ini


void DelVLast (List * L, infotype * X)
/* IS : L TIDAK Kosong */
/* FS : Elemen terakhir list dihapus : nilai info disimpan pada X */
/* 	dan alamat elemen terakhir di dealokasi */
{
	 /* Kamus Lokal */
	address Prec;
	
	 /* Algoritma */
	 if(First(*L) != NULL && First(*L)->next == NULL){
	 	Prec=First(*L);
	 	*X=Prec->info;
	 	First(*L)=NULL;
	 	free(Prec);
	 }
	 else {
	 if(First(*L) != NULL && First(*L)->next != NULL){
	 	Prec=First(*L);
	 	while(Prec->next->next !=NULL){
	 		Prec=Prec->next;
		 }
		 *X=Prec->next->info;
		 free(Prec->next);
	 }
	 }
	 //Buatkan algoritma sesuai spesifikasi modul ini
}


/**** PRIMITIF BERDASARKAN ALAMAT ****/
/**** Penambahan elemen berdasarkan alamat ****/
void InsertFirst (List * L, address P)         //adhasbkjdbjbkhab
/* IS : L sembarang, P sudah dialokasi */
/* FS : menambahkan elemen ber-address P sebagai elemen pertama */
	//Buatkan algoritma sesuai spesifikasi modul ini
{
	if (L->First == NULL){
		L->First = P;
	}else{
		Next(P)=L->First;
		L->First=P;
	}
	
}

void InsertAfter (List * L, address P, address Prec)
/* IS : Prec pastilah elemen List dan bukan elemen terakhir */
/*	P sudah dialokasi */
/* FS : Insert P sebagai elemen sesudah elemen beralamat Prec */
{

	if(Prec->next !=NULL){
	Next(P)=Prec->next;
	Prec->next=P;
		}
	
}

void InsertLast (List * L, address P)
/* IS : L sembarang, P sudah dialokasi */
/* FS : P ditambahkan sebagai elemen terakhir yang baru */
{
	if(First(*L) == NULL){
		First(*L) = P;
	}else{
	address temp=First(*L);
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=P;
	}
	
}

/**** Penghapusan sebuah elemen ****/
void DelFirst (List * L, address * P)
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen pertama list sebelum penghapusan */
/*	elemen list berkurang satu (mungkin menjadi kosong) */
/* First elemen yang baru adalah suksessor elemen pertama yang lama */
{
address del;
if(First(*L) != NULL){

	if(First(*L)->next == NULL){
		*P=L->First;
		First(*L)=NULL;
		
	}else{
		del=First(*L);
		First(*L)=First(*L)->next;
		del->next=NULL;
		*P=del;
		}
	}
}


void DelP (List * L, infotype X)
/* IS : L sembarang */
/* FS : Jika ada elemen list beraddress P, dengan Info(P) = X */
/* 	Maka P dihapus dari list dan di dealokasi */
/* Jika tidak ada elemen list dengan Info(P) = X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	 /* Kamus Lokal */
	address P, Prec;
	boolean found=false;
	 
	 /* Algoritma */
	if(First(*L) != NULL ){
		P=First(*L);
		if(Info(P) == X){
			found=true;
			}
		while(Next(P) != NULL && found !=true){
			if(Next(P)->info == X){
			found=true;
			}
			Prec=P;
			P=Next(P);
		}
			if(found){
			Prec->next=Next(P);
			if(P !=NULL){
				P=NULL;
			}
			free(P);
		}
	}
	 //Buatkan algoritma sesuai spesifikasi modul ini
}

void DelLast (List * L, address * P)
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen terakhir list sebelum penghapusan */
/*	Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last elemen baru adalah predesessor elemen terakhir yang lama, jika ada */
{
	 /* Kamus Lokal */
	address Del,Prec_bf;
	
	 /* Algoritma */
	 if(First(*L) != NULL && First(*L)->next == NULL){
	 	*P=First(*L);
	 	First(*L)=NULL;
	 }
	 else {
	 if(First(*L) != NULL && First(*L)->next != NULL){
	 	Del=First(*L);
	 	while(Del->next !=NULL){
	 		Prec_bf=Del;
	 		Del=Del->next;
		 }
		 Prec_bf->next=NULL;
		 *P=Del;
		 
	 }
	 }
	 //Buatkan algoritma sesuai spesifikasi modul ini
}

void DelAfter (List * L, address Pdel, address Prec)//fix udah bener

/* IS : L TIDAK Kosong, Prec adalah anggota List */
/* FS : menghapus Next(Prec): Pdel adalah alamat elemen list yang dihapus */

{
	address temp;
	if(First(*L) != NULL && Pdel->next !=NULL){
		temp=Pdel;
		Prec->next = Pdel->next;
		free(temp);
		
	}
}

/**** PROSES SEMUA ELEMEN LIST  ****/
void PrintInfo (List L)
/* IS : L mungkin kosong */
/* FS : Jika List tidak kosong, semua info yang disimpan pada elemen list */
/*	diprint. Jika list kosong, hanya menuliskan "List Kosong" */
{
	 /* Kamus Lokal */
	int i=1;
	address P;
	 /* Algoritma */
	if(First(L) !=NULL){
		P=First(L);
	while(P->next !=NULL){
	printf("node %d value nya =%d\n",i,P->info);
	P=P->next;
	++i;
	}
		printf("node %d value nya =%d\n",i,P->info);
	printf("selesai\n");
		}
	//Buatkan algoritma sesuai spesifikasi modul ini
}


void DelAll (List * L)
/* Delete semua elemen list dan alamat elemen di dealokasi */
{
	 /* Kamus Lokal */
	address PDel,Prec;
	if(First(*L) !=NULL){
		PDel=First(*L);
			First(*L)=NULL;
		while(PDel->next !=NULL){
		Prec=PDel;
		PDel=PDel->next;
		Prec->next=NULL;
		free(Prec);
		Prec=NULL;
		}
	free(PDel);
	PDel=NULL;

	}
	
	 //Buatkan algoritma sesuai spesifikasi modul ini
}



