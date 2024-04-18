#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

//Global varables that keep track of the time for the time it takes for merge sort (msTime) and the time it takes for
//quick sort (qsTime).
float msTime = 0.00f, qsTime = 0.00f;

//IT'S VERY IMPORTANT THAT THE TWO TIMER CLASSES ARE THE ONLY ENTITIES WHO CHANGE THE TWO GLOBAL VARIABLES.
//I used a YouTube video to help me with the timer. https://www.youtube.com/watch?v=oEx5vGNFrLk&list=WL&index=8&t=512s
//This class times merge sort.
class msTimer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> START, STOP;
    std::chrono::duration<float> TIME{};
public:
    msTimer()
    {
        START = std::chrono::high_resolution_clock::now();
    }
    ~msTimer()
    {
        STOP = std::chrono::high_resolution_clock::now();
        TIME = STOP - START;
        msTime = TIME.count();
    }
};

//This class times quick sort.
class qsTimer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> START, STOP;
    std::chrono::duration<float> TIME{};
public:
    qsTimer()
    {
        START = std::chrono::high_resolution_clock::now();
    }
    ~qsTimer()
    {
        STOP = std::chrono::high_resolution_clock::now();
        TIME = STOP - START;
        qsTime = TIME.count();
    }
};

//The following two functions are for merge sort and are taken from Professor's slides, "6-Sorting", #89 & #90.
void merge(std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> &vec, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> X(n1);
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> Y(n2);
    for(int i = 0; i < n1; i++)
    {
        X[i] = vec[left + i];
    }
    for(int j = 0; j < n2; j++)
    {
        Y[j] = vec[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2)
    {
        if(std::get<2>(X[i]) <= std::get<2>(Y[j]))
        {
            vec[k] = X[i];
            i++;
        }
        else
        {
            vec[k] = Y[j];
            j++;
        }
        k++;
    }
    while(i < n1)
    {
        vec[k] = X[i];
        i++;
        k++;
    }
    while(j < n2)
    {
        vec[k] = Y[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> &vec, int left, int right)
{
    if(left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

//The following two functions are for quick sort and are taken from Professor's slides, "6-Sorting", #122.
int partition(std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> &vec, int low, int high)
{
    std::tuple<std::string, std::string, int, std::string, std::string> pivot = vec[low];
    int up = low, down = high;
    while(up < down)
    {
        for(int i = up; i < high; i++)
        {
            if(std::get<2>(vec[up]) > std::get<2>(pivot))
            {
                break;
            }
            up++;
        }
        for(int i = high; i > low; i--)
        {
             if(std::get<2>(vec[down]) < std::get<2>(pivot))
             {
                 break;
             }
             down--;
        }
        if(up < down)
        {
            std::swap(vec[up], vec[down]);
        }
    }
    std::swap(vec[low], vec[down]);
    return down;
}

void quickSort(std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> &vec, int low, int high)
{
    if(low < high)
    {
        int pivot = partition(vec, low, high);
        quickSort(vec, low, pivot - 1);
        quickSort(vec, pivot + 1, high);
    }
}

int main()
{
    //This following chunk of code takes the 100k data points from playerList.txt and parses them into two separate vector, one for merge sort and one for quick sort.
    //I used a YouTube video to help me with file i/o. https://www.youtube.com/watch?v=RHngWtyEtTs&list=WL&index=9&t=564s
    //Name School Rank Position Division
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> msPlayers;
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> qsPlayers;
    std::string name, school, position, conference, tempRank, line;
    int rank;
    std::ifstream inFile;
    std::stringstream inLine;
    inFile.open("playerList.txt");
    while(std::getline(inFile, line))
    {
        inLine.clear();
        inLine.str(line);
        std::getline(inLine, name, '_');
        std::getline(inLine, school, '_');
        std::getline(inLine, tempRank, '_');
        rank = std::stoi(tempRank);
        std::getline(inLine, position, '_');
        std::getline(inLine, conference);
        msPlayers.emplace_back(name, school, rank, position, conference);
        qsPlayers.emplace_back(name, school, rank, position, conference);
    }
    inFile.close();

    //Two separate threads do the sorting for each vector, one does merge sort and the other does quick sort.
    //I used this website to help me with multithreading and lambda functions. https://www.bogotobogo.com/cplusplus/C11/3_C11_Threading_Lambda_Functions.php
    std::thread ms
    ([&msPlayers](){
        msTimer timer;
        mergeSort(msPlayers, 0, (int) msPlayers.size() - 1);
    });

    std::thread qs
    ([&qsPlayers](){
        qsTimer timer;
        quickSort(qsPlayers, 0, (int) qsPlayers.size() - 1);
    });
    ms.join();
    qs.join();
/*
    std::cout << msTime << " " << msPlayers.size() << "\n";
    std::cout << qsTime << " " << qsPlayers.size() << "\n";
    for(auto i: msPlayers)
    {
        std::cout << std::get<2>(i) << "\n";
    }*/


    string input;
    string input_char;
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> player_rank;

    while (true){
        cout << "Best College Football Players" << endl << "Select one of the sorting choices:" << endl;
        cout << "1. By School" << endl << "2. By Conference" << endl << "3. By Position" << endl << "4. Overall" << endl << "5. Close Program" << endl;
        getline(cin, input_char);
        int temp_rank = 1;
        if (stoi(input_char) == 1){
            cout << "Input a School: (Ex. University of Florida)" << endl;
            getline(cin, input);

            for(auto i: qsPlayers)
            {//Name School Rank Position Division
                //Check for matching school
                if ((get<1>(i) == input) and (temp_rank < 4)){
                    name = get<0>(i);
                    school = get<1>(i);
                    rank = get<2>(i);
                    position = get<3>(i);
                    conference = get<4>(i);
                    player_rank.emplace_back(name, school, rank, position, conference);
                    temp_rank += 1;
                }}

            if (temp_rank == 1){
                cout << "School not Found" << endl;
            }
            else{
                cout << "--Top 3 Players at " << input << "--" << endl;
                for (unsigned int i = 0; i < 3; i++){
                    //Iterates over the top 3 players in the list
                    name = get<0>(player_rank[i]);
                    school = get<1>(player_rank[i]);
                    rank = get<2>(player_rank[i]);
                    position = get<3>(player_rank[i]);
                    conference = get<4>(player_rank[i]);
                    cout << "School Rank: " << (i + 1) << endl << "Overall Rank: " << rank << endl << "Name: " << name << endl << "Position: " << position << endl;
                    cout << "School: " << school << endl << "Conference: " << conference << endl << endl;
                }}}

        else if (stoi(input_char) == 2){
            cout << "Input a Conference: (Ex. SEC)" << endl;
            cin >> input;
            //cout << "Input: " << input << endl;
        }
        else if (stoi(input_char) == 3){
            cout << "Input a Position: (Ex. QB)" << endl;
            cin >> input;
            //cout << "Input: " << input << endl;
        }
        else if (stoi(input_char) == 4){
            //Print top 3 players overall
            cout << "--Top 3 Players Overall--" << endl;
            for (unsigned int i = 0; i < 3; i++){
                //Iterates over the top 3 players in the list
                name = get<0>(qsPlayers[i]);
                school = get<1>(qsPlayers[i]);
                rank = get<2>(qsPlayers[i]);
                position = get<3>(qsPlayers[i]);
                conference = get<4>(qsPlayers[i]);
                cout << "Overall Rank: " << rank << endl << "Name: " << name << endl << "Position: " << position << endl;
                cout << "School: " << school << endl << "Conference: " << conference << endl << endl;
            }}
        else if (stoi(input_char) == 5){
            break;
        }
        else{
            cout << "Invalid Input" << endl << endl;
        }

    }





    /*std::cout << msTime << " " << msPlayers.size() << "\n";
    std::cout << qsTime << " " << qsPlayers.size() << "\n";
    for(auto i: msPlayers)
    {
        std::cout << std::get<2>(i) << "\n";
    }
    std::cout << "\n";

    for(auto i: qsPlayers)
    {
        std::cout << std::get<0>(i) << "\n";
    }*/
    return 0;
}