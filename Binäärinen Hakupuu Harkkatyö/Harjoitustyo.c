/*

Käytetyt lähteet: 

BM40A0301 Tietorakenteet ja algoritmit Harjoitus 7 - työpaja  

https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx

https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/ 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 10000 //Annetaan max 10 000 avainta
#define COUNT 10


/* Tietue puun solmuille */
typedef struct puusolmu_t {
  int luku;
  short tila; /* tasapainoilmaisin */
  struct puusolmu_t *vasen, *oikea;
} puusolmu, *puuosoitin;

void lisaa_solmu(puuosoitin *, int, int *);
void vasen_kierto(puuosoitin *, int *);
void oikea_kierto(puuosoitin *, int *);
void tulosta_puu(puuosoitin *, int s);
void hae(puuosoitin *, int avain);


int main(void)
{ 
	int valinta = -1, avaimet[MAX], i = 0, a, etp = 0,avain;
	int ala = 1, yla = MAX, maara; // 4): ala- ja yläraja
	char muisti[MAX];	
  	puuosoitin puu = NULL;
  
	printf("\nTasapainoitettu binäärihakupuu:\n");
	
	while (valinta != 0)
	{
		printf("\n1) Lue tiedosto ja rakenna puu\n");
		printf("2) Hae avain puusta\n");
		printf("3) Lisää yksittäinen avain puuhun\n");
		printf("4) Massalisäys\n");
		printf("0) Lopeta\n");
		printf("Valitse: ");
		scanf("%d", &valinta);
		
		if (valinta == 1)
		{
			FILE *tiedosto;
			tiedosto = fopen("HTavaimet.txt", "r");
			while(fgets(muisti, MAX, tiedosto) != NULL)
			{
				//printf("%s", muisti);
				/* Muutetaan kokonaisluvuiksi: */
				avaimet[i] = atoi(muisti);
				i ++;
			}
			fclose(tiedosto);
			for(a = 0; avaimet[a] != 0; a++)
			/*avaimet loppuu kun vastaan tulee nolla*/
  			{
    				lisaa_solmu(&puu, avaimet[a], &etp);
				
				/* Nähdään puun rakentuminen */
				tulosta_puu(&puu,10);
				printf("\n"); 
  			}
		
		}
		else if (valinta == 2)
		{
			/*1. Löytyykö puusta avaimet 6,1,10,16?*/
			/*3. Löytyykö puusta nyt avaimet 10,26 ja 32?*/
			printf("Anna haettava avain: ");
			scanf("%d", &avain);
			hae(&puu, avain);

		} 
		else if (valinta == 3)
		{
			/*2. Lisätään avaimet 26,24,22,20,18 ja 16*/
			printf("Anna lisättävä avain: ");
			scanf("%d", &avain);
			lisaa_solmu(&puu, avain, &etp);
			tulosta_puu(&puu,10);
			printf("\n");
		} 
		else if (valinta == 4)
		{
			/* Testaataan ohjelmaa kun avaimia on 10,100,1000,+ */  
			printf("Montako avainta lisätään: ");
			scanf("%d", &maara);

			/* Tarvitaan, kun halutaan useampi satunnainen*/ 				/* kokonaisluku */
			srand(time(0));

			for (int i=0; i < maara; i++)
			{
				/* Kaava, kun luvut halutaan tietylle välille */
				avain = (rand() % (yla - ala + 1)) + ala;
				
				lisaa_solmu(&puu, avain, &etp);
				
				/* Nähdään puun rakentuminen */
				tulosta_puu(&puu,10);
				printf("\n"); 
			}

		}
		else if (valinta == 0)
		{
			break;
		}
	}
	printf("\n");	
	return 0;
}

void lisaa_solmu(puuosoitin *emo, int luku, int *etp)
{
  if(!(*emo)) //emo = NULL eli solmu on tyhjä -> lisätään avain solmuun
  {
    *etp = 1;
    if(!(*emo = (puuosoitin)malloc(sizeof(puusolmu)))) //muistin varaus
    {
      perror("malloc");
      exit(1);
    }
    (*emo)->vasen = (*emo)->oikea = NULL;
    (*emo)->tila = 0;
    (*emo)->luku = luku;
  
  }else if(luku < (*emo)->luku)
  {
    /* kutsutaan funkiota rekursiivisesti */
    lisaa_solmu(&(*emo)->vasen, luku, etp);
    if(*etp)
    {
      switch((*emo)->tila)
      {
        case -1:
          (*emo)->tila = 0;
          *etp = 0;
          break;
        case 0:
          (*emo)->tila = 1;
          break;
        case 1:
          vasen_kierto(emo, etp);
      }
    }

  }else if(luku > (*emo)->luku)
  {
    lisaa_solmu(&(*emo)->oikea, luku, etp);
    if(*etp)
    {
      switch((*emo)->tila)
      {
        case 1:
          (*emo)->tila = 0;
          *etp = 0;
          break;
        case 0:
          (*emo)->tila = -1;
           break;
        case -1:
          oikea_kierto(emo, etp);
      }
    }

  }else
  {
    *etp = 0;
    printf("Luku '%d' on jo puussa.\n", luku);
  }
}

