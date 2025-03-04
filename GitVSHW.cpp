#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Entity {
public:
    virtual void display() const = 0;
    virtual ~Entity() {}
};

class Product : public Entity {
public:
    string name;
    double price;

    Product(const string& name, double price) {
        if (price < 0) throw invalid_argument("Price cannot be negative");
        this->name = name;
        this->price = price;
    }

    void display() const override {
        cout << "Product: " << name << ", Price: " << price << "\n";
    }
};

class Store : public Entity {
public:
    string name;
    map<string, Product> products;

    Store(const string& name) : name(name) {}

    void addProduct(const string& productName, double price) {
        products[productName] = Product(productName, price);
    }

    bool hasProduct(const string& productName) const {
        return products.find(productName) != products.end();
    }

    double getProductPrice(const string& productName) const {
        if (!hasProduct(productName)) throw runtime_error("Product not found");
        return products.at(productName).price;
    }

    void display() const override {
        cout << "Store: " << name << "\nProducts:\n";
        for (const auto& item : products) {
            item.second.display();
        }
    }

    void saveToFile(ofstream& outFile) const {
        outFile << name << "\n";
        outFile << products.size() << "\n";
        for (const auto& item : products) {
            outFile << item.second.name << " " << item.second.price << "\n";
        }
    }

    void loadFromFile(ifstream& inFile) {
        int productCount;
        inFile >> productCount;
        inFile.ignore();

        for (int i = 0; i < productCount; i++) {
            string productName;
            double productPrice;
            inFile >> productName >> productPrice;
            addProduct(productName, productPrice);
        }
    }
};

template <typename T>
class Network {
private:
    list<shared_ptr<T>> stores;
public:
    void addStore(const string& name) {
        stores.push_back(make_shared<T>(name));
    }

    shared_ptr<T> findCheapestStore(const string& productName) {
        auto it = min_element(stores.begin(), stores.end(), [&productName](const shared_ptr<T>& a, const shared_ptr<T>& b) {
            bool hasA = a->hasProduct(productName);
            bool hasB = b->hasProduct(productName);
            if (!hasA) return false;
            if (!hasB) return true;
            return a->getProductPrice(productName) < b->getProductPrice(productName);
            });
        return (it != stores.end() && (*it)->hasProduct(productName)) ? *it : nullptr;
    }

    void displayAllStores() const {
        for (const auto& store : stores) {
            store->display();
        }
    }

    void saveToFile(const string& filePath) const {
        ofstream outFile(filePath);
        if (!outFile) {
            cout << "Error: Unable to open file for saving." << "\n";
            return;
        }
        outFile << stores.size() << "\n";
        for (const auto& store : stores) {
            store->saveToFile(outFile);
        }
        outFile.close();
    }

 /*   void saveToFile(const string& filename, const string& stationName, const Date& date, const string& fuelType, int amount, const string& action) const {
        ofstream file(filename, ios::app);
        file << "Station: " << stationName << " | Date: " << date << " | Action: " << action << " | Fuel: " << fuelType << " | Quantity: " << amount << " liters\n";
    }*/


    void loadFromFile(const string& filePath) {
        ifstream inFile(filePath);
        if (!inFile) {
            cout << "Error: Unable to open file for loading." << "\n";
            return;
        }
        int storeCount;
        inFile >> storeCount;
        inFile.ignore();

        stores.clear();

        for (int i = 0; i < storeCount; i++) {
            string storeName;
            getline(inFile, storeName);
            shared_ptr<T> store = make_shared<T>(storeName);
            store->loadFromFile(inFile);
            stores.push_back(store);
        }
        inFile.close();
    }
};

int main() {
    Network<Store> storeNetwork;
    storeNetwork.addStore("TechWorld");
    storeNetwork.addStore("GadgetHub");

    auto techWorld = storeNetwork.findCheapestStore("TechWorld");
    if (techWorld) {
        techWorld->addProduct("Laptop", 999.99);
        techWorld->addProduct("Smartphone", 599.99);
    }

    auto gadgetHub = storeNetwork.findCheapestStore("GadgetHub");
    if (gadgetHub) {
        gadgetHub->addProduct("Laptop", 899.99);
        gadgetHub->addProduct("Smartwatch", 299.99);
    }

    string filePath = "D:\\MYSTAT\\testing1.txt";
    storeNetwork.saveToFile(filePath);

    storeNetwork.loadFromFile(filePath);

    cout << "\nAll stores after loading from file:\n";
    storeNetwork.displayAllStores();

    return 0;
}
