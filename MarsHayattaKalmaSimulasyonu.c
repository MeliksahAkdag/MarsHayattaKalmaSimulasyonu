// Melikşah Talha Akdağ
// yazılım mühendisliği 1. sınıf
// 1260505021

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int su = 50;
    int yedekParca = 5;
    int modulHasari = 0;
    int kilitMuhurlu = 0;
    int gun = 1;
    int tur = 0;
    int oyunBitti = 0; 

    char zorlukSecimi;

    //  ZORLUK SEÇİMİ 
    do {
        printf("=========================================\n");
        printf("  MARS KOLONISI YASAM DESTEK SIMULATORU  \n");
        printf("=========================================\n");
        printf("Zorluk Seviyesi Seciniz:\n");
        printf("  KOLAY [K]\n");
        printf("  NORMAL [N]\n");
        printf("  ZOR [Z]\n");
        printf("Seciminiz: ");
        scanf(" %c", &zorlukSecimi);

        switch (zorlukSecimi) {
            case 'K':
            case 'k':
                su = 60;
                yedekParca = 7;
                modulHasari = 10;
                printf("Zorluk: KOLAY secildi.\n");
                break;
            case 'N':
            case 'n':
                su = 40;
                yedekParca = 5;
                modulHasari = 20;
                printf("Zorluk: NORMAL secildi.\n");
                break;
            case 'Z':
            case 'z':
                su = 20;
                yedekParca = 3;
                modulHasari = 30;
                printf("Zorluk: ZOR secildi.\n");
                break;
            default:
                printf("Gecersiz zorluk secimi! Lutfen K, N veya Z seciniz.\n");
                zorlukSecimi = '\0'; 
        }
    } while (zorlukSecimi == '\0');

    // ANA OYUN 
    do {
        if (saglik < 0) saglik = 0; if (saglik > 100) saglik = 100;
        if (enerji < 0) enerji = 0; if (enerji > 100) enerji = 100;
        if (oksijen < 0) oksijen = 0; if (oksijen > 100) oksijen = 100;
        if (modulHasari < 0) modulHasari = 0; if (modulHasari > 100) modulHasari = 100;
        if (su < 0) su = 0;

        if (saglik <= 0 || oksijen <= 0) {
            oyunBitti = -1;
            break;
        }
        if (gun > 15) {
            oyunBitti = 1; 
            break;
        }

        printf("\n-----------------------------------------\n");
        printf("GUN: %d/15 | TUR: %d | Durum: Saglik=%d, Enerji=%d, Oksijen=%d, Su=%d, Parca=%d, Hasar=%d\n", 
               gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari);
        printf("KOMUTLAR: KESIF [G], OKSIJEN URET [O], TAMIR [T], DURUM RAPORU [D], UYU DINLEN [U], KUM FIRTINASI [K], HAVA KILIDI SIFRESI [H], CIKIS [Q]\n");
        printf("Komut giriniz: ");
        
        char komut;
        scanf(" %c", &komut);

        int turGecerli = 1;

        switch (komut) {
            case 'g':
            case 'G':
                if (enerji < 15 || oksijen < 10) {
                    printf("HATA: Kesif icin yeterli enerji (15) veya oksijen (10) yok!\n");
                    turGecerli = 0;
                    break;
                }
                enerji -= 15;
                oksijen -= 10;

                {
                    int suEsik = (enerji > 40 && oksijen > 30) ? 50 : 30;
                    int zarSu = rand() % 100;
                    int zarYaralanma = rand() % 100;
                    int yaralanmaEsik = 10;

                    printf("Zar (Su): %d / Esik: %d -> ", zarSu, suEsik);
                    if (zarSu < suEsik) {
                        int kazanilanSu = 10 + (rand() % 15);
                        su += kazanilanSu;
                        printf("BASARILI! %d birim su bulundu.\n", kazanilanSu);
                    } else {
                        int parcaEsik = 40;
                        printf("BASARISIZ. Zar (Parca): ");
                        int zarParca = rand() % 100;
                        printf("%d / Esik: %d -> ", zarParca, parcaEsik);
                        if (zarParca < parcaEsik) {
                            yedekParca += 2;
                            printf("BASARILI! 2 adet yedek parca bulundu.\n");
                        } else {
                            printf("BASARISIZ. Eli bos donuldu.\n");
                        }
                    }

                    printf("Zar (Yaralanma): %d / Esik: %d (veya Hasar > 70) -> ", zarYaralanma, yaralanmaEsik);
                    if (zarYaralanma < yaralanmaEsik || modulHasari > 70) {
                        saglik -= 20;
                        printf("TEHLIKE! Kesif sirasinda yaralanildi! Saglik -20\n");
                    } else {
                        printf("GUVENLI.\n");
                    }
                }
                break;

            case 'o':
            case 'O':
                {
                    int suMiktari;
                    printf("Uretim icin harcanacak su miktarini giriniz (Mevcut Su: %d): ", su);
                    scanf("%d", &suMiktari);

                    if (suMiktari <= 0) {
                        printf("Gecersiz su miktari!\n");
                        turGecerli = 0;
                    } else if (suMiktari > su) {
                        printf("HATA: Depoda o kadar su yok!\n");
                        turGecerli = 0;
                    } else if (enerji < 10) {
                        printf("HATA: Oksijen uretmek icin yeterli enerji (10) yok!\n");
                        turGecerli = 0;
                    } else {
                        enerji -= 10;
                        su -= suMiktari;

                        int uretilenOksijen = (suMiktari / 2) * 3;
                        int artikSu = 0;

                        if (suMiktari % 2 != 0) {
                            artikSu = 1;
                            su += artikSu; 
                            printf("Tek sayida su girildigi icin 1 birim su depoda artikyeten birakildi.\n");
                        }

                        oksijen += uretilenOksijen;
                        if (oksijen > 100) oksijen = 100;
                        printf("Basariyla %d birim oksijen uretildi. Yeni Oksijen: %d\n", uretilenOksijen, oksijen);
                    }
                }
                break;

            case 't':
            case 'T':
                if (yedekParca <= 0) {
                    printf("HATA: Yedek parca kalmadigi icin tamir yapilamaz!\n");
                    turGecerli = 0;
                } else if (modulHasari == 0) {
                    printf("Modulde tamir edilecek hasar yok.\n");
                    turGecerli = 0;
                } else if (enerji < 15) {
                    printf("HATA: Tamir icin yeterli enerji (15) yok!\n");
                    turGecerli = 0;
                } else {
                    enerji -= 15;
                    yedekParca--;

                    int onarilanHasar = 0;
                    if (modulHasari <= 30) {
                        onarilanHasar = 20;
                        printf("Hasar Kademesi: Hafif (0-30).\n");
                    } else if (modulHasari <= 70) {
                        onarilanHasar = 15;
                        printf("Hasar Kademesi: Orta (31-70).\n");
                    } else {
                        onarilanHasar = 10;
                        printf("Hasar Kademesi: Agir (71-100). Onarim zor!\n");
                    }

                    modulHasari -= onarilanHasar;
                    printf("1 yedek parca harcandi. Modul hasari %d birim azaltildi. Guncel Hasar: %d\n", onarilanHasar, modulHasari);
                }
                break;

            case 'd':
            case 'D':
                turGecerli = 0;
                printf("\n========= DETAYLI DURUM RAPORU =========\n");
                printf(" Gun: %d | Tur: %d\n", gun, tur);
                printf(" Saglik: %d/100\n", saglik);
                printf(" Enerji: %d/100\n", enerji);
                printf(" Oksijen: %d/100\n", oksijen);
                printf(" Su Miktari: %d birim\n", su);
                printf(" Yedek Parca: %d adet\n", yedekParca);
                printf(" Modul Hasari: %d/100\n", modulHasari);
                printf(" Hava Kilidi Muhurlu mu?: %s\n", kilitMuhurlu ? "Evet" : "Hayir");

                if (oksijen < 25) printf(" [Kritik UYARI]: Oksijen cok dusuk (< 25)!\n");
                if (saglik < 30) printf(" [Kritik UYARI]: Saglik kritik seviyede (< 30)!\n");
                if (modulHasari > 70) printf(" [Kritik UYARI]: Modul hasari tehlikeli boyutta (> 70)!\n");

                if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70 && enerji >= 30) {
                    printf(" TUM SISTEMLER NORMAL\n");
                }
                printf("=========================================\n");
                break;

            case 'u':
            case 'U':
                if (enerji > 85) {
                    printf("Zaten yeterince dinlenmissiniz, uykunuz yok.\n");
                    turGecerli = 0;
                    break;
                }
                enerji += 25;
            
                if (oksijen < 20) {
                    saglik -= 10;
                    printf("UYARI: Oksijen cok dusuk (< 20) oldugu icin dinlenirken sagliginiz artti yerine azaldi! Saglik -10\n");
                } else {
                    saglik += 10;
                    printf("Dinlenildi. Enerji ve saglik artti.\n");
                }
                break;

            case 'k':
            case 'K':
                if (enerji < 20) {
                    printf("HATA: Kum firtinasi ile mucadele etmek icin yeterli enerji (20) yok!\n");
                    turGecerli = 0;
                    break;
                }
                enerji -= 20;

                {
                    int firtinaTuru = (zorlukSecimi == 'K' || zorlukSecimi == 'k') ? 3 : ((zorlukSecimi == 'N' || zorlukSecimi == 'n') ? 5 : 7);
                    int kaybedilenSaglikToplam = 0;
                    int kaybedilenOksijenToplam = 0;
                    int hasarliTurSayisi = 0;

                    printf("-> KUM FIRTINASI BASLADI! Sure: %d tur.\n", firtinaTuru);

                    for (int i = 1; i <= firtinaTuru; i++) {
                        int zarFirtina = rand() % 100;
                        int hasarCarpani = 1;

                        if (i % 2 == 0) {
                            hasarCarpani = 2;
                            printf("  [Tur %d]: Ruzgar siddetlendi! Hasar iki katina cikti.\n", i);
                        } else {
                            printf("  [Tur %d]: Normal firtina siddeti.\n", i);
                        }

                        if (kilitMuhurlu == 1) {
                            printf("  [Tur %d]: Hava kilidi muhurlu oldugu icin oksijen sizintisi onlendi (continue).\n", i);
                        } else {
                            int oksijenKaybi = 5 * hasarCarpani;
                            oksijen -= oksijenKaybi;
                            kaybedilenOksijenToplam += oksijenKaybi;
                        }

                        if (zarFirtina < 30) {
                            int canKaybi = 10 * hasarCarpani;
                            saglik -= canKaybi;
                            kaybedilenSaglikToplam += canKaybi;
                            hasarliTurSayisi++;
                            printf("    Zar: %d -> Firtina enkaz carpti! Saglik -%d\n", zarFirtina, canKaybi);
                        } else if (zarFirtina < 60) {
                            modulHasari += 15 * hasarCarpani;
                            hasarliTurSayisi++;
                            printf("    Zar: %d -> Modul darbe aldi! Hasar artti.\n", zarFirtina);
                        } else {
                            printf("    Zar: %d -> Siginaga siginildi, zararsiz atlandi.\n", zarFirtina);
                        }

                        if (saglik <= 0 || oksijen <= 0) {
                            printf("  [Tur %d]: Kritik durum! Firtina sirasinda can/oksijen bitti (break).\n", i);
                            break;
                        }
                    }

                    printf("-> Firtina Ozeti: %d turda hasar alindi. Toplam Saglik Kaybi: %d, Toplam Oksijen Kaybi: %d\n", 
                           hasarliTurSayisi, kaybedilenSaglikToplam, kaybedilenOksijenToplam);
                }
                break;

            case 'h':
            case 'H':
                {
                    char dogruSifre = 'A' + (gun % 26);
                    int denemeHakki = 3;
                    char girilenHarf;
                    int sifreBasarili = 0;

                    printf("IPUCU: Sifre, alfabede 'A' harfinden bugünün gun sayisi (%d) kadar ilerideki buyuk harftir.\n", gun);
                    printf("Hava kilidini mühürlemek icin sifreyi giriniz (3 hakkiniz var):\n");

                    do {
                        printf("Deneme hakki kaldi: %d. Harf giriniz: ", denemeHakki);
                        scanf(" %c", &girilenHarf);
                        
                        // Kütüphanesiz büyük harf dönüşümü (Küçük harf girildiyse büyük harfe çevirir)
                        if (girilenHarf >= 'a' && girilenHarf <= 'z') {
                            girilenHarf -= 32;
                        }

                        if (girilenHarf == dogruSifre) {
                            sifreBasarili = 1;
                            break;
                        } else {
                            denemeHakki--;
                            enerji -= 5;
                            if (girilenHarf < dogruSifre) {
                                printf("Yanlis! Ileri git (Alfabetik olarak daha sonraki harf).\n");
                            } else {
                                printf("Yanlis! Geri git (Alfabetik olarak daha onceki harf).\n");
                            }
                        }
                    } while (girilenHarf != dogruSifre && denemeHakki > 0);

                    if (sifreBasarili) {
                        kilitMuhurlu = 1;
                        printf("TEBRIKLER! Hava kilidi basariyla muhurlendi.\n");
                    } else {
                        modulHasari += 20;
                        printf("BASARISIZ! 3 deneme hakki bitti. Modul hasari 20 artti.\n");
                    }
                }
                break;

            case 'q':
            case 'Q':
                oyunBitti = -2;
                turGecerli = 0;
                break;

            default:
                printf("Tanimssiz komut! Lutfen gecerli bir komut giriniz (Sure harcanmadi).\n");
                turGecerli = 0;
                break;
        }
        
        if (turGecerli) {
            tur++;
            
            if (tur % 3 == 0) {
                gun++;
                printf("\n*** YENI GUN BASLADI: Gun %d ***\n", gun);
                oksijen -= 8;
                if (modulHasari > 70) {
                    saglik -= 5;
                    printf("UYARI: Yuksek modul hasari (>70) nedeniyle gece sizintisi! Saglik -5\n");
                }
            }
        }

    } while (oyunBitti == 0);

    printf("\n=========================================\n");
    printf("           OYUN SONU RAPORU              \n");
    printf("=========================================\n");
    if (oyunBitti == 1) {
        printf(" SONUC: KAZANDINIZ! Kurtarma ekibi ulasti ve koloniyi kurtardi!\n");
    } else if (oyunBitti == -1) {
        printf(" SONUC: KAYBETTINIZ! Karakteriniz hayatta kalamadi.\n");
    } else {
        printf(" SONUC: Oyundan cikis yaptiniz.\n");
    }

    int puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf(" Hayatta Kalinan Gun: %d\n", gun > 15 ? 15 : gun);
    printf(" Toplam Tur Sayisi: %d\n", tur);
    printf(" Son Durum -> Saglik: %d, Enerji: %d, Oksijen: %d, Hasar: %d\n", saglik, enerji, oksijen, modulHasari);
    printf(" TOPLAM PUAN: %d\n", puan);
    printf("=========================================\n");

    return 0;
}