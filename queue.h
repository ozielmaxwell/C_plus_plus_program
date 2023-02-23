#include <iostream>
#include <queue>

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
    queue<Purchase> lifo, fifo;

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

    // calculate average price of MSFT for LIFO queue
    double avgPriceLIFO = avgPrice("MSFT", lifo);
    cout << "Average price of MSFT in LIFO queue: $" << avgPriceLIFO << endl;

    // calculate average price of GME for FIFO queue
    double avgPriceFIFO = avgPrice("GME", fifo);
    cout << "Average price of GME in FIFO queue: $" << avgPriceFIFO << endl;

    return 0;
}
