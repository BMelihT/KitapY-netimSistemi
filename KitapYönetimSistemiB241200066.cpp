// b241200066
// Burhan Melih Taşcıoğlu 
// Bilişim sitemleri Mühendisliği Veri yapıları Ödev 1 ,Ödev 2 ve proje

#include <iostream>
#include <string>
#include <locale.h>
#include <algorithm> 
#include <iomanip>
#include <ctime>
#include <sstream>
#include <unordered_map>

using namespace std;

void kitapEkle();
void ornekKitaplarEkle();
void secimListele();
void kitapDuzenle();
void kitapSil();
void kitapSayisi();
void kitapAra();
void basımYılı5();
void hasarNot();
void personelMenu();
void koleksiyonaKitapEkle();
void AnaMenü();
void hasarlıKitaplar();
void kullaniciGiris();
void yorumYap();
void kitaplariAktar();
void yorumlariGoster();
void koleksiyonuGoruntule();
void kitapKoleksiyonunu();
void okumaDurumuGuncelle();
void koleksiyondanKitapSil();
void oduncRapor();
void oduncAlmaMenu();
void oduncAl();
void oduncListele();
void iadeEt();
void iadeListele();
void iadeRapor();
void erisebilirKitaplariListele();
void kitapTalepEt();
void talepleriYazdir();
void akademikKitapTalepEt();
void talepTedarikEt();
void benzerKitaplariOner();
void oduncAlinanKitaplariPuanla();
void oduncAlinanKitaplariListele();
void dortustu();

struct kitap { //Tek yönlü bağlı liste.1.modül personel girişi için.
    int id;
    string kitapadı;
    string yazar;
    int basımYılı;
    int sayfa;
    string hasarNotu;
    string yayinevi;
    string dil;
    string kategori;
    kitap* next;
};

struct kitapNode { //Çift yönlü dairesel bağlı liste.1.modül kullanıcı girişi için.
    int id;
    string kitapadı;
    string yazar;
    int basımYılı;
    int sayfa;
    string hasarNotu;
    string yorum;
    string yorumYapan;
    string okumaDurumu;
    string yayinevi;
    string dil;
    string kategori;
    kitapNode* next; //ileri
    kitapNode* prev; //geri
};

struct stackNode { // YIĞIN (STACK) 2.modül kullanıcı girişi için.
    int id;
    string kitapadı;
    string yazar;
    int basımYılı;
    int sayfa;
    string hasarNotu;
    string almaZamani;
    string teslimZamani;
    string yayinevi;
    string dil;
    string kategori;
    stackNode* next;
};

struct oduncRaporNode { //TEK YÖNLÜ DAİRESEL BAĞLI LİSTE 2. modül personel girişi için.
    string kitapadı;
    string yazar;
    int basımYılı;
    int sayfa;
    string hasarNotu;
    string almaZamani;
    string teslimZamani;
    oduncRaporNode* next;
};

struct talepNode { //KUYRUK (QUEUE) 3. modül personel ve kullanıcı girişi için.
    int talepId;
    string kitapAdi;
    string talepTuru; // "Normal" veya "Akademik"
    talepNode* next;
};

