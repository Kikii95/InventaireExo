#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Item {
    std::string iName;
    int iWeight;
    std::string iDescription;
};

const int maxCapacity = 100;

int calculateTotalWeight(const std::vector<Item>& Inventory) {
    int totalWeight = 0;
    for (const auto& item : Inventory) {
        totalWeight += item.iWeight;
    }
    return totalWeight;
}

void displayInventory(const std::vector<Item>& Inventory) {
    int totalWeight = calculateTotalWeight(Inventory);
    std::cout << "\nVoici le contenu complet de l'inventaire :\n";
    std::cout << "--------------------------" << std::endl;

    for (const auto& item : Inventory) {
        std::cout << item.iName << " (Poids: " << item.iWeight << ") -> " << item.iDescription << std::endl;
    }

    std::cout << "--------------------------" << std::endl;
    std::cout << "Poids total des items : " << totalWeight << "/" << maxCapacity << std::endl;
}

void optimizeInventory(std::vector<Item>& Inventory, int newItemWeight) {
    std::sort(Inventory.begin(), Inventory.end(), [](const Item& a, const Item& b) {
        return a.iWeight < b.iWeight;
        });

    while (calculateTotalWeight(Inventory) + newItemWeight > maxCapacity && !Inventory.empty()) {
        std::cout << "Retrait de l'item le plus leger : " << Inventory.front().iName << " (Poids: " << Inventory.front().iWeight << ")\n";
        Inventory.erase(Inventory.begin());
    }

    std::cout << "\nOptimisation de l'inventaire terminee. Poids actuel : " << calculateTotalWeight(Inventory) << "/" << maxCapacity << "\n";
}

void newItem(std::vector<Item>& Inventory, const std::string& iName, int iWeight, const std::string& iDescription) {
    int totalWeight = calculateTotalWeight(Inventory);
    std::string choice;

    if (totalWeight + iWeight > maxCapacity) {
        std::cout << "L'ajout de l'objet '" << iName << "' depasse la capacite maximale de " << maxCapacity << " unites.\n";
        std::cout << "--------------------------" << std::endl;
        std::cout << "Souhaitez-vous optimiser l'inventaire afin d'ajouter l'objet " << iName << " ? (oui / non) ";
        std::cin >> choice;
        std::cout << "\n";
        if (choice == "oui") {
            optimizeInventory(Inventory, iWeight);
            std::cout << "--------------------------" << std::endl;
        }
        else {
            return;
        }
    }

    Inventory.push_back({ iName, iWeight, iDescription });
    std::cout << "Objet ajoute : " << iName << std::endl;
}

void dropItem(std::vector<Item>& Inventory, const std::string& itemName) {
    auto it = std::find_if(Inventory.begin(), Inventory.end(), [&itemName](const Item& item) {
        return item.iName == itemName;
        });

    if (it != Inventory.end()) {
        Inventory.erase(it);
        std::cout << "Objet supprime : " << itemName << std::endl;
    }
    else {
        std::cout << "Objet non trouve : " << itemName << std::endl;
    }
}

void findItem(const std::vector<Item>& Inventory, const std::string& itemName) {
    auto it = std::find_if(Inventory.begin(), Inventory.end(), [&itemName](const Item& item) {
        return item.iName == itemName;
        });

    if (it != Inventory.end()) {
        std::cout << "Objet trouve : " << it->iName << " (Poids : " << it->iWeight << ") -> " << it->iDescription << std::endl;
    }
    else {
        std::cout << "Objet non trouve : " << itemName << std::endl;
    }
}

void sortItem(std::vector<Item>& Inventory, const std::string& choix) {
    if (choix == "Nom") {
        std::sort(Inventory.begin(), Inventory.end(), [](const Item& a, const Item& b) {
            return a.iName < b.iName;
            });
    }
    else if (choix == "Poids") {
        std::sort(Inventory.begin(), Inventory.end(), [](const Item& a, const Item& b) {
            return a.iWeight < b.iWeight;
            });
    }
    else {
        std::cout << "Choix invalide. Utilisez 'Nom' ou 'Poids'." << std::endl;
    }
}

int main() {
    std::vector<Item> Inventory = {
        {"Axe", 12, "Tranchant et puissant pour couper"},
        {"Helmet", 8, "Casque pour protéger ta tête"},
        {"Boots", 4, "Bottes rapides pour courir"},
        {"Ring", 1, "Un petit anneau magique"},
        {"Staff", 18, "Baton mystique pour les sorts"},
        {"Map", 3, "Carte du monde pour t'orienter"}
    };

    newItem(Inventory, "Sword", 15, "Grand truc qui coupe");
    newItem(Inventory, "Shield", 20, "Surface qui prend les bobos à ta place");
    newItem(Inventory, "Food", 5, "Mmmhh oh ouais");

    dropItem(Inventory, "Map");

    displayInventory(Inventory);

    findItem(Inventory, "Ring");
    findItem(Inventory, "Sword");

    std::cout << "\nComment souhaitez-vous trier l'inventaire (Nom/Poids) : ";
    std::string choice;
    std::cin >> choice;
    sortItem(Inventory, choice);

    displayInventory(Inventory);

    newItem(Inventory, "Anvil", 75, "Woaaa c'est lourd");
    newItem(Inventory, "Car", 23, "Woaaa c'est lourd");

    displayInventory(Inventory);

    return 0;
}
