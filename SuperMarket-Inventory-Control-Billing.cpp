#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
public:
    User() : username(""), password("") {}
    virtual int login() = 0;  // Pure virtual function for login
};


class Admin : public User {
public:
    Admin() : User() {}  // Initialize base class
    int login(){  // Override the login function
        cout << "**Please Login to access the inventory.**\n";
        do {
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;
            if (username == "23P-3038" && password == "2004") {
                cout << "***Login Successfully!***\n";
                return 1;
            } else {
                cout << "Invalid Username or Password. Please Try again.\n";
            }
        } while (1);
    }
};
//Error-hanlding function to check if a string has numbers or not
bool isNumber(const string& input) {
    bool hasDecimal = false;
    bool hasDigit = false;

    for (int i = 0; i < input.length(); ++i) {
        if (isdigit(input[i])) {
            hasDigit = true;
        } else if (input[i] == '.' && !hasDecimal) {
            hasDecimal = true;
        } else {
            return false;
        }
    }
    return hasDigit; // Ensure there's at least one digit
}

class product {
private:
    string productName;
    double productPrice;
    int quantity;
    int soldCounter; // Counter to track the number of items sold
public:
    string productID;
    product() : productID("0"), productName(""), productPrice(0.0), quantity(0), soldCounter(0) {} //default constructor
    product(string pid, string pname, double pprice, int quant); //parameterized constructor
    void display_productInfo(); //display product details
    void update_productInfo(); //setters
    void decrement_quantity(int quant); // Decrement product quantity
    void set_quantity(int quant) { quantity = quant; } // Setter for quantity
    string get_productName() const { return productName; } //getters
    double get_productPrice() const { return productPrice; }
    int get_productQuantity() const { return quantity; }
    int get_soldCounter() const { return soldCounter; } // getter for soldCounter
    void incrementSoldCounter(int amount) { soldCounter += amount; } // increment soldCounter
};

product::product(string pid, string pname, double pprice, int quant)
    : productID(pid), productName(pname), productPrice(pprice), quantity(quant), soldCounter(0) {}

void product::display_productInfo() {
    cout << "Product Id: " << this->productID << endl;
    cout << "Product Name: " << this->productName << endl;
    cout << "Product Price: " << this->productPrice << endl;
    cout << "Product Quantity: " << this->quantity << endl;
}

void product::update_productInfo() {
    while (true) {
        int choice;
        cout << "Enter the corresponding number to update attributes:\n"
             << "1: Product Name\n"
             << "2: Product Price\n"
             << "3: Product Quantity\n";
        cin >> choice;

        if (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            continue; // Prompt user again
        }

        if (choice == 1) {
            string pname;
            cout << "Enter new product name: ";
            cin.ignore();
            getline(cin, pname);

            if (isNumber(pname)) {
                cout << "Invalid input for product name. Please enter a valid string." << endl;
                continue; // Prompt user again
            }

            productName = pname;
        } else if (choice == 2) {
            string pprice_str;
            cout << "Enter new product price: ";
            cin >> pprice_str;
            if (!isNumber(pprice_str)) {
                cout << "Invalid input for product price. Please enter a valid number." << endl;
                continue; // Prompt user again
            }
            productPrice = stod(pprice_str);
        } else if (choice == 3) {
            string quant_str;
            cout << "Enter new product quantity: ";
            cin >> quant_str;
            if (!isNumber(quant_str)) {
                cout << "Invalid input for product quantity. Please enter a valid number." << endl;
                continue; // Prompt user again
            }
            quantity = stoi(quant_str);
        }
        break; // Valid input received, exit loop
    }
}


void product::decrement_quantity(int quant) {
    if (quantity >= quant) {
        quantity -= quant;
    } else {
        cout << "Not enough stock to decrement by " << quant << endl;
    }
}

