#include <iostream>
using namespace std;

struct Treap {
    int id, price, priority;
    long long sum;
    Treap *left, *right;
};
void UpdatePrice(Treap* treap) {
    if (treap != nullptr) {
        treap->sum = treap->price;
        if (treap->left != nullptr) {
            treap->sum += treap->left->sum;
        }
        if (treap->right != nullptr) {
            treap->sum += treap->right->sum;
        }
    }
}

void Split(int id, Treap *treap, Treap *&left, Treap *&right) {
    if (treap == nullptr) {
        left = right = nullptr;
    } else if (treap->id <= id) {
        Split(id, treap->right, treap->right, right);
        left = treap;
    } else {
        Split(id, treap->left, left, treap->left);
        right = treap;
    }
    UpdatePrice(treap);
}

void Merge(Treap *&treap, Treap *left, Treap *right) {
    if (left == nullptr || right == nullptr) {
        treap = left ? left : right;
    } else if (left->priority > right->priority) {
        Merge(left->right, left->right, right);
        treap = left;
    } else {
        Merge(right->left, left, right->left);
        treap = right;
    }
    UpdatePrice(treap);
}

void Delete(Treap *&treap, const int id, int &item_count) {
    Treap *left = nullptr;
    Treap *right = nullptr;
    Treap *right_temp = nullptr;
    Treap *middle = nullptr;

    Split(id - 1, treap, left, right_temp);
    Split(id, right_temp, middle, right);

    if (middle != nullptr) {
        delete middle;
        item_count--;
    }

    Merge(treap, left, right);
}

Treap* NewNode(const int id, const int price) {
    const auto temp = new Treap;
    temp->id = id;
    temp->price = price;
    temp->priority = rand();
    temp->sum = price;
    temp->left = temp->right = nullptr;
    return temp;
}

void NewItem(Treap *&treap, int id, int price, int &item_count) {
    Treap *left = nullptr;
    Treap *right = nullptr;
    Treap *right_temp = nullptr;
    Treap *middle = nullptr;

    Split(id - 1, treap, left, right_temp);
    Split(id, right_temp, middle, right);

    if (middle == nullptr) {
        middle = NewNode(id, price);
        item_count++;
    } else {
        middle->price = price;
        middle->sum = price;
    }

    Merge(right_temp, middle, right);
    Merge(treap, left, right_temp);
}

long long SumRange(Treap *&treap, int min_id, int max_id) {
    Treap *left = nullptr;
    Treap *right = nullptr;
    Treap *right_temp = nullptr;
    Treap *middle = nullptr;
    long long sum = 0;

    if (min_id > max_id) {
        return 0;
    }

    Split(min_id - 1, treap, left, right_temp);
    Split(max_id, right_temp, middle, right);

    if (middle != nullptr) {
        sum = middle->sum;
    }

    Merge(right_temp, middle, right);
    Merge(treap, left, right_temp);

    return sum;
}

int main() {
    Treap *treap = nullptr;
    int item_count = 0;
    int N;
    cin >> N;

    while (N--) {
        char cases;
        cin >> cases;
        switch (cases) {
            case 'A': {
                int id, price;
                cin >> id >> price;
                NewItem(treap, id, price, item_count);
                break;
            }
            case 'D': {
                int id;
                cin >> id;
                Delete(treap, id, item_count);
                break;
            }
            case 'C': {
                cout << item_count << endl;
                break;
            }
            case 'S': {
                int min_id, max_id;
                cin >> min_id >> max_id;
                cout << SumRange(treap, min_id, max_id) << endl;
                break;
            }
            default:
            break;
        }
    }
    return 0;
}