#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node
{
    string product_name;
    string merk;
    int price;
    int stock;
    Node *next;
};

bool login(string username, string password)
{
    string correct_uname = "admin";
    string correct_pass = "123";

    if (username == correct_uname && password == correct_pass)
    {
        return true;
    }
    else
    {
        return false;
    }
}

struct HistoryNode
{
    string description;
    HistoryNode *next;
};

Node *head = nullptr;
HistoryNode *historyHead = nullptr;
int many_product = 0;

bool hanyadigit(const string &str)
{
    return str.find_first_not_of("0123456789") == string::npos;
}

bool hanyahuruf(const string &str)
{
    for (char c : str)
    {
        if (!isalpha(c) && c != ' ')
        {
            return false;
        }
    }
    return true;
}

string ValidProduk(const string &prompt)
{
    string input;
    bool valid = false;

    do
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty() || input.find_first_not_of(" ") == string::npos)
        {
            cout << "Error: Input tidak boleh kosong!" << endl;
            continue;
        }

        bool isValid = true;
        for (char c : input)
        {
            if (!isalnum(c) && c != ' ')
            {
                isValid = false;
                break;
            }
        }

        if (!isValid)
        {
            cout << "Error: Nama produk hanya boleh berisi huruf, angka, dan spasi!" << endl;
        }
        else
        {
            valid = true;
        }

    } while (!valid);

    return input;
}

int ValidInteger(const string &prompt, bool nilai = false)
{
    string input;
    int value;
    bool valid = false;

    do
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty() || input.find_first_not_of(" ") == string::npos)
        {
            cout << "Error: Input tidak boleh kosong!" << endl;
            continue;
        }

        if (!hanyadigit(input))
        {
            cout << "Error: Input harus berupa angka!" << endl;
            continue;
        }

        try
        {
            value = stoi(input);

            if (value < 0)
            {
                cout << "Error: Input tidak boleh negatif!" << endl;
                continue;
            }

            if (!nilai && value == 0)
            {
                cout << "Error: Input tidak boleh nol!" << endl;
                continue;
            }

            valid = true;
        }
        catch (const exception &e)
        {
            cout << "Error: Input tidak valid!" << endl;
        }
    } while (!valid);

    return value;
}

string ValidString(const string &prompt, bool allowNumbers = false)
{
    string input;
    bool valid = false;

    do
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty() || input.find_first_not_of(" ") == string::npos)
        {
            cout << "Error: Input tidak boleh kosong!" << endl;
            continue;
        }

        if (!allowNumbers && !hanyahuruf(input))
        {
            cout << "Error: Input hanya boleh berisi huruf dan spasi!" << endl;
            continue;
        }

        valid = true;
    } while (!valid);

    return input;
}

void add_history(const string &description)
{
    HistoryNode *newHistory = new HistoryNode();
    newHistory->description = description;
    newHistory->next = historyHead;
    historyHead = newHistory;
}

void view_history()
{
    if (historyHead == nullptr)
    {
        cout << "Tidak ada riwayat perubahan." << endl;
        return;
    }

    cout << "\nRiwayat Perubahan:" << endl;
    HistoryNode *temp = historyHead;
    int index = 1;

    while (temp != nullptr)
    {
        cout << index << ". " << temp->description << endl;
        temp = temp->next;
        index++;
    }
}

void create_stationery(Node *&head, int &many_product)
{
    cout << "Tambah produk baru:" << endl;
    
    string product_name = ValidProduk("Masukkan nama produk: ");
    
    Node *current = head;
    while (current != nullptr) {
        if (current->product_name == product_name) {
            cout << "Gagal menambahkan produk. Nama produk '" << product_name << "' sudah ada." << endl;
            return;
        }
        current = current->next;
    }

    Node *new_node = new Node();
    new_node->product_name = product_name;
    new_node->merk = ValidString("Masukkan merk: ", false);
    new_node->price = ValidInteger("Masukkan harga: ");
    new_node->stock = ValidInteger("Masukkan stok: ");

    new_node->next = head;
    head = new_node;

    many_product++;
    cout << "Produk berhasil ditambahkan!" << endl;

    add_history("Menambahkan produk: " + new_node->product_name + ", Merk: " + new_node->merk);
}

