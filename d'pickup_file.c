#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct
{
    char name[50], alamat_pengirim[50], alamat_penerima[50];
    int kg;
	double price, dist;
}a;

struct
{
	char adm[50];
	char pwadm[50];
}admin;

struct user
{
	char nama_lengkap[50];
	char email[50];
	char password [50];
	char username [50];
	int tanggal;
	int bulan;
	int tahun;
};

void takeinput(char ch[50])
{

	fgets(ch,50,stdin);
	ch[strlen(ch)-1] = 0; 
}

char membuat_username (char email[50], char username[50])
{
	int i;
	for(i=0;i<=strlen(email);i++)
	{
		if(email[i] == '@') break;
		else username[i] = email[i];
	}
}

bool IsSameString(const char *_dest,const char *src)
{
	if (strcmp(_dest, src) == 0)
		return TRUE;
	return FALSE;
}

bool validateGmail(const char* gmail)
{
	const char* validate = "@gmail.com";
	char* res = strrchr(gmail, '@');
	if (!res)
		{
		printf("Domain tidak valid, masukan kembali email anda\n");
		return FALSE;
	}
	
	if (!IsSameString(validate, res))
	{
		printf("Domain tidak valid, masukan kembali email anda\n");
		return FALSE;
	}
	return TRUE;
}

void membuat_password(char pwd[50])
{
	int i;
	char ch;
	while(1)
	{
		ch = getch();
		if(ch == ENTER || ch == TAB)
		{
			pwd[i] = '\0';
			break;
		}
		else if(ch == BCKSPC)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
		}
		else
		{
			pwd[i++] = ch;
			printf("* \b");
		}
	}
}

void signup()
{
	FILE *f_user;
	int usrFound = 0,i=1;
	struct user user;
	char password2[50];
	system("cls");
	membuat_username(user.email,user.username);
	f_user = fopen("List user.dat","ab");
	
	printf("Nama Lengkap\t:\t"); takeinput(user.nama_lengkap);
	
	do
	{
		printf("Masukkan Email\t:\n"); takeinput(user.email);

	} while (!validateGmail(user.email));
			
	printf("Masukkan Tanggal Lahir (DD/MM/YY)\n"); 
	printf("Tanggal\t\t:\t"); scanf("%d",&user.tanggal);
	printf("Bulan\t\t:\t"); scanf("%d",&user.bulan);
	printf("Tahun\t\t:\t"); scanf("%d",&user.tahun);
	printf("Masukkan password\t:"); membuat_password(user.password);
	printf("\nKonfirmasi password\t:"); membuat_password(password2);
	
			
	if(!strcmp(user.password,password2))
	{
		membuat_username(user.email,user.username);
		f_user = fopen("List user.dat","ab+");
		
		printf("\n\n\t\t====Data Anda====\n");
		printf("\n%d.\tNama\t\t\t: %s\n",i,user.nama_lengkap);
		printf("\tUsername\t\t: %s\n",user.username);
		printf("\tEmail\t\t: %s\n",user.email);
		printf("\tTanggal Lahir\t: %d/%d/%d\n",user.tanggal,user.bulan,user.tahun);
		printf("\tPassword\t: %s\n",user.password);
		printf("\n");
        getchar();fwrite(&user,sizeof(struct user),1,f_user);
		if(fwrite !=0)
		{
			printf("\nPendaftaran pengguna berhasil, username anda %s\n",user.username);
		} 
		else 
		{
			printf("\n\nMaaf! Anda memasukkan data yang salah :(");
		}
		fclose(f_user);
	}
	else
	{
		printf("\n\nPassword tidak cocok");
		Beep(600,500);
	}
	
}

void login()
{
	FILE *f_user;
	char username[50], pword[50];
	int usrFound = 0;
	struct user usr;
	
	system("cls");
	printf("Masukkan username\t:\t"); takeinput(username);
	printf("Masukkan password\t:\t"); membuat_password(pword);	
	f_user = fopen("List user.dat", "rb");
	while(fread(&usr,sizeof(struct user),1,f_user))
	{
		if(!strcmp(usr.username,username))
		{
			if(!strcmp(usr.password,pword))
			{	
				printf("\nLogin berhasil\n");
			}
			else
			{
				printf("\n\nPassword salah!");
				Beep(800,300);
			}
			usrFound = 1;
		}
	}if(!usrFound)
	{
		printf("\nPengguna tidak terdaftar!\n");
		Beep(800,300);login();
	}
	fclose(f_user);
	
}