struct TreeNode { //AĞAÇ (TREE) 4.modül kullanıcı ve personel girişi için 
    int id;
    string kitapAdi;
    string yazar;
    int basimYili;
    int sayfa;
    string almaZamani;
    string teslimZamani;
    string yayinevi;
    string dil;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* yeniDugum(stackNode* kitap) { // stackNode'dan alınan kitap verileriyle yeni bir ağaç düğümü oluşturur
    TreeNode* yeni = new TreeNode; // Yeni düğüm için bellek ayır
    yeni->id = kitap->id;
    yeni->kitapAdi = kitap->kitapadı;
    yeni->yazar = kitap->yazar;
    yeni->basimYili = kitap->basımYılı;
    yeni->sayfa = kitap->sayfa;
    yeni->almaZamani = kitap->almaZamani;
    yeni->teslimZamani = kitap->teslimZamani;
    yeni->yayinevi = kitap->yayinevi;
    yeni->dil = kitap->dil;
    yeni->left = nullptr;  // Sol çocuk başlangıçta boş
    yeni->right = nullptr; // Sağ çocuk başlangıçta boş
    return yeni;
}

TreeNode* agacaEkle(TreeNode* root, stackNode* kitap) { // stackNode’dan gelen kitap verisini ikili arama ağacına ekler
    if (root == nullptr) {
        // Eğer ağaç boşsa, bu kitap ağacın kökü olur
        return yeniDugum(kitap);
    }
    if (kitap->id < root->id) { // Kitap ID’si kök düğümün ID’sinden küçükse sol alt ağaçta yer almal
        root->left = agacaEkle(root->left, kitap); // Sol dala ekleme yap
    }
    else { // Kitap ID’si kök düğümün ID’sinden büyük veya eşitse sağ alt ağaçta yer almalı
        root->right = agacaEkle(root->right, kitap); // Sağ dala ekleme yap
    }
    return root; // Güncellenmiş root düğümünü döndür
}

TreeNode* agacaEkleKitap(TreeNode* root, kitap* kitapBilgi) { //struct kitap bilgilerini ağaç yapısına ekler
    if (root == nullptr) {
        // Eğer ağaç boşsa, bu kitap ağacın kökü olur
        TreeNode* yeni = new TreeNode;
        yeni->id = kitapBilgi->id;
        yeni->kitapAdi = kitapBilgi->kitapadı;
        yeni->yazar = kitapBilgi->yazar;
        yeni->basimYili = kitapBilgi->basımYılı;
        yeni->sayfa = kitapBilgi->sayfa;
        yeni->yayinevi = kitapBilgi->yayinevi; // Yayınevi bilgisi
        yeni->almaZamani = ""; // Alma zamanı boş
        yeni->teslimZamani = ""; // Teslim zamanı boş
        yeni->left = nullptr;
        yeni->right = nullptr;
        return yeni;
    }
    if (kitapBilgi->id < root->id) {
        root->left = agacaEkleKitap(root->left, kitapBilgi);
    }
    else {
        root->right = agacaEkleKitap(root->right, kitapBilgi);
    }
    return root;
}

int kitapIDSayacı = 1;
int kitapSayacı = 0;

// Kategorilere göre hash tablosu
unordered_map<string, kitapNode*> kategoriHashTablosu;

// Ödünç alınan kitapların bilgilerini ve tek bir puanı saklayan hash tablosu
unordered_map<int, pair<stackNode*, int>> oduncKitaplarHash;

// Ödünç alınan kitapların bilgilerini ve birden fazla puanı saklayan hash tablosu
unordered_map<int, pair<stackNode*, pair<int, int>>> kitapPuanHash;

void pushStack(stackNode*& top, kitapNode* kitap, const string& almaZamani, const string& teslimZamani);
stackNode* popStack(stackNode*& top);
int tarihFarki(string teslimTarihi, string almaTarihi);
void raporOlustur(TreeNode* root);
void listele1950Once(TreeNode* root);
void listele1950Sonra(TreeNode* root);
void kitaplariYilaGoreListele(TreeNode* root);
void raporOlustur1950Once30Gundurumu(TreeNode* root);
void yayinevineGoreListeleHelper(TreeNode* root, const string& yayinevi);
void yayinevineGoreListele(TreeNode* root);
void kitaplariAgacaEkle(TreeNode*& root, kitap* head);
void dileGoreListele(TreeNode* root);
void dileGoreListeleHelper(TreeNode* root, const string& dil);
void sayfaSayisi1000denFazla(TreeNode* root);
void sayfaSayisi1000denAz(TreeNode* root);

struct kitap* head = NULL;
struct kitapNode* headNode = nullptr;
kitapNode* koleksiyonHead = nullptr; // Kullanıcının koleksiyonundaki ilk kitap
stackNode* top = nullptr;
stackNode* iadeTop = nullptr;
oduncRaporNode* oduncRaporHead = nullptr; //2.modül personelgirişi için 
talepNode* talepFront = nullptr; // Kuyruğun başı
talepNode* talepRear = nullptr;  // Kuyruğun sonu
int talepIdSayaci = 1;           // Talep ID sayaç
TreeNode* root = nullptr;        // İkili arama ağacının kök düğümü
bool oduncKitaplarAgacaEklendi = false; // Kitapların ağaca eklenip eklenmediğini kontrol eden bayrak

void AnaMenü() {
    int secim1;
    cout << " ------------------------------------------ " << endl;
    cout << "|               ANA MENU                   |" << endl;
    cout << " ------------------------------------------ " << endl;
    cout << "|1.Personel Girisi                         |" << endl;
    cout << "|2.Kullanıcı Girisi                        |" << endl;
    cout << "|3.Çıkış                                   |" << endl;
    cout << " ------------------------------------------ " << endl;
    cin >> secim1;
    cout << endl;
    switch (secim1)
    {
    case 1:
        personelMenu();
        break;
    case 2:
        kullaniciGiris();
        break;
    case 3:
        cout << "Programdan çıkılıyor..." << endl;
        exit(0);
    default:
        cout << "Geçersiz seçim! Lütfen tekrar deneyin." << endl;
        break;
    }
}

void personelMenu() {
    int secimPersonel;
    do {
        cout << " -------------------------------------------------------------------------- " << endl;
        cout << "|                                Personel Menü                             |" << endl;
        cout << " -------------------------------------------------------------------------- " << endl;
        cout << "|   1.Kitap Ekle (tek yönlü bağlı liste)                                   |" << endl;
        cout << "|   2.Kitapları sırala (sayfa sayısına göre) (tek yönlü bağlı liste)       |" << endl;
        cout << "|   3.Kitabı düzenle (tek yönlü bağlı liste)                               |" << endl;
        cout << "|   4.Kitap sil (tek yönlü bağlı liste)                                    |" << endl;
        cout << "|   5.Toplam Kitap sayısı (tek yönlü bağlı liste)                          |" << endl;
        cout << "|   6.Kitap ara (tek yönlü bağlı liste)                                    |" << endl;
        cout << "|   7.Basım yılı en eski 5 kitap (tek yönlü bağlı liste)                   |" << endl;
        cout << "|   8.Hasar notu ekle (tek yönlü bağlı liste)                              |" << endl;
        cout << "|   9.Hasarlı kitapları göster (tek yönlü bağlı liste)                     |" << endl;
        cout << "|   10.30 gün raporu oluştur (Ağaç)                                        |" << endl;
        cout << "|   11.Ödünç alınan kitapların raporu (tek yönlü dairesel bağlı liste)     |" << endl;
        cout << "|   12.İade edilen kitapların raporu  (tek yönlü dairesel bağlı liste)     |" << endl;
        cout << "|   13.Erişilebilir kitapların listesi (tek yönlü dairesel bağlı liste)    |" << endl;
        cout << "|   14.Talep tedarik et (kuyruk)                                           |" << endl;
        cout << "|   15.Ödünç alınan 1950’den önce ve sonra olan kitapları listele (Ağaç)   |" << endl;
        cout << "|   16.1950’den önce ve ödünç süresi 30 günü aşan kitapları listele (Ağaç) |" << endl;
        cout << "|   17.Puanı 4 ve üzeri olan kitapların listesi                            |" << endl;
        cout << "|   0.Ana Menü                                                             |" << endl;
        cout << " -------------------------------------------------------------------------- " << endl;
        cin >> secimPersonel;
        cout << endl;
        switch (secimPersonel) {
        case 1:
            kitapEkle();
            break;
        case 2:
            secimListele();
            break;
        case 3:
            kitapDuzenle();
            break;
        case 4:
            kitapSil();
            break;
        case 5:
            kitapSayisi();
            break;
        case 6:
            kitapAra();
            break;
        case 7:
            basımYılı5();
            break;
        case 8:
            hasarNot();
            break;
        case 9:
            hasarlıKitaplar();
            break;
        case 10:
            raporOlustur(root);
            break;
        case 11:
            oduncRapor();
            break;
        case 12:
            iadeRapor();
            break;
        case 13:
            erisebilirKitaplariListele();
            break;
        case 14:
            talepTedarikEt();
            break;
        case 15:
            kitaplariYilaGoreListele(root);
            break;
        case 16:
            raporOlustur1950Once30Gundurumu(root);
            break;
        case 17:
            dortustu();
            break;
        case 0:
            AnaMenü();
            break;
        default:
            cout << "Geçersiz seçim! Lütfen tekrar deneyin." << endl;
        }

    } while (secimPersonel != 0);  // Döngü, secimPersonel 0 olmadığı sürece devam eder.
}

void kullaniciGiris() {
    kitaplariAktar();
    int KullaniciSecim;
    do {
        cout << " ---------------------------------------------------------------------- " << endl;
        cout << "|                     Kullanıcı Menü                                   |" << endl;
        cout << " ---------------------------------------------------------------------- " << endl;
        cout << "|  1. Kitaba yorum yap (çift yönlü dairesel bağlı liste)               |" << endl;
        cout << "|  2. Kitap Yorumlarını göster (çift yönlü dairesel bağlı liste)       |" << endl;
        cout << "|  3. Kitap koleksiyonu (çift yönlü dairesel bağlı liste)              |" << endl;
        cout << "|  4. Ödünç alma menü                                                  |" << endl;
        cout << "|  5. Kitap talep et (kuyruk)                                          |" << endl;
        cout << "|  6. Akademik kitap talep et (kuyruk)                                 |" << endl;
        cout << "|  7. Talepleri göster (kuyruk)                                        |" << endl;
        cout << "|  0. Çıkış                                                            |" << endl;
        cout << " ---------------------------------------------------------------------- " << endl;
        cin >> KullaniciSecim;
        cout << endl;
        switch (KullaniciSecim)
        {
        case 1:
            yorumYap();
            break;
        case 2:
            yorumlariGoster();
            break;
        case 3:
            kitapKoleksiyonunu();
            break;
        case 4:
            oduncAlmaMenu();
            break;
        case 5:
            kitapTalepEt();
            break;
        case 6:
            akademikKitapTalepEt();
            break;
        case 7:
            talepleriYazdir();
            break;
        case 0:
            AnaMenü();
            break;
        default:
            cout << "Geçersiz seçim! Lütfen tekrar deneyin." << endl;
        }
    } while (KullaniciSecim != 0);
}


void oduncAlmaMenu() {
    int secimOdunc;
    do {
        cout << " ------------------------------------------------------- \n";
        cout << "|  1.  Kitap ödünç al (stack)                           |\n";
        cout << "|  2.  Ödünç alınanları listele (stack)                 |\n";
        cout << "|  3.  Kitap iade et (stack)                            |\n";
        cout << "|  4.  İade edilenleri listele (stack)                  |\n";
        cout << "|  5.  Yayınevine göre listele (Ağaç)                   |\n";
        cout << "|  6.  Diline göre listele (Ağaç)                       |\n";
        cout << "|  7.  Sayfa sayısına göre filtrele (Ağaç)              |\n";
        cout << "|  8.  Benzer kitaplar öner (ödünç alınanlar arasında)  |\n";
        cout << "|  9.  Ödünç alınan kitapları puanla                    |\n";
        cout << "|  10. Ödünç alınan kitapların puanlamalarını listele   |\n";
        cout << "|  0.  Çıkış                                            |\n";
        cout << " ------------------------------------------------------- \n";
        cin >> secimOdunc;
        switch (secimOdunc) {
        case 1:
            oduncAl();
            break;
        case 2:
            oduncListele();
            break;
        case 3:
            iadeEt();
            break;
        case 4:
            iadeListele();
            break;
        case 5:
            yayinevineGoreListele(root);
            break;
        case 6:
            dileGoreListele(root);
            break;
        case 7:
            cout << " -------------------------------------------------- " << endl;
            cout << "|    1000'DEN AZ SAYFA SAYISINA SAHİP KİTAPLAR     |" << endl;
            cout << " -------------------------------------------------- " << endl;
            sayfaSayisi1000denAz(root);
            cout << " -------------------------------------------------- " << endl;
            cout << "|    1000'DEN FAZLA SAYFA SAYISINA SAHİP KİTAPLAR  |" << endl;
            cout << " -------------------------------------------------- " << endl;
            sayfaSayisi1000denFazla(root);
            break;
        case 8:
            benzerKitaplariOner();
            break;
        case 9:
            oduncAlinanKitaplariPuanla();
            break;
        case 10:
            oduncAlinanKitaplariListele();
            break;
        case 0:
            AnaMenü();
            break;
        }
    } while (secimOdunc != 5);
}

stackNode* popStack(stackNode*& top) {
    // Bu fonksiyon, stack (yığın) veri yapısından en üstteki elemanı çıkarır ve döndürür.
    if (top == nullptr) {
        cout << "Yığın boş! Çıkarılacak eleman yok." << endl;
        return nullptr;
    }

    // Yığının en üstündeki elemanı al
    stackNode* silinecek = top;

    // Yığının en üstünü bir sonraki elemana kaydır
    top = top->next;

    // Çıkarılan elemanı döndür
    return silinecek;
}

void pushStack(stackNode*& top, kitapNode* kitap, const string& almaZamani, const string& teslimZamani) {
    // Bu fonksiyon, ödünç alınan bir kitabı stack (yığın) veri yapısına ekler.
    stackNode* yeni = new stackNode;  // Yeni bir stack node oluşturuluyor.
    yeni->id = kitap->id;
    yeni->kitapadı = kitap->kitapadı;
    yeni->yazar = kitap->yazar;
    yeni->basımYılı = kitap->basımYılı;
    yeni->sayfa = kitap->sayfa;
    yeni->hasarNotu = kitap->hasarNotu;
    yeni->almaZamani = almaZamani;
    yeni->teslimZamani = teslimZamani; // - top: Stack'in en üst düğümünü işaret eden pointer.
    yeni->kategori = kitap->kategori;
    yeni->dil = kitap->dil;
    yeni->yayinevi = kitap->yayinevi;
    yeni->next = top;                 // Stack'e ekleme işlemi
    top = yeni;                       // Yeni node stack'in en üstü oldu
    cout << "Kitap ödünç alındı: " << kitap->kitapadı << endl;
}

void ornekKitaplarEkle() {
    kitap* kitap1 = new kitap{ 1, "Yüzüklerin Efendisi: Yüzük Kardeşliği", "J.R.R. Tolkien", 1954, 423, "", "Yabancı", "Türkçe", "Roman" };
    kitap* kitap2 = new kitap{ 2, "Suç ve Ceza", "Fyodor Dostoyevski", 1866, 671, "", "Yabancı", "Türkçe", "Roman" };
    kitap* kitap3 = new kitap{ 3, "Veri Yapıları ve Algoritmalar", "Thomas H. Cormen", 2009, 1312, "", "Yabancı", "İngilizce", "Eğitim" };
    kitap* kitap4 = new kitap{ 4, "Küçük Prens", "Antoine de Saint-Exupéry", 1943, 96, "", "Yabancı", "Türkçe", "Çocuk" };
    kitap* kitap5 = new kitap{ 5, "Serway Fizik", "Raymond A. Serway", 2014, 1320, "", "Yabancı", "İngilizce", "Eğitim" };
    kitap* kitap6 = new kitap{ 6, "Saatleri Ayarlama Enstitüsü", "Ahmet Hamdi Tanpınar", 1961, 361, "", "Yerli", "Türkçe", "Roman" };
    kitap* kitap7 = new kitap{ 7, "Çalıkuşu", "Reşat Nuri Güntekin", 1922, 408, "", "Yerli", "Türkçe", "Roman" };
    kitap* kitap8 = new kitap{ 8, "Bilgisayar Ağları", "Andrew S. Tanenbaum", 2011, 960, "", "Yabancı", "İngilizce", "Eğitim" };
    kitap* kitap9 = new kitap{ 9, "İşletim Sistemleri", "Abraham Silberschatz", 2018, 976, "", "Yabancı", "İngilizce", "Eğitim" };
    kitap* kitap10 = new kitap{ 10, "Harry Potter ve Ölüm Yadigarları", "J.K. Rowling", 2007, 607, "", "Yabancı", "İngilizce", "Roman" };
    kitap* kitap11 = new kitap{ 11, "Kürk Mantolu Madonna", "Sabahattin Ali", 1943, 177, "", "Yerli", "Türkçe", "Roman" };
    kitap* kitap12 = new kitap{ 12, "Yüzyıllık Yalnızlık", "Gabriel García Márquez", 1967, 417, "", "Yabancı", "Türkçe", "Roman" };
    kitap* kitap13 = new kitap{ 13, "Dönüşüm", "Franz Kafka", 1915, 74, "", "Yabancı", "Türkçe", "Roman" };
    kitap* kitap14 = new kitap{ 14, "İnce Memed", "Yaşar Kemal", 1955, 419, "", "Yerli", "Türkçe", "Roman" };
    kitap* kitap15 = new kitap{ 15, "Karamazov Kardeşler", "Fyodor Dostoyevski", 1880, 840, "", "Yabancı", "Türkçe", "Roman" };
    kitap* kitap16 = new kitap{ 16, "Sefiller", "Victor Hugo", 1862, 1463, "", "Yabancı", "Türkçe", "Roman" };
    kitap* kitap17 = new kitap{ 17, "Harry Potter ve Felsefe Taşı", "J.K. Rowling", 1997, 223, "", "Yabancı", "İngilizce", "Roman" };
    kitap* kitap18 = new kitap{ 18, "Don Kişot", "Miguel de Cervantes", 1605, 1072, "", "Yabancı", "Türkçe", "Roman" };
    kitap* kitap19 = new kitap{ 19, "Tutunamayanlar", "Oğuz Atay", 1971, 724, "", "Yerli", "Türkçe", "Roman" };
    kitap* kitap20 = new kitap{ 20, "Hayvan Çiftliği", "George Orwell", 1945, 152, "", "Yabancı", "Türkçe", "Roman" };

    // Kitapları listeye ekle
    kitap* kitaplar[] = { kitap1, kitap2, kitap3, kitap4, kitap5, kitap6, kitap7, kitap8, kitap9, kitap10,
                         kitap11, kitap12, kitap13, kitap14, kitap15, kitap16, kitap17, kitap18, kitap19, kitap20 };
    for (int i = 0; i < 20; i++) {
        if (head == nullptr) {
            head = kitaplar[i];
        }
        else {
            kitap* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = kitaplar[i];
        }
        kitapSayacı++;
    }
    // ID sayaçlarını güncelle
    kitapIDSayacı = 21; // Son ID 20 olduğu için bir sonraki ID 21 olacak
}

void oduncAl() {
    if (headNode == nullptr) {
        cout << "Ödünç alınabilecek kitap bulunamadı! Liste boş." << endl;
        return;
    }

    int oduncId;
    cout << "Ödünç almak istediğiniz kitabın ID'sini giriniz: ";
    cin >> oduncId;

    kitapNode* temp = headNode;
    bool bulundu = false;

    // Kitap arama döngüsü
    do {
        if (temp->id == oduncId) {
            // Kitap bulundu, ödünç alma işlemi yapılacak
            bulundu = true;

            // Ödünç alma süresi seçimi
            int oduncSuresi;
            do {
                cout << "Ödünç alma süresini girin (en fazla 60 gün): ";
                cin >> oduncSuresi;

                if (oduncSuresi > 60) {
                    cout << "Hata: Ödünç alma süresi en fazla 60 gün olabilir. Lütfen tekrar deneyin." << endl;
                }
            } while (oduncSuresi > 60); // Kullanıcı geçerli bir süre girene kadar döngü devam eder

            // Hash tablosuna ekleme
            string kategori = temp->kategori;
            if (kategoriHashTablosu.find(kategori) == kategoriHashTablosu.end()) {
                // Eğer kategori hash tablosunda yoksa, yeni bir bağlı liste başlat
                kategoriHashTablosu[kategori] = nullptr;
            }

            // Yeni bir düğüm oluştur ve bağlı listenin başına ekle
            kitapNode* yeniNode = new kitapNode(*temp); // Kitap bilgilerini kopyala
            yeniNode->next = kategoriHashTablosu[kategori];
            kategoriHashTablosu[kategori] = yeniNode;

            // Alma zamanı ve teslim tarihini hesapla
            time_t now = time(0); // Şu anki zaman
            tm localTime;
            localtime_s(&localTime, &now);

            // Alma zamanı
            char almaZamani[20];
            strftime(almaZamani, sizeof(almaZamani), "%Y-%m-%d", &localTime);

            // Teslim tarihi (seçilen gün sonrası)
            localTime.tm_mday += oduncSuresi; // Günleri ekle
            mktime(&localTime);              // Tarihi normalize et
            char teslimTarihi[20];
            strftime(teslimTarihi, sizeof(teslimTarihi), "%Y-%m-%d", &localTime);

            // Kitabı stack'e ekle
            pushStack(top, temp, almaZamani, teslimTarihi);

            // Ödünç alınan kitabı ağaca ekle
            root = agacaEkle(root, top);

            // Alma ve teslim tarihlerini ekrana yazdır
            cout << "Kitap başarıyla ödünç alındı: " << temp->kitapadı << endl;
            cout << "Alma Zamanı: " << almaZamani << endl;
            cout << "Teslim Tarihi: " << teslimTarihi << endl;

            break;
        }
        temp = temp->next;
    } while (temp != headNode);

    if (!bulundu) {
        cout << "Bu ID'ye sahip bir kitap bulunamadı." << endl;
    }
}

void benzerKitaplariOner() {
    if (top == nullptr) {
        cout << "Ödünç alınan kitap bulunmamaktadır!" << endl;
        return;
    }

    int kitapId;
    cout << "Benzer kitap önerisi almak istediğiniz ödünç alınan kitabın ID'sini giriniz: ";
    cin >> kitapId;

    // Ödünç alınan kitaplar arasında ID'yi bul
    stackNode* temp = top;
    stackNode* secilenKitap = nullptr;
    while (temp != nullptr) {
        if (temp->id == kitapId) {
            secilenKitap = temp;
            break;
        }
        temp = temp->next;
    }

    if (secilenKitap == nullptr) {
        cout << "Bu ID'ye sahip ödünç alınan bir kitap bulunamadı." << endl;
        return;
    }

    string kategori = secilenKitap->kategori;

    // Hash tablosundan aynı kategorideki ödünç alınan kitapları al
    if (kategoriHashTablosu.find(kategori) == kategoriHashTablosu.end() || kategoriHashTablosu[kategori] == nullptr) {
        cout << "Bu kategoriye ait başka ödünç alınan kitap bulunmamaktadır." << endl;
        return;
    }

    cout << "Benzer kitap önerileri (" << kategori << " kategorisi, ödünç alınanlar arasında):" << endl;
    kitapNode* iter = kategoriHashTablosu[kategori];
    bool bulundu = false;
    while (iter != nullptr) {
        if (iter->id != secilenKitap->id) { // Seçilen kitabı önerme
            cout << "Kitap ID: " << iter->id << ", Kitap Adı: " << iter->kitapadı << ", Yazar: " << iter->yazar << endl;
            bulundu = true;
        }
        iter = iter->next;
    }

    if (!bulundu) {
        cout << "Bu kategoriye ait başka ödünç alınan kitap bulunmamaktadır." << endl;
    }
}

void oduncRapor() {
    // Eğer ödünç alınan kitaplar yığını boşsa
    if (top == nullptr) {
        cout << "Ödünç alınan kitap bulunmamaktadır!" << endl;
        return;
    }

    // Yığındaki kitapları dolaş
    while (top != nullptr) {
        // Yığından eleman çıkar
        stackNode* current = popStack(top);

        // Yeni bir rapor düğümü oluştur
        oduncRaporNode* yeniRapor = new oduncRaporNode;
        yeniRapor->kitapadı = current->kitapadı;
        yeniRapor->yazar = current->yazar;
        yeniRapor->basımYılı = current->basımYılı;
        yeniRapor->sayfa = current->sayfa;
        yeniRapor->hasarNotu = current->hasarNotu;
        yeniRapor->almaZamani = current->almaZamani;     // Alma zamanı
        yeniRapor->teslimZamani = current->teslimZamani; // Teslim zamanı

        // Yeni düğümü dairesel bağlı listeye ekle
        if (oduncRaporHead == nullptr) {
            oduncRaporHead = yeniRapor;
            yeniRapor->next = oduncRaporHead; // Dairesel bağlantı
        }
        else {
            oduncRaporNode* iter = oduncRaporHead;
            while (iter->next != oduncRaporHead) {
                iter = iter->next;
            }
            iter->next = yeniRapor;
            yeniRapor->next = oduncRaporHead; // Dairesel bağlantı
        }

        // Bellekteki yığın elemanını serbest bırak
        delete current;
    }

    // Raporu ekrana yazdır
    cout << " ------------------------------- " << endl;
    cout << "|      Ödünç Alınan Kitaplar    |" << endl;
    cout << " ------------------------------- " << endl;

    oduncRaporNode* iter = oduncRaporHead;
    do {
        cout << "Kitap Adı    : " << iter->kitapadı << endl;
        cout << "Yazar        : " << iter->yazar << endl;
        cout << "Basım Yılı   : " << iter->basımYılı << endl;
        cout << "Sayfa Sayısı : " << iter->sayfa << endl;
        cout << "Hasar Notu   : " << iter->hasarNotu << endl;
        cout << "Alma Zamanı  : " << iter->almaZamani << endl;
        cout << "Teslim Zamanı: " << iter->teslimZamani << endl;
        cout << "---------------------------------" << endl;

        iter = iter->next;
    } while (iter != oduncRaporHead);
}

void oduncListele() {
    // Eğer yığın (stack) boşsa, ödünç alınan kitap olmadığını belirt
    if (top == nullptr) {
        cout << "Ödünç alınan kitap bulunmamaktadır!" << endl;
        return; // Fonksiyonu sonlandır
    }

    // Başlık yazdır
    cout << " ------------------------------- " << endl;
    cout << "|      Ödünç Alınan Kitaplar    |" << endl;
    cout << " ------------------------------- " << endl;

    // Yığının en üstünden başlayarak elemanları dolaşmak için geçici bir pointer oluştur
    stackNode* temp = top;

    // Yığın boş olana kadar tüm elemanları dolaş
    while (temp != nullptr) {
        // Kitap bilgilerini ekrana yazdır
        cout << "Kitap Adı    : " << temp->kitapadı << endl;
        cout << "Yazar        : " << temp->yazar << endl;
        cout << "Basım Yılı   : " << temp->basımYılı << endl;
        cout << "Sayfa Sayısı : " << temp->sayfa << endl;
        cout << "Alma Zamanı  : " << temp->almaZamani << endl;
        cout << "Teslim Tarihi: " << temp->teslimZamani << endl;
        cout << "---------------------------------" << endl;

        // Bir sonraki stack elemanına geç
        temp = temp->next;
    }
}

void iadeEt() {
    // Eğer ödünç alınan kitaplar yığını boşsa, işlem yapılamaz
    if (top == nullptr) {
        cout << "İade edilecek kitap bulunmamaktadır! Ödünç alınan kitap yığını boş." << endl;
        return;
    }

    int iadeId;
    cout << "İade etmek istediğiniz kitabın ID'sini giriniz: ";
    cin >> iadeId;

    stackNode* tempStack = nullptr; // Geçici bir yığın oluşturuluyor
    stackNode* silinecek = nullptr;
    bool bulundu = false;

    // Yığındaki kitapları dolaşarak ID'yi arıyoruz
    while (top != nullptr) {
        stackNode* current = popStack(top);

        if (current->id == iadeId) { // ID eşleşmesi
            silinecek = current;
            bulundu = true;
            break;
        }
        else {
            current->next = tempStack; // ID eşleşmiyorsa, kitabı geçici yığına taşı
            tempStack = current;
        }
    }

    if (bulundu) {
        // İade edilen zamanın alınması
        time_t now = time(0);
        tm localTime;
        localtime_s(&localTime, &now);

        char iadeZamani[20];
        strftime(iadeZamani, sizeof(iadeZamani), "%Y-%m-%d", &localTime);

        cout << "İade edilen kitap bilgileri:" << endl;
        cout << "Kitap ID     : " << silinecek->id << endl;
        cout << "Kitap Adı    : " << silinecek->kitapadı << endl;
        cout << "Yazar        : " << silinecek->yazar << endl;
        cout << "Basım Yılı   : " << silinecek->basımYılı << endl;
        cout << "Sayfa Sayısı : " << silinecek->sayfa << endl;
        cout << "Hasar Notu   : " << silinecek->hasarNotu << endl;
        cout << "İade Zamanı  : " << iadeZamani << endl;

        // İade edilen kitabı iadeTop yığınına ekle
        silinecek->next = iadeTop;
        iadeTop = silinecek;

        cout << "Kitap başarıyla iade edildi!" << endl;
    }
    else {
        cout << "Bu ID'ye sahip ödünç alınan bir kitap bulunamadı." << endl;
    }

    // Geçici yığındaki kitapları tekrar ana yığına taşı
    while (tempStack != nullptr) {
        stackNode* current = popStack(tempStack);
        current->next = top;
        top = current;
    }
}

void iadeRapor() {
    // Eğer iade yığını (iadeTop) boşsa, rapor oluşturulamaz
    if (iadeTop == nullptr) {
        cout << "İade edilen kitap bulunmamaktadır!" << endl;
        return;
    }

    // Başlık yazdır
    cout << " ------------------------------- " << endl;
    cout << "|      İade Edilen Kitaplar     |" << endl;
    cout << " ------------------------------- " << endl;

    // Yığının en üstünden başlayarak elemanları dolaşmak için geçici bir pointer oluştur
    stackNode* temp = iadeTop;

    // Yığın boş olana kadar tüm elemanları dolaş
    while (temp != nullptr) {
        // Teslim süresine göre kontrol
        int fark = tarihFarki(temp->teslimZamani, temp->almaZamani);
        if (fark >= 0) {
            cout << "30 gün altı sürede iade edildi: " << temp->kitapadı << endl;
        }
        else {
            cout << "30 gün üstü sürede iade edildi: " << temp->kitapadı << endl;
        }

        // Kitap bilgilerini yazdır
        cout << "Kitap ID     : " << temp->id << endl;
        cout << "Kitap Adı    : " << temp->kitapadı << endl;
        cout << "Yazar        : " << temp->yazar << endl;
        cout << "Basım Yılı   : " << temp->basımYılı << endl;
        cout << "Sayfa Sayısı : " << temp->sayfa << endl;
        cout << "Hasar Notu   : " << temp->hasarNotu << endl;
        cout << "İade Zamanı  : " << temp->almaZamani << endl;
        cout << "---------------------------------" << endl;

        temp = temp->next;
    }
}

void iadeListele() {
    // Eğer iade yığını (iadeTop) boşsa, iade edilen kitap olmadığını belirt
    if (iadeTop == nullptr) {
        cout << "İade edilen kitap bulunmamaktadır!" << endl;
        return;
    }

    // Başlık yazdır
    cout << "---------------------------------" << endl;
    cout << "|      İade Edilen Kitaplar     |" << endl;
    cout << "---------------------------------" << endl;

    // Yığının en üstünden başlayarak elemanları dolaşmak için geçici bir pointer oluştur
    stackNode* temp = iadeTop;

    // Yığın boş olana kadar tüm elemanları dolaş
    while (temp != nullptr) {
        // Kitap bilgilerini ekrana yazdır
        cout << "Kitap Adı    : " << temp->kitapadı << endl;
        cout << "Yazar        : " << temp->yazar << endl;
        cout << "Basım Yılı   : " << temp->basımYılı << endl;
        cout << "Sayfa Sayısı : " << temp->sayfa << endl;
        cout << "Hasar Notu   : " << temp->hasarNotu << endl;

        // İade edilen zaman bilgisi
        time_t now = time(0); // Şu anki zaman
        tm localTime;
        localtime_s(&localTime, &now);

        // Zamanı formatla
        char iadeZamani[20];
        strftime(iadeZamani, sizeof(iadeZamani), "%Y-%m-%d", &localTime);
        cout << "İade Zamanı  : " << iadeZamani << endl;

        cout << "---------------------------------" << endl;

        // Bir sonraki stack elemanına geç
        temp = temp->next;
    }
}

void oduncAlinanKitaplariPuanla() {
    if (top == nullptr) {
        cout << "Ödünç alınan kitap bulunmamaktadır!" << endl;
        return;
    }

    int kitapId;
    cout << "Puanlamak istediğiniz kitabın ID'sini giriniz: ";
    cin >> kitapId;

    // Ödünç alınan kitaplar arasında ID'yi bul
    stackNode* temp = top;
    stackNode* secilenKitap = nullptr;
    while (temp != nullptr) {
        if (temp->id == kitapId) {
            secilenKitap = temp;
            break;
        }
        temp = temp->next;
    }

    if (secilenKitap == nullptr) {
        cout << "Bu ID'ye sahip ödünç alınan bir kitap bulunamadı." << endl;
        return;
    }

    // Puanlama işlemi
    int puan;
    do {
        cout << "Kitap ID: " << secilenKitap->id << ", Kitap Adı: " << secilenKitap->kitapadı << endl;
        cout << "Bu kitabı 1 ile 5 arasında puanlayın: ";
        cin >> puan;

        if (puan < 1 || puan > 5) {
            cout << "Geçersiz puan! Lütfen 1 ile 5 arasında bir değer girin." << endl;
        }
    } while (puan < 1 || puan > 5);

    // Hash tablosuna ekle veya güncelle
    if (kitapPuanHash.find(secilenKitap->id) == kitapPuanHash.end()) {
        // Eğer kitap hash tablosunda yoksa, yeni bir giriş oluştur
        kitapPuanHash[secilenKitap->id] = make_pair(secilenKitap, make_pair(puan, 1));
    }
    else {
        // Eğer kitap zaten hash tablosunda varsa, puan toplamını ve sayısını güncelle
        kitapPuanHash[secilenKitap->id].second.first += puan; // Puan toplamını artır
        kitapPuanHash[secilenKitap->id].second.second += 1;   // Puan sayısını artır
    }

    cout << "Kitap başarıyla puanlandı!" << endl;
}

void dortustu() {
    if (kitapPuanHash.empty()) {
        cout << "Puanlanmış kitap bulunmamaktadır!" << endl;
        return;
    }

    cout << "\nPuan ortalaması 4 ve üzerinde olan kitaplar:" << endl;
    bool bulundu = false;

    for (const auto& kitap : kitapPuanHash) {
        int toplamPuan = kitap.second.second.first; // Puanların toplamı
        int puanSayisi = kitap.second.second.second; // Puan sayısı
        double ortalama = static_cast<double>(toplamPuan) / puanSayisi; // Ortalama hesapla

        if (ortalama >= 4.0) {
            bulundu = true;
            cout << "Kitap ID: " << kitap.first
                << ", Kitap Adı: " << kitap.second.first->kitapadı
                << ", Ortalama Puan: " << fixed << setprecision(2) << ortalama << endl;
        }
    }

    if (!bulundu) {
        cout << "Puan ortalaması 4 ve üzerinde olan kitap bulunmamaktadır!" << endl;
    }
}

void oduncAlinanKitaplariListele() {
    if (oduncKitaplarHash.empty()) {
        cout << "Ödünç alınan kitap bulunmamaktadır!" << endl;
        return;
    }
    // Hash tablosundaki kitapları listele
    cout << "\nÖdünç alınan kitaplar ve puanları:" << endl;
    for (const auto& kitap : oduncKitaplarHash) {
        cout << "Kitap ID: " << kitap.first
            << ", Kitap Adı: " << kitap.second.first->kitapadı
            << ", Puan: " << kitap.second.second << endl;
    }
}

void erisebilirKitaplariListele() {
    // Eğer ödünç alınan kitaplar yığını boşsa, tüm kitaplar erişilebilirdir
    if (top == nullptr) {
        cout << "Tüm kitaplar erişilebilirdir. Ödünç alınmış kitap bulunmamaktadır!" << endl;
        return;
    }

    // Yeni bir tek yönlü dairesel bağlı liste oluştur
    kitapNode* erisebilirHead = nullptr;

    // Stack'teki kitapları dolaş
    stackNode* tempStack = top;
    while (tempStack != nullptr) {
        // Yeni bir kitapNode oluştur
        kitapNode* yeniNode = new kitapNode;
        yeniNode->id = tempStack->id;
        yeniNode->kitapadı = tempStack->kitapadı;
        yeniNode->yazar = tempStack->yazar;
        yeniNode->basımYılı = tempStack->basımYılı;
        yeniNode->sayfa = tempStack->sayfa;
        yeniNode->hasarNotu = tempStack->hasarNotu;
        yeniNode->next = nullptr;

        // Eğer liste boşsa, ilk düğümü oluştur
        if (erisebilirHead == nullptr) {
            erisebilirHead = yeniNode;
            erisebilirHead->next = erisebilirHead; // Dairesel bağlantı
        }
        else {
            // Listeye yeni düğüm ekle
            kitapNode* iter = erisebilirHead;
            while (iter->next != erisebilirHead) {
                iter = iter->next;
            }
            iter->next = yeniNode;
            yeniNode->next = erisebilirHead; // Dairesel bağlantı
        }

        // Bir sonraki stack elemanına geç
        tempStack = tempStack->next;
    }

    // Listeyi ekrana yazdır
    if (erisebilirHead == nullptr) {
        cout << "Erişilebilir kitap bulunmamaktadır!" << endl;
        return;
    }

    cout << "---------------------------------" << endl;
    cout << "|    Erişilebilir Kitaplar      |" << endl;
    cout << "---------------------------------" << endl;

    kitapNode* iter = erisebilirHead;
    do {
        cout << "Kitap ID     : " << iter->id << endl;
        cout << "Kitap Adı    : " << iter->kitapadı << endl;
        cout << "Yazar        : " << iter->yazar << endl;
        cout << "Basım Yılı   : " << iter->basımYılı << endl;
        cout << "Sayfa Sayısı : " << iter->sayfa << endl;
        cout << "Hasar Notu   : " << iter->hasarNotu << endl;
        cout << "---------------------------------" << endl;
        iter = iter->next;
    } while (iter != erisebilirHead);
}

void yorumYap() {
    int alinanID;
    if (headNode == nullptr) {
        cout << "Yorum yapacak kitap bulunamadı! Liste boş." << endl;
        return;
    }
    cout << "Yorum yapmak istediğiniz kitabın ID'sini giriniz:";
    cin >> alinanID;
    cout << endl;
    bool bulundu = false;
    kitapNode* temp = headNode;
    do
    {
        if (temp->id == alinanID) {
            cin.ignore();
            cout << "İsminizi girin: ";
            getline(cin, temp->yorumYapan); // Yorumu yapan kişinin adı
            cout << "Yorumunuzu yazın: ";
            getline(cin, temp->yorum); // Yorumu ilgili düğümün 'yorum' alanına yaz
            cout << "Yorum başarıyla eklendi!" << endl;
            bulundu = true;
            break;
        }
        temp = temp->next;
    } while (temp != headNode); // Baştan sona kadar git, başa dönünce dur
    if (!bulundu) {
        cout << "Bu ID'ye sahip bir kitap bulunamadı." << endl;
    }
}

void yorumlariGoster() {
    int alinanID;
    if (headNode == nullptr) {
        cout << "Yorumları gösterecek kitap bulunamadı! Liste boş." << endl;
        return; //kitap yoksa Fonksiyonu sonlandır ve yorum gösterilmesini engelle
    }
    cout << "Yorumları göstermek istediğiniz kitabın ID'sini giriniz: ";
    cin >> alinanID;
    cout << endl;
    bool bulundu = false; // Kitap bulunup bulunmadığını kontrol etmek için
    kitapNode* temp = headNode; // Çift yönlü dairesel bağlı listeyi gezmek için geçici bir pointer oluşturuyoruz
    // Dairesel bağlı listeyi geziyoruz. Yani, listeyi baştan sona kadar döneceğiz
    do {
        // Eğer şu anki kitap (temp) verilen ID'ye sahipse
        if (temp->id == alinanID) {
            // Kitap bulundu, yorumları göster
            cout << "Kitap: " << temp->kitapadı << " (" << temp->id << ")" << endl;
            if (temp->yorum.empty()) {
                cout << "Bu kitap için herhangi bir yorum yapılmamış." << endl;
            }
            else {
                cout << "kullanıcı:" << temp->yorumYapan << endl;
                cout << "Yorum: " << temp->yorum << endl;
            }
            bulundu = true; // Kitap bulundu, o yüzden flag'i true yap
            break; // Kitap bulunduğu için döngüden çıkıyoruz
        }
        temp = temp->next;
    } while (temp != headNode); // Dairesel yapı olduğu için başa dönene kadar devam et
    // Eğer kitap bulunamadıysa, kullanıcıya bir mesaj ver
    if (!bulundu) {
        cout << "Bu ID'ye sahip bir kitap bulunamadı." << endl;
    }
}

void kitaplariAktar()
{
    if (head == NULL)
    {
        return;
    }
    // Bağlı listeyi geziyoruz
    kitap* temp = head;
    while (temp != NULL) {
        // Yeni bir kitapNode oluşturuyoruz ve personel listesindeki kitaptan bilgileri aktarıyoruz
        kitapNode* yeniKitapNode = new kitapNode;
        yeniKitapNode->id = temp->id;
        yeniKitapNode->kitapadı = temp->kitapadı;
        yeniKitapNode->yazar = temp->yazar;
        yeniKitapNode->basımYılı = temp->basımYılı;
        yeniKitapNode->sayfa = temp->sayfa;
        yeniKitapNode->hasarNotu = temp->hasarNotu;
        yeniKitapNode->yorum = ""; // Başlangıçta kullanıcı yorumu boş olacak.
        yeniKitapNode->dil = temp->dil;
        yeniKitapNode->yayinevi = temp->yayinevi;
        // Eğer kullanıcı listesi boşsa, ilk kitapNode'u head olarak atıyoruz
        if (headNode == nullptr) {
            headNode = yeniKitapNode;
            yeniKitapNode->next = yeniKitapNode;  // Tek elemanlı dairesel liste
            yeniKitapNode->prev = yeniKitapNode;
        }
        else
        {
            kitapNode* last = headNode->prev;  // Kullanıcı listesindeki son eleman
            last->next = yeniKitapNode;        // Yeni kitabı sona ekliyoruz
            yeniKitapNode->prev = last;        // Yeni kitabın prev işaretçisi son elemana işaret eder
            yeniKitapNode->next = headNode;    // Son eleman bir sonraki eleman olarak head'e bağlanır
            headNode->prev = yeniKitapNode;    // Head'in prev işaretçisi de yeni kitaba işaret eder
        }
        temp = temp->next;
    }
}

void kitapKoleksiyonunu() {
    int secimKoleksiyon;
    do {
        cout << " ---------------------------------------------------------------- " << endl;
        cout << "|      Kitap koleksiyonu                                         |" << endl;
        cout << " ---------------------------------------------------------------- " << endl;
        cout << "|  1. Koleksiyona kitap ekle (çift yönlü dairesel bağlı liste)   |" << endl;
        cout << "|  2. Koleksiyonu görüntüle (çift yönlü dairesel bağlı liste)    |" << endl;
        cout << "|  3. Okuma durumunu güncelle (çift yönlü dairesel bağlı liste)  |" << endl;
        cout << "|  4. Kitap sil (çift yönlü dairesel bağlı liste)                |" << endl;
        cout << "|  5. Kullanıcı Menüye dön                                       |" << endl;
        cout << " ---------------------------------------------------------------- " << endl;
        cout << "Seçiminiz: ";
        cin >> secimKoleksiyon;
        switch (secimKoleksiyon) {
        case 1:
            koleksiyonaKitapEkle();
            break;
        case 2:
            koleksiyonuGoruntule();
            break;
        case 3:
            okumaDurumuGuncelle();
            break;
        case 4:
            koleksiyondanKitapSil();
            break;
        case 5:
            kullaniciGiris();
            break;
        default:
            cout << "Geçersiz seçim!\n";
            break;
        }
    } while (secimKoleksiyon != 5);
}

void koleksiyonaKitapEkle() {
    if (headNode == nullptr) {
        cout << "Kitap listesi boş! Önce personel girişinden kitap ekleyin." << endl;
        return;
    }
    int kitapId;
    cout << "Eklemek istediğiniz kitabın ID'sini girin: ";
    cin >> kitapId;
    kitapNode* temp = headNode; // Ana kitap listesi başından başla
    bool bulundu = false;
    // Ana kitap listesinde kitap arıyoruz
    do {
        if (temp->id == kitapId) {
            // Kitap bulundu, şimdi koleksiyon için kopyasını oluşturuyoruz
            kitapNode* yeniNode = new kitapNode;
            yeniNode->id = temp->id;
            yeniNode->kitapadı = temp->kitapadı;
            yeniNode->yazar = temp->yazar;
            yeniNode->basımYılı = temp->basımYılı;
            yeniNode->sayfa = temp->sayfa;
            yeniNode->hasarNotu = temp->hasarNotu;
            yeniNode->yorum = temp->yorum;
            yeniNode->next = nullptr;
            yeniNode->prev = nullptr;

            // Koleksiyon boşsa başa ekle
            if (koleksiyonHead == nullptr) {
                koleksiyonHead = yeniNode;
                koleksiyonHead->next = koleksiyonHead;
                koleksiyonHead->prev = koleksiyonHead;
            }
            else {
                // Koleksiyonun sonuna ekleme
                kitapNode* son = koleksiyonHead->prev;
                son->next = yeniNode;
                yeniNode->prev = son;
                yeniNode->next = koleksiyonHead;
                koleksiyonHead->prev = yeniNode;
            }

            cout << "Kitap koleksiyona başarıyla eklendi!" << endl;
            bulundu = true;
            break;
        }
        temp = temp->next;
    } while (temp != headNode); // Dairesel yapıda başa dönünce dur

    if (!bulundu) {
        cout << "Bu ID’ye sahip kitap bulunamadı!" << endl;
    }
}

void koleksiyonuGoruntule() {
    if (koleksiyonHead == NULL) {
        cout << "Koleksiyon boş.\n";
        return;
    }
    cout << " --------------------------------- \n";
    cout << "|      Koleksiyondaki Kitaplar    |\n";
    kitapNode* temp = koleksiyonHead;
    do {
        cout << " --------------------------------- \n";
        cout << "Kitap ID     : " << temp->id << endl;
        cout << "Kitap Adı    : " << temp->kitapadı << endl;
        cout << "Yazar        : " << temp->yazar << endl;
        cout << "Sayfa Sayısı : " << temp->sayfa << endl;
        cout << "Basım Yılı   : " << temp->basımYılı << endl;
        cout << "Okuma Durumu   : " << temp->okumaDurumu << endl;
        cout << " --------------------------------- \n";
        temp = temp->next;
    } while (temp != koleksiyonHead);  // Dönüş noktası: başa gelene kadar devam et
}

void koleksiyondanKitapSil() {
    if (koleksiyonHead == nullptr) {
        cout << "Koleksiyon boş.\n";
        return;
    }
    int koleksiyonId;
    cout << "Koleksiyondan silmek istediğiniz Kitabın Id'sini giriniz:";
    cin >> koleksiyonId;

    kitapNode* temp = koleksiyonHead;
    kitapNode* silinecek = nullptr;

    // Eğer sadece bir düğüm varsa ve o da silinecek kitap ise
    if (temp->next == koleksiyonHead && temp->id == koleksiyonId) {
        delete temp; // düğümü bellekten sil
        koleksiyonHead = nullptr; // koleksiyon artık boş
        cout << "Kitap basariyla silindi. Koleksiyon artik bos." << endl;
        return;
    }
    //dairesel lisatede dolaş
    do
    {
        if (temp->id == koleksiyonId) {
            silinecek = temp;
            break;
        }
        temp = temp->next;
    } while (temp != koleksiyonHead);
    if (silinecek == nullptr) {
        cout << "Kitap bulunamadi." << endl;
        return;
    }
    // Eğer silinecek kitap baştaki (head) düğümse
    if (silinecek == koleksiyonHead) {
        koleksiyonHead = koleksiyonHead->next; // head'i bir sonraki elemana kaydır
    }
    // Silinecek düğümün öncesi ve sonrasındaki bağlantıları güncelle
    silinecek->prev->next = silinecek->next; // önceki düğümün next'i, silinecek düğümün sonrasına bağlanır
    silinecek->next->prev = silinecek->prev; // sonraki düğümün prev'i, silinecek düğümün öncesine bağlanır
    delete silinecek;
    cout << "Kitap basariyla silindi." << endl;
}

void  okumaDurumuGuncelle() {
    if (koleksiyonHead == NULL) {
        cout << "Koleksiyon boş.\n";
        return;
    }
    int arananID;
    cout << "Okuma durumunu güncellemek istediğiniz kitabın ID'sini girin: ";
    cin >> arananID;
    kitapNode* temp = koleksiyonHead;
    // Kitap arama döngüsü
    while (temp != NULL) {
        if (temp->id == arananID) {
            cout << "Kitap bulundu: " << temp->kitapadı << " (Mevcut durum: " << temp->okumaDurumu << ")\n";

            int secimOkuma;
            cout << "Yeni okuma durumu seçin:\n";
            cout << "1. Okundu\n";
            cout << "2. Okunmadı\n";
            cout << "Seçiminiz: ";
            cin >> secimOkuma;

            // Girişe göre durumu güncelle
            if (secimOkuma == 1) {
                temp->okumaDurumu = "( Okundu )";
            }
            else if (secimOkuma == 2) {
                temp->okumaDurumu = "( Okunmadı )";
            }
            else {
                cout << "Geçersiz seçim. Güncelleme yapılmadı.\n";
                return;
            }

            cout << "Okuma durumu güncellendi.\n";
            return;
        }
        temp = temp->next;
    }
    // Kitap bulunamazsa
    cout << "Bu ID'ye sahip bir kitap bulunamadı.\n";
}

void secimListele() {
    if (head == NULL) {
        cout << "Liste boş!" << endl;
        return;
    }
    kitap* temp = head;
    kitap** kitaplar = new kitap * [kitapSayacı];
    int i = 0;
    while (temp != NULL) { // Bağlı listedeki tüm kitapları tek tek geziyoruz.
        kitaplar[i++] = temp;
        temp = temp->next;
    }
    // Sıralama: Küçükten büyüğe sayfa sayısına göre
    for (int j = 0; j < kitapSayacı - 1; j++)
    {
        for (int k = j + 1; k < kitapSayacı; k++) {
            if (kitaplar[j]->sayfa > kitaplar[k]->sayfa) {
                swap(kitaplar[j], kitaplar[k]);
            }    // Eğer kitaplar[j] daha fazla sayfa içeriyorsa, kitaplar[k] ile yer değiştir.                               
        }        // Böylece daha küçük sayfa sayısına sahip kitap başa yaklaşır.                                   
    }
    cout << " ---------------------------------------------- " << endl;
    cout << "| Kitaplar sayfa sayısına göre sıralandı:      |" << endl;
    cout << " ---------------------------------------------- " << endl;
    for (int j = 0; j < kitapSayacı; j++)
    {
        cout << " ---------------------------------------------- " << endl;
        if (!kitaplar[j]->hasarNotu.empty()) {
            cout << " (HASARLI)";
        }
        cout << "(id:" << kitaplar[j]->id << ")" << endl;
        cout << "Kitap ismi: " << kitaplar[j]->kitapadı << endl;
        cout << "Yazar ismi: " << kitaplar[j]->yazar << endl;
        cout << "Sayfa sayısı: " << kitaplar[j]->sayfa << endl;
        cout << "Basım yılı: " << kitaplar[j]->basımYılı << endl;
        cout << "Yayınevi: " << kitaplar[j]->yayinevi << endl;
        cout << "Dil: " << kitaplar[j]->dil << endl;
    }
    cout << " ---------------------------------------------- " << endl;
    delete[] kitaplar;
}

void kitapEkle() {
    kitap* yeniKitap = new kitap;
    yeniKitap->id = kitapIDSayacı;
    kitapIDSayacı++;
    kitapSayacı++;
    cout << "Kitap ismi:";
    cin.ignore();
    getline(cin, yeniKitap->kitapadı);
    cout << "Yazar ismi:";
    getline(cin, yeniKitap->yazar);
    cout << "Basım yılı:"; cin >> yeniKitap->basımYılı;
    cout << "Sayfa sayısı:"; cin >> yeniKitap->sayfa;

    int yayineviSecim;
    do {
        cout << "Yayınevi seçin (1-Yerli / 2-Yabancı): ";
        cin >> yayineviSecim;

        switch (yayineviSecim) {
        case 1:
            yeniKitap->yayinevi = "Yerli";
            break;
        case 2:
            yeniKitap->yayinevi = "Yabancı";
            break;
        default:
            cout << "Geçersiz seçim! Lütfen tekrar deneyin.\n";
            break;
        }
    } while (yayineviSecim != 1 && yayineviSecim != 2);

    int dilSecim;
    do {
        cout << "Kitap dili seçin:\n";
        cout << "1. Türkçe\n";
        cout << "2. İngilizce\n";
        cout << "Seçiminiz: ";
        cin >> dilSecim;

        switch (dilSecim) {
        case 1:
            yeniKitap->dil = "Türkçe";
            break;
        case 2:
            yeniKitap->dil = "İngilizce";
            break;
        default:
            cout << "Geçersiz seçim! Lütfen tekrar deneyin.\n";
            break;
        }
    } while (dilSecim != 1 && dilSecim != 2); // Geçerli bir seçim yapılana kadar döngü devam eder


    int kategoriSecim;
    cout << "Kategori seçin:\n";
    cout << "| 1. Roman      |\n";
    cout << "| 2. Eğitim     |\n";
    cout << "| 3. Çocuk      |\n";
    cout << "| 4. Tarih      |\n";
    cout << "| 5. Diğer      |\n";
    cout << "Seçiminiz: ";
    cin >> kategoriSecim;

    switch (kategoriSecim) {
    case 1:
        yeniKitap->kategori = "Roman";
        break;
    case 2:
        yeniKitap->kategori = "Eğitim";
        break;
    case 3:
        yeniKitap->kategori = "Çocuk";
        break;
    case 4:
        yeniKitap->kategori = "Tarih";
        break;
    case 5:
        yeniKitap->kategori = "Diğer";
        break;
    default:
        cout << "Geçersiz seçim! Varsayılan olarak 'Diğer' kategorisi atanıyor.\n";
        yeniKitap->kategori = "Diğer";
        break;
    }

    yeniKitap->next = NULL;
    if (head == NULL)
    {
        head = yeniKitap;
    }
    else
    {
        kitap* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = yeniKitap;
    }
    cout << "Kitap başarıyla eklendi (id =" << yeniKitap->id << ")" << endl;
}

void kitapAra() {
    int arananKitapId;
    cout << "Aranan id giriniz:"; cin >> arananKitapId;
    kitap* temp = head;
    bool bulundu = false;
    while (temp != NULL)
    {
        if (temp->id == arananKitapId) // ID eşleşirse
        {
            bulundu = true;
            cout << "kitap bulundu";
            cout << "(id:" << temp->id << ")" << endl;
            cout << "ismi:" << temp->kitapadı << endl;
            cout << "yazar ismi:" << temp->yazar << endl;
            cout << "sayfa sayısı:" << temp->sayfa << endl;
            cout << "basım yılı:" << temp->basımYılı << endl;
            bulundu = true;
            break; // Kitap bulunduysa döngüyü durdur
        }
        temp = temp->next;
    }
    if (!bulundu) { // Eğer hiç eşleşme bulunmadıysa
        cout << "Aranan ID'ye sahip kitap bulunamadı." << endl;
    }
}

void kitapDuzenle() {
    string arananİsim;
    cout << "Kitap ismi giriniz:";
    cin >> arananİsim;
    kitap* temp = head;
    bool bulundu2 = false;
    while (temp != NULL) {
        if (temp->kitapadı == arananİsim)
        {
            bulundu2 = true;
            cout << " ------------------------- " << endl;
            cout << "| 1-İsmi düzenle          |" << endl;
            cout << "| 2-Yazarı düzenle        |" << endl;
            cout << "| 3-Sayfayı düzenle       |" << endl;
            cout << "| 4-Basım yılını düzenle  |" << endl;
            cout << " ------------------------- " << endl;
            int secimduzen;
            cout << "Düzenlemek istediğiniz bilgiyi seçin: ";
            cin >> secimduzen;
            cin.ignore();
            switch (secimduzen)
            {
            case 1:
                cout << "Yeni kitap ismi: ";
                getline(cin, temp->kitapadı);
                break;
            case 2:
                cout << "Yeni yazar ismi: ";
                getline(cin, temp->yazar);
                break;
            case 3:
                cout << "Yeni sayfa sayısı: ";
                cin >> temp->sayfa;
                break;
            case 4:
                cout << "Yeni basım yılı: ";
                cin >> temp->basımYılı;
                break;
            default:
                cout << "Geçersiz seçim.";
            }
            cout << "Bilgiler başarıyla güncellendi." << endl;
            break;
        }
        temp = temp->next; // Listedeki bir sonraki kitaba geç
    }
    if (!bulundu2) {
        cout << "Aradığınız isimde kitap bulunamadı!" << endl;
    }
}

void kitapSayisi() {
    cout << "Toplam kitap sayısı: " << kitapSayacı << endl;
}

void kitapSil() {
    int Arananid;
    cout << "Silmek istediğiniz Id giriniz:"; cin >> Arananid;

    kitap* temp = head;
    // Liste boşsa
    if (head == NULL)
    {
        cout << "Liste boş!" << endl;
        return;
    }
    // ilk eleman aranan id ise
    if (head->id == Arananid) {
        kitap* silinecek = head;
        head = head->next; // listenin başını bir sonraki elemana kaydırıyoruz.
        delete silinecek; // eski baş elemanı siliyoruz.
        kitapSayacı--; // Toplam kitap sayısını azaltıyoruz.
        cout << "Silme işlemi başarılı." << endl;
        return;
    }
    // Arada veya sonda ise
    kitap* prev = head;
    temp = head->next;
    while (temp != NULL) {
        if (temp->id == Arananid) {
            prev->next = temp->next;
            delete temp;
            kitapSayacı--;
            cout << "Silme işlemi başarılı." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    // Eğer Id bulunamazsa
    cout << "Kitap bulunamadı!" << endl;
}

void hasarNot() {
    int arananId;
    cout << "Id giriniz:";
    cin >> arananId;
    kitap* temp = head;
    bool bulundu = false;
    while (temp != NULL) {
        if (temp->id == arananId) {
            bulundu = true;
            cout << "Eklemek istediğiniz hasar notu: ";
            cin.ignore();
            getline(cin, temp->hasarNotu);
            cout << "Hasar notu başarıyla eklendi. " << endl;
        }
        temp = temp->next;
    }
    if (!bulundu) {
        cout << "Bu ID'ye sahip kitap bulunamadı." << endl;
    }
}

void hasarlıKitaplar() {
    kitap* temp = head;
    bool varmi = false;
    cout << "---- Hasarlı Kitaplar ----" << endl;
    while (temp != NULL) {
        if (!temp->hasarNotu.empty()) // Eğer kitabın hasar notu boş değilse
        {
            varmi = true;
            cout << "(id:" << temp->id << ")" << endl;
            cout << "ismi:" << temp->kitapadı << endl;
            cout << "yazar ismi:" << temp->yazar << endl;
            cout << "sayfa sayısı:" << temp->sayfa << endl;
            cout << "basım yılı:" << temp->basımYılı << endl;
            cout << "Hasar notu:" << temp->hasarNotu << endl;
        }
        temp = temp->next;
    }
    if (!varmi) {
        cout << "Hasarlı kitap bulunamadı." << endl;
    }
}

bool strptime(const char* buffer, const char* format, struct tm* tm) { // strptime alternatifi
    std::istringstream input(buffer);
    input >> std::get_time(tm, format);
    return !input.fail();
}

int tarihFarki(string teslimTarihi, string almaTarihi) { // Tarih farkını hesaplayan yardımcı fonksiyon
    struct tm teslim = {}, alma = {};
    strptime(teslimTarihi.c_str(), "%Y-%m-%d", &teslim);
    strptime(almaTarihi.c_str(), "%Y-%m-%d", &alma);

    time_t teslimZaman = mktime(&teslim);
    time_t almaZaman = mktime(&alma);

    double fark = difftime(teslimZaman, almaZaman) / (60 * 60 * 24); // Gün cinsinden fark
    return (int)fark;
}

void basımYılı5() {
    if (head == NULL) {
        cout << "Liste boş!" << endl;
        return;
    }
    kitap* temp = head;
    kitap** kitaplar = new kitap * [kitapSayacı];
    int i = 0;
    while (temp != NULL) {
        kitaplar[i++] = temp;
        temp = temp->next;
    }
    for (int j = 0; j < kitapSayacı - 1; j++)
    {
        for (int k = j + 1; k < kitapSayacı; k++) {
            if (kitaplar[j]->basımYılı > kitaplar[k]->basımYılı) {
                swap(kitaplar[j], kitaplar[k]);
            }   // secimListele() fonksiyonu ile aynı sayfa yerine
        }       // basımYılına göre sıralıyoruz
    }
    cout << "En eski 5 kitap: ";

    for (int j = 0; j < kitapSayacı && j < 5; j++)
    {   // En fazla 5 kitap göster, kitap sayısı 5'ten azsa sadece mevcut olanları göster
        cout << "(id=" << kitaplar[j]->id << ")";
        cout << "Basım yılı:" << kitaplar[j]->basımYılı << endl;
        cout << "Kitap ismi:" << kitaplar[j]->kitapadı << endl;
        cout << "Sayfa:" << kitaplar[j]->sayfa << endl;
        cout << endl;
    }
    delete[] kitaplar;
}

void talepTedarikEt() {
    if (talepFront == nullptr) {
        cout << "Tedarik edilecek talep bulunmamaktadır!" << endl;
        return;
    }

    // Kuyruğun başındaki talebi al
    talepNode* tedarikEdilecek = talepFront;
    talepFront = talepFront->next; // Kuyruğun başını bir sonraki elemana kaydır

    // Kullanıcıdan kitap bilgilerini al
    string yazarAdi;
    int basimYili, sayfaSayisi;
    cout << "Talep edilen kitap: " << tedarikEdilecek->kitapAdi << endl;
    cout << "Talep edilen kitabın bilgilerini giriniz:" << endl;
    cout << "Yazar Adı: ";
    cin.ignore();
    getline(cin, yazarAdi);
    cout << "Basım Yılı: ";
    cin >> basimYili;
    cout << "Sayfa Sayısı: ";
    cin >> sayfaSayisi;

    // Talep edilen kitabı kütüphaneye ekle
    kitap* yeniKitap = new kitap;
    yeniKitap->id = kitapIDSayacı++;
    yeniKitap->kitapadı = tedarikEdilecek->kitapAdi;
    yeniKitap->yazar = yazarAdi;
    yeniKitap->basımYılı = basimYili;
    yeniKitap->sayfa = sayfaSayisi;
    yeniKitap->hasarNotu = "";
    yeniKitap->next = nullptr;

    // Kitabı tek yönlü bağlı listeye ekle
    if (head == nullptr) {
        head = yeniKitap;
    }
    else {
        kitap* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = yeniKitap;
    }
    kitapSayacı++;

    // Talep edilen kitabın bilgilerini ekrana yazdır
    cout << "Talep edilen kitap tedarik edildi ve kütüphaneye eklendi:" << endl;
    cout << "Kitap ID: " << yeniKitap->id << ", Kitap Adı: " << yeniKitap->kitapadı << endl;
    cout << "Yazar Adı: " << yeniKitap->yazar << ", Basım Yılı: " << yeniKitap->basımYılı << ", Sayfa Sayısı: " << yeniKitap->sayfa << endl;

    // Bellekteki talep düğümünü serbest bırak
    delete tedarikEdilecek;
}

void kitapTalepEt() {
    string kitapAdi;
    cout << "Talep etmek istediğiniz kitabın adını giriniz: ";
    cin.ignore();
    getline(cin, kitapAdi);

    // Yeni bir talep düğümü oluştur
    talepNode* yeniTalep = new talepNode;
    yeniTalep->talepId = talepIdSayaci++;
    yeniTalep->kitapAdi = kitapAdi;
    yeniTalep->talepTuru = "Normal"; // Varsayılan talep türü
    yeniTalep->next = nullptr;

    // Talebi kuyruğa ekle
    if (talepFront == nullptr) {
        talepFront = yeniTalep;
        talepRear = yeniTalep;
    }
    else {
        talepRear->next = yeniTalep;
        talepRear = yeniTalep;
    }

    cout << "Kitap talebi kuyruğa eklendi. Talep ID: " << yeniTalep->talepId << ", Kitap Adı: " << yeniTalep->kitapAdi << endl;
}

void talepleriYazdir() {
    if (talepFront == nullptr) {
        cout << "Kuyrukta talep bulunmamaktadır!" << endl;
        return;
    }

    cout << "Kuyruktaki Talepler:" << endl;
    talepNode* temp = talepFront;
    while (temp != nullptr) {
        cout << "Talep ID: " << temp->talepId << ", Kitap Adı: " << temp->kitapAdi << ", Talep Türü: " << temp->talepTuru << endl;
        temp = temp->next;
    }
}

void listele1950Once(TreeNode* root) { // 1950 öncesi kitapları listeleyen yardımcı fonksiyon
    if (root == nullptr) return;

    listele1950Once(root->left); // Sol alt ağacı gez

    if (root->basimYili < 1950) {
        cout << " ------------------------------" << endl;
        cout << "| Kitap Adı    : " << root->kitapAdi << endl;
        cout << "| Yazar        : " << root->yazar << endl;
        cout << "| Basım Yılı   : " << root->basimYili << endl;
        cout << " ------------------------------" << endl;
    }

    listele1950Once(root->right); // Sağ alt ağacı gez
}

void listele1950Sonra(TreeNode* root) { // 1950 ve sonrası kitapları listeleyen yardımcı fonksiyon
    if (root == nullptr) return;

    listele1950Sonra(root->left); // Sol alt ağacı gez

    if (root->basimYili >= 1950) {
        cout << " ------------------------------" << endl;
        cout << "| Kitap Adı    : " << root->kitapAdi << endl;
        cout << "| Yazar        : " << root->yazar << endl;
        cout << "| Basım Yılı   : " << root->basimYili << endl;
        cout << " ------------------------------" << endl;
    }

    listele1950Sonra(root->right); // Sağ alt ağacı gez
}

void kitaplariYilaGoreListele(TreeNode* root) { // Tüm listeleme işlemlerini çağıran ana fonksiyon
    if (root == nullptr) {
        cout << "Ağaç yapısı boş, listelenecek kitap yok." << endl;
        return;
    }

    cout << "====== 1950'DEN ÖNCE BASILAN KİTAPLAR ======" << endl;
    listele1950Once(root);

    cout << "\n====== 1950 VE SONRASI BASILAN KİTAPLAR ======" << endl;
    listele1950Sonra(root);
}

void raporOlustur1950Once30Gundurumu(TreeNode* root) {
    if (root == nullptr) { // Eğer ağaç boşsa
        cout << "Ağaçta ödünç alınan kitap bulunmamaktadır!" << endl;
        return;
    }
    cout << " --------------------------------------- " << endl;
    cout << "| 1950'den Önce ve 30 Gün Üstü Kitaplar |" << endl;
    cout << " --------------------------------------- " << endl;
    if (root->basimYili < 1950)
    {
        int fark = tarihFarki(root->teslimZamani, root->almaZamani); // tarihFarki fonksiyonu ödünç alma süresini hesaplar
        if (fark > 30)
        {
            cout << "| Kitap Adı    : " << root->kitapAdi << endl;
            cout << "| Yazar        : " << root->yazar << endl;
            cout << "| Basım Yılı   : " << root->basimYili << endl;
            cout << "| Sayfa Sayısı : " << root->sayfa << endl;
            cout << "| Alma Zamanı  : " << root->almaZamani << endl;
            cout << "| Teslim Zamanı: " << root->teslimZamani << endl;
            cout << "| Ödünç Alma Süresi: " << fark << " gün" << endl;
            cout << " ---------------------------------------" << endl;
        }
    }
    raporOlustur1950Once30Gundurumu(root->left); // Sol alt ağacı dolaş
    raporOlustur1950Once30Gundurumu(root->right); // Sağ alt ağacı dolaş
}

void raporOlustur(TreeNode* root) {
    if (root == nullptr) {
        cout << " Ödünç alınan kitap bulunanamaktadır."; return; // Ağaç boşsa hiçbir şey yapma }
        // Sol alt ağacı gez
        raporOlustur(root->left);

        // Ödünç alma süresine göre raporla
        int fark = tarihFarki(root->teslimZamani, root->almaZamani);
        if (fark < 0) {
            cout << "Teslim tarihi geçmiş: " << root->kitapAdi << " (ID: " << root->id << ")" << endl;
        }
        else if (fark < 30) {
            cout << "30 günün altında: " << root->kitapAdi << " (ID: " << root->id << ")" << endl;
        }
        else {
            cout << "30 günün üstünde: " << root->kitapAdi << " (ID: " << root->id << ")" << endl;
        }
        // Sağ alt ağacı gez
        raporOlustur(root->right);
    }
}


void akademikKitapTalepEt() {
    string kitapAdi;
    cout << "Akademik olarak talep etmek istediğiniz kitabın adını giriniz: ";
    cin.ignore();
    getline(cin, kitapAdi);

    // Yeni bir talep düğümü oluştur
    talepNode* yeniTalep = new talepNode;
    yeniTalep->talepId = talepIdSayaci++;
    yeniTalep->kitapAdi = kitapAdi;
    yeniTalep->talepTuru = "Akademik";
    yeniTalep->next = nullptr;

    // Kuyruk boşsa, doğrudan ekle
    if (talepFront == nullptr) {
        talepFront = yeniTalep;
        talepRear = yeniTalep;
        cout << "Akademik talep kuyruğa eklendi. Talep ID: " << yeniTalep->talepId << ", Kitap Adı: " << yeniTalep->kitapAdi << endl;
        return;
    }

    // Kuyrukta yalnızca bir eleman varsa, akademik talebi başa ekle
    if (talepFront == talepRear) {
        yeniTalep->next = talepFront;
        talepFront = yeniTalep;
        cout << "Akademik talep kuyruğa eklendi. Talep ID: " << yeniTalep->talepId << ", Kitap Adı: " << yeniTalep->kitapAdi << endl;
        return;
    }

    // Kuyrukta birden fazla eleman varsa, akademik talebi bir önceki elemanın önüne ekle
    talepNode* temp = talepFront;
    talepNode* prev = nullptr;

    // Kuyruğun sonuna kadar ilerle
    while (temp != nullptr && temp != talepRear) {
        prev = temp;
        temp = temp->next;
    }

    // Akademik talebi bir önceki elemanın önüne ekle
    if (prev != nullptr) {
        prev->next = yeniTalep;
        yeniTalep->next = temp;
    }

    // Eğer akademik talep kuyruğun sonuna ekleniyorsa, talepRear'ı güncelle
    if (temp == talepRear) {
        talepRear = yeniTalep;
    }

    cout << "Akademik talep kuyruğa eklendi. Talep ID: " << yeniTalep->talepId << ", Kitap Adı: " << yeniTalep->kitapAdi << endl;

    // Kuyruğu yazdır
    talepleriYazdir();
}

void kitaplariAgacaEkle(TreeNode*& root, kitap* head) {
    kitap* temp = head; // Bağlı listenin başından başla
    while (temp != nullptr) {
        root = agacaEkleKitap(root, temp); // Her bir kitabı ağaca ekle
        temp = temp->next; // Bir sonraki kitaba geç
    }
}

void yayinevineGoreListele(TreeNode* root) {
    if (root == nullptr) {
        cout << "Ağaç yapısı boş, listelenecek kitap yok." << endl;
        return;
    }

    // Yerli yayınevine ait kitapları listele
    cout << " ----------------------------------------- " << endl;
    cout << "|      YERLİ YAYINEVİNE AİT KİTAPLAR      |" << endl;
    cout << " ----------------------------------------- " << endl;
    yayinevineGoreListeleHelper(root, "Yerli");

    // Yabancı yayınevine ait kitapları listele
    cout << " ----------------------------------------- " << endl;
    cout << "|     YABANCI YAYINEVİNE AİT KİTAPLAR     |" << endl;
    cout << " ----------------------------------------- " << endl;
    yayinevineGoreListeleHelper(root, "Yabancı");
}

void yayinevineGoreListeleHelper(TreeNode* root, const string& yayinevi) {
    if (root == nullptr) return; // Ağaç boşsa işlem yapma

    // Sol alt ağacı gez
    yayinevineGoreListeleHelper(root->left, yayinevi);

    // Eğer düğümün yayınevi bilgisi belirtilen yayıneviyle eşleşiyorsa, bilgileri yazdır
    if (root->yayinevi == yayinevi) {
        cout << "| Kitap ID     : " << root->id << endl;
        cout << "| Kitap Adı    : " << root->kitapAdi << endl;
        cout << "| Yazar        : " << root->yazar << endl;
        cout << "| Basım Yılı   : " << root->basimYili << endl;
        cout << "| Sayfa Sayısı : " << root->sayfa << endl;
        cout << "| Yayınevi     : " << root->yayinevi << endl;
        cout << " ----------------------------------------- " << endl;
    }

    // Sağ alt ağacı gez
    yayinevineGoreListeleHelper(root->right, yayinevi);
}

void dileGoreListele(TreeNode* root) {
    if (root == nullptr) {
        cout << "Ağaç yapısı boş, listelenecek kitap yok." << endl;
        return;
    }

    // Türkçe dilindeki kitapları listele
    cout << " ----------------------------------------- " << endl;
    cout << "|         TÜRKÇE DİLİNDE KİTAPLAR         |" << endl;
    cout << " ----------------------------------------- " << endl;
    dileGoreListeleHelper(root, "Türkçe");

    // İngilizce dilindeki kitapları listele
    cout << " ----------------------------------------- " << endl;
    cout << "|        İNGİLİZCE DİLİNDE KİTAPLAR       |" << endl;
    cout << " ----------------------------------------- " << endl;
    dileGoreListeleHelper(root, "İngilizce");
}

void dileGoreListeleHelper(TreeNode* root, const string& dil) {
    if (root == nullptr) return;

    // Sol alt ağacı gez
    dileGoreListeleHelper(root->left, dil);

    // Eğer düğümün dil bilgisi belirtilen dil ile eşleşiyorsa, bilgileri yazdır
    if (root->dil == dil) { // root->yayinevi yerine root->dil kontrol ediliyor
        cout << "| Kitap ID     : " << root->id << endl;
        cout << "| Kitap Adı    : " << root->kitapAdi << endl;
        cout << "| Yazar        : " << root->yazar << endl;
        cout << "| Basım Yılı   : " << root->basimYili << endl;
        cout << "| Sayfa Sayısı : " << root->sayfa << endl;
        cout << "| Dil          : " << root->dil << endl;
        cout << " ----------------------------------------- " << endl;
    }

    // Sağ alt ağacı gez
    dileGoreListeleHelper(root->right, dil);
}

void sayfaSayisi1000denFazla(TreeNode* root) {
    if (root == nullptr) return;
    // Sol alt ağacı gez
    sayfaSayisi1000denFazla(root->left);
    // Kök düğümü işle
    if (root->sayfa >= 1000) {
        cout << " ------------------------------" << endl;
        cout << "| Kitap Adı    : " << root->kitapAdi << endl;
        cout << "| Yazar        : " << root->yazar << endl;
        cout << "| Basım Yılı   : " << root->basimYili << endl;
        cout << "| Sayfa Sayısı : " << root->sayfa << endl;
        cout << " ------------------------------" << endl;
    }
    // Sağ alt ağacı gez
    sayfaSayisi1000denFazla(root->right);
}

void sayfaSayisi1000denAz(TreeNode* root) {
    if (root == nullptr) return;
    // Sol alt ağacı gez
    sayfaSayisi1000denAz(root->left);

    // Kök düğümü işle
    if (root->sayfa < 1000) {
        cout << " ------------------------------" << endl;
        cout << "| Kitap Adı    : " << root->kitapAdi << endl;
        cout << "| Yazar        : " << root->yazar << endl;
        cout << "| Basım Yılı   : " << root->basimYili << endl;
        cout << "| Sayfa Sayısı : " << root->sayfa << endl;
        cout << " ------------------------------" << endl;
    }
    // Sağ alt ağacı gez
    sayfaSayisi1000denAz(root->right);
}

int main()
{
    setlocale(LC_ALL, "Turkish");
    ornekKitaplarEkle(); // Örnek kitaplar
    AnaMenü();
    return 0;
}
