#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

struct Purchase {
    string stockName;
    int numOfShares;
    double perSharePrice;
};

int main() {
    stack<Purchase> lifo;
    queue<Purchase> fifo;


    cout << "Enter 1 to enter a purchase" << endl;
    cout << "Enter 2 to find the LIFO and FIFO price" << endl;
    cout << "Enter 3 to make a sale" << endl;
    cout << "Enter 4 to exit" << endl;
    int choice;

    cin >> choice;
    if (choice == 1) {
        
        while (true) 
        {
            // Get purchase data
            string name;
            int shares;
            double pricePerShare;
            cout << "Name of stock: ";
            cin >> name;
            cout << "Number of shares: ";
            cin >> shares;
            cout << "Price per share: ";
            cin >> pricePerShare;
            // Add purchase to data structures
            Purchase p = { name, shares, pricePerShare };
            fifo.push(p);
            lifo.push(p);
            cout << "Share added succeffully" << endl;
            cout << "Press 0 to end buying of share or 1 to buy more: ";
            int i;
            cin >> i;
            if (i == 0)
                break;

        }
        cin >> choice;
    }

    // remove shares from stack and queue
    string stockName;
    int numOfShares;
    cout << "Enter the stock name: ";
    cin >> stockName;
    cout << "Enter the number of shares: ";
    cin >> numOfShares;

    double fifoPrice = 0.0;
    double lifoPrice = 0.0;

    // remove from FIFO queue
    int remainingShares = numOfShares;
    while (!fifo.empty() && remainingShares > 0) {
        Purchase p = fifo.front();
        fifo.pop();
        if (p.stockName == stockName) {
            int sharesToRemove = min(remainingShares, p.numOfShares);
            fifoPrice += sharesToRemove * p.perSharePrice;
            remainingShares -= sharesToRemove;
            if (sharesToRemove < p.numOfShares) {
                p.numOfShares -= sharesToRemove;
                fifo.push(p);
            }
        }
    }

    // remove from LIFO stack
    stack<Purchase> lifoCopy = lifo;
    remainingShares = numOfShares;
    while (!lifoCopy.empty() && remainingShares > 0) {
        Purchase p = lifoCopy.top();
        lifoCopy.pop();
        if (p.stockName == stockName) {
            int sharesToRemove = min(remainingShares, p.numOfShares);
            lifoPrice += sharesToRemove * p.perSharePrice;
            remainingShares -= sharesToRemove;
            if (sharesToRemove < p.numOfShares) {
                p.numOfShares -= sharesToRemove;
                lifo.push(p);
            }
        }
    }

    if (remainingShares > 0) {
        cout << "Could not sell " << remainingShares << " shares of " << stockName << endl;
    }
    else {
        cout << "FIFO price for " << numOfShares << " shares of " << stockName << " is " << fifoPrice / numOfShares << endl;
        cout << "LIFO price for " << numOfShares << " shares of " << stockName << " is " << lifoPrice / numOfShares << endl;
    }

    return 0;
}
