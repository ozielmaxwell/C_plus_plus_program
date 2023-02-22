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

    // fill data structures with purchase data
    Purchase purchase1 = {"MSFT", 100, 200.39};
    Purchase purchase2 = {"GME", 500, 9.39};
    Purchase purchase3 = {"MSFT", 250, 214.22};
    Purchase purchase4 = {"MSFT", 300, 222.59};
    lifo.push(purchase1);
    lifo.push(purchase2);
    lifo.push(purchase3);
    lifo.push(purchase4);
    fifo.push(purchase1);
    fifo.push(purchase2);
    fifo.push(purchase3);
    fifo.push(purchase4);

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
    } else {
        cout << "FIFO price for " << numOfShares << " shares of " << stockName << " is " << fifoPrice/numOfShares << endl;
        cout << "LIFO price for " << numOfShares << " shares of " << stockName << " is " << lifoPrice/numOfShares << endl;
    }

    return 0;
}