class inventory {
private:
    int inventory_count; //total number of items in inventory
    int max_products; //maximum capacity of products that can be stored in inventory
    string* list_of_all_ids_names; //pointer str array to keep track of all id's
    product* inventory_products; //AGGREGATION -> using has-a relation with product class.

public:
    inventory(int pmax);
    ~inventory();
    void display_productInfo(string pid);
    void add_product();
    void update_product(string pid); //setter
    void delete_product(string pid);
    void list_products(); //displays all the products
    int get_inventory_count() const { return inventory_count; } //getters
    string get_product_id(int index) const { return list_of_all_ids_names[index]; }
    product* get_inventory_products() const { return inventory_products; }
    string* get_list_of_all_ids_names() const { return list_of_all_ids_names; }
    void zeroStock();
    void highestSold();
};

inventory::inventory(int pmax) : inventory_count(0), max_products(pmax), list_of_all_ids_names(new string[pmax * 2]), inventory_products(new product[pmax]) {
    for (int i = 0; i < max_products; ++i) {
        list_of_all_ids_names[i * 2] = "0";
        list_of_all_ids_names[i * 2 + 1] = "";
        inventory_products[i] = product("0", "", 0, 0); // Default product values
    }
}

inventory::~inventory() {
    delete[] list_of_all_ids_names;
    delete[] inventory_products;
}

void inventory::add_product() {
    if (inventory_count >= max_products) {
        cout << "Inventory is full\n";
        return;
    }

    string p_id;
    string p_name;
    double p_price;
    int p_quantity;

  
     while (true) {
          cout << "Enter product Id: " << endl;
    cin >> p_id;

        if (!isNumber(p_id)) {
            cout << "Invalid input for product ID. Please enter a valid number." << endl;
            continue; // Prompt user again
        }

        break;
    }

    // Check if the entered product ID already exists
    for (int i = 0; i < inventory_count; ++i) {
        if (list_of_all_ids_names[i * 2] == p_id) {
            cout << "Product Id already exists, please enter a valid product Id: ";
            cin >> p_id;
            break;
        }
    }

    list_of_all_ids_names[inventory_count * 2] = p_id;

    // Prompt user for product name with error handling
    while (true) {
        cout << "Enter product name: " << endl;
        cin.ignore();
        getline(cin, p_name);

        if (isNumber(p_name)) {
            cout << "Invalid input for product name. Please enter a valid string." << endl;
            continue; // Prompt user again
        }
        break; // Valid input received, exit loop
    }

    list_of_all_ids_names[inventory_count * 2 + 1] = p_name;

    // Prompt user for product price with error handling
    string p_price_str;
    while (true) {
        cout << "Enter product price: " << endl;
        cin >> p_price_str;

        if (!isNumber(p_price_str)) {
            cout << "Invalid input for product price. Please enter a valid number." << endl;
            continue; // Prompt user again
        }

        p_price = stod(p_price_str);
        break;
    }

    // Prompt user for product quantity with error handling
    string p_quantity_str;
    while (true) {
        cout << "Enter product quantity: " << endl;
        cin >> p_quantity_str;

        if (!isNumber(p_quantity_str)) {
            cout << "Invalid input for product quantity. Please enter a valid number." << endl;
            continue; // Prompt user again
        }

        p_quantity = stoi(p_quantity_str);
        break;
    }

    // Add the product to the inventory
    inventory_products[inventory_count] = product(p_id, p_name, p_price, p_quantity);
    inventory_count++;
}



void inventory::display_productInfo(string pid) {
    for (int i = 0; i < inventory_count; ++i) {
        if (list_of_all_ids_names[i * 2] == pid || list_of_all_ids_names[i * 2 + 1] == pid) {
            inventory_products[i].display_productInfo();
            return;
        }
    }
    cout << "Product with Id/Name not found \n";
}

void inventory::update_product(string pid) {
    for (int i = 0; i < inventory_count; ++i) {
        if (list_of_all_ids_names[i * 2] == pid || list_of_all_ids_names[i * 2 + 1] == pid) {
            inventory_products[i].update_productInfo();
            return;
        }
    }
    cout << "Product with Id/Name not found \n";
}

