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

// function to compute the average price of a particular stock name
double avgPrice(string stockName, queue<Purchase> q) {
    double totalPrice = 0;
    int count = 0;

    while (!q.empty()) {
        if (q.front().stockName == stockName) {
            totalPrice += q.front().numOfShares * q.front().perSharePrice;
            count += q.front().numOfShares;
        }
        q.pop();
    }

    if (count == 0) {
        cout << "No purchases found for " << stockName << endl;
        return 0;
    }

    return totalPrice / count;
}


int main() {
    stack<Purchase> lifo;
    queue<Purchase> fifo;

    int choice = 0;
    cout << "Enter 1 to enter a purchase" << endl;
    cout << "Enter 2 to find the LIFO and FIFO price" << endl;
    cout << "Enter 3 to make a sale" << endl;
    cout << "Enter 4 to exit" << endl;
    cin >> choice;

    while (choice != 3 && choice !=2 && choice != 4)
    {
        
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
            cout << "Enter 1 to enter a purchase" << endl;
            cout << "Enter 2 to find the LIFO and FIFO price" << endl;
            cout << "Enter 3 to make a sale" << endl;
            cout << "Enter 4 to exit" << endl;
            cin >> choice;
       
    }
    if (choice == 2)
    {
        string stockName;
        int numOfShares;
        cout << "Enter the stock name: ";
        cin >> stockName;
        cout << "Enter the number of shares: ";
        cin >> numOfShares;
        // calculate average price of MSFT for LIFO queue
        double avgPriceLIFO = avgPrice(stockName, lifo);
        cout << "Average price of MSFT in LIFO queue: $" << avgPriceLIFO << endl;

        // calculate average price of GME for FIFO queue
        double avgPriceFIFO = avgPrice(stockName, fifo);
        cout << "Average price of GME in FIFO queue: $" << avgPriceFIFO << endl;
    }

    if (choice == 3) {
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
    }
    else {
        cout << "Wrong Option" << endl;
    }
    

    return 0;
}