void input_barang(){

	FILE *Barang;
	int y,n,total;
    Barang = fopen("List barang.dat", "ab+"); 
    
    printf("\n--------Silahkan input barang yang akan dikirim--------\n");
    printf("Banyak barang : "); scanf("%d", &n);
    getchar();
    for (y = 1; y <= n; y++)
    {
        printf("%d.\tNama Barang\t\t:\t ", y); gets(a.name);
        printf("\tAlamat Pengirim\t\t:\t "); gets(a.alamat_pengirim);
        printf("\tAlamat Penerima\t\t:\t "); gets(a.alamat_penerima);
        printf("\tBerat barang(Kg)\t:\t "); scanf("%d", &a.kg); 
		printf("\tJarak Rumah(Km)\t\t:\t "); scanf("%lf", &a.dist); 
		printf("\n");
        getchar();
        
        //perhitungan harga angkut barang berdasarkan jarak
        a.price=a.dist*10000;
        
        fwrite(&a,sizeof(a), 1, Barang); 
    }
    fclose(Barang);

    printf("------List Barang-----\n\n");
    int i = 1;
    Barang = fopen("List barang.dat", "rb");
    while (fread(&a, sizeof(a), 1, Barang) == 1)
    {
        printf("%d.\tNama Barang\t\t: %s\n", i, a.name);
        printf("\tAlamat Pengirim\t: %s\n", a.alamat_pengirim);
        printf("\tAlamat Penerima\t: %s\n", a.alamat_penerima);
        printf("\tBerat Barang\t: %d Kg\n", a.kg);
        printf("\tJarak Rumah\t: %.2f Km\n", a.dist);
        printf("\tHarga Barang\t: Rp.%.2f\n", a.price);
        printf("\tStatus\t\t: Pesanan sedang diproses\n");
        i++;
    }
    fclose(Barang);
    getch();
    system("cls");
}

void list_barang(){
	FILE *Barang;
	int no_struct;
	long int offset_byte;
	printf("------List Barang-----\n\n");
    int i = 1;
    Barang = fopen("List barang.dat", "rb");
    while (fread(&a, sizeof(a), 1, Barang) == 1)
    {
        printf("%d.\tNama Barang\t: %s\n", i, a.name);
        printf("\tAlamat Pengirim\t:%s\n", a.alamat_pengirim);
        printf("\tAlamat Penerima\t:%s \n", a.alamat_penerima);
        printf("\tBerat Barang\t: %dkg\n", a.kg);
        printf("\tJarak Rumah\t: %.2fkm\n", a.dist);
        printf("\tHarga Barang\t: Rp.%.2f\n", a.price);
        i++;
    }
    fclose(Barang);
    getch();Barang = fopen("List barang.dat", "rb");
	printf("Silahkan masukkan nomor barang yang dicari: ");
	scanf("%d", &no_struct);system("cls");
	offset_byte = (no_struct - 1) * sizeof(a);
	fseek(Barang, offset_byte, SEEK_SET);
	if (fread(&a, sizeof (a), 1, Barang) == 0){
	printf("Barang yang dicari tidak dapat ditemukan pada list.\n");
	} else {
		printf("\tNama Barang\t: %s\n", a.name);
        printf("\tAlamat Pengirim\t:%s\n ",a.alamat_pengirim);
        printf("\tAlamat Penerima\t:%s\n ",a.alamat_penerima);
        printf("\tBerat Barang\t: %d Kg\n", a.kg);
        printf("\tJarak Rumah\t: %.2f Km\n", a.dist);
        printf("\tHarga Barang\t: Rp.%.2f\n", a.price);
	}
	fclose(Barang);
	getch();

    system("cls");
}

