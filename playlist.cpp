#include <iostream>
#include <iomanip>
using namespace std;

struct lagu{
    string judul_lagu;
    string penyanyi;
    float durasi;
    int tahun_terbit;
};

struct PTB{
    lagu data_lagu;
    PTB *left;
    PTB *right;
};

PTB* root = NULL;

struct Stack{
    lagu data_lagu[100];
    int top;
};

Stack riwayat;
// riwayat.top = -1;

struct Queue{
    lagu data_lagu[100];
    int depan;
    int belakang;
};

Queue playlist;

int menu_pilihan, pilih_metode_tampil;
string input_judul_lagu, input_penyanyi, input_tahun_terbit, input_durasi, nama_lagu_cari, lagu_masuk_playlist, lagu_replay;

PTB* buat_ptb(lagu input_lagu){
    PTB* baru = new PTB;
    baru->data_lagu = input_lagu;
    baru->left = NULL;
    baru->right = NULL;
    return baru;
}

PTB* cari_root(PTB* root, lagu input_lagu){
    if (root == NULL){
        return buat_ptb(input_lagu);
    }

    if (input_lagu.judul_lagu < root->data_lagu.judul_lagu){
        root->left = cari_root(root->left, input_lagu);
    } else if (input_lagu.judul_lagu > root->data_lagu.judul_lagu){
        root->right = cari_root(root->right, input_lagu);
    }

    return root;
}

void hiasan(string judul){
    cout << "===" << judul << "===" << endl;
}

void main_menu(){
    do {
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Tampil Daftar Lagu" << endl;
        cout << "3. Cari Lagu" << endl;
        cout << "4. Tambah Lagu ke Playlist" << endl;
        cout << "5. Lihat Playlist" << endl;
        cout << "6. Putar Playlist" << endl;
        cout << "7. Replay Lagu" << endl;
        cout << "8. Riwayat Lagu" << endl;
        cout << "9. Hapus Lagu" << endl;
        cout << "10. Keluar Program" << endl;
        cout << "Pilih menu : ";
        cin >> menu_pilihan;
    } while (menu_pilihan < 1 || menu_pilihan > 10);
}

void tampilkan(PTB* root){
    for (int i = 1; i < 75; i++) { cout << "-"; }
    cout << endl;
    cout << "|" << setw(30) << left << root->data_lagu.judul_lagu << "|" << setw(15) << left << root->data_lagu.penyanyi << "|" << setw(10) << left << fixed << setprecision(2) << root->data_lagu.durasi << "|" << setw(15) << left << root->data_lagu.tahun_terbit << "|" << endl;
    // fixed << setprecision(2) --> buat nampilin banyaknya angka di belakagn koma
}

void preorder(PTB* root){
    if(root == NULL){
        return;
    }
    tampilkan(root);
    preorder(root->left);
    preorder(root->right);
}

void inorder(PTB* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    tampilkan(root);
    inorder(root->right);
}

