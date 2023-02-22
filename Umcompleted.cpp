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

    // Asking the user what operation he want
    cout << "Welcome to share buy and sell using LIFO and FIFO: \nEnter 1 to BUY share or \nEnter 2 to find LIFO and FIFO or \nEnter 3 to sell your share \nEnter 0 to quit" << endl;
    int choice;
    cin >> choice;
    while(choice != 0) {
        string stockName;
        int numOfShares;
        switch (choice)
        {
            
            case 1:
                while (true) {
                    // Get purchase data
                    string name;
                    char more;
                    int shares;
                    double pricePerShare;
                    cout << "Name of stock: ";
                    cin >> name;
                    cout << "Number of shares: ";
                    cin >> shares;
                    cout << "Price per share: ";
                    cin >> pricePerShare;
                    cout << "Do you still want to buy share? y or n: ";
                    cin >> more;
                    if (more != 'y')
                        break;
                    // Add purchase to data structures
                    Purchase p = { name, shares, pricePerShare };
                    fifo.push(p);
                    lifo.push(p);
                    string stockName;
                    int numOfShares;
                }
                break;

            case 2:
                cout << "Average LIFO price: " << endl;
                cout << "Average FIFO price: " << endl;
                break;
            case 3:
                // remove shares from stack and queue
                
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
                break;
            default:
                cout << "Invalid seletion. Please try again" << endl;
                break;
        }
        cout << "Welcome to share buy and sell using LIFO and FIFO: \nEnter 1 to BUY share or \nEnter 2 to find LIFO and FIFO or \nEnter 3 to sell your share \nEnter 0 to quit" << endl;
        cin >> choice;
    }
 
    return 0;
}