void hapus_barang(){
	FILE *Barang;
    FILE *Barang2;
    char v[225];
    
    printf("------OUTPUT READING BINER-----\n\n");
    int i = 1;
    Barang = fopen("List barang.dat", "rb"); 

    while (fread(&a, sizeof(a), 1, Barang) == 1) 

    {
        printf("%d.\tNama Barang\t: %s\n", i, a.name);
        printf("\tAlamat Pengirim\t:%s\n ",a.alamat_pengirim);
        printf("\tAlamat Penerima\t:%s\n ",a.alamat_penerima);
        printf("\tBerat Barang\t: %dkg\n", a.kg);
        printf("\tJarak Rumah\t: %.2fkm\n", a.dist);
        printf("\tHarga Barang\t: Rp.%.2f\n", a.price);
        i++;
    }
    fclose(Barang);
    getch();
    Barang = fopen("List barang.dat", "rb"); 
    Barang2 = fopen("List barang2.dat", "wb");
    printf("\nMasukkan nama barang untuk dihapus: ");
    gets(v);
	while (fread(&a, sizeof(a), 1, Barang) == 1){
		if(strcmp(a.name,v)!=0){
			fwrite(&a, sizeof(a), 1, Barang2);
		}
	}
	fclose(Barang);
	fclose(Barang2);
	remove("List barang.dat");
	rename("List barang2.dat","List barang.dat");
	
	 printf("------OUTPUT READING BINER-----\n\n");
    i = 1;
    Barang = fopen("List barang.dat", "rb"); 

    while (fread(&a, sizeof(a), 1, Barang) == 1) 

    {
        printf("%d.\tNama Barang\t: %s\n", i, a.name);
        printf("\tAlamat Pengirim\t:%s\n ",a.alamat_pengirim);
        printf("\tAlamat Penerima\t:%s\n ",a.alamat_penerima);
        printf("\tBerat Barang\t: %d kg\n", a.kg);
        printf("\tJarak Rumah\t: %.2f km\n", a.dist);
        printf("\tHarga Barang\t: Rp.%.2f\n", a.price);
        i++;
    }
    fclose(Barang);
    getch();
	system("cls");
}


void list_user()
{
	int c;
	struct user user;
	FILE*f_user;
	FILE*f_user2;
	f_user = fopen("List user.dat", "rb");
	f_user2 = fopen("List user2.dat", "wb");
	
	printf("\n-----USER INFO-----\n");
	printf("\n1.Daftar User");
	printf("\n2.Hapus User");
	printf("\n3.Kembali");
	printf("\n\nYour choice :\t");
	scanf("%d", &c);
	fgetc(stdin);
	system("cls");
	if(c==1){
		int i=1;
		printf("------USER LIST-----\n\n");
		
		while (fread(&user, sizeof(struct user), 1,f_user) == 1) 
	{
        printf("%d.\tNama\t: %s\n", i, user.nama_lengkap);
        printf("\tUsername\t: %s\n",user.username);
        printf("\tEmail\t: %s\n", user.email);
        printf("\tTanggal lahir(mm/dd/yyyy): %d/%d/%d\n",user.tanggal, user.bulan ,user.tahun);
		i++;
    }
    fclose(f_user);
    	getch();
		system("cls");
	}
	else if(c==2){
    	char v[225];
    	printf("------OUTPUT USER LIST-----\n\n");
    	int i = 1;
	
    	while (fread(&user, sizeof(struct user), 1, f_user) == 1)
	{
		printf("%d.\tNama\t\t\t: %s\n", i, user.nama_lengkap);
		printf("\tUsername\t\t: %s\n",user.username);
        printf("\tEmail\t\t: %s\n", user.email);
        printf("\tTanggal lahir(mm/dd/yyyy): %d/%d/%d\n",user.tanggal, user.bulan, user.tahun);
    	i++;
	}
    	fclose(f_user);
    	getch();
    	f_user = fopen("List user.dat", "rb"); 
    	f_user2 = fopen("List user2.dat", "wb");
    	printf("Masukkan nama user yang ingin dihapus: ");
    	gets(v);
		while (fread(&user, sizeof(struct user), 1, f_user) == 1){
		if(strcmp(user.nama_lengkap,v)!=0){
			fwrite(&user, sizeof(struct user), 1, f_user2);
		}
	}
		fclose(f_user);
		fclose(f_user2);
		remove("List user.dat");
		rename("List user2.dat","List user.dat");
	
	 	printf("------OUTPUT USER LIST-----\n\n");
    	i = 1;
    	f_user = fopen("List user.dat", "rb"); 

    	while (fread(&user, sizeof(struct user), 1, f_user) == 1) 
    {
    	printf("%d.\tNama\t: %s\n", i, user.nama_lengkap);
    	printf("\tUsername\t: %s\n",user.username);
        printf("\tEmail\t: %s\n", user.email);
        printf("\tTanggal lahir(mm/dd/yyyy): %d/%d/%d\n",user.tanggal, user.bulan, user.tahun);
		i++;
    }
    fclose(f_user);
    getch();
	system("cls");
	
	}else {
		main();
		system("cls");
		
	}
    fclose(f_user);
    getch();
    system("cls");
    
}