void postorder(PTB* root){
    if(root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    tampilkan(root);
}

void enqueue(lagu masuk_playlist) {
    playlist.belakang++;
    playlist.data_lagu[playlist.belakang] = masuk_playlist;
}

void tambah_lagu(){
    lagu input_lagu;    

    cout << "Judul Lagu : ";
    cin.ignore();
    getline(cin, input_lagu.judul_lagu);
    cout << "Penyanyi : ";
    getline(cin, input_lagu.penyanyi);
    cout << "Tahun Terbit : ";
    cin >> input_lagu.tahun_terbit;
    cout << "Durasi Lagu : ";
    cin >> input_lagu.durasi;

    root = cari_root(root, input_lagu);
    
    cout << "Lagu berhasil ditambahkan!" << endl;
}

void tampil_daftar_lagu(){
    cout << "Pilih metode penampilan :" << endl;
    cout << "1. Preorder" << endl;
    cout << "2. Inorder" << endl;
    cout << "3. Postorder" << endl;
    cout << "Pilih : ";
    cin >> pilih_metode_tampil;

    for (int i = 1; i < 75; i++) { cout << "-"; }
    cout << endl;
    cout << "|" << setw(30) << left << "JUDUL LAGU" << "|" << setw(15) << left << "PENYANYI" << "|" << setw(10) << left << "DURASI" << "|" << setw(15) << left << "TAHUN TERBIT" << "|" << endl;
    if (pilih_metode_tampil == 1){
        preorder(root);
    } else if (pilih_metode_tampil == 2){
        inorder(root);
    } else if (pilih_metode_tampil == 3){
        postorder(root);
    }   
    for (int i = 1; i < 75; i++) { cout << "-"; }
    cout << endl;
}

PTB* cari_lagu(PTB* root, string nama_lagu_cari){
    if (root == NULL || root->data_lagu.judul_lagu == nama_lagu_cari){
        return root;
    }

    if (nama_lagu_cari < root->data_lagu.judul_lagu){
        return cari_lagu(root->left, nama_lagu_cari);
    }

    return cari_lagu(root->right, nama_lagu_cari);
}

void tambah_ke_playlist(string lagu_masuk_playlist){
    PTB* temukan_lagu = cari_lagu(root, lagu_masuk_playlist);

    if(temukan_lagu == NULL){
        cout << "Yah:( ... Lagu tidak ditemukan";
        return;
    } else {
        enqueue(temukan_lagu->data_lagu);
        cout << "Berhasil masuk playlist" << endl;
    }

}

void tampil_playlist(){
    if(playlist.belakang == -1){
        cout << "yahh...playlistmu masih kosong :(" << endl;
        return;
    }

    for (int i = 1; i < 75; i++) { cout << "-"; }
    cout << endl;
    cout << "|" << setw(30) << left << "JUDUL LAGU" << "|" << setw(15) << left << "PENYANYI" << "|" << setw(10) << left << "DURASI" << "|" << setw(15) << left << "TAHUN TERBIT" << "|" << endl;

    for (int i = playlist.depan; i <= playlist.belakang; i++){
        for (int i = 1; i < 75; i++) { cout << "-"; }
        cout << endl;
        cout << "|" << setw(30) << left << playlist.data_lagu[i].judul_lagu << "|" << setw(15) << left << playlist.data_lagu[i].penyanyi << "|" << setw(10) << left << fixed << setprecision(2) << playlist.data_lagu[i].durasi << "|" << setw(15) << left << playlist.data_lagu[i].tahun_terbit << "|" << endl;
        // fixed << setprecision(2) --> buat nampilin banyaknya angka di belakagn koma
    }
    for (int i = 1; i < 75; i++) { cout << "-"; }
    cout << endl;
}

void putar_playlist(){
    if(playlist.belakang == -1){
        cout << "yahh...playlistmu masih kosong :(" << endl;
        return;
    }

    for(int i = playlist.depan; i <= playlist.belakang; i++){
        riwayat.top++;
        riwayat.data_lagu[riwayat.top] = playlist.data_lagu[i];
        
        cout << "==================================" << endl;
        cout << "Sedang memutar:" << endl;
        cout << playlist.data_lagu[i].judul_lagu << " - " << playlist.data_lagu[i].penyanyi  << endl;
        cout << "==================================" << endl << endl;

        int lanjut_putar;
        do{
            cout << "1. Lagu Selanjutnya?" << endl;
            cout << "2. Stop Putar Playlist?" << endl;
            cout << "Pilihan : ";
            cin >> lanjut_putar;
        } while (lanjut_putar != 1 && lanjut_putar != 2);
        
        if (lanjut_putar == 2){
            break;
        }

        if (i == playlist.belakang){
            cout << "playlist selesai diputar (lagu habis)" << endl;
            break;
        }
    }
}

void replay(string lagu_replay){
    PTB* temukan_lagu = cari_lagu(root, lagu_replay);

    if (temukan_lagu == NULL){
        cout << "Yah:( ... Lagu tidak ditemukan";
        return;
    } else {
        int mode_replay, jumlah_replay;

        hiasan("MODE REPLAY");
        cout << "\n1. Berdasarkan jumlah" << endl;
        cout << "2. Berdasarkan menit" << endl;
        cout << "pilihan : ";
        cin >> mode_replay;

        if(mode_replay == 1){
            int jml;
            cout << "Berapa kali replay : ";
            cin >> jml;

            jumlah_replay = jml;
        } else if (mode_replay == 2){
            int jml;
            cout << "Berapa menit replay : ";
            cin >> jml;

            jumlah_replay = jml / temukan_lagu->data_lagu.durasi;

            cout << "Jumlah replay : " << jumlah_replay << endl;
        }

        cout << "Memutar lagu..." << endl;
        for (int i = 0; i < jumlah_replay; i++){
            riwayat.top++;
            riwayat.data_lagu[riwayat.top] = temukan_lagu->data_lagu;

            cout << i+1 << ". " << temukan_lagu->data_lagu.judul_lagu << " - " << temukan_lagu->data_lagu.penyanyi << endl;
        }
    }
}

void riwayat_lagu(){
    if(riwayat.top == -1){
        cout << "yahh...playlistmu masih kosong :(" << endl;
        return;
    }

    for (int i = 1; i < 75; i++) { cout << "-"; }
    cout << endl;
    cout << "|" << setw(30) << left << "JUDUL LAGU" << "|" << setw(15) << left << "PENYANYI" << "|" << setw(10) << left << "DURASI" << "|" << setw(15) << left << "TAHUN TERBIT" << "|" << endl;

    for (int i = riwayat.top; i >= 0; i--){
        for (int i = 1; i < 75; i++) { cout << "-"; }
        cout << endl;
        cout << "|" << setw(30) << left << riwayat.data_lagu[i].judul_lagu << "|" << setw(15) << left << riwayat.data_lagu[i].penyanyi << "|" << setw(10) << left << fixed << setprecision(2) << riwayat.data_lagu[i].durasi << "|" << setw(15) << left << riwayat.data_lagu[i].tahun_terbit << "|" << endl;
        // fixed << setprecision(2) --> buat nampilin banyaknya angka di belakagn koma
    }
    for (int i = 1; i < 75; i++) { cout << "-"; }
    cout << endl;
}

void hapus_lagu(){

}

int main(){
    playlist.belakang = -1;
    playlist.depan = 0;
    riwayat.top = -1;
    
    do {
        hiasan("2PLAY");
        main_menu();
        if (menu_pilihan == 1){
            hiasan("TAMBAH LAGU");
            tambah_lagu();
        } else if (menu_pilihan == 2){
            hiasan("TAMPIL DAFTAR LAGU");
            tampil_daftar_lagu();
        } else if (menu_pilihan == 3){
            cout << endl;
            hiasan("CARI LAGU");
            cout << "Masukkan nama lagu yang dicari :";
            cin.ignore();
            getline(cin, nama_lagu_cari);
            cout << endl;
            
            PTB* hasil_cari = cari_lagu(root, nama_lagu_cari);

            cout << endl;
            hiasan("HASIL PENCARIAN");
            cout << endl;

            if(hasil_cari == NULL){
                cout << "Lagu tidak ditemukan" << endl;
            } else {
                cout << setw(15) << left << "Judul Lagu" << ":" << hasil_cari->data_lagu.judul_lagu << endl; 
                cout << setw(15) << left << "Penyanyi" << ":" << hasil_cari->data_lagu.penyanyi << endl; 
                cout << setw(15) << left << "Tahun Terbit" << ":" << hasil_cari->data_lagu.tahun_terbit << endl; 
                cout << setw(15) << left << "Durasi" << ":" << hasil_cari->data_lagu.durasi << endl; 
            }
        } else if (menu_pilihan == 4){
            hiasan("TAMBAH LAGU KE PLAYLIST");
            cout << "Masukkan nama lagu :";
            cin.ignore();
            getline(cin, lagu_masuk_playlist);

            tambah_ke_playlist(lagu_masuk_playlist);
        } else if (menu_pilihan == 5){
            hiasan("PLAYLIST AKTIF");
            tampil_playlist();
        } else if (menu_pilihan == 6){
            hiasan("PUTAR PLAYLIST");
            putar_playlist();
        } else if (menu_pilihan == 7){
            hiasan("REPLAY");
            cout << "Masukkan judul lagu yang akan direplay : ";
            cin.ignore();
            getline(cin, lagu_replay);

            replay(lagu_replay);
        } else if (menu_pilihan == 8){
            hiasan("RIWAYAT LAGU");
            riwayat_lagu();
        } else if (menu_pilihan == 9){
            hiasan("HAPUS LAGU");
            hapus_lagu();
        } else if (menu_pilihan == 10){
            break;
        }

        char next;

        do{
            cout << "\nMau lanjut program? (N/Y) : ";
            cin >> next;
            next = toupper(next);

            if (next == 'N'){
                system("cls");
                cout << "\nMakasih guys!";
                return 0;
            }
        } while (next != 'Y' && next != 'N');
        system("cls");
    } while (menu_pilihan != 10);
    
    system("cls");
    cout << "\nMakasih guys!";
    return 0;
}