void read_stationery(Node *head)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    cout << "\nDaftar Produk:" << endl;
    Node *temp = head;
    int index = 1;

    while (temp != nullptr)
    {
        cout << "Produk " << index << ": "
             << temp->product_name << ", Merk: " << temp->merk
             << ", Harga: " << temp->price << ", Stok: " << temp->stock << endl;
        temp = temp->next;
        index++;
    }
}

void update_stationery(Node *head, int many_product)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    read_stationery(head);

    int index = ValidInteger("Pilih nomor produk yang ingin di-update: ");

    if (index > 0 && index <= many_product)
    {
        Node *temp = head;

        for (int i = 1; i < index; i++)
        {
            temp = temp->next;
        }

        string old_product_name = temp->product_name;
        string new_product_name = ValidProduk("Masukkan nama produk baru: ");
        
        Node *current = head;
        bool duplicate = false;
        while (current != nullptr)
        {
            if (current->product_name == new_product_name && current != temp)
            {
                duplicate = true;
                break;
            }
            current = current->next;
        }
        if (duplicate)
        {
            cout << "Gagal mengupdate produk. Nama produk '" << new_product_name << "' sudah ada." << endl;
            return;
        }

        temp->product_name = new_product_name;
        temp->merk = ValidString("Masukkan merk baru: ", false);
        temp->price = ValidInteger("Masukkan harga baru: ");
        temp->stock = ValidInteger("Masukkan stok baru: ");

        cout << "Data berhasil di-update!" << endl;

        add_history("Mengupdate produk pada indeks " + to_string(index) + ": " + temp->product_name + ", Merk: " + temp->merk);
    }
    else
    {
        cout << "Produk tidak ditemukan!" << endl;
    }
}

void delete_stationery(Node *&head, int &many_product)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    int choice;
    bool valid_choice = false;

    do
    {
        cout << "1. Hapus produk pertama (dequeue)" << endl;
        cout << "2. Hapus produk terakhir (pop)" << endl;
        choice = ValidInteger("Pilih opsi penghapusan: ");

        if (choice == 1 || choice == 2)
        {
            valid_choice = true;
        }
        else
        {
            cout << "Error: Pilihan tidak valid! Pilih 1 atau 2." << endl;
        }
    } while (!valid_choice);

    if (choice == 1)
    {
        Node *temp = head;
        string deleted_product = temp->product_name;
        head = head->next;
        delete temp;
        many_product--;
        cout << "Produk pertama berhasil dihapus!" << endl;

        add_history("Menghapus produk pertama: " + deleted_product);
    }

    else if (choice == 2)
    {

        if (head->next == nullptr)
        {
            string deleted_product = head->product_name;
            delete head;
            head = nullptr;
            many_product--;
            add_history("Menghapus produk terakhir: " + deleted_product);
            cout << "Produk terakhir berhasil dihapus!" << endl;
        }
        else
        {
            Node *temp = head;
            while (temp->next->next != nullptr)
            {
                temp = temp->next;
            }
            string deleted_product = temp->next->product_name;
            delete temp->next;
            temp->next = nullptr;
            many_product--;
            add_history("Menghapus produk terakhir: " + deleted_product);
            cout << "Produk terakhir berhasil dihapus!" << endl;
        }
    }
}

Node *partition(Node *low, Node *high)
{
    int pivot = high->price;
    Node *i = low;
    Node *j = low;

    while (j != high)
    {
        if (j->price < pivot)
        {
            swap(i->price, j->price);
            swap(i->product_name, j->product_name);
            swap(i->merk, j->merk);
            swap(i->stock, j->stock);
            i = i->next;
        }
        j = j->next;
    }

    swap(i->price, high->price);
    swap(i->product_name, high->product_name);
    swap(i->merk, high->merk);
    swap(i->stock, high->stock);
    return i;
}

