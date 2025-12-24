#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
#pragma execution_character_set("utf-8")
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

vector<int> skorOku(){
    vector<int> skorlar;
    ifstream dosya("scores.json");
    
    if(!dosya.is_open()) 
        return skorlar; // dosya yoksa boş dönüyoruz

    int s;
    while(dosya >> s){ 
        skorlar.push_back(s); // dosyadaki skorları sırayla alıyoruz
    }
    dosya.close();
    return skorlar;
}

void skorKaydet(int skor){
    ofstream dosya("scores.json", ios::app); // dosyaya sona ekleme yapıyoruz
    dosya << skor << endl;
    dosya.close();
}

void skorTablosuGoster(){
    vector<int> skorlar = skorOku();

    if(skorlar.empty()){ 
        cout << "Henuz skor bulunmuyor!" << endl;
        return;
    }

    sort(skorlar.begin(), skorlar.end(), greater<int>()); // en yüksekten küçüğe sıralama

    cout << BLUE << "\n--- En Yuksek Skorlar ---" << RESET << endl;
    for(int i = 0; i < skorlar.size() && i < 5; i++){
        cout << i+1 << ". " << skorlar[i] << endl; // ilk 5 skoru gösteriyoruz
    }
    cout << "------------------------\n" << endl;
}

void tekrar_kelime(string &kelime, string &tahmin,string &secim, vector<string> &kelime_kutusu, string &acma,int &bonus){
    cout<< BLUE << "Kelime: " << RESET;

    for(int j=0; j<kelime.length(); j++){
        cout<<acma[j]<<" "; // kelimenin açık-kapalı durumunu yazdırıyoruz
    }

    cout<<endl;
    cout<< BLUE <<"Tahmin edilen harfler: " << RESET;

    for(int i=0;i<kelime_kutusu.size();i++){
        cout<<kelime_kutusu[i];
        if(i<kelime_kutusu.size()-1)
            cout<<", ";
    }

    cout<<endl;
    cout<<YELLOW<<"Bonus puan: "<<bonus<<RESET<<endl; // kalan bonusu gösteriyoruz
}

void adam1(bool &bulundu, string &kelime,string &tahmin,int &hata, string &secim,vector<string> &kelime_kutusu, string &acma,int &bonus){
    // burası tamamen adam çizimi, hata arttıkça parça ekleniyor

    if(hata == 0){
        cout << "  +---+"<< endl;
        cout << "  |   |"<<endl;
        for(int i=0;i<6;i++){ cout<<"      |"<<endl; }
        cout<<"========="<<endl;
    } 
    else if(hata==1){
        cout << "--- Yeni Tur ---"<< "\n\n";
        cout << RED << "  +---+"<< endl;
        cout << "  |   |"<<endl;
        cout << "  O   |"<<RESET<<endl; // kafa eklendi
        for(int i=0;i<4;i++){ cout<<"      |"<<endl; }
        cout <<"========="<<endl;
    }
    else if(hata == 2){
        cout << "--- Yeni Tur ---"<< "\n\n";
        cout << RED << "  +---+"<< endl;
        cout << "  |   |"<<endl;
        cout << "  O   |"<<endl;
        cout << "  |   |"<<RESET<<endl; // vücut eklendi
        for(int i=0;i<3;i++){ cout<<"      |"<<endl; }
        cout <<"========="<<endl;
    }
    else if(hata == 3){
        cout << "--- Yeni Tur ---"<< "\n\n";
        cout << RED << "  +---+"<< endl;
        cout << "  |   |"<<endl;
        cout << "  O   |"<<endl;
        cout << "  |   |"<<endl;
        cout << " /    |"<<RESET<<endl; // sol bacak
        for(int i=0;i<2;i++){ cout<<"      |"<<endl; }
        cout <<"========="<<endl;
    }
    else if(hata == 4){
        cout << "--- Yeni Tur ---"<< "\n\n";
        cout << RED << "  +---+"<< endl;
        cout << "  |   |"<<endl;
        cout << "  O   |"<<endl;
        cout << "  |   |"<<endl;
        cout << " / \\  |"<<RESET<<endl; // iki bacak tamam
        for(int i=0;i<2;i++){ cout<<"      |"<<endl; }
        cout <<"========="<<endl;
    }
    else if(hata == 5){
        cout << "--- Yeni Tur ---"<< "\n\n";
        cout << RED << "  +---+"<< endl;
        cout << "  |   |"<<endl;
        cout << "  O   |"<<endl;
        cout << "  |   |"<<endl;
        cout << " /|\\  |"<<endl; // kollar eklendi
        cout << " /    |"<<RESET<<endl;
        for(int i=0;i<1;i++){ cout<<"      |"<<endl; }
        cout <<"========="<<endl;
    }
    else if(hata == 6){
        cout << "--- Yeni Tur ---"<< "\n\n";
        cout << RED << "  +---+"<< endl;
        cout << "  |   |"<<endl;
        cout << "  O   |"<<endl;
        cout << "  |   |"<<endl;
        cout << " / \\  |"<<endl;
        cout << "  |   |"<<endl;
        cout << " / \\  |"<<RESET<<endl; // adam tamamen çizildi
        cout <<"========="<<endl;
    }
}

