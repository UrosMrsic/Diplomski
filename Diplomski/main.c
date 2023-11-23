#include"deklaracije.h"
struct knjige{
	char naslov[100];
	char autor[50];
	char godina[50];
	char zanr[50];
};
struct nalozi{
	char username[100];
	char password[100];
	int id;
};
struct korisnici{
	int id;
	char ime[100];
	char prezime[100];
	int danUplate;
	int mesecUplate;
	int danIsteka;
	int mesecIsteka;
};
struct zaduzenja{
	int id;
	char ime[100];
	char prezime[100];
	char naziv[100];
	int dan;
	int mesec;
};
struct knjige *k;
struct nalozi *n;
struct korisnici *u;
struct zaduzenja *z;
char opcija[20];
int brRed, brKnjiga, brNaloga, brKorisnika,brZaduzenja, admin=0;

			int main() {
				int i;
				ucitajKnjige();
				ucitajNaloge();
				ucitajZaduzenja();
				ucitajKorisnike();
				loadingBar();	
				system("cls");  
				naslov();
				login();
				free(k);
				free(n);
				free(u);
				free(z);
			}

//Funkcija koja prikazuje loading bar
void loadingBar()
{
    char a = 177;
	char b = 219;
	int i;
    system("color 07");
    printf("\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t      UCITAVA SE...\n\n");
    printf("\t\t\t\t\t");
    for(i=0; i<26; i++){
		printf("%c", a);
	}
    printf("\r");
    printf("\t\t\t\t\t");
    for(i=0; i<26; i++){
        printf("%c", b);
        Sleep(100);
    }
}

//Funkcija za ispis reda linija
void linije() {
	printf("\n------------------------------------------------------------------------------------------------\n");
}

//Funkcija za ispis naslova 'eBIBLIOTEKA'
void naslov() {
	linije();
	printf("\n\n            DDDDDDD  D  DDDDDDD  D        D  DDDDDDD  DDDDDDD  DDDDDDD  D     D     D     \n");
    printf("            D     D  D  D     D  D        D  D     D     D     D        D     D    D D    \n");
    printf("            D    D   D  D    D   D        D  D     D     D     D        D    D    D   D   \n");
    printf("     DDD    DDDDD    D  DDDDD    D        D  D     D     D     DDDDDDD  DDDDD    DDDDDDD  \n");
    printf("    D   D   D    D   D  D    D   D        D  D     D     D     D        D    D   D     D  \n");
    printf("   DDDDDDD  D     D  D  D     D  D        D  D     D     D     D        D    D   D     D  \n");
    printf("    D       D     D  D  D     D  D        D  D     D     D     D        D     D  D     D  \n");
    printf("     DDD    DDDDDDD  D  DDDDDDD  DDDDDDD  D  DDDDDDD     D     DDDDDDD  D     D  D     D  \n");
    printf("\n\t\t\t\t\t\t\t\t\t\t\t   v1.9");
}