void vasen_kierto(puuosoitin *emo, int *etp)
{
  puuosoitin lapsi, lapsenlapsi;

  lapsi = (*emo)->vasen;
  if(lapsi->tila == 1) /* LL-kierto */
  {
    (*emo)->vasen = lapsi->oikea;
    lapsi->oikea = *emo;
    (*emo)->tila = 0;
    (*emo) = lapsi;
  } else /* LR-kierto */
  {
    lapsenlapsi = lapsi->oikea;
    lapsi->oikea = lapsenlapsi->vasen;
    lapsenlapsi->vasen = lapsi;
    (*emo)->vasen = lapsenlapsi->oikea;
    lapsenlapsi->oikea = *emo;
    switch(lapsenlapsi->tila)
    {
      case 1:
        (*emo)->tila = -1;
        lapsi->tila = 0;
        break;
      case 0:
        (*emo)->tila = lapsi->tila = 0;
        break;
      case -1:
        (*emo)->tila = 0;
        lapsi->tila = 1;
    }
    *emo = lapsenlapsi;
  }
  (*emo)->tila = 0;
  *etp = 0;
}

void oikea_kierto(puuosoitin *emo, int *etp)
{
  puuosoitin lapsi, lapsenlapsi;

  lapsi = (*emo)->oikea;
  if(lapsi->tila == -1) /* RR-kierto */
  {
    (*emo)->oikea = lapsi->vasen;
    lapsi->vasen = *emo;
    (*emo)->tila = 0;
    (*emo) = lapsi;
  } else /* RL-kierto */
  {
    lapsenlapsi = lapsi->vasen;
    lapsi->vasen = lapsenlapsi->oikea;
    lapsenlapsi->oikea = lapsi;
    (*emo)->oikea = lapsenlapsi->vasen;
    lapsenlapsi->vasen = *emo;
    switch(lapsenlapsi->tila)
    {
      case 1:
        (*emo)->tila = 0;
        lapsi->tila = -1;
        break;
      case 0:
        (*emo)->tila = lapsi->tila = 0;
        break;
      case -1:
        (*emo)->tila = 1;
        lapsi->tila = 0;
    }
    *emo = lapsenlapsi;
  }
  (*emo)->tila = 0;
  *etp = 0;
}

void tulosta_puu(puuosoitin *solmu, int s)
{
	/* Lopetetaan, jos solmu on tyhjä */
	if(!*solmu)
	{
		return;
	}
	/* Kasvatetaan solmujen väliä*/
	s += COUNT; //s = space

	/* Käsitellään ensin oikea lapsi*/
    	tulosta_puu(&(*solmu)->oikea, s);
 
	/* Tulostetaan solmu etäisyyden kasvattamisen jälkeen*/
    	printf("\n");
    	for (int i = COUNT; i < s; i++)
	{
        	printf(" ");
	}
    	printf("%d\n", (*solmu)->luku);
 
   	 /* Käsitellään vasen lapsi*/
   	tulosta_puu(&(*solmu)->vasen, s);
}

void hae(puuosoitin *solmu, int avain) 
{ 
	/*Avainta ei ole puussa*/
	if ((*solmu) == NULL)
	{
		printf("Avainta '%d' ei löydy puusta.\n", avain);
	}

	/* Avain löytyy puusta*/
	else if ((*solmu)->luku == avain)
	{
	       printf("Avain '%d' löytyy puusta.\n", avain); 
	}
     
	/*Jos haettava avain on suurempi kuin solmun avain, mennään oikealle*/
	else if ((*solmu)->luku < avain)
	{
        	hae(&(*solmu)->oikea, avain);
	}
  
	/* Jos haettava avain on pienempi kuin solmun avain, mennään*/
	/*vasemmalle*/
	else if ((*solmu)->luku > avain)
	{
		hae(&(*solmu)->vasen, avain); 
	}
} 