Node *get_last(Node *head)
{
    while (head->next != nullptr)
    {
        head = head->next;
    }
    return head;
}

void quick_sort(Node *low, Node *high)
{
    if (low != high && low != nullptr && high != nullptr && low != high->next)
    {
        Node *p = partition(low, high);
        if (p != nullptr && p != low)
        {
            Node *temp = low;
            while (temp != nullptr && temp->next != p)
            {
                temp = temp->next;
            }
            quick_sort(low, temp);
        }
        if (p != nullptr && p != high && p->next != nullptr)
        {
            quick_sort(p->next, high);
        }
    }
}

void shell_sort(Node *head)
{
    int gap = many_product / 2;
    while (gap > 0)
    {
        for (int i = gap; i < many_product; i++)
        {
            Node *temp = head;
            for (int j = 0; j < i; j++)
            {
                temp = temp->next;
            }

            int current_price = temp->price;
            string current_product = temp->product_name;
            string current_merk = temp->merk;
            int current_stock = temp->stock;

            Node *prev = temp;
            for (int j = i - gap; j >= 0; j -= gap)
            {
                Node *gap_node = head;
                for (int k = 0; k < j; k++)
                {
                    gap_node = gap_node->next;
                }

                if (gap_node->price >= current_price)
                {
                    break;
                }

                prev->price = gap_node->price;
                prev->product_name = gap_node->product_name;
                prev->merk = gap_node->merk;
                prev->stock = gap_node->stock;
                prev = gap_node;
            }

            prev->price = current_price;
            prev->product_name = current_product;
            prev->merk = current_merk;
            prev->stock = current_stock;
        }
        gap /= 2;
    }
}

void sort_stationery(Node *head)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    string input;
    int choice;
    bool valid = false;

    do
    {
        cout << "1. Sorting Ascending (Quick Sort)" << endl;
        cout << "2. Sorting Descending (Shell Sort)" << endl;
        cout << "Pilih jenis sorting: ";
        getline(cin, input);

        if (input.empty() || !hanyadigit(input))
        {
            cout << "Error: Input harus berupa angka!" << endl;
            continue;
        }

        choice = stoi(input);
        if (choice != 1 && choice != 2)
        {
            cout << "Error: Pilihan tidak valid!" << endl;
            continue;
        }

        valid = true;
    } while (!valid);

    Node *last = get_last(head);

    if (choice == 1)
    {
        quick_sort(head, last);
        cout << "Produk berhasil diurutkan secara ascending (Quick Sort)." << endl;
        read_stationery(head);
    }
    else if (choice == 2)
    {
        shell_sort(head);
        cout << "Produk berhasil diurutkan secara descending (Shell Sort)." << endl;
        read_stationery(head);
    }
}

