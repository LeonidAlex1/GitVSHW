#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <string>
#include <limits>

using namespace std;

class InvalidPriceException : public exception {
public:
    const char* what() const throw() {
        return "Invalid price";
    }
};

class Entity {
public:
    virtual void print() const = 0;
};

class Product : public Entity {
private:
    string name;
    double price;

public:
    Product(const string& name, double price) : name(name), price(price) {
        if (price < 0) {
            throw InvalidPriceException();
        }
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    void print() const override {
        cout << "Product: " << name << ", Price: " << price << "\n";
    }
};

class Store : public Entity {
private:
    string name;
    list<Product> products;

public:
    Store() : name(""), products() {}

    Store(const string& name) : name(name), products() {}

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    list<Product> getProducts() const {
        return products;
    }

    string getName() const {
        return name;
    }

    void print() const override {
        cout << "Store: " << name << "\n";
        for (const auto& product : products) {
            product.print();
        }
    }
};

template <typename T>
class Network {
private:
    list<T> stores;

public:
    void addStore(const T& store) {
        stores.push_back(store);
    }

    list<T> getStores() const {
        return stores;
    }

    T findCheapestStore(const string& productName) const {
        T cheapestStore;
        double minPrice = numeric_limits<double>::max();

        for (const auto& store : stores) {
            for (const auto& product : store.getProducts()) {
                if (product.getName() == productName && product.getPrice() < minPrice) {
                    minPrice = product.getPrice();
                    cheapestStore = store;
                }
            }
        }

        return cheapestStore;
    }

    void print() const {
        for (const auto& store : stores) {
            store.print();
        }
    }
};

bool compareStores(const Store& store1, const Store& store2) {
    return store1.getProducts().size() > store2.getProducts().size();
}

int countProducts(const Network<Store>& network) {
    int count = 0;
    for (const auto& store : network.getStores()) {
        count += store.getProducts().size();
    }
    return count;
}

list<Product> filterProducts(const Store& store, double minPrice, double maxPrice) {
    list<Product> filteredProducts;
    for (const auto& product : store.getProducts()) {
        if (product.getPrice() >= minPrice && product.getPrice() <= maxPrice) {
            filteredProducts.push_back(product);
        }
    }
    return filteredProducts;
}

void saveNetwork(const Network<Store>& network, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& store : network.getStores()) {
            file << "Store: " << store.getName() << "\n";
            for (const auto& product : store.getProducts()) {
                file << "Product: " << product.getName() << ", Price: " << product.getPrice() << "\n";
            }
            file << "\n";
        }
        file.close();
    }
    else {
        cout << "Unable to open file\n";
    }
}

void loadNetwork(Network<Store>& network, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        Store store;
        while (getline(file, line)) {
            if (line.find("Store:") != string::npos) {
                store = Store(line.substr(7));
            }
            else if (line.find("Product:") != string::npos) {
                size_t commaPos = line.find(", Price:");
                string productName = line.substr(9, commaPos - 9);
                double price = stod(line.substr(commaPos + 8));
                store.addProduct(Product(productName, price));
            }
            else if (line.empty()) {
                network.addStore(store);
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file\n";
    }
}

int main() {
    Network<Store> network;
    string filename = "D:\\MYSTAT\\testing1.txt";
    ifstream file;

    loadNetwork(network, filename);

    while (true) {
        cout << "-----------------------------------------------\n";
        cout << "              Store Management System          \n";
        cout << "-----------------------------------------------\n";
        cout << "1. Add store\n";
        cout << "2. Add product to store\n";
        cout << "3. Find cheapest store for product\n";
        cout << "4. Print all stores and products\n";
        cout << "5. Compare two stores by number of products\n";
        cout << "6. Count number of products in all stores\n";
        cout << "7. Filter products by price range\n";
        cout << "8. Save and view network data\n";
        cout << "9. Exit\n";
        cout << "-----------------------------------------------\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string storeName;
            cout << "Enter store name: ";
            cin >> storeName;
            Store store(storeName);
            network.addStore(store);
            break;
        }
        case 2: {
            string storeName;
            cout << "Enter store name: ";
            cin >> storeName;
            string productName;
            double price;
            cout << "Enter product name: ";
            cin >> productName;
            cout << "Enter product price: ";
            cin >> price;
            for (auto& store : network.getStores()) {
                if (store.getName() == storeName) {
                    store.addProduct(Product(productName, price));
                    break;
                }
            }
            break;
        }
        case 3: {
            string productName;
            cout << "Enter product name: ";
            cin >> productName;
            Store cheapestStore = network.findCheapestStore(productName);
            cheapestStore.print();
            break;
        }
        case 4:
            for (const auto& store : network.getStores()) {
                cout << "-----------------------------------------------\n";
                cout << "Store: " << store.getName() << "\n";
                cout << "-----------------------------------------------\n";
                for (const auto& product : store.getProducts()) {
                    cout << "Product: " << product.getName() << ", Price: " << product.getPrice() << "\n";
                }
                cout << "\n";
            }
            
            break;
        case 5: {
            string storeName1;
            cout << "Enter first store name: ";
            cin >> storeName1;
            string storeName2;
            cout << "Enter second store name: ";
            cin >> storeName2;
            Store store1;
            Store store2;
            for (const auto& store : network.getStores()) {
                if (store.getName() == storeName1) {
                    store1 = store;
                }
                else if (store.getName() == storeName2) {
                    store2 = store;
                }
            }
            if (compareStores(store1, store2)) {
                cout << storeName1 << " has more products than " << storeName2 << "\n";
            }
            else {
                cout << storeName2 << " has more products than " << storeName1 << "\n";
            }
            break;
        }
        case 6:
            cout << "Total number of products: " << countProducts(network) << "\n";
            break;
        case 7: {
            string storeName;
            cout << "Enter store name: ";
            cin >> storeName;
            double minPrice;
            double maxPrice;
            cout << "Enter minimum price: ";
            cin >> minPrice;
            cout << "Enter maximum price: ";
            cin >> maxPrice;
            for (const auto& store : network.getStores()) {
                if (store.getName() == storeName) {
                    list<Product> filteredProducts = filterProducts(store, minPrice, maxPrice);
                    for (const auto& product : filteredProducts) {
                        product.print();
                    }
                    break;
                }
            }
            break;
        }
        case 8:
            saveNetwork(network, filename);
            file.open(filename);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    cout << line << "\n";
                }
                file.close();
            }
            else {
                cout << "Unable to open file\n";
            }
            break;
        case 9:
            saveNetwork(network, filename);
            return 0;
        default:
            cout << "Invalid choice\n";
        }
    }

    return 0;
}
