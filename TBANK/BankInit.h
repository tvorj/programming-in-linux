#include <vector>
#include <limits.h>

using namespace std;

struct BankCell
{
    int cur_balance;
    int min_balance;
    int max_balance;
    bool frozen;
    BankCell() : frozen(true), cur_balance(0), min_balance(INT_MAX), max_balance(INT_MIN)
    {
        cout << "Default constructor for BankCell" << endl;
    }
};

class Bank
{
private:
    vector<BankCell> cells;

public:
    Bank(size_t N) : cells(N)
    {
        cout << "Default constructor for Bank" << endl;
    }
    void printAccount(int i)
    {
        cout << cells[i].cur_balance << " " << cells[i].max_balance << " " << cells[i].min_balance << " " << cells[i].frozen;
        cout << endl;
    }
    void froze(int i)
    {
    }
    void transfer(int from, int to, int amount)
    {
    }
    void addToAll(int amount)
    {
    }
    void setMinBalance(int i, int m)
    {
    }
    void setMaxBalance(int i, int M)
    {
    }
};

