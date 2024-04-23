#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <fstream>
#include <chrono>
#include <string>
#include <thread>
using namespace std;

//I used a YouTube video to help me with the timer. https://www.youtube.com/watch?v=oEx5vGNFrLk&list=WL&index=8&t=512s
//This class acts as the timer.
class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> START, STOP;
    std::chrono::duration<float> TIME{};
    bool isRunning;
    float finalTime = 0.00f;

public:
    Timer()
    {
        isRunning = false;
    }
    void start()
    {
        if(!isRunning)
        {
            START = std::chrono::high_resolution_clock::now();
            isRunning = true;
        }
    }
    void stop()
    {
        if(isRunning)
        {
            STOP = std::chrono::high_resolution_clock::now();
            TIME = STOP - START;
            finalTime = TIME.count();
            isRunning = false;
        }
    }
    float getTime() const
    {
        return finalTime;
    }
    ~Timer() = default;
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

// Merge sort function
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

//Quick sort function
void quickSort(std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> &vec, int low, int high)
{
    if(low < high)
    {
        int pivot = partition(vec, low, high);
        quickSort(vec, low, pivot - 1);
        quickSort(vec, pivot + 1, high);
    }
}

//Helper function for checking if a string exists anywhere in a name
bool searchName(const string& name1, const string& name2) {
    unsigned int len1 = name1.size();
    unsigned int len2 = name2.size();
    if(len2 >= len1) {
        for(int i = 0; i < len2 - len1 + 1; i++) {
            if (name2.substr(i, len1) == name1) {
                return true;
            }
        }
    }
    return false;
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
    float msTime, qsTime;
    std::ifstream inFile;
    std::stringstream inLine;
    inFile.open("playerList.txt");
    while(std::getline(inFile, line))
    {
        inLine.clear();
        inLine.str(line);
        std::getline(inLine, name, '_');
        std::getline(inLine, school, '_');
        std::getline(inLine, conference, '_');
        std::getline(inLine, tempRank, '_');
        rank = std::stoi(tempRank);
        std::getline(inLine, position);
        msPlayers.emplace_back(name, school, rank, position, conference);
        qsPlayers.emplace_back(name, school, rank, position, conference);
    }
    inFile.close();

    Timer timer;
    timer.start();
    mergeSort(msPlayers, 0, (int) msPlayers.size() - 1);
    timer.stop();
    msTime = timer.getTime();
    std::cout << "Merge sort time: " << msTime << " seconds" << "\n";

    timer.start();
    quickSort(qsPlayers, 0, (int) qsPlayers.size() - 1);
    timer.stop();
    qsTime = timer.getTime();
    std::cout << "Quick sort time: " << qsTime << " seconds" << "\n";

    string input;
    string input_char;

    while (true){
        cout << "\n" << "Best College Football Players" << endl;
        cout << "Select one of the sorting choices:" << endl;
        cout << "1. By School" << endl;
        cout << "2. By Conference" << endl;
        cout << "3. By Position" << endl;
        cout << "4. Overall" << endl;
        cout << "5. Search" << endl;
        cout << "6. Close Program" << endl;
        getline(cin, input_char);
        try
        {
            stoi(input_char);
        }
        catch(...)
        {
            cout << "Invalid input" << "\n";
            continue;
        }
        // Search by school
        if (stoi(input_char) == 1){
            cout << "Input a School: (Ex. University of Florida)" << endl;
            getline(cin, input);
            // Ask for input
            std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> player_rank;
            int temp_rank = 1;

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
                // If temp rank never iterated
                cout << "School not Found" << endl;
            }
            else {
                // Output the top 3 results for the given school
                cout << "--Top 3 Players at " << input << "--" << endl;
                for (unsigned int i = 0; i < 3; i++){
                    //Iterates over the top 3 players in the list
                    name = get<0>(player_rank[i]);
                    school = get<1>(player_rank[i]);
                    rank = get<2>(player_rank[i]);
                    position = get<3>(player_rank[i]);
                    conference = get<4>(player_rank[i]);
                    cout << "School Rank: " << (i + 1) << endl;
                    cout << "Overall Rank: " << rank << endl;
                    cout << "Name: " << name << endl;
                    cout << "Position: " << position << endl;
                    cout << "School: " << school << endl;
                    cout << "Conference: " << conference << endl << endl;
                }
                // Output the total number of players for the school
                unsigned int numRanked = player_rank.size();
                cout << input << " has " << numRanked << " ranked players." << endl;
            }
        }

        // Search by conference
        else if (stoi(input_char) == 2){
            cout << "Input a Conference: (Ex. Southeastern Conference)" << endl;
            getline(cin, input);
            std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> player_rank;
            int temp_rank = 1;

            for(auto i: qsPlayers)
            {
                //Check for matching conference
                if ((get<4>(i) == input) and (temp_rank < 4)){
                    name = get<0>(i);
                    school = get<1>(i);
                    rank = get<2>(i);
                    position = get<3>(i);
                    conference = get<4>(i);
                    player_rank.emplace_back(name, school, rank, position, conference);
                    temp_rank += 1;
                }
            }
            // If temp_rank never iterated
            if(temp_rank == 1) {
                cout << "Conference not Found" << endl;
            }
            else {
                // Output first three results
                cout << "--Top 3 Players from ";
                if (input == "Independent") {
                    cout << input << " Schools--" << endl;
                }
                else {
                    cout << "the " << input << "--" << endl;
                }
                for (unsigned int i = 0; i < 3; i++){
                    //Iterates over the top 3 players in the list
                    name = get<0>(player_rank[i]);
                    school = get<1>(player_rank[i]);
                    rank = get<2>(player_rank[i]);
                    position = get<3>(player_rank[i]);
                    conference = get<4>(player_rank[i]);
                    cout << "Conference Rank: " << (i + 1) << endl;
                    cout << "Overall Rank: " << rank << endl;
                    cout << "Name: " << name << endl;
                    cout << "Position: " << position << endl;
                    cout << "School: " << school << endl;
                    cout << "Conference: " << conference << endl << endl;
                }
            }
        }

        // Position search
        else if (stoi(input_char) == 3){
            cout << "Input a Position: (Ex. QB)" << endl;
            getline(cin, input);
            std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> player_rank;
            int temp_rank = 1;

            for(auto i: qsPlayers)
            {
                //Check for matching position, up to third result
                if ((get<3>(i) == input) and (temp_rank < 4)){
                    name = get<0>(i);
                    school = get<1>(i);
                    rank = get<2>(i);
                    position = get<3>(i);
                    conference = get<4>(i);
                    player_rank.emplace_back(name, school, rank, position, conference);
                    temp_rank += 1;
                }
            }

            // If temp_rank never iterated
            if(temp_rank == 1) {
                cout << "Position not Found" << endl;
            }
            else {
                // Output top three results
                cout << "--Top 3 Players at the " << input << " position--" << endl;
                for(unsigned int i = 0; i < 3; i++) {
                    name = get<0>(player_rank[i]);
                    school = get<1>(player_rank[i]);
                    rank = get<2>(player_rank[i]);
                    position = get<3>(player_rank[i]);
                    conference = get<4>(player_rank[i]);

                    cout << "Position Rank: " << (i + 1) << endl;
                    cout << "Overall Rank: " << rank << endl;
                    cout << "Name: " << name << endl;
                    cout << "Position: " << position << endl;
                    cout << "School: " << school << endl;
                    cout << "Conference: " << conference << endl << endl;
                }
            }
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
                cout << "Overall Rank: " << rank << endl;
                cout << "Name: " << name << endl;
                cout << "Position: " << position << endl;
                cout << "School: " << school << endl;
                cout << "Conference: " << conference << endl << endl;
            }
        }

        // In-depth search function
        else if (stoi(input_char) == 5) {
            cout << "Search by:" << endl;
            cout << "1. By Name" << endl;
            cout << "2. By Rank" << endl;
            cout << "3. By School" << endl;
            cout << "4. By Conference" << endl;
            cout << "5. Back to Main Menu" << endl;

            string searchInput;
            getline(cin, searchInput);
            try
            {
                stoi(searchInput);
            }
            catch(...)
            {
                cout << "Invalid input" << "\n";
                continue;
            }
            bool playerFound = false;

            // Search by name
            if(stoi(searchInput) == 1)
            {
                string nameSearch;
                std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> search_vec;

                cout << "Input a Name: " << endl;
                getline(cin, nameSearch);

                for(auto i : qsPlayers) {
                    // Check if the search exists anywhere in the string
                    if(searchName(nameSearch, get<0>(i))) {
                        playerFound = true;
                        name = get<0>(i);
                        school = get<1>(i);
                        rank = get<2>(i);
                        position = get<3>(i);
                        conference = get<4>(i);

                        search_vec.emplace_back(name, school, rank, position, conference);
                    }
                }

                // If any players matched
                if(playerFound) {
                    string numPlayers;
                    int numTop;
                    cout << "How many players do you want to see?" << "\n";
                    getline(cin, numPlayers);
                    try
                    {
                        numTop = stoi(numPlayers);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << "\n";
                        continue;
                    }
                    // Return first results as chosen by the user
                    unsigned int first = min((unsigned int) search_vec.size(), (unsigned int) numTop);
                    cout << "--" << "First " << first << " Results for: \"" << nameSearch << "\"--" << endl;
                    cout << "(" << search_vec.size() << " results)" << endl;
                    for(unsigned int i = 0; i < first; i++) {
                        cout << "Full Name: " << get<0>(search_vec[i]) << endl;
                        cout << "Overall Rank: " << get<2>(search_vec[i]) << endl;
                        cout << "Position: " << get<3>(search_vec[i]) << endl;
                        cout << "School: " << get<1>(search_vec[i]) << endl;
                        cout << "Conference: " << get<4>(search_vec[i]) << endl << endl;
                    }

                    // Prompt to see all results
                    cout << "Show All Results?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    string moreInput;
                    getline(cin, moreInput);
                    try
                    {
                        stoi(moreInput);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << endl;
                        continue;
                    }
                    if(stoi(moreInput) != 1 and stoi(moreInput) != 2) {
                        cout << "Invalid input" << endl << endl;
                    }
                    else if(stoi(moreInput) == 1) {
                        for(auto i : search_vec) {
                            cout << "Full Name: " << get<0>(i) << endl;
                            cout << "Overall Rank: " << get<2>(i) << endl;
                            cout << "Position: " << get<3>(i) << endl;
                            cout << "School: " << get<1>(i) << endl;
                            cout << "Conference: " << get<4>(i) << endl << endl;
                        }
                    }
                    else if(stoi(moreInput) == 2) {
                        continue;
                    }
                }
                else {
                    cout << "Name not Found" << endl;
                }
            }
            else if(stoi(searchInput) == 2)
            {
                string numPlayers;
                cout << "1. Get a Single Player" << endl;
                cout << "2. Get Multiple Players" << endl;
                getline(cin, numPlayers);
                try
                {
                    stoi(numPlayers);
                }
                catch(...)
                {
                    cout << "Invalid input" << endl << endl;
                    continue;
                }
                if(stoi(numPlayers) == 1)
                {
                    string rankSearch;
                    cout << "Input a Rank: " << endl;
                    getline(cin, rankSearch);
                    try
                    {
                        stoi(rankSearch);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << endl << endl;
                        continue;
                    }

                    int rankNum = stoi(rankSearch);

                    // Can simply check the player at position rank, since the vector is already sorted.
                    if (rankNum <= 100000 && rankNum > 0) {
                        cout << "Player at Rank " << rankSearch << ":" << endl;
                        cout << "Name: " << get<0>(qsPlayers[rankNum - 1]) << endl;
                        cout << "Position: " << get<3>(qsPlayers[rankNum - 1]) << endl;
                        cout << "School: " << get<1>(qsPlayers[rankNum - 1]) << endl;
                        cout << "Conference: " << get<4>(qsPlayers[rankNum - 1]) << endl << endl;
                    }
                    else {
                        cout << "Rank not Found" << endl;
                    }
                }
                // Show top ranked players based on user input
                else if(stoi(numPlayers) == 2)
                {
                    string topPlayers;
                    int numTop;
                    cout << "How many players do you want to see?" << endl;
                    getline(cin, topPlayers);
                    try
                    {
                        numTop = stoi(topPlayers);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << endl << endl;
                        continue;
                    }
                    unsigned int first = min((unsigned int) qsPlayers.size(), (unsigned int)numTop);
                    cout << "--Top " << first << " Players-- " << endl;
                    for(unsigned int i = 0; i < first; i++) {
                        cout << "Full Name: " << get<0>(qsPlayers[i]) << endl;
                        cout << "Overall Rank: " << get<2>(qsPlayers[i]) << endl;
                        cout << "Position: " << get<3>(qsPlayers[i]) << endl;
                        cout << "School: " << get<1>(qsPlayers[i]) << endl;
                        cout << "Conference: " << get<4>(qsPlayers[i]) << endl << endl;
                    }

                    cout << "Show All Results?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    string moreInput;
                    getline(cin, moreInput);
                    try
                    {
                        stoi(moreInput);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << endl << endl;
                        continue;
                    }
                    if(stoi(moreInput) != 1 and stoi(moreInput) != 2) {
                        cout << "Invalid input" << endl << endl;
                    }
                    // Show all results
                    else if(stoi(moreInput) == 1) {
                        for(auto i : qsPlayers) {
                            cout << "Full Name: " << get<0>(i) << endl;
                            cout << "Overall Rank: " << get<2>(i) << endl;
                            cout << "Position: " << get<3>(i) << endl;
                            cout << "School: " << get<1>(i) << endl;
                            cout << "Conference: " << get<4>(i) << endl << endl;
                        }
                    }
                    // Return to menu
                    else if(stoi(moreInput) == 2) {
                        continue;
                    }
                }
                else
                {
                    cout << "Invalid input" << endl << endl;
                    continue;
                }
            }
            // Search school by keyword
            else if(stoi(searchInput) == 3)
            {
                string schoolSearch;
                std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> search_vec;
                bool schoolFound = false;

                cout << "Search for a School:" << endl;
                getline(cin, schoolSearch);

                // If the search term exists anywhere in the school name, add it to search_vec
                for(auto i : qsPlayers) {
                    if(searchName(schoolSearch, get<1>(i)))
                    {
                        schoolFound = true;
                        name = get<0>(i);
                        school = get<1>(i);
                        rank = get<2>(i);
                        position = get<3>(i);
                        conference = get<4>(i);

                        search_vec.emplace_back(name, school, rank, position, conference);
                    }
                }
                // If any players were found
                if(schoolFound)
                {
                    string numPlayers;
                    int numTop;
                    cout << "How many players do you want to see?" << "\n";
                    getline(cin, numPlayers);
                    try
                    {
                        numTop = stoi(numPlayers);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << endl;
                        continue;
                    }
                    // Show first results
                    unsigned int first = min((unsigned int) search_vec.size(), (unsigned int)numTop);
                    cout << "--First " << first << " Results for: \"" << schoolSearch << "\"--" << endl;
                    cout << "(" << search_vec.size() << " results)" << endl;
                    for(unsigned int i = 0; i < first; i++) {
                        cout << "Full Name: " << get<0>(search_vec[i]) << endl;
                        cout << "Overall Rank: " << get<2>(search_vec[i]) << endl;
                        cout << "Position: " << get<3>(search_vec[i]) << endl;
                        cout << "School: " << get<1>(search_vec[i]) << endl;
                        cout << "Conference: " << get<4>(search_vec[i]) << endl << endl;
                    }

                    cout << "Show All Results?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    string moreInput;
                    getline(cin, moreInput);
                    try
                    {
                        stoi(moreInput);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << endl;
                        continue;
                    }

                    if(stoi(moreInput) != 1 && stoi(moreInput) != 2) {
                        cout << "Invalid input" << endl << endl;
                    }
                    // Show all results
                    else if(stoi(moreInput) == 1) {
                        for(auto i : search_vec) {
                            cout << "Full Name: " << get<0>(i) << endl;
                            cout << "Overall Rank: " << get<2>(i) << endl;
                            cout << "Position: " << get<3>(i) << endl;
                            cout << "School: " << get<1>(i) << endl;
                            cout << "Conference: " << get<4>(i) << endl << endl;
                        }
                    }
                    // Return to menu
                    else if(stoi(moreInput) == 2) {
                        continue;
                    }
                }
                // Search result not found
                else {
                    cout << "School Not Found" << endl;
                }
            }
            // Search by keyword for conference
            else if(stoi(searchInput) == 4)
            {
                string conferenceSearch;
                std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> search_vec;
                bool conferenceFound = false;

                cout << "Search for a Conference:" << endl;
                getline(cin, conferenceSearch);

                // Check if the search term exists anywhere in the conference name
                for(auto i : qsPlayers) {
                    if(searchName(conferenceSearch, get<4>(i)))
                    {
                        conferenceFound = true;
                        name = get<0>(i);
                        school = get<1>(i);
                        rank = get<2>(i);
                        position = get<3>(i);
                        conference = get<4>(i);

                        search_vec.emplace_back(name, school, rank, position, conference);
                    }
                }
                // If results were found
                if(conferenceFound)
                {
                    string numPlayers;
                    int numTop;
                    cout << "How many players do you want to see?" << endl;
                    getline(cin, numPlayers);
                    try
                    {
                        numTop = stoi(numPlayers);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << endl;
                        continue;
                    }
                    // Show first choices as asked by user, or show all if there are less than asked.
                    unsigned int first = min((unsigned int) search_vec.size(), (unsigned int)numTop);
                    cout << "--First " << first << " Results for: \"" << conferenceSearch << "\"--" << endl;
                    cout << "(" << search_vec.size() << " results)" << endl;
                    for(unsigned int i = 0; i < first; i++) {
                        cout << "Full Name: " << get<0>(search_vec[i]) << endl;
                        cout << "Overall Rank: " << get<2>(search_vec[i]) << endl;
                        cout << "Position: " << get<3>(search_vec[i]) << endl;
                        cout << "School: " << get<1>(search_vec[i]) << endl;
                        cout << "Conference: " << get<4>(search_vec[i]) << endl << endl;
                    }

                    cout << "Show All Results?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    string moreInput;
                    getline(cin, moreInput);
                    try
                    {
                        stoi(moreInput);
                    }
                    catch(...)
                    {
                        cout << "Invalid input" << "\n";
                        continue;
                    }

                    if(stoi(moreInput) != 1 && stoi(moreInput) != 2) {
                        cout << "Invalid input" << endl << endl;
                    }

                    // Show all results
                    else if(stoi(moreInput) == 1) {
                        for(auto i : search_vec) {
                            cout << "Full Name: " << get<0>(i) << endl;
                            cout << "Overall Rank: " << get<2>(i) << endl;
                            cout << "Position: " << get<3>(i) << endl;
                            cout << "School: " << get<1>(i) << endl;
                            cout << "Conference: " << get<4>(i) << endl << endl;
                        }
                    }
                    // Return to menu
                    else if(stoi(moreInput) == 2) {
                        continue;
                    }
                }
                else {
                    cout << "School Not Found" << endl;
                }
            }
            // Return to menu 
            else if(stoi(searchInput) == 5) {
                continue;
            }
            else {
                cout << "Invalid input" << endl << endl;
            }
        }

        // End program
        else if (stoi(input_char) == 6){
            cout << "Thank you for using our program, goodbye." << "\n";
            break;
        }

        else{
            cout << "Invalid input" << endl << endl;
        }
    }
    std::this_thread::sleep_for(1.5s);
    return 0;
}
