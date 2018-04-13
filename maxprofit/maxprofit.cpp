/*
 * Program to find max difference between 2 elements;
 * Max profit problem: buy n sell stock for max profit.
 */

#include <iostream>
using namespace std;

int maxProfit(int prices[], int n)
{
    // initially, max profit is set to 0
    int maxprofit = 0;

    // begin with last 2 elements
    int hi = n-1;
    int lo = hi-1;

    // till we exhaust all the elements, traverse in reverse order
    while (lo >= 0) {

        // compute profit at current indices, determine max profit
        int profit = prices[hi]-prices[lo];
        if (profit > maxprofit) {
            maxprofit = profit;
        }

        // exhausted all elements?
        if(lo == 0) {
            return maxprofit;
        }

        // next element > self, we have new high
        if (prices[hi-1] > prices[hi]) {
            hi--;
        }
        
        // decrement low index anyway
        lo--;

        // next element that is lower than self
        if (prices[lo] > prices[lo+1]) {
            hi = lo;
            lo--;
        }
    }
    return maxprofit;
}

int main()
{
    int prices[] = {10, 7, 5, 8, 11, 9};
    int max_profit = maxProfit(prices, sizeof(prices)/sizeof(int));
    cout << "result: " << max_profit << endl;
    return 0;
}
