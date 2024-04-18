#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>

//Global varables that keep track of the time for the time it takes for merge sort (msTime) and the time it takes for
//quick sort (qsTime).
float msTime = 0.00f, qsTime = 0.00f;

//IT'S VERY IMPORTANT THAT THE TWO TIMER CLASSES ARE THE ONLY ENTITIES WHO CHANGE THE TWO GLOBAL VARIABLES.
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

//The following two functions are for merge sort and are taken from the discussion slides, "Disscusion 12: Final Review", #32.
std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> merge(std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> &left,
                                                                                       std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> &right)
{
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> result;
    while(!left.empty() && !right.empty())
    {
        if(std::get<2>(left[0]) <= std::get<2>(right[0]))
        {
            result.push_back(left[0]);
            left.erase(left.begin());
        }
        else
        {
            result.push_back(right[0]);
            right.erase(right.begin());
        }
    }
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}

std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> mergeSort(std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> &vec)
{
    if(vec.size() <= 1)
    {
        return vec;
    }
    int mid = (int) vec.size()/2;
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> left(vec.begin(), vec.begin() + mid);
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> right(vec.begin() + mid, vec.end());
    left = mergeSort(left);
    right = mergeSort(right);
    return merge(left, right);
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
    std::thread ms
    ([&msPlayers](){
        msTimer timer;
        msPlayers = mergeSort(msPlayers);
    });

    std::thread qs
    ([&qsPlayers](){
        qsTimer timer;
        quickSort(qsPlayers, 0, (int) qsPlayers.size() - 1);
    });
    ms.join();
    qs.join();

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