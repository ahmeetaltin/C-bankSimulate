#include <stdio.h>
#include <stdlib.h>
#include <conio.h>// getch icin
#include <unistd.h>// ctrcpy ve time komutlari icin
#include <time.h>// srand icin 
int musteriSayi=10;
#define vezneSayi 3
#define bekle  0//eger islemleri adim adim gormek istiyorsaniz 1 yapiniz.
int ilgilenenMusteri=0;						//
int veznedeKalinanToplamDakika=0;			//
float beklenenToplamDakika=0;				//	istatislik icin
float beklenenToplamMusteri=0;				//
int enCokBekleyenSure=0,enCokBekleyenID=0;	//
char enCokBekleyenIslem[15];				//
int yeniEklenen=0;// kac kisi sonradan kuyruga girdi
int eft=0;int kredi=0;int fatura=0;int para=0;

struct a{
	int sira;// hangi musteri
	int giris;// giris dakikasi
	int ctrl;// herhangi bir vezneye giris yapinca 1 olacak
	int ctrl2;// herhangi bir vezneden cikis yapinca 1 olacak
	int ctrl3;// eger butun vezneler dolu ise 1 olacak
	int vezno;//hangi vezneye giris yaptigi
	int is;// yaptigi is int
	char is2[15];// yaptigi is char
	int isDK;// yaptigi isin kac dk surecegi
	int cikis;// cikis dakikasi
	struct a *next;	
};
typedef struct a musteri;

struct b{
	int vezneSira;//hangi vezne
	int durum;// icerisinde musteri varsa 1 olacak cikinca 0
	int musteri;// icerisinde hangi musteri var
	int toplamMusteri;// en sondaki istatislikler icin
	int toplamHizmetSuresi;// en sondaki istatislikler icin
	struct b *next;
	struct b *prev;
};
typedef struct b vezne;

int toplamDK=0;int sira=0;int vezneSira=0;

musteri *head=NULL,*tail=NULL,*p=head,*gP=head,*temp=head;
vezne *head2=NULL,*tail2=NULL,*q=head2,*q2=head2,*qP=head2;

