#include<iostream>
#include<fstream>

const int MAX = 52;
const int DECK = 52;
const int STOP = 1000000;

class Deck
{
private:
    int cards[MAX];
    int top;
    int low;
    int size;

public:

    Deck(int size)
    {
        top = -1;
        low = 0;
        this->size = size;
    }

    bool isFull() const
    {
        return ((top == 0 && low == size - 1) || top == low + 1);
    }

    bool isEmpty() const
    {
        return (top == -1);
    }

    int drawTop()
    {
        if (isEmpty())
        {
            std::cerr << "Error1" << '\n';
            return -1;
        }
        int topper = cards[top];
        if (top == low)
        {
            top = -1;
            low = -1;
        }
        else if (top == size - 1)
        {
            top = 0;
        }
        else
        {
            top++;
        }
        return topper;
    }

    int drawLow()
    {
        if (isEmpty())
        {
            std::cout << "Error2" << '\n';
            return -1;
        }
        int lowest = cards[low];
        if (top == low)
        {
            top = -1;
            low = -1;
        }
        else if (low == 0)
        {
            low = size - 1;
        }
        else
        {
            low--;
        }
        return lowest;
    }

    void pushTop(int card)
    {
        if (isFull())
        {
            std::cout << "Error3" << '\n';
            return;
        }
        if (top == -1)
        {
            top = 0;
            low = 0;
        }
        else if (top == 0)
        {
            top = size - 1;
        }
        else
        {
            top--;
        }
        cards[top] = card;
    }

    void pushLow(int card)
    {
        if (isFull())
        {
            std::cout << "Error!" << std::endl;
            return;
        }
        if (top == -1)
        {
            top = 0;
            low = 0;
        }
        else if (low == size - 1)
        {
            low = 0;
        }
        else
        {
            low++;
        }
        cards[low] = card;
    }
};

void game(Deck& first_player, Deck& second_player)
{
    int first_card;
    int second_card;
    int step = 0;
    Deck disp(52);

    while (!first_player.isEmpty() && !second_player.isEmpty() && step < STOP)
    {
        first_card = first_player.drawTop();
        second_card = second_player.drawTop();
        if ((first_card == 2 && second_card == 14) || ((second_card != 2 || first_card != 14) && (first_card > second_card)))
        {
            first_player.pushLow(first_card);
            first_player.pushLow(second_card);
        }
        else if ((second_card == 2 && first_card == 14) || (second_card > first_card))
        {
            second_player.pushLow(first_card);
            second_player.pushLow(second_card);
        }
        else
        {
            step++;
            disp.pushTop(first_card);
            disp.pushTop(second_card);
            while (step < STOP && !first_player.isEmpty() && !second_player.isEmpty())
            {
                int first_card_disp = first_player.drawTop();
                int second_card_disp = second_player.drawTop();

                disp.pushTop(first_card_disp);
                disp.pushTop(second_card_disp);
                if ((first_card_disp == 2 && second_card_disp == 14) || ((second_card_disp != 2 || first_card_disp != 14) && (first_card_disp > second_card_disp)))
                {
                    while (!disp.isEmpty())
                    {
                        first_player.pushLow(disp.drawLow());
                    }
                }
                else if ((second_card_disp == 2 && first_card_disp == 14) || (second_card_disp > first_card_disp))
                {
                    while (!disp.isEmpty())
                    {
                        second_player.pushLow(disp.drawLow());
                    }
                }
                else
                {
                    //step++;
                    continue;
                }
                break;
            }
        }
        step++;
    }

    if (step >= STOP) 
    {
        std::cout << "unknown";
    }
    else if (first_player.isEmpty() && second_player.isEmpty()) 
    {
        std::cout << "draw";
    }
    else if (first_player.isEmpty()) 
    {
        std::cout << "second";
    }
    else if (second_player.isEmpty()) 
    {
        std::cout << "first";
     }
}
 
 
int main(int argc, char* argv[])
{
    int cards[MAX];
    for (int i = 0; i < MAX; i++)
    {
        cards[i] = 0;
    }

    std::ifstream inputFile(argv[1]);
    //std::ifstream inputFile("input0.txt");

    char line[10];
    Deck firstPlayer(DECK);
    Deck secondPlayer(DECK);

    if (!inputFile.is_open())
    {
        std::cout << "Error" << '\n';
        return -1;
    }

    int counter = 0;

   while (inputFile.getline(line, 10) && counter < MAX)
    {
        char letter = line[0];
        int value = 0;

        switch (letter)
        {
        case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9':
            value = letter - '0';
            break;
        case '1':
            value = 10;
            break;
        case 'J':
            value = 11;
            break;
        case 'Q':
            value = 12;
            break;
        case 'K':
            value = 13;
            break;
        case 'A':
            value = 14;
            break;
        }

        cards[counter] = value;
        counter++;
    }


    for (int i = 0; i < DECK; i++)
    {
        if (i < DECK/2)
        {
            firstPlayer.pushLow(cards[i]);
        }
        else
        {
            secondPlayer.pushLow(cards[i]);
        }
    }

    game(firstPlayer, secondPlayer);

    inputFile.close();

    return 0;
}