void fibonacci_search(Node *head, int key)
{
    quick_sort(head, get_last(head));
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    vector<Node *> nodes;
    Node *temp = head;
    while (temp != nullptr)
    {
        nodes.push_back(temp);
        temp = temp->next;
    }

    int n = nodes.size();
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);

        if (nodes[i]->price < key)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (nodes[i]->price > key)
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
        {
            cout << "Produk ditemukan: " << nodes[i]->product_name << ", Merk: " << nodes[i]->merk << ", Harga: " << nodes[i]->price << ", Stok: " << nodes[i]->stock << endl;
            int j = i - 1;
            while (j >= 0 && nodes[j]->price == key)
            {
                cout << "Produk ditemukan: " << nodes[j]->product_name << ", Merk: " << nodes[j]->merk << ", Harga: " << nodes[j]->price << ", Stok: " << nodes[j]->stock << endl;
                j--;
            }
            j = i + 1;
            while (j < n && nodes[j]->price == key)
            {
                cout << "Produk ditemukan: " << nodes[j]->product_name << ", Merk: " << nodes[j]->merk << ", Harga: " << nodes[j]->price << ", Stok: " << nodes[j]->stock << endl;
                j++;
            }
            return;
        }
    }

    if (fibMMm1 && nodes[offset + 1]->price == key)
    {
        cout << "Produk ditemukan: " << nodes[offset + 1]->product_name << ", Merk: " << nodes[offset + 1]->merk << ", Harga: " << nodes[offset + 1]->price << ", Stok: " << nodes[offset + 1]->stock << endl;
        int j = offset;
        while (j >= 0 && nodes[j]->price == key)
        {
            cout << "Produk ditemukan: " << nodes[j]->product_name << ", Merk: " << nodes[j]->merk << ", Harga: " << nodes[j]->price << ", Stok: " << nodes[j]->stock << endl;
            j--;
        }
        j = offset + 2;
        while (j < n && nodes[j]->price == key)
        {
            cout << "Produk ditemukan: " << nodes[j]->product_name << ", Merk: " << nodes[j]->merk << ", Harga: " << nodes[j]->price << ", Stok: " << nodes[j]->stock << endl;
            j++;
        }
        return;
    }

    cout << "Produk dengan harga " << key << " tidak ditemukan." << endl;
}

void jump_search(Node *head, int key)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    vector<Node *> nodes;
    Node *temp = head;

    while (temp != nullptr)
    {
        nodes.push_back(temp);
        temp = temp->next;
    }

    sort(nodes.begin(), nodes.end(), [](Node *a, Node *b)
         { return a->stock < b->stock; });

    int n = nodes.size();
    int step = sqrt(n);
    int prev = 0;

    while (nodes[min(step, n) - 1]->stock < key)
    {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
        {
            cout << "Produk dengan stok " << key << " tidak ditemukan." << endl;
            return;
        }
    }

    bool found = false;
    while (nodes[prev]->stock < key)
    {
        prev++;
        if (prev == min(step, n))
        {
            break;
        }
    }

    while (prev < n && nodes[prev]->stock == key)
    {
        if (!found)
        {
            cout << "Produk ditemukan: " << endl;
            found = true;
        }
        cout << nodes[prev]->product_name << ", Merk: " << nodes[prev]->merk << ", Harga: " << nodes[prev]->price << ", Stok: " << nodes[prev]->stock << endl;
        prev++;
    }

    if (!found)
    {
        cout << "Produk dengan stok " << key << " tidak ditemukan." << endl;
    }
}

vector<int> preprocess_boyer_moore(const string &pattern)
{
    vector<int> bad_char(256, -1);
    for (int i = 0; i < pattern.size(); i++)
    {
        bad_char[pattern[i]] = i;
    }
    return bad_char;
}

void boyer_moore_search(Node *head, const string &key)
{
    vector<Node *> nodes;
    Node *temp = head;
    while (temp != nullptr)
    {
        nodes.push_back(temp);
        temp = temp->next;
    }

    int n = nodes.size();
    vector<int> bad_char = preprocess_boyer_moore(key);

    for (int i = 0; i < n; i++)
    {
        string text = nodes[i]->product_name;
        int m = text.size();
        int s = 0;

        while (s <= (m - key.size()))
        {
            int j = key.size() - 1;

            while (j >= 0 && key[j] == text[s + j])
            {
                j--;
            }

            if (j < 0)
            {
                cout << "Produk ditemukan: " << nodes[i]->product_name << ", Merk: " << nodes[i]->merk << ", Harga: " << nodes[i]->price << ", Stok: " << nodes[i]->stock << endl;
                return;
            }
            else
            {
                s += max(1, j - bad_char[text[s + j]]);
            }
        }
    }

    cout << "Produk dengan nama " << key << " tidak ditemukan." << endl;
}