void inventory::delete_product(string pid) {
    for (int i = 0; i < inventory_count; ++i) {
        if (list_of_all_ids_names[i * 2] == pid || list_of_all_ids_names[i * 2 + 1] == pid) {
            cout << "Product with Id/Name: " << list_of_all_ids_names[i * 2] << " deleted \n";
            for (int j = i; j < inventory_count - 1; ++j) {
                list_of_all_ids_names[j * 2] = list_of_all_ids_names[(j + 1) * 2];
                list_of_all_ids_names[j * 2 + 1] = list_of_all_ids_names[(j + 1) * 2 + 1];
                inventory_products[j] = inventory_products[j + 1];
            }
            inventory_count--;
            return;
        }
    }
    cout << "Product with Id/Name not found \n";
}

void inventory::list_products() {
    cout << "The products in inventory are: \n";
    int found=0;
    for (int i = 0; i < inventory_count; ++i) {
        inventory_products[i].display_productInfo();
        cout << endl;
        found=1;
    }
    if(found==0){
        cout<<"Inventory is empty!"<<endl;
    }
}

void inventory::zeroStock() {
    int found = 0;
    cout << "Items with zero stock:\n";
    for (int i = 0; i < inventory_count; ++i) {
        if (inventory_products[i].get_productQuantity() == 0) {
            cout << "Item: " << inventory_products[i].get_productName()
                 << " | Price: $" << inventory_products[i].get_productPrice() << endl;
            found = 1;
        }
    }

    if (!found) {
        cout << "No products with zero stock." << endl;
    }
}

void inventory::highestSold() {
    int highestIndex = -1;
    int highestSoldCount = 0;

    for (int i = 0; i < inventory_count; ++i) {
        if (inventory_products[i].get_soldCounter() > highestSoldCount) {
            highestSoldCount = inventory_products[i].get_soldCounter();
            highestIndex = i;
        }
    }

    if (highestIndex != -1) {
        cout << "Highest selling product is: " << inventory_products[highestIndex].get_productName()
             << " with " << highestSoldCount << " units sold." << endl;
    } else {
        cout << "No products have been sold yet." << endl;
    }
}
class billing {
private:
    inventory* inv; //using has-a relation with class inventory to access its functions
    //to define the size of productid and quantites array 
    static const int MAX_PRODUCTS = 100; // Maximum number of products in a bill
    string product_ids[MAX_PRODUCTS]; // Stores product IDs for billing
    int quantities[MAX_PRODUCTS]; // Stores quantities for each product
    int product_count; // Current count of products added
    double discount_rate; // Stores discount rate as a percentage

public:
//This is the constructor for the billing class.
//It takes a pointer to an inventory object as a parameter and initializes inv with it. 
//which allows it to interact with the inventory member functions.
    billing(inventory* inventory_ref) : inv(inventory_ref), discount_rate(0.0), product_count(0) {}

