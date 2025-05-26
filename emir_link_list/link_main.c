/* File        : mainNRSL.cpp */
/* Deskripsi   : Driver / main program untuk ADT Non Restricted Single Linked/Linear List */
/* Dibuat oleh : Ade Chandra Nugraha*/
/* Tanggal     : 25-10-2001 */
/* Diupdate oleh : Santi Sundari, 6-4-2011, hanya tdd operasi2 dasar */
/* Diupdate oleh : WW & AM, 8-3-2025, penyesuaian area body & main untuk latihan Diploma 3 */

#include "SpNRSLL.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	/* Kamus Lokal */
		List MyList;
		infotype isi;
		address P, Prec;
	/* Program */
	P=(address)malloc(sizeof(ElmtList));
	P->info=9;
	P->next=NULL;

	//List sudah terbentuk, digunakan untuk memanipulasi elemen
	InsVFirst(&MyList,7);
	Prec=MyList.First;
	InsVLast(&MyList,11);
	InsertAfter(&MyList,P,Prec);
	InsVFirst(&MyList,5);
	InsVLast(&MyList,13);
	DelLast(&MyList,&P);
	DelP(&MyList,7);
	DelFirst(&MyList,&P);
	DelAll(&MyList);
	PrintInfo(MyList);
	/* Finishing */
	
	//Pastikan List di Dealokasi setelah manipulasi elemen selesai
	
	return 0;
}