void cek_harga()
{
	FILE *Barang;
	float total;
	int n;
	Barang = fopen("List barang.dat", "rb");
	
	a.price = a.dist*10000;
	total = a.price*n;
	
    printf("Total biaya yang harus dibayar : Rp %d", total);
	
}

void Adm()
{
	system("cls");
	int b;
	
	printf("-----Admin Menu------\n");
	printf("\nUsername\t: "); gets(admin.adm);
	printf("Password\t: "); gets(admin.pwadm);
	system("cls");
	
	if (strcmp(admin.adm,"Admin")==0 && strcmp(admin.pwadm,"Dpickup")==0)
	{
	printf("\n--------Selamat Datang--------\n");
	printf("\n=Silahkan pilih fungsi=");
	printf("\n1.User Info");
	printf("\n2.List Barang");
	printf("\n3.Hapus Barang");
	printf("\n4.Logout kembali ke Menu");
	printf("\n\nYour choice :\t");
	scanf("%d", &b);
	fgetc(stdin);
	system("cls");
	
	switch(b){
		case 1:
			list_user();
		break;		
		case 2:
			list_barang();
			break;	
		case 3:
			hapus_barang();
		break;
		case 4:	
			main();
		break;
		default:
			printf("Pilihan Invalid!");
		break;
		}
	}
}

void status(){
	FILE*Barang;
	int i=1;	
	Barang = fopen("List barang.dat", "rb");
    while (fread(&a, sizeof(a), 1, Barang) == 1)
    {
        printf("%d.\tNama Barang\t: %s\n", i, a.name);
        printf("\tAlamat Pengirim\t:%s\n ",a.alamat_pengirim);
        printf("\tAlamat Penerima\t:%s\n ",a.alamat_penerima);
        printf("\tBerat Barang\t: %dkg\n", a.kg);
        printf("\tJarak Rumah\t: %.2fkm\n", a.dist);
        printf("\tHarga Barang\t: Rp.%.2f\n", a.price);
        printf("\tStatus\t\t: Sedang dikirim\n");
        i++;
    }
    fclose(Barang);
    getch();
	

}

int main()
{	
	
	int a;
	int usrFound = 0;
	
	printf("\n\t\t\t\t--------SEWA JASA ANGKUT BARANG---------");
	printf("\nSilahkan pilih menu :");
	printf("\n1.Signup");
	printf("\n2.Login sebagai admin");
	printf("\n3.Login sebagai user");
	printf("\n4.Exit");
	
	printf("\n\nPilihan anda :\t");
	scanf("%d", &a);
	fgetc(stdin);
	
	switch(a)
	{
		case 1:
			signup();
			break;
		
		case 2:
			Adm();
			break;
			
		case 3:
			login();
			system("cls");
			printf("Pilih menu :");
			printf("\n1.Input barang");
			printf("\n2.Cek Harga");
			printf("\n3.Status Pemesanan");
			printf("\n4.Kembali");
			
			printf("\n\nPilihan anda :\t");
			scanf("%d", &a);
			fgetc(stdin);
			switch(a)
			{
				
				case 1:
				input_barang();
				break;
				case 2:
					cek_harga();
					break;
				case 3:
					status();
					break;
				default :
					break;
			}
			break;
		
		case 4:
			printf("\n\n\t\tTerimakasih sudah memakai jasa kami");
			exit(300);
			break;
	}
	
	return main();

	return 0;	
}
