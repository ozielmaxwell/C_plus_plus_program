#include <iostream>
#include <string>
#include <queue>
#include <stack>

struct Purchase {
    std::string name;
    int shares;
    double pricePerShare;
};

int main() {
    // Initialize data structures
    std::queue<Purchase> fifo;
    std::stack<Purchase> lifo;

    // Get purchase data from user
    std::cout << "Enter purchase data (one purchase per line, empty line to finish):" << std::endl;
    while (true) {
        // Get purchase data
        std::string name;
        int shares;
        double pricePerShare;
        std::cout << "Name of stock: ";
        std::getline(std::cin, name);
        if (name.empty()) {
            break;
        }
        std::cout << "Number of shares: ";
        std::cin >> shares;
        std::cout << "Price per share: ";
        std::cin >> pricePerShare;
        std::cin.ignore();  // Ignore leftover newline character

        // Add purchase to data structures
        Purchase p = {name, shares, pricePerShare};
        fifo.push(p);
        lifo.push(p);
    }

    // Get number of shares to sell
    int numSharesToSell;
    std::cout << "Enter number of shares to sell: ";
    std::cin >> numSharesToSell;

    // Calculate FIFO price
    double fifoPrice = 0.0;
    int numSharesSold = 0;
    while (!fifo.empty() && numSharesSold < numSharesToSell) {
        Purchase p = fifo.front();
        int sharesToSell = std::min(numSharesToSell - numSharesSold, p.shares);
        fifoPrice += sharesToSell * p.pricePerShare;
        numSharesSold += sharesToSell;
        if (sharesToSell == p.shares) {
            fifo.pop();
        } else {
            p.shares -= sharesToSell;
            fifo.front() = p;
        }
    }
    fifoPrice /= numSharesToSell;

    // Calculate LIFO price
    double lifoPrice = 0.0;
    numSharesSold = 0;
    while (!lifo.empty() && numSharesSold < numSharesToSell) {
        Purchase p = lifo.top();
        int sharesToSell = std::min(numSharesToSell - numSharesSold, p.shares);
        lifoPrice += sharesToSell * p.pricePerShare;
        numSharesSold += sharesToSell;
        if (sharesToSell == p.shares) {
            lifo.pop();
        } else {
            p.shares -= sharesToSell;
            lifo.top() = p;
        }
    }
    lifoPrice /= numSharesToSell;

    // Output results
    std::cout << "FIFO price for selling " << numSharesToSell << " shares: " << fifoPrice << std::endl;
    std::cout << "LIFO price for selling " << numSharesToSell << " shares: " << lifoPrice << std::endl;

    return 0;
}
