#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKS_KITAP 90

typedef struct {
    char isbn[20];
    char ad[100];
    int oduncAlindi;
} Kitap;

Kitap kitaplar[MAKS_KITAP];
int kitapSayisi = 0;

void kitaplariYukle() {
    FILE *dosya = fopen("kitaplar.txt", "r");
    if (dosya == NULL) {
        printf("Kitap dosyası bulunamadı!\n");
        return;
    }
    while (fscanf(dosya, "%s %[^\n] %d", kitaplar[kitapSayisi].isbn, kitaplar[kitapSayisi].ad, &kitaplar[kitapSayisi].oduncAlindi) != EOF) {
        kitapSayisi++;
    }
    fclose(dosya);
}

void kitaplariKaydet() {
    FILE *dosya = fopen("kitaplar.txt", "w");
    for (int i = 0; i < kitapSayisi; i++) {
        fprintf(dosya, "%s %s %d\n", kitaplar[i].isbn, kitaplar[i].ad, kitaplar[i].oduncAlindi);
    }
    fclose(dosya);
}

void tumKitaplariListele() {
    printf("Tüm Kitaplar ve ISBN'ler\n");
    printf("------------------------------\n");
    for (int i = 0; i < kitapSayisi; i++) {
        printf("%-30s ISBN: %s %s\n", kitaplar[i].ad, kitaplar[i].isbn, kitaplar[i].oduncAlindi ? "(Ödünç Alındı)" : "");
    }
}

void oduncAlinanKitaplariListele() {
    printf("Ödünç Alınan Kitaplar\n");
    printf("------------------------------\n");
    for (int i = 0; i < kitapSayisi; i++) {
        if (kitaplar[i].oduncAlindi) {
            printf("%-30s ISBN: %s\n", kitaplar[i].ad, kitaplar[i].isbn);
        }
    }
}

void kitapEkle() {
    if (kitapSayisi >= MAKS_KITAP) {
        printf("Kitap ekleme sınırına ulaşıldı!\n");
        return;
    }
    Kitap yeniKitap;
    printf("Kitap ISBN: ");
    scanf("%s", yeniKitap.isbn);
    printf("Kitap Adı: ");
    scanf(" %[^\n]", yeniKitap.ad);
    yeniKitap.oduncAlindi = 0;
    kitaplar[kitapSayisi++] = yeniKitap;
    printf("Kitap başarıyla eklendi!\n");
}

void kitapSil() {
    char isbn[20];
    printf("Silmek istediğiniz kitabın ISBN numarasını girin: ");
    scanf("%s", isbn);
    for (int i = 0; i < kitapSayisi; i++) {
        if (strcmp(kitaplar[i].isbn, isbn) == 0 && !kitaplar[i].oduncAlindi) {
            for (int j = i; j < kitapSayisi - 1; j++) {
                kitaplar[j] = kitaplar[j + 1];
            }
            kitapSayisi--;
            printf("Kitap başarıyla silindi!\n");
            return;
        }
    }
    printf("Kitap bulunamadı veya ödünç alınmış!\n");
}

void isbnIleKitapAra() {
    char isbn[20];
    printf("Aramak istediğiniz kitabın ISBN numarasını girin: ");
    scanf("%s", isbn);
    for (int i = 0; i < kitapSayisi; i++) {
        if (strcmp(kitaplar[i].isbn, isbn) == 0) {
            printf("Kitap Adı: %s, ISBN: %s, Durum: %s\n", kitaplar[i].ad, kitaplar[i].isbn, kitaplar[i].oduncAlindi ? "Ödünç Alındı" : "Mevcut");
            return;
        }
    }
    printf("Kitap bulunamadı!\n");
}

void kitapOduncAl() {
    char isbn[20];
    printf("Ödünç almak istediğiniz kitabın ISBN numarasını girin: ");
    scanf("%s", isbn);
    for (int i = 0; i < kitapSayisi; i++) {
        if (strcmp(kitaplar[i].isbn, isbn) == 0 && !kitaplar[i].oduncAlindi) {
            kitaplar[i].oduncAlindi = 1;
            printf("Kitap başarıyla ödünç alındı!\n");
            return;
        }
    }
    printf("Kitap bulunamadı veya zaten ödünç alınmış!\n");
}

void menuGoster() {
    printf("\nKütüphane Sistemi\n");
    printf("-----------------------------------------------\n");
    printf("1) Kütüphanedeki tüm kitapları listele\n");
    printf("2) Ödünç alınan tüm kitapları listele\n");
    printf("3) Yeni bir kitap ekle\n");
    printf("4) Ödünç alınmamış bir kitabı sil\n");
    printf("5) ISBN numarası ile kitap ara\n");
    printf("6) Bir kitabı ödünç al\n");
    printf("7) Çıkış\n");
}

int main() {
    char kullaniciAdi[100];
    int sifre;
    printf("Kullanıcı adı: ");
    scanf("%s", kullaniciAdi);
    printf("Şifre: ");
    scanf("%d", &sifre);
    printf("Hoş Geldiniz, %s!\n", kullaniciAdi);
    printf("-----------------------------------------------\n");

    kitaplariYukle();

    int secim;
    do {
        menuGoster();
        printf("Menüden bir seçim yapın: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                tumKitaplariListele();
                break;
            case 2:
                oduncAlinanKitaplariListele();
                break;
            case 3:
                kitapEkle();
                break;
            case 4:
                kitapSil();
                break;
            case 5:
                isbnIleKitapAra();
                break;
            case 6:
                kitapOduncAl();
                break;
            case 7:
                kitaplariKaydet();
                printf("Çıkış yapılıyor .\n");
                break;
            default:
                printf(" Lütfen tekrar deneyin.\n");
                break;
        }
    } while (secim != 7);

    return 0;
}