//Funkcija koja racuna broj redova u tekstualnom fajlu, uz poziv f-je salje se i naziv .txt fajla
// i funkcija ocita broj redova koji se nalaze u .txt fajlu, ovo kasnije sluzi kako bi se video broj elemenata nekog fajla
int brRedova(char filename[100]) {
	char c;
	FILE *file;
	file=fopen(filename,"r");
	if(file==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	brRed=1;
	do{
		c=fgetc(file);
		if(c=='\n') brRed++;
	}while(c!=EOF);
	fclose(file);
	return brRed;
}

//Funkcija koja sluzi da ucita sve knjige iz .txt fajla u niz strukture k
void ucitajKnjige(){
	int i;
	FILE *fptr;

	brKnjiga=brRedova("Knjige.txt")/4;
	fptr=fopen("Knjige.txt","r");
	if(fptr==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	if((k=(struct knjige *)malloc(brKnjiga*sizeof(struct knjige)))==NULL)
		printf("Greska u nizu knjiga!");
	fseek(fptr, 0, SEEK_SET);
	for(i=0;i<brKnjiga;i++){
		fgets(k[i].naslov,100,fptr);
		fgets(k[i].autor,50,fptr);
		fgets(k[i].godina,50,fptr);
		fgets(k[i].zanr,50,fptr);
	}
	fclose(fptr);
}

//Funkcija koja sluzi za ispis menija i iscitavanje unete opcije od strane korisnika, ova f-ja je
// zaduzena za ispis svakog menija u programu
void opcije(int vrstaOpcije){
	int i=0,j=0;
	char ch;
	do{
		linije();
		if(admin){
			printf("\t\t\t\t\t\t\t\t\t\t\t  ADMIN");
		}
		if(vrstaOpcije==1){
			printf("\n\t\t\t\t----==== eBIBLIOTEKA ====----\n");
			if(admin){
				puts("\n - Ako zelite da vidite sve opcije za admina kucajte  ---->  ADMIN");
			}
			puts(" - Ako zelite da vidite sve opcije za knjige kucajte  ---->  KNJIGE"
				"\n - Ako zelite da vidite korisnike, kucajte  ---->  KORISNICI"
				"\n - Ako zelite da procitate istorijat programa, upisite ----> ISTORIJA"
				"\n - Ako zelite da se odjavite sa ovog naloga, upisite  ---->  ODJAVI"
				"\n - Ako zelite da izadjete iz programa, upisite  ---->  IZADJI");
			linije();
			printf("\n");
			gets(opcija);
			j=0;
			while (opcija[j]) {
				ch = opcija[j];
				opcija[j]=toupper(ch);
				j++;
			}
			if(!strcmp(opcija,"IZADJI"))
				exit(1);
			else if(!strcmp(opcija,"KNJIGE")){
				opcije(2);
			}
			else if(!strcmp(opcija,"ISTORIJA")){
				istorija();
			}
			else if(!strcmp(opcija,"KORISNICI")){
				opcije(3);
			}
			else if(!strcmp(opcija,"ADMIN") && admin){
				opcije(5);
			}
			else if(!strcmp(opcija,"ODJAVI")){
				login();
			}
			else{
				puts("\nNiste uneli dobru opciju");
			}
		}
		else if(vrstaOpcije==2){
			printf("\n\t\t\t\t----==== KNJIGE ====----\n");
			printf("\n - Ako zelite da vidite sve knjige kucajte  ---->  PRIKAZ"
				"\n - Ako zelite da nadjete posebno knjigu, upisite ----> NADJI"
				"\n - Ako zelite da unesete novu knjigu, kucajte  ---->  UNESI"
				"\n - Ako zelite da obrisete knjigu, upisite ----> BRISI"
				"\n - Ako zelite da se vratite, upisite  ---->  NAZAD");
			linije();
			printf("\n");
			gets(opcija);
			j=0;
			while (opcija[j]) {
				ch = opcija[j];
				opcija[j]=toupper(ch);
				j++;
			}
			if(!strcmp(opcija,"NAZAD"))
				opcije(1);
			else if(!strcmp(opcija,"PRIKAZ")){
				prikaziKnjige();
			}
			else if(!strcmp(opcija,"UNESI")){
				unesiKnjigu();
			}
			else if(!strcmp(opcija,"BRISI")){
				obrisiKnjigu();
			}
			else if(!strcmp(opcija,"NADJI")){
				nadjiKnjigu();
			}
			else if(!strcmp(opcija,"IZADJI")){
				exit(1);
			}
			else{
				puts("\nNiste uneli dobru opciju");
			}
		}
		else if(vrstaOpcije==3){
			printf("\n\t\t\t\t----==== KORISNICI ====----\n");
			puts("\n - Ako zelite da vidite sve korisnike, kucajte  ---->  PRIKAZ"
				"\n - Ako zelite da nadjete posebno korisnika, kucajte ----> NADJI"
				"\n - Ako zelite da unesete novog korisnika, kucajte  ---->  UNESI"
				"\n - Ako zelite da obrisete korisnika, kucajte ----> BRISI"
				"\n - Ako zelite da uplatite clanarinu korisniku, kucajte  ---->  UPLATI"
				"\n - Ako zelite da vidite sve opcije za zaduzenja, kucajte ----> ZADUZENJA"
				"\n - Ako zelite da se vratite, kucajte  ---->  NAZAD");
			linije();
			printf("\n");
			gets(opcija);
			j=0;
			while (opcija[j]) {
				ch = opcija[j];
				opcija[j]=toupper(ch);
				j++;
			}
			if(!strcmp(opcija,"NAZAD"))
				opcije(1);
			else if(!strcmp(opcija,"PRIKAZ")){
				prikaziKorisnika();
			}
			else if(!strcmp(opcija,"UNESI")){
				unesiKorisnika();
			}
			else if(!strcmp(opcija,"BRISI")){
				obrisiKorisnika();
			}
			else if(!strcmp(opcija,"NADJI")){
				nadjiKorisnika();
			}
			else if(!strcmp(opcija,"UPLATI")){
				uplatiKorisnika();
			}
			else if(!strcmp(opcija,"IZADJI")){
				exit(1);
			}
			else if(!strcmp(opcija,"ZADUZENJA")){
				opcije(4);
			}
			else{
				puts("\nNiste uneli dobru opciju");
			}
		}
		else if(vrstaOpcije==4){
			printf("\n\t\t\t\t----==== ZADUZENJA ====----\n");
			puts("\n - Ako zelite da vidite sva zaduzenja kucajte  ---->  PRIKAZ"
				"\n - Ako zelite da dodate novo zaduzenje, kucajte  ---->  UNESI"
				"\n - Ako zelite da obrisete, kucajte  ---->  BRISI"
				"\n - Ako zelite da se vratite nazad, kucajte  ---->  NAZAD");
			linije();
			printf("\n");
			gets(opcija);
			j=0;
			while (opcija[j]) {
				ch = opcija[j];
				opcija[j]=toupper(ch);
				j++;
			}
			if(!strcmp(opcija,"NAZAD"))
				opcije(3);
			else if(!strcmp(opcija,"PRIKAZ")){
				prikazZaduzenja();
			}
			else if(!strcmp(opcija,"UNESI")){
				unesiZaduzenje();
			}
			else if(!strcmp(opcija,"BRISI")){
				obrisiZaduzenje();
			}
			else if(!strcmp(opcija,"IZADJI")){
				exit(1);
			}
			else{
				puts("\nNiste uneli dobru opciju");
			}
		}
		else if(vrstaOpcije==5){
			printf("\n\t\t\t\t----==== NALOZI ====----\n");
			puts("\n - Ako zelite da vidite sve naloge, kucajte  ---->  PRIKAZ"
				"\n - Ako zelite da dodate nov nalog, kucajte  ---->  UNESI"
				"\n - Ako zelite da obrisete nalog, kucajte  ---->  BRISI"
				"\n - Ako zelite da se vratite nazad, kucajte  ---->  NAZAD");
			linije();
			printf("\n");
			gets(opcija);
			j=0;
			while (opcija[j]) {
				ch = opcija[j];
				opcija[j]=toupper(ch);
				j++;
			}
			if(!strcmp(opcija,"NAZAD"))
				opcije(1);
			else if(!strcmp(opcija,"PRIKAZ")){
				prikazNaloga();
			}
			else if(!strcmp(opcija,"UNESI")){
				unesiNalog();
			}
			else if(!strcmp(opcija,"BRISI")){
				obrisiNalog();
			}
			else if(!strcmp(opcija,"IZADJI")){
				exit(1);
			}
			else{
				puts("\nNiste uneli dobru opciju");
			}
		}
	}while(!i);
}

//Funkcija koja prikazuje istorijat verzija aplikacije, vidi se napredak aplikacije kroz verzije
void istorija(){
	linije();
	printf("1.0 - pocetak programa, naslov, linije i opcije\n1.1 - dodat je unos, prikaz, brisanje knjiga sa svim opcijama\n1.1.1 - dodata opcija nadji knjigu\n1.1.2 - trazenje je promenjeno sa id-a na naziv\n1.2 - napravljen je login\n1.2.1 - razlika izmedju admin i obicnog naloga\n1.2.2 - admin nalog moze da upravlja ostalim nalozima, dodaje nove i brise stare\n1.3 - korisnici knjiga ubaceni u program\n1.3.1 - prikaz, unos, brisanje i trazenje korisnika ubaceno u program\n1.4 - veza izmedju korisnika i knjiga ubacena pod nazivom zaduzenja\n1.4.1 - dodat je unos, prikaz i brisanje zaduzenja\n1.5 - validacija clanarina kod zaduzenja\n1.6 - napravljen sistem uplate clanarine korisniku\n1.7 - ubacen loading bar I slovo 'e' ispred naslova 'BIBLIOTEKA'\n1.8 - dodatno poliranje\n1.9 - dodata je provera kod uplate clanarine, da li je clanarina istekla, ako jeste pise se trenutni datum kao uplacen I broj meseci na trenutni datum kao datum isteka, a ako nije istekla samo se nadodaju novi meseci na prethodni datum\n");
}

//Funkcija koja je zaduzena za ispis svih knjiga
void prikaziKnjige(){
	int i;
	linije();
	printf("\n\t\t\t\t----==== PRIKAZ KNJIGA====----\n\n");
	free(k);
	ucitajKnjige();
	for(i=0;i<brKnjiga;i++){
		printf("-%d. knjiga:\n",i+1);
		printf("\tNaziv: %s",k[i].naslov);
		printf("\tAutor: %s",k[i].autor);
		printf("\tGodina Izdanja: %s",k[i].godina);
		printf("\tZanr: %s",k[i].zanr);
	}
}

//Funkcija koja je zaduzena za unos knjige u .txt fajl
void unesiKnjigu(){
	int i;
	char naziv[100],autor[50],godina[50],zanr[50];
	FILE *fptr;
	fptr=fopen("Knjige.txt","a");
	linije();
	printf("\n\t\t\t\t----==== UNOS KNJIGA====----\n\n");
	printf("\nUnesite naziv nove knjige: ");
	gets(naziv);
	printf("Unesite autora nove knjige: ");
	gets(autor);
	printf("Unesite godinu izdanja nove knjige: ");
	gets(godina);
	printf("Unesite zanr nove knjige: ");
	gets(zanr);
	fprintf(fptr,"%s",naziv);
	fprintf(fptr,"\n%s",autor);
	fprintf(fptr,"\n%s",godina);
	fprintf(fptr,"\n%s\n",zanr);
	fclose(fptr);
	free(k);
	ucitajKnjige();
	opcije(2);
}

//Funkcija koja je zaduzena za brisanje knjige iz .txt fajla
void obrisiKnjigu(){
	FILE *fileptr2;
	int provera=1;
    char filename[40],naziv[100];
    char ch;
    int delete_line, temp = 1,i;
	
    strcpy(filename,"Knjige.txt");
	linije();
	printf("\n\t\t\t ----==== BRISANJE KNJIGA ====----\n");
    fileptr2 = fopen("replika.txt", "w");
	if(fileptr2==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	fseek(fileptr2, 0, SEEK_SET);
	do{
		printf("\nUnesite naziv knjige koji zelite da obrisete: ");
		gets(naziv);
		fflush(stdin);
		strcat(naziv,"\n");
		for(i=0;i<brKnjiga;i++){
			if(!strcmp(naziv,k[i].naslov)){
				delete_line=i;
				provera=0;
			}
		}
		if(provera)
				printf("Ta knjiga ne postoji!");
	}while(provera);
	for(i=0;i<brKnjiga;i++){
		if(i!=delete_line){
			if(i==0)
				fprintf(fileptr2,"%s",k[i].naslov);
			else
				fprintf(fileptr2,"%s",k[i].naslov);
			fprintf(fileptr2,"%s",k[i].autor);
			fprintf(fileptr2,"%s",k[i].godina);
			fprintf(fileptr2,"%s",k[i].zanr);
		}
	}
    fclose(fileptr2);
    remove(filename);
    rename("replika.txt", filename);
	free(k);
	ucitajKnjige();
}

//Funkcija koja je zaduzena za trazenje knjiga u sistemu, npr unesete deo naziva ili prvu rec u nazivu i program
// ce naci sve knjige koje pocinju tim stringom koji unesete
void nadjiKnjigu(){
	int i, j, provera=0,br=0, provera2=0;
	char naziv[100];
	linije();
	printf("\nUnesite naziv knjige koji trazite: ");
	scanf("%s",naziv);
	fflush(stdin);
	strcat(naziv,"\n");
	for(i=0;i<brKnjiga;i++){
		provera=0;
		for(j=0;j<strlen(naziv)-1;j++){
			if(tolower(naziv[j])!=tolower(k[i].naslov[j])){
				provera=0;
				break;
			}
			else
				provera=1;
		}
		if(provera){
			printf("-%d. knjiga:\n",i+1);
			printf("\tNaziv: %s",k[i].naslov);
			printf("\tAutor: %s",k[i].autor);
			printf("\tGodina Izdanja: %s",k[i].godina);
			printf("\tZanr: %s",k[i].zanr);
			br++;
		}
	}
	//                                                               PONOVNO PRETRAZIVANJE U SLUCAJU VISKA KNJIGA KOJE SE SLICNO ZOVU
	/*if(br>1){
		printf("\nPostoji vise knjiga sa takvim nazivom, na koju ste tacno mislili: ");
		scanf("%s",naziv);
		fflush(stdin);
		strcat(naziv,"\n");
		for(i=0;i<brKnjiga;i++){
			if(!strcmp(naziv,k[i].naslov)){
			printf("-%d. knjiga:\n",i+1);
			printf("\tNaziv: %s",k[i].naslov);
			printf("\tAutor: %s",k[i].autor);
			printf("\tGodina Izdanja: %s",k[i].godina);
			printf("\tZanr: %s\n",k[i].zanr);
			}
			else
				provera=0;
		}
	}*/
	if(br==0) printf("Ta knjiga ne postoji!");
}

//Funkcija koja je zaduzena za ucitavanje svih naloga u niz strukture iz .txt fajla
void ucitajNaloge(){
	int i;
	FILE *fptr;
	char id[100];
	brNaloga=brRedova("login.txt")/3;
	fptr=fopen("login.txt","r");
	if(fptr==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	if((n=(struct nalozi *)malloc(brNaloga*sizeof(struct nalozi)))==NULL)
		printf("Greska u nizu knjiga!");
	fseek(fptr, 0, SEEK_SET);
	for(i=0;i<brNaloga;i++){
		fgets(id,100,fptr);
		fgets(n[i].username,100,fptr);
		fgets(n[i].password,100,fptr);
		n[i].id=atoi(id);
	}
	fclose(fptr);
}

//Funkcija za prijavljivanje naloga, korisnik unosi username i password i ova f-ja proverava
// da li taj nalog postoji
void login(){
	char username[100],password[100],c;
	int i=0,provera=0;
	admin=0;
	strcpy(username,"");

	do{
		i=0;
		linije();
		provera=0;
		printf("\n - Username: ");
		gets(username);
		printf(" - Password: ");
		do{
			password[i]=getch();
			if(password[i]==8)
				continue;
			if(password[i]!='\r'){
				printf("*");
			}
			i++;
		}while(password[i-1]!='\r');
		password[i-1]='\n';
		password[i] = '\0';
		strcat(username,"\n");
		printf("\n");
		for(i=0;i<brNaloga;i++){
		if(!strcmp(username,n[i].username) && !strcmp(password,n[i].password)){
				if(n[i].id==1)
					admin=1;
				printf("\nUspesno ste se prijavili!");
				provera=1;
			}
		}
		if(!provera)
			printf("\n\nUneli ste pogresne podatke za prijavu!\n");
	}while(!provera);
	opcije(1);
}

//Funkcija koja sluzi da ucita sve korisnike iz .txt fajla u niz strukture
void ucitajKorisnike(){
	int i;
	char id[100], danU[100], danI[100], mesecU[100], mesecI[100];
	FILE *fptr;
	brKorisnika=brRedova("Korisnici.txt")/7;
	fptr=fopen("Korisnici.txt","r");
	if(fptr==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	if((u=(struct korisnici *)malloc(brKorisnika*sizeof(struct korisnici)))==NULL)
		printf("Greska u nizu knjiga!");
	fseek(fptr, 0, SEEK_SET);
	for(i=0;i<brKorisnika;i++){
		fgets(id,100,fptr);
		fgets(u[i].ime,100,fptr);
		fgets(u[i].prezime,100,fptr);
		fgets(danU ,100,fptr);
		fgets(mesecU ,100,fptr);
		fgets(danI ,100,fptr);
		fgets(mesecI ,100,fptr);
		u[i].danUplate=atoi(danU);
		u[i].danIsteka=atoi(danI);
		u[i].mesecIsteka=atoi(mesecI);
		u[i].mesecUplate=atoi(mesecU);
		u[i].id=atoi(id);
	}
	fclose(fptr);
}

//Funkcija koja sluzi da ispise sve korisnike
void prikaziKorisnika(){
	int i;
	linije();
	printf("\n\t\t\t\t----==== PRIKAZ KORISNIKA====----\n\n");
	for(i=0;i<brKorisnika;i++){
		printf("-%d. korisnik:\n",i+1);
		printf("\tID: %d\n",u[i].id);
		printf("\tIme: %s",u[i].ime);
		printf("\tPrezime: %s",u[i].prezime);
		printf("\tDatum uplate clanarine: %d.%d.\n",u[i].danUplate,u[i].mesecUplate);
		printf("\tDatum isteka clanarine: %d.%d.\n",u[i].danIsteka,u[i].mesecIsteka);
	}
}

//Funkcija koja sluzi da korisnik aplikacije unese novog korisnika biblioteke u .txt fajl
void unesiKorisnika(){
	int i,id,m,d,brojClanarina;
	char ime[100],prezime[100],mesec[50],dan[50];
	FILE *fptr;
	time_t time_raw_format;
    struct tm * ptr_time;

	time ( &time_raw_format );
    ptr_time = localtime ( &time_raw_format );
	if(strftime(dan,50,"%d",ptr_time) == 0){
        perror("Couldn't prepare formatted string");
    }
	if(strftime(mesec,50,"%m",ptr_time) == 0){
        perror("Couldn't prepare formatted string");
    }
	d=atoi(dan);
	m=atoi(mesec);
	fptr=fopen("Korisnici.txt","a");
	if(fptr==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	linije();
	printf("\n\t\t\t\t----==== UNOS KORISNIKA====----\n\n");
	printf("\nUnesite ime novog korisnika: ");
	gets(ime);
	printf("Unesite prezime novog korisnika: ");
	gets(prezime);
	printf("Unesite koliko je meseci uplaceno: ");
	scanf("%d",&brojClanarina);
	fflush(stdin);
	id=u[brKorisnika-1].id+(u[brKorisnika-1].id%43);
	fprintf(fptr,"%d",id);
	fprintf(fptr,"\n%s",ime);
	fprintf(fptr,"\n%s",prezime);
	fprintf(fptr,"\n%d",d);
	fprintf(fptr,"\n%d",m);
	fprintf(fptr,"\n%d",d);
	if(m+brojClanarina>12)
		m=(m+brojClanarina)%12;
	fprintf(fptr,"\n%d\n",m);
	fclose(fptr);
	free(u);
	ucitajKorisnike();
	opcije(3);
}

//Funkcija koja sluzi da obrise korisnika biblioteke iz .txt fajla
void obrisiKorisnika(){
	FILE *fileptr2;
	int provera=1,id;
    char filename[40],naziv[100], ime[100], prezime[100];
    char ch;
    int delete_line, temp = 1,i,p=0,br=0,br2=0;
	

    strcpy(filename,"Korisnici.txt");
	linije();
	printf("\n\t\t\t ----==== BRISANJE KORISNIKA ====----\n");
    fileptr2 = fopen("replikaKorisnici.txt", "w");
	if(fileptr2==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	fseek(fileptr2, 0, SEEK_SET);
	do{
		printf("\nUnesite ime i prezime korisnika kog zelite da obrisete: ");
		gets(naziv);
		printf("Unesite id korisnika kog zelite da obrisete: ");
		scanf("%d",&id);
		fflush(stdin);
		for(i=0;i<strlen(naziv);i++){
			if(!p){
				if(naziv[i]!=' '){
					ime[br2]=naziv[i];
					br2++;
				}
				else{
					ime[br2]='\n';
					br2++;
					p=1;
					continue;
				}
			}
			if(p){
					prezime[br]=naziv[i];
					br++;
			}
		}
		ime[br2]='\0';
		prezime[br]='\n';
		br++;
		prezime[br]='\0';
		for(i=0;i<brKorisnika;i++){
			if(!strcmp(ime,u[i].ime) && !strcmp(prezime,u[i].prezime) && id==u[i].id){
				delete_line=i;
				provera=0;
			}
		}
		if(provera){
				printf("Taj korisnik ne postoji!");
				br=0;
				br2=0;
		}
	}while(provera);
	for(i=0;i<brKorisnika;i++){
		if(i!=delete_line){
			if(i==0)
				fprintf(fileptr2,"%d\n",u[i].id);
			else
				fprintf(fileptr2,"%d\n",u[i].id);
			fprintf(fileptr2,"%s",u[i].ime);
			fprintf(fileptr2,"%s",u[i].prezime);
			fprintf(fileptr2,"%d\n",u[i].danUplate);
			fprintf(fileptr2,"%d\n",u[i].mesecUplate);
			fprintf(fileptr2,"%d\n",u[i].danIsteka);
			fprintf(fileptr2,"%d\n",u[i].mesecIsteka);
		}
	}
    fclose(fileptr2);
    remove(filename);
    rename("replikaKorisnici.txt", filename);
	free(u);
	ucitajKorisnike();
}

//Funkcija koja sluzi da nadje korisnika biblioteke, korisnik aplikacije unese ime ili prezime ili deo imena ili prezimena
// i program ce ispisati sve korisnike biblioteke koji imaju taj string na pocetku imena ili prezimena
void nadjiKorisnika(){
	int i, j, provera=0,br=0, provera2=0;
	char naziv[100];
	linije();
	printf("\nUnesite ime ili prezime korisnika kog trazite: ");
	scanf("%s",naziv);
	fflush(stdin);
	strcat(naziv,"\n");
	for(i=0;i<brKorisnika;i++){
		provera=0;
		for(j=0;j<strlen(naziv)-1;j++){
			if(tolower(naziv[j])!=tolower(u[i].ime[j])){
				provera=0;
				break;
			}
			else
				provera=1;
		}
		if(!provera){
		for(j=0;j<strlen(naziv)-1;j++){
			if(tolower(naziv[j])!=tolower(u[i].prezime[j])){
				provera=0;
				break;
			}
			else
				provera=1;
		}
		}
		if(provera>0){
			printf("-%d. korisnik:\n",i+1);
			printf("\tID: %d\n",u[i].id);
			printf("\tIme: %s",u[i].ime);
			printf("\tPrezime: %s",u[i].prezime);
			printf("\tDatum uplate clanarine: %d.%d.\n",u[i].danUplate,u[i].mesecUplate);
			printf("\tDatum isteka clanarine: %d.%d.\n",u[i].danIsteka,u[i].mesecIsteka);
			br++;
		}
	}
	if(br==0) printf("Taj korisnik ne postoji!");
}

//Funkcija koja ucitava sva zaduzenja iz .txt datoteke u aplikaciju
void ucitajZaduzenja(){
	int i,d,m;
	char id[100],dan[50],mesec[50];
	FILE *fptr;
	brZaduzenja=brRedova("Zaduzenja.txt")/6;
	fptr=fopen("Zaduzenja.txt","r");
	if(fptr==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	if((z=(struct zaduzenja *)malloc(brZaduzenja*sizeof(struct zaduzenja)))==NULL)
		printf("Greska u nizu knjiga!");
	fseek(fptr, 0, SEEK_SET);
	for(i=0;i<brZaduzenja;i++){
		fgets(id,100,fptr);
		fgets(z[i].ime,100,fptr);
		fgets(z[i].prezime,100,fptr);
		fgets(z[i].naziv,100,fptr);
		fgets(dan ,50,fptr);
		fgets(mesec ,50,fptr);
		z[i].dan=atoi(dan);
		z[i].mesec=atoi(mesec);
		z[i].id=atoi(id);
	}
	fclose(fptr);
}

//Funkcija koja ispisuje sva zaduzenja 
void prikazZaduzenja(){
	int i;
	linije();
	printf("\n\t\t\t\t----==== PRIKAZ ZADUZENJA ====----\n\n");
	for(i=0;i<brZaduzenja;i++){
		printf(" - %d:\n",i+1);
		printf("\tID: %d\n",z[i].id);
		printf("\tIme: %s",z[i].ime);
		printf("\tPrezime: %s",z[i].prezime);
		printf("\tNaziv knjige: %s",z[i].naziv);
		printf("\tDatum uzimanja knjige: %d.%d.\n",z[i].dan,z[i].mesec);
	}
}

//Funkcija koja upisuje novo zaduzenje koje je korisnik uneo u .txt fajl
void unesiZaduzenje(){
	int i,id,provera=0,provera2=0,d,m;
	char ime[100],prezime[100],naziv[100],dan[50],mesec[50],datum[50];
	FILE *fptr;
	time_t time_raw_format;
    struct tm * ptr_time;

	time ( &time_raw_format );
    ptr_time = localtime ( &time_raw_format );
	if(strftime(dan,50,"%d",ptr_time) == 0){
        perror("Couldn't prepare formatted string");
    }
	if(strftime(mesec,50,"%m",ptr_time) == 0){
        perror("Couldn't prepare formatted string");
    }
	d=atoi(dan);
	m=atoi(mesec);
	fptr=fopen("Zaduzenja.txt","a");
	linije();
	printf("\n\t\t\t      ----==== UNOS ZADUZENJA====----\n\n");

	do{
	printf("\n - Unesite ime korisnika: ");
	gets(ime);
	if(!strcmp(ime,"izadji") || !strcmp(ime,"IZADJI"))
		opcije(4);
	printf(" - Unesite prezime korisnika: ");
	gets(prezime);
	if(!strcmp(prezime,"izadji") || !strcmp(prezime,"IZADJI"))
		opcije(4);
	strcat(ime,"\n");
	strcat(prezime,"\n");
	for(i=0;i<brKorisnika;i++){
		if(!strcmp(ime,u[i].ime) && !strcmp(prezime,u[i].prezime)){
			if(u[i].mesecIsteka<m){
				printf("\tOvom korisniku je istekla clanarina!");
				provera=2;
			}
			else if(u[i].mesecIsteka==m){
				if(u[i].danIsteka<d){
					printf("\tOvom korisniku je istekla clanarina!");
					provera=2;
				}
			}
			else
				provera=1;
		}
	}
	if(!provera)
		printf("\tTaj korisnik ne postoji!");
	if(provera==2)
		provera=0;
	}while(!provera);
	
	do{
	printf(" - Unesite naziv knjige: ");
	fflush(stdin);
	gets(naziv);
	fflush(stdin);
	strcat(naziv,"\n");
	for(i=0;i<brKorisnika;i++){
		if(!strcmp(naziv,k[i].naslov)){
			provera2=1;
		}
	}
	if(!provera2)
		printf("\tTa knjiga ne postoji!\n");
	}while(!provera2);
	
	printf (" - Datum uzimanja knjige: %d.%d.", d,m);

    
	id=z[brZaduzenja-1].id+1;
	fprintf(fptr,"%d\n",id);
	fprintf(fptr,"%s",ime);
	fprintf(fptr,"%s",prezime);
	fprintf(fptr,"%s",naziv);
	fprintf(fptr,"%d\n",d);
	fprintf(fptr,"%d\n",m);
	fclose(fptr);
	free(z);
	ucitajZaduzenja();
	opcije(4);
}

//Funkcija koja brise zeljeno zaduzenje iz .txt fajla
void obrisiZaduzenje(){
	FILE *fileptr2;
	int provera=1;
    char filename[40],naziv[100], ime[100], prezime[100],naslov[100];
    char ch;
    int delete_line, temp = 1,i,p=0,br=0,br2=0,brojac=0,id;
	
    strcpy(filename,"Zaduzenja.txt");
	linije();
	printf("\n\t\t\t    ----==== BRISANJE ZADUZENJA ====----\n");
    fileptr2 = fopen("replikaZaduzenja.txt", "w");
	if(fileptr2==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	fseek(fileptr2, 0, SEEK_SET);
	do{
		printf("\n - Unesite ime i prezime korisnika kog zelite da obrisete: ");
		gets(naziv);
		printf(" - Unesite i naziv knjige: ");
		gets(naslov);
		fflush(stdin);
		for(i=0;i<strlen(naziv);i++){
			if(!p){
				if(naziv[i]!=' '){
					ime[br2]=naziv[i];
					br2++;
				}
				else{
					ime[br2]='\n';
					br2++;
					p=1;
					continue;
				}
			}
			if(p){
					prezime[br]=naziv[i];
					br++;
			}
		}
		ime[br2]='\0';
		prezime[br]='\n';
		br++;
		prezime[br]='\0';
		strcat(naslov,"\n");
		for(i=0;i<brZaduzenja;i++){
			if(!strcmp(ime,z[i].ime) && !strcmp(prezime,z[i].prezime) && !strcmp(naslov,z[i].naziv)){
				brojac++;
				delete_line=i;
				provera=0;
			}
		}
		if(brojac>1){
			printf(" - Unesite id zaduzenja: ");
			scanf("%d",&id);
			fflush(stdin);
			for(i=0;i<brZaduzenja;i++){
				if(!strcmp(ime,z[i].ime) && !strcmp(prezime,z[i].prezime) && !strcmp(naslov,z[i].naziv) && id==z[i].id){
					provera=0;
					delete_line=i;
				}
			}
		}
		if(provera){
				printf("\tTo zaduzenje ne postoji!");
				br=0;
				br2=0;
		}
	}while(provera);
	for(i=0;i<brZaduzenja;i++){
		if(i!=delete_line){
			if(i==0)
				fprintf(fileptr2,"%d\n",z[i].id);
			else
				fprintf(fileptr2,"%d\n",z[i].id);
			fprintf(fileptr2,"%s",z[i].ime);
			fprintf(fileptr2,"%s",z[i].prezime);
			fprintf(fileptr2,"%s",z[i].naziv);
			fprintf(fileptr2,"%d\n",z[i].dan);
			fprintf(fileptr2,"%d\n",z[i].mesec);
		}
	}
    fclose(fileptr2);
    remove(filename);
    rename("replikaZaduzenja.txt", filename);
	free(z);
	ucitajZaduzenja();
}

//Funkcija koja je zaduzena za uplacivanje clanarina korisniku
void uplatiKorisnika(){
	FILE *fileptr2;
	int provera=0,m,d,brDan=0,brMes=0,kraj=0,brMeseci;
    char filename[40],naziv[100], ime[100], prezime[100],datum[50],dan[50],mesec[50],datumIsteka[50];
    char ch,temp2[50];
    int indexKorisnika, temp = 1,i,p=0,br=0,br2=0;
	time_t time_raw_format;
    struct tm * ptr_time;

	time ( &time_raw_format );
    ptr_time = localtime ( &time_raw_format );
    if(strftime(datum,50,"%d.%m.",ptr_time) == 0){
        perror("Couldn't prepare formatted string");
    }
	if(strftime(dan,50,"%d",ptr_time) == 0){
        perror("Couldn't prepare formatted string");
    }
	if(strftime(mesec,50,"%m",ptr_time) == 0){
        perror("Couldn't prepare formatted string");
    }

	strcpy(filename,"Korisnici.txt");
    fileptr2 = fopen("replikaKorisnici.txt", "w");
	if(fileptr2==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	fseek(fileptr2, 0, SEEK_SET);

	prikaziKorisnika();
	do{
		printf("\nUnesite ime i prezime korisnika kom zelite da uplatite clanarinu: ");
		gets(naziv);
		fflush(stdin);
		fflush(stdin);
		for(i=0;i<strlen(naziv);i++){
			if(!p){
				if(naziv[i]!=' '){
					ime[br2]=naziv[i];
					br2++;
				}
				else{
					ime[br2]='\n';
					br2++;
					p=1;
					continue;
				}
			}
			if(p){
					prezime[br]=naziv[i];
					br++;
			}
		}
		ime[br2]='\0';
		prezime[br]='\n';
		br++;
		prezime[br]='\0';
		for(i=0;i<brKorisnika;i++){
			if(!strcmp(ime,u[i].ime) && !strcmp(prezime,u[i].prezime)){
				indexKorisnika=i;
				provera=1;
			}
		}
		if(!provera){
				printf("Taj korisnik ne postoji!");
				br=0;
				br2=0;
		}
	}while(!provera);
	printf("Unesite broj meseci koji zelite da uplatite: ");
	scanf("%d",&brMeseci);
	fflush(stdin);
	kraj=0;
	brDan=0;
	brMes=0;
	d=atoi(dan);
	m=atoi(mesec);

	if(u[indexKorisnika].mesecIsteka<m){
		u[indexKorisnika].danUplate=d;
		u[indexKorisnika].mesecUplate=m;
		u[indexKorisnika].danIsteka=d;
		if(m+brMeseci>12){
			brMeseci=(m+brMeseci)%12;
			u[indexKorisnika].mesecIsteka=brMeseci;
		}
		else
			u[indexKorisnika].mesecIsteka=m+brMeseci;
	}
	else if(u[indexKorisnika].mesecIsteka==m){
		if(u[indexKorisnika].danIsteka<d){
			u[indexKorisnika].danUplate=d;
			u[indexKorisnika].mesecUplate=m;
			u[indexKorisnika].danIsteka=d;
			if(m+brMeseci>12){
				brMeseci=(m+brMeseci)%12;
				u[indexKorisnika].mesecIsteka=brMeseci;
			}
			else
				u[indexKorisnika].mesecIsteka=m+brMeseci;
		}
	}
	else{
		if(u[indexKorisnika].mesecIsteka+brMeseci>12){
				brMeseci=(u[indexKorisnika].mesecIsteka+brMeseci)%12;
				u[indexKorisnika].mesecIsteka=brMeseci;
			}
			else
				u[indexKorisnika].mesecIsteka+=brMeseci;
		
	}
	for(i=0;i<brKorisnika;i++){
		if(i==0)
			fprintf(fileptr2,"%d\n",u[i].id);
		else
			fprintf(fileptr2,"%d\n",u[i].id);
		fprintf(fileptr2,"%s",u[i].ime);
		fprintf(fileptr2,"%s",u[i].prezime);
		fprintf(fileptr2,"%d\n",u[i].danUplate);
		fprintf(fileptr2,"%d\n",u[i].mesecUplate);
		fprintf(fileptr2,"%d\n",u[i].danIsteka);
		fprintf(fileptr2,"%d\n",u[i].mesecIsteka);
	}
    fclose(fileptr2);
    remove(filename);
    rename("replikaKorisnici.txt", filename);
	free(u);
	ucitajKorisnike();
}

//Funkcija koja sluzi da prikaze sve naloge
void prikazNaloga(){
	int i;
	linije();
	printf("\n\t\t\t\t----==== PRIKAZ NALOGA ====----\n\n");
	for(i=1;i<brNaloga;i++){
		printf(" - %d:\n",i);
		printf("\tID: %d\n",n[i].id);
		printf("\tUsername: %s",n[i].username);
		printf("\tPassword: %s",n[i].password);
	}
}

//Funkcija koja sluzi da se unese novi nalog u .txt fajl
void unesiNalog(){
	int i,id;
	char user[100],pass[100],mesecUplate[50],mesecIsteka[50];
	FILE *fptr;
	fptr=fopen("login.txt","a");
	linije();
	printf("\n\t\t\t\t----==== UNOS NALOGA====----\n\n");
	printf("\nUnesite username: ");
	gets(user);
	printf("Unesite password: ");
	gets(pass);
	id=n[brNaloga-1].id+(n[brNaloga-1].id%43);
	fprintf(fptr,"%d\n",id);
	fprintf(fptr,"%s\n",user);
	fprintf(fptr,"%s\n",pass);
	fclose(fptr);
	free(n);
	ucitajNaloge();
	opcije(5);
}

//Funkcija koja sluzi da se zeljeni fajl obrise iz .txt datoteke
void obrisiNalog(){
	FILE *fileptr2;
	int provera=1,provera2=1;
    char filename[40],username[100],password[100];
    char ch;
    int delete_line, temp = 1,i;
	
    strcpy(filename,"login.txt");
	linije();
	printf("\n\t\t\t ----==== BRISANJE NALOGA ====----\n");
    fileptr2 = fopen("replikaLogin.txt", "w");
	if(fileptr2==NULL){
		puts("Neuspesno otvaranje za citanje");
		exit(1);
	}
	fseek(fileptr2, 0, SEEK_SET);
	do{
		printf("\nUnesite username koji zelite da obrisete\nUsername: ");
		gets(username);
		fflush(stdin);
		strcat(username,"\n");
		for(i=0;i<brNaloga;i++){
			if(!strcmp(username,n[i].username)){
				printf("Molim vas unesite password tog naloga.\n");
				do{
					printf("Password: ");
					gets(password);
					strcat(password,"\n");
					if(!strcmp(password,n[i].password)){
						delete_line=i;
						provera2=0;
						provera=0;
					}
					else{
						printf("Probajte ponovo!\n");
					}
				}while(provera2);
			}
		}
		if(provera)
				printf("Taj nalog ne postoji!");
	}while(provera);	
	for(i=0;i<brNaloga;i++){
		if(i!=delete_line){
			fprintf(fileptr2,"%d\n",n[i].id);
			fprintf(fileptr2,"%s",n[i].username);
			fprintf(fileptr2,"%s",n[i].password);
		}
	}
    fclose(fileptr2);
    remove(filename);
    rename("replikaLogin.txt", filename);
	free(n);
	ucitajNaloge();
}