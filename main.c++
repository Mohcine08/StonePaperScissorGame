#include <iostream>
#include <time.h>
#include <limits>
using namespace std;
enum enStonePaperScissor{ Stone =1 , Paper = 2 , scissor = 3};
enum enWinner {ComputerWon =1 , NoWinner =2 , PlayerWon = 3};
struct stRoundInfo 
{
    
    enStonePaperScissor PlayerChoice ;
    enStonePaperScissor ComputerChioce ;
    enWinner RoundWinner;

};
struct stGameinfo
{
    stRoundInfo RoundInfo;
    short NumberOfRounds=0;
    short NumberOfPlayerWons =0;
    short NumberOfDraws = 0;
    short NumberOfComputerWon=0;
    enWinner FinalWinner;
};
int ReadRandomNumbers(short from, short to)
{
    return rand() % (to - from +1) + from;
}
string PrintWinner(enWinner Winner)
{
    string W[3] ={"Computer","No Winner" , "Player"};
    return W[Winner - 1];
}
string PrintStonePaperScissor(enStonePaperScissor choice)
{
    string ensomble[3] = {"Stone","Paper","scissor"};
    return ensomble[choice -1];
}
enStonePaperScissor GetStonePaperScissor()
{
    return (enStonePaperScissor)ReadRandomNumbers(1,3);
}
void SetScreenColor(enWinner Result)
{
    switch (Result)
    {
    case  enWinner::PlayerWon:
        system("color 2F");
        break;
    case enWinner::ComputerWon:
        system("color 4F");
        break;
    case enWinner::NoWinner:
        system("color 6F");
        break;
    }
}
enWinner LogicGame(stRoundInfo RoundInfo)
{
    if(RoundInfo.PlayerChoice == RoundInfo.ComputerChioce)
    {
       return enWinner::NoWinner;
    }
    else if(RoundInfo.PlayerChoice == enStonePaperScissor::Paper)
    {
        if(RoundInfo.ComputerChioce == enStonePaperScissor::Stone)
        {
           return enWinner::PlayerWon;
        }
    }
    else if(RoundInfo.PlayerChoice == enStonePaperScissor::scissor)
    {
        if(RoundInfo.ComputerChioce == enStonePaperScissor::Paper)
        {
            return enWinner::PlayerWon;
        }
    }
    else if(RoundInfo.PlayerChoice == enStonePaperScissor::Stone)
    {
        if(RoundInfo.ComputerChioce == enStonePaperScissor::scissor)
        {
            return enWinner::PlayerWon;
        }
    }
    
    return enWinner::ComputerWon;
}
enStonePaperScissor ReadPlayerChoice()
{
    int playerChoice;
    cin >> playerChoice;
    return (enStonePaperScissor)playerChoice;
}
void PrintRoundResult(stGameinfo GameInfo, short NumberOfRound)
{
    printf("\n_____________Round[%d]_____________\n",NumberOfRound);
    cout << "Player Choice : " << PrintStonePaperScissor(GameInfo.RoundInfo.PlayerChoice) << "\n";
    cout << "Computer Chioce : " << PrintStonePaperScissor(GameInfo.RoundInfo.ComputerChioce) << "\n";
    cout << "Round winner : [" << PrintWinner(GameInfo.RoundInfo.RoundWinner) << endl << endl;
}
int ReadHowManyRounds()
{
    int NumberOfRounds=0;
    do
    {
        cout << "please enter how many rounds do you want to play from 1 to 10 ?  ";
        cin >> NumberOfRounds;
         while(cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "invalid number,please enter how many rounds do you want to play from 1 to 10 ?  ";
            cin >> NumberOfRounds;
        }
    }while(NumberOfRounds <= 1 || NumberOfRounds >= 10);

    return NumberOfRounds;
}
void GenerateRound(stGameinfo &GameInfo, short NumberOfRound)
{
    
    printf("\nRound [%d] begins :\n",NumberOfRound);
    cout << "\nYour choice: [1]Stone , [2]Paper , [3]scissor ? ";
    GameInfo.RoundInfo.PlayerChoice = ReadPlayerChoice();
    GameInfo.RoundInfo.ComputerChioce = GetStonePaperScissor();
    GameInfo.RoundInfo.RoundWinner = LogicGame(GameInfo.RoundInfo);
    PrintRoundResult(GameInfo,NumberOfRound);
    SetScreenColor(GameInfo.RoundInfo.RoundWinner);
    switch(GameInfo.RoundInfo.RoundWinner)
        {
            case enWinner::PlayerWon :
            GameInfo.NumberOfPlayerWons++;
            break;
            case enWinner::ComputerWon :
            GameInfo.NumberOfComputerWon++;
            break;
            default:
            GameInfo.NumberOfDraws++;
        }
}
void GenerateRounds(stGameinfo &GameInfo)
{
    for(short NumberOfRound = 1; NumberOfRound <= GameInfo.NumberOfRounds; NumberOfRound++ )
    {
        GenerateRound(GameInfo,NumberOfRound);
    }

    if(GameInfo.NumberOfPlayerWons >= GameInfo.NumberOfComputerWon)
    {
        GameInfo.FinalWinner = enWinner::PlayerWon;
    }
    else if(GameInfo.NumberOfComputerWon >= GameInfo.NumberOfPlayerWons)
    {
        GameInfo.FinalWinner = enWinner::ComputerWon;
    }
    else
    {
        GameInfo.FinalWinner = enWinner::NoWinner;
    }
}
void RestScreen()
{
    system("cls");
    system("color 0F");
}
void PrintFinalResult(stGameinfo GameInfo)
{
    cout << "\n_______________________________________\n";
    cout << "\t\t +++ Game Over +++\n";
    cout << "_______________________________________\n";
    cout << "_____________[Game Result]_____________\n";
    cout << "Game Rounds         :" << GameInfo.NumberOfRounds << '\n';
    cout << "Player won times    :" << GameInfo.NumberOfPlayerWons << '\n';
    cout << "Computer Won times  :" << GameInfo.NumberOfComputerWon << '\n';
    cout << "Draw times          :" << GameInfo.NumberOfDraws << '\n';
    cout << "Final Winner        :" << PrintWinner(GameInfo.FinalWinner);
    cout << endl;
}
void PlayGame()
{
    stGameinfo GameInfo;
    GameInfo.NumberOfRounds = ReadHowManyRounds();
    GenerateRounds(GameInfo);
    PrintFinalResult(GameInfo);
}
void StartGame()
{
    char PlayMore = 'y';
    while (PlayMore == 'Y' || PlayMore == 'y')
    {
        RestScreen();
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