void search(Node *head)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    string input;
    int choice;
    bool valid = false;

    do
    {
        cout << "1. Fibonacci Search" << endl;
        cout << "2. Jump Search" << endl;
        cout << "3. Boyer-Moore Search" << endl;
        cout << "Pilih jenis pencarian: ";
        getline(cin, input);

        if (input.empty() || !hanyadigit(input))
        {
            cout << "Error: Input harus berupa angka!" << endl;
            continue;
        }

        choice = stoi(input);
        if (choice < 1 || choice > 3)
        {
            cout << "Error: Pilihan tidak valid!" << endl;
            continue;
        }

        valid = true;
    } while (!valid);

    if (choice == 1)
    {
        string priceInput;
        int key;
        do
        {
            cout << "Masukkan harga produk yang dicari: ";
            getline(cin, priceInput);

            if (priceInput.empty() || !hanyadigit(priceInput))
            {
                cout << "Error: Input harus berupa angka!" << endl;
                continue;
            }

            key = stoi(priceInput);
            break;
        } while (true);

        fibonacci_search(head, key);
    }
    else if (choice == 2)
    {
        string stockInput;
        int key;
        do
        {
            cout << "Masukkan stok produk yang dicari: ";
            getline(cin, stockInput);

            if (stockInput.empty() || !hanyadigit(stockInput))
            {
                cout << "Error: Input harus berupa angka!" << endl;
                continue;
            }

            key = stoi(stockInput);
            break;
        } while (true);

        jump_search(head, key);
    }
    else if (choice == 3)
    {
        string key;
        do
        {
            cout << "Masukkan nama produk yang dicari: ";
            getline(cin, key);

            if (key.empty() || key.find_first_not_of(" ") == string::npos)
            {
                cout << "Error: Input tidak boleh kosong!" << endl;
                continue;
            }
            break;
        } while (true);

        boyer_moore_search(head, key);
    }
}

void choice()
{
    int choice;
    do
    {
        cout << "=============================================" << endl;
        cout << "=         Admin Toko Dara's Stationery       =" << endl;
        cout << "=============================================" << endl;
        cout << "=                [ MENU UTAMA ]             =" << endl;
        cout << "=              1. Tambah produk             =" << endl;
        cout << "=              2. Lihat produk              =" << endl;
        cout << "=              3. Update produk             =" << endl;
        cout << "=              4. Hapus produk              =" << endl;
        cout << "=              5. Sorting produk            =" << endl;
        cout << "=              6. Searching produk          =" << endl;
        cout << "=              7. Lihat Riwayat Perubahan   =" << endl;
        cout << "=              8. Keluar                    =" << endl;
        cout << "=============================================" << endl;

        choice = ValidInteger("Pilih menu: ");
        cout << "---------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            create_stationery(head, many_product);
            break;
        case 2:
            read_stationery(head);
            break;
        case 3:
            update_stationery(head, many_product);
            break;
        case 4:
            delete_stationery(head, many_product);
            break;
        case 5:
            sort_stationery(head);
            break;
        case 6:
            search(head);
            break;
        case 7:
            view_history();
            break;
        case 8:
            cout << "Program dihentikan!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid! Pilih menu 1-6." << endl;
            break;
        }
    } while (choice != 8);
}

int main()
{
    string username;
    string password;
    int attempt = 0;
    bool success = false;

    while (attempt < 3 && !success)
    {
        cout << "Masukkan username: ";
        getline(cin, username);

        cout << "Masukkan password: ";
        getline(cin, password);

        if (login(username, password))
        {
            cout << "Login berhasil!" << endl;
            success = true;
            choice();
        }
        else
        {
            attempt++;
            cout << "Login gagal! Username atau password salah." << endl;
            if (attempt < 3)
            {
                cout << "Anda memiliki " << 3 - attempt << " kesempatan lagi." << endl;
            }
        }
    }

    if (!success)
    {
        cout << "Anda telah gagal login 3 kali. Program dihentikan." << endl;
    }

    return 0;
}