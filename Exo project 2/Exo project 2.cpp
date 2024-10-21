#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef struct Item {
    std::string iName;
    int iWeight;
    std::string iDescription;
};

const int maxInventory = 5;

void newItem(std::vector<Item>& Inventory, std::string iName, int iWeight, std::string iDescription) {
    if (Inventory.size() >= maxInventory) {
        std::cout << "Inventaire plein, impossible d'ajouter l'objet " << iName << " !" << std::endl;
        return;
    }

    for (int i = 0; i < Inventory.size(); i++) {
        if (iName == Inventory[i].iName && iWeight == Inventory[i].iWeight) {
            std::cout << "Objet deja present : " << iName << std::endl;
            return;
        }
    }

    Item newItem = { iName, iWeight, iDescription };
    Inventory.push_back(newItem);
    std::cout << "Objet ajoute : " << iName << std::endl;
}

void dropItem(std::vector<Item>& Inventory, const std::string& itemName) {
    for (auto it = Inventory.begin(); it != Inventory.end(); ++it) {
        if (it->iName == itemName) {
            Inventory.erase(it);
            std::cout << "Objet supprime : " << itemName << std::endl;
            return;
        }
    }
    std::cout << "Objet non trouve : " << itemName << std::endl;
}

void findItem(const std::vector<Item>& Inventory, const std::string& itemName) {
    for (auto it = Inventory.begin(); it != Inventory.end(); ++it) {
        if (it->iName == itemName) {
            std::cout << "Objet trouve : " << it->iName << " (Weight : " << it->iWeight << ") -> " << it->iDescription << std::endl;
            return;
        }
    }
    std::cout << "Objet non trouve : " << itemName << std::endl;
}

void sortbyName(std::vector<Item>& Inventory) {
    std::sort(Inventory.begin(), Inventory.end(), [](const Item& a, const Item& b) {
        return a.iName < b.iName;
        });
}

void sortbyWeight(std::vector<Item>& Inventory) {
    std::sort(Inventory.begin(), Inventory.end(), [](const Item& a, const Item& b) {
        return a.iWeight < b.iWeight;
        });
}

void sortItem(std::vector<Item>& Inventory, const std::string& choix) {
    if (choix == "Name") {
        sortbyName(Inventory);
    }
    else if (choix == "Weight") {
        sortbyWeight(Inventory);
    }
    else {
        std::cout << "Choix invalide. Utilisez 'Name' ou 'Weight'." << std::endl;
    }
}

int main() {
    std::vector<Item> Inventory = {};

    newItem(Inventory, "Sword", 15, "Grand truc qui coupe");
    newItem(Inventory, "Shield", 20, "Surface qui prend les bobos a ta place");
    newItem(Inventory, "Bow", 10, "Une guitare a une corde qui peut faire mal");
    newItem(Inventory, "Food", 5, "Mmmhh oh ouais");
    newItem(Inventory, "Potion", 2, "Un cul sec et t'es tout frais");

    dropItem(Inventory, "Shield");
    dropItem(Inventory, "Arrow");

    std::cout << "\nVoici l'inventaire actuel :\n--------------------------" << std::endl;
    for (int i = 0; i < Inventory.size(); i++) {
        std::cout << Inventory[i].iName << " (Weight: " << Inventory[i].iWeight << ")" << std::endl;
    }
    std::cout << "--------------------------" << std::endl;

    findItem(Inventory, "Arrow");
    findItem(Inventory, "Potion");
    findItem(Inventory, "Sword");

    std::cout << "\nComment souhaitez-vous trier l'inventaire (Name/Weight) : ";
    std::string choice;
    std::cin >> choice;
    sortItem(Inventory, choice);
    
    std::cout << "\nVoici l'inventaire tri par " << choice << " :\n--------------------------" << std::endl;
    for (int i = 0; i < Inventory.size(); i++) {
        std::cout << Inventory[i].iName << " (Weight: " << Inventory[i].iWeight << ")" << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
   

    return 0;
}