    void set_discount_rate(double rate) {//setter for discount
        discount_rate = rate;
    }
//pid, quantity as an input 
 void add_product_to_bill(string pid, int quantity) {
    bool productFound = false;
    int available_quantity = 0;

    // Check if the product is inside inventory
    for (int i = 0; i < inv->get_inventory_count(); ++i) {//iterates through eahc product
        if (inv->get_product_id(i) == pid) { // Check if the product ID matches
            productFound = true;
            available_quantity = inv->get_inventory_products()[i].get_productQuantity();//gets product quantiy from product class
            break;
        } else if (inv->get_inventory_products()[i].get_productName() == pid) { // Check if the product name matches
            productFound = true;
            pid = inv->get_product_id(i); // Update pid with the actual product ID 
            available_quantity = inv->get_inventory_products()[i].get_productQuantity();
            break;
        }
    }

    if (!productFound) {
        cout << "Product with ID/Name: " << pid << " not found in inventory. Cannot add to bill." << endl;
        return;
    }

    // Check if the requested quantity is within the available quantity
    if (quantity > available_quantity) {
        cout << "Error: Requested quantity (" << quantity << ") exceeds available stock (" << available_quantity << ")." << endl;
        return;
    }

    if (product_count < MAX_PRODUCTS) {
        product_ids[product_count] = pid;
        quantities[product_count++] = quantity;
        cout << "Product added successfully!" << endl;
    } else {
        cout << "Cannot add more products. Maximum capacity reached." << endl;
    }
}
void generate_bill() {
    double total = 0.0;  // Initialize total cost to 0
    cout << "Detailed Bill:" << endl;  // Print header for detailed bill
    cout << "--------------------------------" << endl;  // Print separator line

    // Loop through each product added to the bill
    for (int i = 0; i < product_count; ++i) {
        string pid = product_ids[i];  // Get the product ID from the list
        int quantity = quantities[i];  // Get the quantity for the product
        bool productFound = false;  // Initialize flag to check if product is found

        // Loop through the inventory to find the product
        for (int j = 0; j < inv->get_inventory_count(); ++j) {
            if (inv->get_product_id(j) == pid) {  // Check if product ID matches
                productFound = true;  // Set flag to true if product is found

                // Get product details from the inventory
                string name = inv->get_inventory_products()[j].get_productName();
                double price = inv->get_inventory_products()[j].get_productPrice();
                int available_quantity = inv->get_inventory_products()[j].get_productQuantity();

                // Check if there is enough quantity available
                if (available_quantity >= quantity) {
                    // Print product details and calculate total cost
                    cout << "Product Name: " << name << ", Price: $" << price << ", Quantity: " << quantity << endl;
                    total += price * quantity;

                    // Update inventory and sold counter
                    inv->get_inventory_products()[j].incrementSoldCounter(quantity);
                    inv->get_inventory_products()[j].decrement_quantity(quantity);
                } else {
                    // Print message if not enough quantity is available
                    cout << "Not enough quantity available for product: " << name << endl;
                    quantity = available_quantity;  // Adjust quantity to available amount

                    // Print adjusted product details and calculate total cost
                    cout << "Adding the maximum available quantity: " << quantity << endl;
                    cout << "Product Name: " << name << ", Price: $" << price << ", Quantity: " << quantity << endl;
                    total += price * quantity;

                    // Update inventory and sold counter
                    inv->get_inventory_products()[j].incrementSoldCounter(quantity);
                    inv->get_inventory_products()[j].decrement_quantity(quantity);
                }
                break;  // Exit the loop once the product is found
            }
        }

        // Print message if product is not found in inventory
        if (!productFound) {
            cout << "Product with ID: " << pid << " not found in inventory." << endl;
        }
    }

    // Calculate discount and total after discount
    double discount = total * (discount_rate / 100.0);  // Calculate discount amount
    double total_after_discount = total - discount;  // Calculate total after discount

    // Print bill summary
    cout << "--------------------------------" << endl;  // Print separator line
    cout << "Subtotal: $" << total << endl;  // Print subtotal
    cout << "Discount (" << discount_rate << "%): -$" << discount << endl;  // Print discount amount
    cout << "Total After Discount: $" << total_after_discount << endl;  // Print total after discount
}
};