void kelime_acma(string &kelime, string tahmin,bool &bulundu, string &acma, int &hata){
    bulundu=false;

    for (int i = 0; i < kelime.length(); i++) {
        if (kelime.substr(i,1) == tahmin) { 
            acma[i] = tahmin[0];  // doğru harfse kelimeyi açıyoruz
            bulundu = true;
        }
    }

    if(!bulundu) 
        hata++; // yanlış harfte hata artıyor
}

void harf_tahmini(string &kelime, string &tahmin,bool &bulundu,int &hata,string &acma, string &secim,vector<string> &kelime_kutusu, int &skor){
    cout<<"Harf: ";
    cin >> tahmin;

    // tek karakter mi kontrolü
    if (tahmin.length() != 1 || !((tahmin[0]>='a' && tahmin[0]<='z') || (tahmin[0]>='A' && tahmin[0]<='Z'))) {
        cout<<RED<<"Lutfen sadece tek bir harf giriniz!!"<<RESET<<endl;
        return;
    }

    // daha önce girilmiş mi kontrolü
    for(string kontrol:kelime_kutusu){
        if(kontrol == tahmin){
            cout<<RED<<"Bu harf tahmin edilmis"<<RESET<<endl;
            return;
        }
    }

    kelime_kutusu.push_back(tahmin); // tahmin edilen harfleri kaydediyoruz
    kelime_acma(kelime, tahmin,bulundu,acma,hata);

    if(!bulundu){
        cout<<RED<<"Yanlis harf: "<<tahmin<<", kalan hak: "<<6-hata<<RESET<<endl;
        skor -= 5; // yanlış harfte skor düşüyor
    }
    else{
        skor += 10; // doğru harfte skor artıyo
    }
}

void rastgele_katagori(string &kelime,string &kategori){
    srand(time(0)); // rastgelelik için seed

    // rastgele kategori seçimi
    string kategoriler[]={"meyve","hayvan","teknoloji"};
    int rastgele_katagori = rand() % 3;
    kategori = kategoriler[rastgele_katagori];

    // kategoriye göre kelime seçiyoruz
    if (kategori == "meyve") { 
        string meyveler[]={"elma","portakal","cilek","muz","nar"}; 
        kelime = meyveler[rand()%5];
    }
    else if (kategori == "hayvan") { 
        string hayvanlar[]={"kedi","maymun","fil","aslan","kus"}; 
        kelime = hayvanlar[rand()%5];
    }
    else if (kategori == "teknoloji") { 
        string teknolojiler[]={"bilgisayar","internet","yazilim","robot","telefon"}; 
        kelime = teknolojiler[rand()%5];
    }
}