int musteriGir()
{
	int beklemeSuresi=0;
	
	if(head==NULL)
	{
		temp=(musteri *)malloc(sizeof(musteri));
		head=temp;
		gP=head;
		tail=temp;
	}
	else
	{
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=(musteri *)malloc(sizeof(musteri));
		temp=temp->next;
		tail=temp;
	}
	sira++;
	temp->next=NULL;
	beklemeSuresi=rand() % 6;
	temp->giris=beklemeSuresi+toplamDK;
	temp->sira=sira;
	temp->ctrl=0;
	temp->ctrl2=0;
	temp->ctrl3=0;
	temp->is=rand()%4;
	temp->vezno=0;
		
	if(temp->is==0)
	{
		temp->isDK=rand()%8+3;
		strcpy(temp->is2,"EFT");
	}
	else if(temp->is==1)
	{
		temp->isDK=rand()%11+10;
		strcpy(temp->is2,"Kredi Cekim");
	}
	else if(temp->is==2)
	{
		temp->isDK=rand()%11+2;
		strcpy(temp->is2,"Fatura Yatirma");
	}
	else
	{
		temp->isDK=rand()%7+1;
		strcpy(temp->is2,"Para Cekim");
	}
		
	toplamDK=toplamDK+beklemeSuresi;
	temp->cikis=toplamDK+temp->isDK;
	sleep(0);
}
int vezneEkle()
{
	if(head2==NULL)
	{
		q=(vezne *)malloc(sizeof(vezne));
		head2=q;
		head2->prev=NULL;
		q2=head2;//q2 bir onceki vezneyi tutmak icin
		qP=head2;
	}
	else
	{
		
		q->next=(vezne *)malloc(sizeof(vezne));
		q2=q;//q2 bir onceki vezneyi tutmak icin
		q=q->next;
		q->prev=q2;
	}
	vezneSira++;
	q->toplamHizmetSuresi=0;
	q->toplamMusteri=0;
	q->durum=1;
	q->vezneSira=vezneSira;
	tail2=q;
	q->next=NULL;
}
int cikis(int is)
{
	if(is==0)// cikis yapan musteriye gore istatislik
		eft++;
	else if(is==1)
		kredi++;
	else if(is==2)
		fatura++;
	else
		para++;
	ilgilenenMusteri++;
}
int yazdir()
{
	system("CLS");
	printf("\n Sirada Beklenen Toplam Dakika : %.2f\n\n",beklenenToplamDakika);
	sleep(1);
	beklenenToplamDakika=beklenenToplamDakika/beklenenToplamMusteri;
	printf(" Sirada Beklenen Ortalama Sure : %.2f\n\n",beklenenToplamDakika);
	sleep(1);
	printf(" Ilgilenilen Toplam Musteri : %d\n\n",ilgilenenMusteri);
	sleep(1);
	qP=head2;
	for(int i=0;i<vezneSayi;i++)
	{
		printf("\n\n  %d. Vezne - \t Toplam hizmet verilen musteri sayisi : %d",qP->vezneSira,qP->toplamMusteri);
		float ortalama=qP->toplamHizmetSuresi/qP->toplamMusteri;
		printf("\n\t\t Ortalama Hizmet verme suresi : %.2f dk\n\n\n",ortalama);
		qP=qP->next;
	}
	
	if(enCokBekleyenSure<=8)
	{
		system("Color A");	
	}
	else
	{
		system("Color C");
		printf(" %d.Musterimiz %s islemi icin %d dk sira bekledi \n\t\t\t\t[En Cok Bekleyen Musteri]",enCokBekleyenID,enCokBekleyenIslem,enCokBekleyenSure);
	}
	sleep(bekle);
	//printf("\n\n %d kisi sonradan eklendi ..\n",yeniEklenen);
	//sleep(1);
	printf("\n\n\n EFT yaptiran Toplam Musteri : %d",eft);
	sleep(1);
	printf("\n Kredi Ceken Toplam Musteri : %d",kredi);
	sleep(1);
	printf("\n Fatura yatiran Toplam Musteri : %d",fatura);
	sleep(1);
	printf("\n Para Ceken Toplam Musteri : %d\n\n\n\n\n",para);
	sleep(1);
	p=head;
	printf("\n SIRA\t VEZNE\tGIRIS\tISLEM SURESI\tCIKIS\tISLEM ISMI\n\n");
	while(p!=NULL)
	{
		printf("  %d.-",p->sira);
		printf("\t  %d.-",p->vezno);
		printf("\t%d.dk",p->giris);
		printf("\t - %d.dk",p->isDK);	
		printf(" \t%d.dk",p->cikis);	
		printf("\t- %s\n",p->is2);
		p=p->next;
	}
	printf("\n\n\t\t\t\t Bitirmek icin herhangi bir tusa basiniz.. \n\n\t\t\t\t\ta.Can Altin\n\n\t\t\t\t\t20152105004");
	getch();
}
int main()
{
	system("Color E");
	int sure=0,eklendi=0,beklenen=0;
	
	srand (time(NULL));
	
	for (int i=0;i<musteriSayi;i++)
		musteriGir();
	for (int i=1;i<=vezneSayi;i++)
		vezneEkle();
	
	
	printf("\n\n Kac Dakikalik Bir Simulasyon Istiyorsunuz ? ",musteriSayi);
	scanf("%d",&sure);
	sleep(bekle);
	p=head;
	q=head2;
	//system("CLS");
	for(int i=0;i<sure+200;i++)// +200 ün sebebi banka kapanmasina ragmen kuyrukta musteri varsa onlarla ilgilenilmesini saglamak
	{
		
		gP=head;// Musteriler arasindaki Gezici Pointerimiz
		qP=head2;// Vezneler arasindaki Gezici Pointerimiz
		
		while(gP!=NULL)
		{
			// Musterinin vezneden cikis blogu ->
			
			if(gP->cikis==i && gP->ctrl==1 && gP->ctrl2==0)	// ilk yaptigimda for'un icinde direk musterinin vezneye girmesini kontrol ettim fakat 
			{																// ayni dakikada hem giris hem cikis olunca ve butun veznelerde dolu olunca  
				system("Color C");   								// once girisi kontrol ediyor ve bos vezne olmadigi icin giremiyordu bu yuzden bir sonraki dakikaya 
				printf("\n %d. Musteri %d.Vezneden Cikis Yapti..",gP->sira,gP->vezno);	// kayiyordu boylece dogru calismiyordu bu yuzden cikisi uste aldim
				cikis(gP->is);// cikan musteriye gore islem
				gP->ctrl2=1;
				i--;				
				sleep(bekle);
				while(qP!=NULL)
				{
					if(gP->vezno==qP->vezneSira)
						qP->durum=1;
					qP=qP->next;
				}
				
				if(beklenen>enCokBekleyenSure)
				{
					enCokBekleyenSure=beklenen;
					enCokBekleyenID=p->sira;
					strcpy(enCokBekleyenIslem,p->is2);
				}
				beklenen=0;
				if(i>=sure)//
				{
					
					break;
				}
				else
				{
					musteriGir();// müsteri cikis yaptikca kuyruga baskasi eklenecek
					yeniEklenen++;
					musteriSayi++;
				}
			}
			gP=gP->next;
		}
		
		// Musterinin vezneye giris blogu ->
		
		if(p->giris==i && p->ctrl==0)//p deki musterinin giris zamani geldiyse iceri gir
		{
			i=0;
			q=head2;//q ile hangi veznenin bos oldugunu kontrol ediyor
			eklendi=0;
			while(q!=NULL)
			{
				if(q->durum==1)
				{
					system("Color A");
					q->musteri=p->sira;
					p->vezno=q->vezneSira;
					
					printf("\n %d. Musteri %d.Veznede - Giris : %d.dk - Cikis : %d.dk ~ %s",p->sira,q->vezneSira,p->giris,p->cikis,p->is2);
					q->toplamMusteri++;
					q->toplamHizmetSuresi=q->toplamHizmetSuresi+p->isDK;
					sleep(bekle);
					eklendi++;
					p->ctrl=1;
					q->durum=0;
					if(p->sira!=tail->sira)
						p=p->next;
					break;
				}
				else
				{
					q=q->next;
				}
			}
			if(eklendi<1)//eger musteri hic bir vezneye eklenmemis ise elimizde tutup veznelerin bosalacagi zamani bekliyoruz 
			{// biz bu bekleme istemini yaparken haliyle giris ve cikis dakikalari ilerliyor
				system("Color F");
				if(p->ctrl3==0)// ekrana ard arda vezne bekliyor yazmasin diye ctrl3 ekledim
				{
					printf("\n %d. Musteri - Vezne Bekliyor.. ",p->sira);
					toplamDK++;
					p->ctrl3=1;
					beklenenToplamMusteri++;
				}
				beklenenToplamDakika++;//en sondaki istatislikler icin gerekli
				beklenen++;// en cok bekleyen musteriyi hesaplamak icin
				p->giris++;
				p->cikis++;
				
				sleep(bekle);
			}
		}
	}
	yazdir();
}
