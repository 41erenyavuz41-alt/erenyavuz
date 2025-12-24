#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Kitap Sinifi 
class Book {
private:
    string kitapAdi;
    string yazarAdi;
    int yayinYili;

public:
    Book(string k, string y, int yil) {
        kitapAdi = k;
        yazarAdi = y;
        yayinYili = yil;
    }

    string getAd() {
        return kitapAdi;
    }

    bool yazarMi(string y) {
        return yazarAdi == y;
    }

    void yazdir() {
        cout << "Kitap: " << kitapAdi << endl;
        cout << "Yazar: " << yazarAdi << endl;
        cout << "Yil  : " << yayinYili << endl;
        cout << "****************\n";
    }
};

// Kutuphane Sinifi
class Library {
private:
    vector<Book> kitapListesi;

public:
    void kitapEkle() {
        string ad, yazar;
        int yil;

        cin.ignore();
        cout << "Kitap adi giriniz: ";
        getline(cin, ad);

        cout << "Yazar adi giriniz: ";
        getline(cin, yazar);

        cout << "Yayin yili giriniz: ";
        cin >> yil;

        kitapListesi.push_back(Book(ad, yazar, yil));
        cout << ">> Kitap eklendi.\n";
    }

    void kitapSil() {
        string ad;
        cin.ignore();
        cout << "Silinecek kitap adi: ";
        getline(cin, ad);

        for (int i = 0; i < kitapListesi.size(); i++) {
            if (kitapListesi[i].getAd() == ad) {
                kitapListesi.erase(kitapListesi.begin() + i);
                cout << ">> Kitap silindi.\n";
                return;
            }
        }
        cout << ">> Kitap bulunamadi.\n";
    }

    void adaGoreAra() {
        string ad;
        cin.ignore();
        cout << "Aranan kitap adi: ";
        getline(cin, ad);

        bool bulundu = false;
        for (int i = 0; i < kitapListesi.size(); i++) {
            if (kitapListesi[i].getAd().find(ad) != string::npos) {
                kitapListesi[i].yazdir();
                bulundu = true;
            }
        }

        if (!bulundu)
            cout << ">> Sonuc yok.\n";
    }

    void yazaraGoreAra() {
        string yazar;
        cin.ignore();
        cout << "Aranan yazar adi: ";
        getline(cin, yazar);

        bool bulundu = false;
        for (int i = 0; i < kitapListesi.size(); i++) {
            if (kitapListesi[i].yazarMi(yazar)) {
                kitapListesi[i].yazdir();
                bulundu = true;
            }
        }

        if (!bulundu)
            cout << ">> Yazara ait kitap yok.\n";
    }

    void tumunuListele() {
        if (kitapListesi.empty()) {
            cout << ">> Kutuphane bos.\n";
            return;
        }

        for (int i = 0; i < kitapListesi.size(); i++) {
            kitapListesi[i].yazdir();
        }
    }
};

//Ana Program 
int main() {
    Library kutuphane;
    int secim;

    for (;;) {
        cout << "\n==== KUTUPHANE OTOMASYONU ====\n";
        cout << "[1] Yeni Kitap Ekle\n";
        cout << "[2] Kitap Sil\n";
        cout << "[3] Ada Gore Kitap Ara\n";
        cout << "[4] Yazara Gore Kitap Ara\n";
        cout << "[5] Tum Kitaplari Listele\n";
        cout << "[6] Cikis\n";
        cout << "Seciminiz: ";
        cin >> secim;

        if (secim == 1) kutuphane.kitapEkle();
        else if (secim == 2) kutuphane.kitapSil();
        else if (secim == 3) kutuphane.adaGoreAra();
        else if (secim == 4) kutuphane.yazaraGoreAra();
        else if (secim == 5) kutuphane.tumunuListele();
        else if (secim == 6) {
            cout << "Program sonlandirildi.\n";
            break;
        }
        else {
            cout << "Hatali secim!\n";
        }
    }

    return 0;
}
