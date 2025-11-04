// Name : Rohit Bhika Kolate
// PRN : 123B1F049
// Year : TY-IT(A)
// Batch : A3

//emergency relief boat loading system
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

struct Item {
    string name;
    double weight;
    double value;
    bool divisible;
    int priority; 

    Item(string n, double w, double v, bool d, int p)
        : name(n), weight(w), value(v), divisible(d), priority(p) {}

    double valuePerWeight() const {
        return value / weight;
    }
};

bool compare(const Item& a, const Item& b) {
    if (a.priority == b.priority)
        return a.valuePerWeight() > b.valuePerWeight();
    
    // Lower priority number comes first
    return a.priority < b.priority; 
}

double fractionalKnapsack(vector<Item>& items, double capacity, double& totalWeightCarried) {
    sort(items.begin(), items.end(), compare);

    cout << "\n--- Sorted Items (by Priority, then Value/Weight) ---\n";
    cout << left << setw(20) << "Item"
         << setw(10) << "Weight"
         << setw(10) << "Value"
         << setw(12) << "Priority"
         << setw(15) << "Value/Weight"
         << setw(15) << "Type" << "\n";
    cout << setfill('-') << setw(82) << "" << setfill(' ') << "\n";
    
    for (const auto& item : items) {
        cout << left << setw(20) << item.name
             << setw(10) << fixed << setprecision(1) << item.weight
             << setw(10) << item.value
             << setw(12) << item.priority
             << setw(15) << fixed << setprecision(2) << item.valuePerWeight()
             << setw(15) << (item.divisible ? "Divisible" : "Indivisible")
             << "\n";
    }

    double totalValue = 0.0;
    totalWeightCarried = 0.0;

    cout << "\n--- Items Selected for Transport ---\n";
    cout << fixed << setprecision(2);

    for (const auto& item : items) {
        if (capacity <= 0) break;

        if (item.divisible) {
            double takenWeight = min(item.weight, capacity);
            double takenValue = item.valuePerWeight() * takenWeight;
            
            totalValue += takenValue;
            capacity -= takenWeight;
            totalWeightCarried += takenWeight;

            cout << " - \033[1;32mDivisible\033[0m: " << item.name << " | Taken: " << takenWeight << " kg (" << (takenWeight / item.weight * 100) << "%) | Utility: " << takenValue
                 << " | Cap. Left: " << capacity << " kg\n";
        } else {
            if (item.weight <= capacity) {
                totalValue += item.value;
                capacity -= item.weight;
                totalWeightCarried += item.weight;

                cout << " - \033[1;34mIndivisible\033[0m: " << item.name << " | Taken: " << item.weight << " kg (FULL) | Utility: " << item.value
                     << " | Cap. Left: " << capacity << " kg\n";
            } else {
                cout << " - \033[1;31mIndivisible\033[0m: " << item.name << " | Skipped (Too Heavy: " << item.weight << " kg)\n";
            }
        }
    }

    return totalValue;
}

int main() {
    vector<Item> items = {
        Item("Infant Formula", 5, 50, false, 1),
        Item("Medical Kits", 10, 100, false, 1),
        Item("Drinking Water", 30, 90, true, 2),
        Item("Water Filters", 2, 8, false, 2),
        Item("Blankets", 15, 45, false, 3),
        Item("Food Packets", 20, 60, true, 3),
    };

    double capacity;
    cout << "🛶 Emergency Relief Boat Loading System\n";
    cout << "Enter maximum weight capacity of the boat (in kg): ";
    
    if (!(cin >> capacity) || capacity <= 0) {
        cout << "Invalid capacity. Exiting.\n";
        return 1;
    }

    double totalWeightCarried;
    double maxValue = fractionalKnapsack(items, capacity, totalWeightCarried);

    cout << "        FINAL TRANSPORT SUMMARY\n";
    cout << "Total weight carried:     " << fixed << setprecision(2) << totalWeightCarried << " kg\n";
    cout << "Remaining boat capacity:  " << max(0.0, capacity - totalWeightCarried) << " kg\n";
    cout << "Total utility value:      " << fixed << setprecision(2) << maxValue << " units\n";

    return 0;
}