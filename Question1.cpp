#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Argument
{
public:
    vector<int> premises;
    int conclusion;

    Argument(const string& expr)
    {
        for (char c : expr)
        {
            if (c == 'P' || c == 'Q' || c == 'R' || c == 'S')
                premises.push_back(-1);
        }
        conclusion = -1;
    }
};

int applyLogicalOperator(int a, int b, char op)
{
    if (op == 'v')
        return a || b;
    else if (op == '^')
        return a && b;
    else if (op == '>')
        return !a || b;
    else if (op == '<')
        return (!a || b) && (!b || a);
    return -1; // Handle invalid operator case
}

void printPremises(const Argument& arg)
{
    for (int value : arg.premises)
    {
        if (value == -1)
            cout << "   ";
        else
            cout << (value == 1 ? "T" : "F") << "  ";
    }
}

void printConclusion(const Argument& arg)
{
    cout << (arg.conclusion == 1 ? "T" : "F") << "     ";
}

int main()
{
    cout << "Enter v for OR\n ^ for AND\n > for Conditional\n < for Biconditional" << endl;
    string expr1, expr2;
    cout << "Enter argument 1st (3 variables all upper case): ";
    cin >> expr1;
    cout << "Enter argument 2nd (3 variables all upper case): ";
    cin >> expr2;

    Argument arg1(expr1);
    Argument arg2(expr2);

    int count = 0;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                int p1 = arg1.premises[0] = i;
                int p2 = arg1.premises[1] = j;
                int p3 = arg1.premises[2] = k;

                arg1.conclusion = applyLogicalOperator(
                    applyLogicalOperator(p1, p2, expr1[1]),
                    p3,
                    expr1[5]
                );

                arg2.premises[0] = i;
                arg2.premises[1] = j;
                arg2.premises[2] = k;

                arg2.conclusion = applyLogicalOperator(
                    applyLogicalOperator(p1, p2, expr2[1]),
                    p3,
                    expr2[5]
                );

                count++;
            }
        }
    }

    // Check if equivalent
    bool flag = true;
    for (int i = 0; i < 8; i++)
    {
        if (arg1.conclusion != arg2.conclusion)
            flag = false;
    }

    if (flag)
    {
        cout << "Equivalent" << endl;
        cout << "Step-by-Step Proof:" << endl;
        cout << "------------------" << endl;

        for (int i = 0; i < 8; i++)
        {
            cout << "Case " << i + 1 << ":" << endl;

            // Print premises for argument 1
            cout << "Argument 1 Premises: ";
            printPremises(arg1);
            cout << "  Conclusion: ";
            printConclusion(arg1);
            cout << endl;

            // Print premises for argument 2
            cout << "Argument 2 Premises: ";
            printPremises(arg2);
            cout << "  Conclusion: ";
            printConclusion(arg2);
            cout << endl;

            cout << "------------------" << endl;
        }
    }
    else
        cout << "Not Equivalent" << endl;

    return 0;
}

