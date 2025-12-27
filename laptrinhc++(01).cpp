#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

/* ===== ENUM TRANG THAI ===== */
enum TrangThai {
    DANG_LAM,
    HOAN_THANH,
    KHONG_HOAN_THANH
};

/* ===== CLASS CONG VIEC ===== */
class Work {
private:
    int ma;
    string noiDung;
    int soGio;
    string ngayTao;
    TrangThai trangThai;

    string layNgayHienTai() {
        time_t now = time(0);
        tm* t = localtime(&now);

        char buf[11];
        sprintf(buf, "%02d/%02d/%d",
                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
        return string(buf);
    }

public:
    Work() {
        ma = 0;
        soGio = 0;
        trangThai = DANG_LAM;
    }

    void nhap(int maMoi) {
        ma = maMoi;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap noi dung: ";
        getline(cin, noiDung);

        cout << "Nhap so gio: ";
        cin >> soGio;

        ngayTao = layNgayHienTai();
        trangThai = DANG_LAM;
    }

    void hienThi() const {
        cout << left
             << setw(8)  << ma
             << setw(30) << noiDung
             << setw(10) << soGio
             << setw(12) << ngayTao
             << setw(18) << trangThaiToString()
             << endl;
    }

    int getMa() const { return ma; }
    TrangThai getTrangThai() const { return trangThai; }

    void setNoiDung(const string& nd) {
        noiDung = nd;
    }

    void setTrangThai(TrangThai tt) {
        trangThai = tt;
    }

    bool dangLam() const {
        return trangThai == DANG_LAM;
    }

    string trangThaiToString() const {
        if (trangThai == DANG_LAM) return "Dang lam";
        if (trangThai == HOAN_THANH) return "Hoan thanh";
        return "Khong hoan thanh";
    }
};

/* ===== CLASS QUAN LY ===== */
class WorkManager {
private:
    vector<Work> ds;
    int maTuTang;

    int timViTri(int ma) {
        for (int i = 0; i < ds.size(); i++) {
            if (ds[i].getMa() == ma)
                return i;
        }
        return -1;
    }

    void inTieuDe() {
        cout << left
             << setw(8)  << "Ma"
             << setw(30) << "Noi dung"
             << setw(10) << "So gio"
             << setw(12) << "Ngay tao"
             << setw(18) << "Trang thai"
             << endl;
    }

public:
    WorkManager() {
        maTuTang = 1;
    }

    void hienThiDanhSach() {
        if (ds.empty()) {
            cout << "Danh sach rong!\n";
            return;
        }

        inTieuDe();
        for (int i = 0; i < ds.size(); i++) {
            ds[i].hienThi();
        }
    }

    void themCongViec() {
        Work w;
        w.nhap(maTuTang);
        ds.push_back(w);
        cout << "Da them cong viec, ma = " << maTuTang << endl;
        maTuTang++;
    }

    void suaNoiDung() {
        int ma;
        cout << "Nhap ma cong viec: ";
        cin >> ma;

        int pos = timViTri(ma);
        if (pos == -1) {
            cout << "Khong tim thay!\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string nd;
        cout << "Nhap noi dung moi: ";
        getline(cin, nd);

        ds[pos].setNoiDung(nd);
        cout << "Cap nhat thanh cong!\n";
    }

    void doiTrangThai() {
        int ma;
        cout << "Nhap ma cong viec: ";
        cin >> ma;

        int pos = timViTri(ma);
        if (pos == -1) {
            cout << "Khong tim thay!\n";
            return;
        }

        if (!ds[pos].dangLam()) {
            cout << "Chi doi trang thai khi dang lam!\n";
            return;
        }

        cout << "1. Hoan thanh\n";
        cout << "2. Khong hoan thanh\n";
        cout << "Chon: ";

        int ch;
        cin >> ch;

        if (ch == 1)
            ds[pos].setTrangThai(HOAN_THANH);
        else if (ch == 2)
            ds[pos].setTrangThai(KHONG_HOAN_THANH);
        else
            cout << "Lua chon sai!\n";
    }
};

/* ===== MAIN ===== */
void menu() {
    cout << "\n===== QUAN LY CONG VIEC =====\n";
    cout << "1. Hien thi danh sach\n";
    cout << "2. Them cong viec\n";
    cout << "3. Sua noi dung\n";
    cout << "4. Doi trang thai\n";
    cout << "0. Thoat\n";
    cout << "Chon: ";
}

int main() {
    WorkManager ql;
    int ch;

    do {
        system("cls");
        menu();
        cin >> ch;

        switch (ch) {
            case 1: ql.hienThiDanhSach(); break;
            case 2: ql.themCongViec(); break;
            case 3: ql.suaNoiDung(); break;
            case 4: ql.doiTrangThai(); break;
            case 0: cout << "Tam biet!\n"; break;
            default: cout << "Chon sai!\n";
        }

        if (ch != 0) {
            system("pause");
        }

    } while (ch != 0);

    return 0;
}