// Assume the existence of Admin, inventory, and billing classes and their me1thods
int main() {
    int pmax = 50; // Maximum number of products in inventory
    //creates an instance inv of inventory using 
    //paramterized const takes pmax as arg which sets max capacity
    inventory inv(pmax);
//creats an instance of billing taking inventory object
//inv as an arguement which allows billing to access & interact with inventory
    billing bill(&inv);
   User* user = new Admin();  // Create an Admin object but use a User pointer
//user is a pointer of type User (the abstract base class)
//new admin dynamically creates an instance of admin and assigns it user
    int mainChoice, choice;
    string pid;
    string username, password;
    do {
        cout << "Main Menu:\n";
        cout << "1. Admin Panel\n";
        cout << "2. Buyer Panel\n";
        cout << "3. Exit\n";
        string choiceStr;
        while (true) {
            cout << "Enter your choice: ";
            cin >> choiceStr;

            if (!isNumber(choiceStr)) {
                cout << "Invalid input for choice. Please enter a valid number." << endl;
                continue; // Prompt user again
            }

            mainChoice = stoi(choiceStr);
            break;
        }
 switch (mainChoice) {
        case 1: {
            if (user->login()) {
                do {
                    cout << "Admin Panel:\n";
                    cout << "1. Add a product\n";
                    cout << "2. Update a product\n";
                    cout << "3. Delete a product\n";
                    cout << "4. Product with highest sold\n";
                    cout << "5. Items with zero stock\n";
                    cout << "6. List all products\n";
                    cout << "7. Return to Main Menu\n";
                    cout << "8. Exit\n";

                    string choiceStr;
                    while (true) {
                        cout << "Enter your choice: ";
                        cin >> choiceStr;

                        if (!isNumber(choiceStr)) {
                            cout << "Invalid input for choice. Please enter a valid number." << endl;
                            continue; // Prompt user again
                        }

                        choice = stoi(choiceStr);
                        break;
                    }
                    switch (choice) {
                    case 1:
                        inv.add_product();
                        break;
                    case 2:
                        cout << "Enter product ID/Name to update: ";
                        cin.ignore(); // To consume the '\n' character left in the input buffer
                        getline(cin, pid);
                        inv.update_product(pid);
                        break;
                    case 3:
                        cout << "Enter product ID/Name to delete: ";
                        cin >> pid;
                        inv.delete_product(pid);
                        break;
                    case 4:
                        inv.highestSold();
                        break;
                    case 5:
                        inv.zeroStock();
                        break;
                    case 6:
                        inv.list_products();
                        break;
                    case 7:
                        break;
                    case 8:
                        return 0;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                        break;
                    }

                } while (choice != 7);
            }
            break;
        }
        case 2: {
            do {
                cout << "Buyer Panel:\n";
                cout << "1. Display product information\n";
                cout << "2. List all products\n";
                cout << "3. Add product to bill\n";
                cout << "4. Generate bill\n";
                cout << "5. Return to Main Menu\n";

                string choiceStr;
                while (true) {
                    cout << "Enter your choice: ";
                    cin >> choiceStr;

                    if (!isNumber(choiceStr)) {
                        cout << "Invalid input for choice. Please enter a valid number." << endl;
                        continue; // Prompt user again
                    }

                    choice = stoi(choiceStr);
                    break;
                }
                switch (choice) {
                case 1:
                    cout << "Enter product ID/Name to display information: ";
                    cin >> pid;
                    inv.display_productInfo(pid);
                    break;
                case 2:
                    inv.list_products();
                    break;
                case 3: {
                    int quantity;
                    cout << "Enter product ID/Name to add to bill: ";
                    cin >> pid;
                    cout << "Enter quantity to buy: ";
                    cin >> quantity;
                    bill.add_product_to_bill(pid, quantity);
                    break;
                }
                case 4: { // Generate bill
                    char applyDiscount;
                    cout << "Do you want to apply discount % (Y/N)? ";
                    cin >> applyDiscount;
                    if (applyDiscount == 'Y' || applyDiscount == 'y') {
                        string discountRateStr;
                        double discountRate;
                        while (true) {
                            cout << "Enter discount %: ";
                            cin >> discountRateStr;

                            if (!isNumber(discountRateStr)) {
                                cout << "Invalid input for discount rate. Please enter a valid number." << endl;
                                continue; // Prompt user again
                            }

                            discountRate = stod(discountRateStr);
                            break;
                        }
                        bill.set_discount_rate(discountRate);
                    }
                    bill.generate_bill();
                    break;
                }
                case 5:
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            } while (choice != 5);
            break;
        }
        case 3:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (mainChoice != 3);

    return 0;
}