void islem_coz(string &islem,int &ilk_kelime,int &ikinci_kelime,int &sonuc_tutma,int &kullanici_cevap,string &secim,string &kelime,string &tahmin,vector<string> &kelime_kutusu,string &acma,int &bonus,int &hata,bool &bulundu,int &skor){
    
    cout<<"islem (+,-,x,/ veya iptal): ";
    cin>>islem;

    if(islem=="iptal") 
        return;

    // geçerli operatör kontrolü
    else if(islem!="+" && islem!="-" && islem!="x" && islem!="/"){
        cout<<"lutfen gecerli bir operator giriniz!"<<endl;
        return;
    }

    string s1,s2;

    cout<<"1. sayi (veya iptal): ";
    cin>>s1;
    if(s1=="iptal") return;

    cout<<"2. sayi (veya iptal): ";
    cin>>s2;
    if(s2=="iptal") return;

    try { 
        // kullanıcı sayı girdi mi kontrol
        ilk_kelime = stoi(s1);
        ikinci_kelime = stoi(s2);
    } 
    catch(...){
        cout<<RED<<"Hatali giriş!\n"<<RESET;
        return;
    }

    // işleme göre sonuç hesaplama
    if(islem=="+") 
        sonuc_tutma = ilk_kelime + ikinci_kelime;
    else if(islem=="-") 
        sonuc_tutma = ilk_kelime - ikinci_kelime;
    else if(islem=="x") 
        sonuc_tutma = ilk_kelime * ikinci_kelime;
    else if(islem=="/"){
        if(ikinci_kelime==0){
            cout<<RED<<"0'a bolunmez!\n"<<RESET;
            hata++;
            return;
        }
        sonuc_tutma = ilk_kelime / ikinci_kelime;
    }

    cout<<"Soru: "<<ilk_kelime<<islem<<ikinci_kelime<<"= ?"<<endl;
    cout<<"cevabiniz: ";
    cin>>kullanici_cevap;

    if(kullanici_cevap==sonuc_tutma){
        cout<<GREEN<<"Dogru!"<<RESET<<endl;

        bonus++; // doğru yapınca bonus birikiyor
        skor += 15; // işlem sorusundan ekstra puan

        // bonus ile rastgele harf açma
        vector<int> gizli;
        for(int i=0;i<kelime.length();i++)
            if(acma[i]=='_') 
                gizli.push_back(i); // kapalı harflerin indexini topluyoruz

        if(!gizli.empty()){
            int secilen = rand()%gizli.size(); // rastgele bir kapalı harf
            acma[gizli[secilen]] = kelime[gizli[secilen]];
            cout<<GREEN<<"Bonus ile '"<<kelime[gizli[secilen]]<<"' harfi acildi!"<<RESET<<endl;
        }
    }
    else{
        cout<<RED<<"Yanlis! Dogru = "<<sonuc_tutma<<RESET<<endl;
        hata++; // yanlış işlemde hata artıyor
    }
}

void kategori_ipucu(string kategori, int &bonus){
    if(bonus > 0){
        cout << BLUE << "Kategori ipucu: " << kategori << RESET << endl;
        bonus--; // ipucu kullanınca bonus gidiyor
    }
    else{
        cout << RED << "Yeterli bonus yok!" << RESET << endl;
    }
}


// --- Oyun Döngüsü ---
int main(){
    string kelime, acma, tahmin, secim, islem, kategori;
    vector<string> kelime_kutusu;
    int hata = 0, bonus = 0, skor = 0;
    int ilk_kelime, ikinci_kelime, sonuc_tutma, kullanici_cevap;
    bool bulundu = false;

    rastgele_katagori(kelime,kategori); // kelime ve kategori seçiliyor
    acma = string(kelime.length(), '_'); // kelimeyi tamamen gizli hale getiriyoruz

    while (acma != kelime && hata <= 6) {
        adam1(bulundu, kelime, tahmin, hata, secim, kelime_kutusu, acma, bonus);
        tekrar_kelime(kelime, tahmin, secim, kelime_kutusu, acma, bonus);

        cout << "[H]arf tahmini | [I]slem coz | [i]pucu | [C]ikis\nseciminiz: ";
        cin >> secim;

        // yanlış menü seçimi kontrolü
        if (!(secim == "H" || secim == "h" || secim == "I" || secim == "ı" || 
              secim == "i" || secim == "İ" || secim == "C" || secim == "c")) {
            cout<<"lutfen dogru harfi sectiginizden emin olun!"<<endl;
            continue;
        }

        if (secim=="H" || secim=="h")
            harf_tahmini(kelime, tahmin, bulundu, hata, acma, secim, kelime_kutusu,skor);

        else if (secim=="ı" || secim=="I") 
            islem_coz(islem, ilk_kelime, ikinci_kelime, sonuc_tutma, kullanici_cevap,
                      secim, kelime, tahmin, kelime_kutusu, acma, bonus, hata, bulundu, skor);

        else if (secim=="i" || secim=="İ") 
            kategori_ipucu(kategori, bonus);

        else if (secim=="C" || secim=="c") 
            break;

        if(hata==6){
            adam1(bulundu, kelime, tahmin, hata, secim, kelime_kutusu, acma, bonus);
            break;
        }
    }

    // kazandı mı kaybetti mi kontrolü
    if(acma==kelime){ 
        cout<<GREEN<<"Kelimeyi buldunuz! "<<kelime<<RESET<<endl;
        skor += 50; // kazanınca ekstra puan
    }
    else{ 
        cout<<RED<<"Hakkiniz bitti! Kelime: "<<kelime<<RESET<<endl;
        skor -= 20; // kaybedince eksi puan
    }

    cout << BLUE << "Toplam Skorunuz: " << skor << RESET << endl;
    skorKaydet(skor); // skoru dosyaya ekliyoruz
    skorTablosuGoster(); // en yüksek skorları gösteriyoruz

    return 0;
}