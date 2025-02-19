#include <iostream>
#include <time.h>
#include <limits>
using namespace std;
enum enGameChoice{ Stone =1 , Paper = 2 , Scissor = 3};
enum enWinner {Computer =1 , NoWinner =2 , Player = 3};
struct stRoundInfo 
{
    enGameChoice PlayerChoice ;
    enGameChoice ComputerChioce ;
    enWinner RoundWinner;
};
struct stGameResults
{
    short GameRoumds=0;
    short PlayerWonTimes =0;
    short DrawTimes = 0;
    short ComputerWonTimes=0;
    enWinner FinalWinner;
};
int ReadRandomNumbers(short from, short to)
{
    return rand() % (to - from +1) + from;
}
string WinnerName(enWinner Winner)
{
    string W[3] ={"Computer","No Winner" , "Player"};
    return W[Winner - 1];
}
string ChoiceName(enGameChoice choice)
{
    string ensomble[3] = {"Stone","Paper","Scissor"};
    return ensomble[choice -1];
}
enGameChoice GetComputerChoice()
{
    return (enGameChoice)ReadRandomNumbers(1,3);
}
void SetScreenColor(enWinner Result)
{
    switch (Result)
    {
    case  enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    case enWinner::NoWinner:
        system("color 6F");
        break;
    }
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if(RoundInfo.PlayerChoice == RoundInfo.ComputerChioce)
    {
       return enWinner::NoWinner;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Paper :
        if(RoundInfo.ComputerChioce == enGameChoice::Stone)
        {
           return enWinner::Player;
        }
        break;
    case enGameChoice::Scissor :
        if(RoundInfo.ComputerChioce == enGameChoice::Paper)
        {
            return enWinner::Player;
        }
        break;
    case enGameChoice::Stone :
        if(RoundInfo.ComputerChioce == enGameChoice::Scissor)
        {
            return enWinner::Player;
        }
        break;
    }

    return enWinner::Computer;
}
enGameChoice ReadPlayerChoice(string message)
{
    int playerChoice;
    do
    {
        cout << message << "  ";
        cin >> playerChoice;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');
            cout << message;
            cin >> playerChoice;
        }
    } while (playerChoice < 1 || playerChoice > 3);
    
    return (enGameChoice)playerChoice;
}
void ShowRoundResults(stRoundInfo RoundInfo, short NumberOfRound)
{
    printf("\n_____________Round[%d]_____________\n",NumberOfRound);
    cout << "Player Choice : " << ChoiceName(RoundInfo.PlayerChoice) << "\n";
    cout << "Computer Chioce : " << ChoiceName(RoundInfo.ComputerChioce) << "\n";
    cout << "Round winner : [" << WinnerName(RoundInfo.RoundWinner) <<']';
    cout << "\n__________________________________\n";
    cout << endl;
}
short ReadHowManyRounds()
{
    short GameRoumds=0;
    do
    {
        cout << "please enter how many rounds do you want to play from 1 to 10 ?  ";
        cin >> GameRoumds;
         while(cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "please enter how many rounds do you want to play from 1 to 10 ?  ";
            cin >> GameRoumds;
        }
    }while(GameRoumds < 1 || GameRoumds > 10);

    return GameRoumds;
}
string Tabs(short NumberOfTabs)
{
    string t = "";
    for(short x = 0; x < NumberOfTabs; x++)
    {
        t += "\t";
    }
    return t;
}
void GenerateRound(stGameResults &GameResults, short NumberOfRound)
{
    stRoundInfo RoundInfo;

    printf("\nRound [%d] begins :\n\n",NumberOfRound);
    RoundInfo.PlayerChoice = ReadPlayerChoice("Your choice: [1]Stone , [2]Paper , [3]Scissor ?");
    RoundInfo.ComputerChioce = GetComputerChoice();
    RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
    ShowRoundResults(RoundInfo,NumberOfRound);
    SetScreenColor(RoundInfo.RoundWinner);
    switch(RoundInfo.RoundWinner)
        {
            case enWinner::Player :
            GameResults.PlayerWonTimes++;
            break;
            case enWinner::Computer :
            GameResults.ComputerWonTimes++;
            break;
            default:
            GameResults.DrawTimes++;
        }
}
enWinner WhoWonTheGame(stGameResults GameResults)
{
    if(GameResults.PlayerWonTimes > GameResults.ComputerWonTimes)
    {
        return enWinner::Player;
    }
    else if(GameResults.ComputerWonTimes > GameResults.PlayerWonTimes)
    {
        return enWinner::Computer;
    }
    else
    {
        return enWinner::NoWinner;
    }
}
void GenerateRounds(stGameResults &GameResults)
{
    for(short NumberOfRound = 1; NumberOfRound <= GameResults.GameRoumds; NumberOfRound++ )
    {
        GenerateRound(GameResults,NumberOfRound);
    }

    GameResults.FinalWinner =  WhoWonTheGame(GameResults);

}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void ShowFinalGameResults(stGameResults GameResults)
{
    cout << "\n";
    cout << Tabs(2) << "_______________________________________\n";
    cout << Tabs(3) << "+++ Game Over +++\n";
    cout << Tabs(2) << "_______________________________________\n";
    cout << Tabs(2) << "_____________[Game Result]_____________\n";
    cout << Tabs(2) << "Game Rounds         :" << GameResults.GameRoumds << '\n';
    cout << Tabs(2) << "Player won times    :" << GameResults.PlayerWonTimes << '\n';
    cout << Tabs(2) << "Computer Won times  :" << GameResults.ComputerWonTimes << '\n';
    cout << Tabs(2) << "Draw times          :" << GameResults.DrawTimes << '\n';
    cout << Tabs(2) << "Final Winner        :" << WinnerName(GameResults.FinalWinner) << '\n';
    cout << Tabs(2) << "_______________________________________\n";
    cout << endl;
}
void PlayGame()
{
    stGameResults GameResults;
    GameResults.GameRoumds = ReadHowManyRounds();
    GenerateRounds(GameResults);
    ShowFinalGameResults(GameResults);
}
void StartGame()
{
    char PlayMore = 'y';
    while (PlayMore == 'Y' || PlayMore == 'y')
    {
        ResetScreen();
        PlayGame();

        cout << "do you want to play again? Y/N ";
        cin >> PlayMore;
    }
}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
}