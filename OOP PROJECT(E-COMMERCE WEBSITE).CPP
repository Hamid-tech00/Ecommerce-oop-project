#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User(string u, string p) : username(u), password(p) {}
    virtual void display() {
        cout << "Username: " << username << endl;
    }
};

class Customer : public User {
public:
    Customer(string u, string p) : User(u, p) {}
    void display() {
        cout << "Customer - ";
        User::display();
    }
};

class Product {
public:
    string name;
    double price;

    Product(string n, double p) : name(n), price(p) {}
};

class ShoppingCart {
private:
    vector<Product> items;

public:
    void addItem(Product& p) {
        items.push_back(p);
    }

    void displayCart() {
        if (items.empty()) {
            cout << "Shopping cart is empty!" << endl;
        } else {
            cout << "Shopping Cart:" << endl;
            for (size_t i = 0; i < items.size(); ++i) { 
                cout << items[i].name << endl; 
            }
        }
    }
};

void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "User registered successfully!" << endl;
}


bool loginUser(string& username) {
    string password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        if (username == storedUsername && password == storedPassword) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

int main() {
    vector<Product> products;
	
    products.push_back(Product("Laptop", 100.00));
    products.push_back(Product("Smartphone", 218.00));
    products.push_back(Product("Headphones", 88.99));
    products.push_back(Product("Smartwatch", 386.99));
    
    ShoppingCart cart;
    string username;
    int choice;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            if (loginUser(username)) {
                cout << "Login successful!" << endl;
                Customer customer(username, "");
                customer.display();

                while (true) {
                    cout << "\n1. View Products\n2. Add to Cart\n3. View Cart\n4. Logout\nChoice: ";
                    cin >> choice;

                    if (choice == 1) {
                        cout << "Products:" << endl;
                        for (size_t i = 0; i < products.size(); ++i) {
                            cout << i + 1 << ". " << products[i].name << " - $" << products[i].price << endl;
                        }
                    } else if (choice == 2) {
                        int productIndex;
                        cout << "Enter product number to add to cart: ";
                        cin >> productIndex;
                        if (productIndex > 0 && productIndex <= static_cast<int>(products.size())) {
                            cart.addItem(products[productIndex - 1]);
                            cout << "Product added to cart!" << endl;
                        } else {
                            cout << "Invalid product number!" << endl;
                        }
                    } else if (choice == 3) {
                        cart.displayCart();
                    } else if (choice == 4) {
                        cout << "Logging out..." << endl;
                        break;
                    } else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            } else {
                cout << "Login failed! Please try again." << endl;
            }
        } else if (choice == 3) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    }

    return 0;
}
