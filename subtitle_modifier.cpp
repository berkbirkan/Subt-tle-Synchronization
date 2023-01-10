#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

/*

Hello, my name is Nejmettin Berk Birkan and this is a simple program that modifies the timestamps in a subtitle file.

This program starts by checking if the number of command line arguments is less than 3, 
in which case it prints an error message and exits. Then it opens the input file and the output file. 

2)Next, it reads the input file line by line, and checks if each line contains the "-->" string which indicates the timestamp 
line, if it finds the timestamp line, it extracts the timestamps in hours, minutes, seconds, milliseconds and calculate the new
timestamp by adding or subtracting the time specified by the user. At last it writes the modified timestamp back to output file.

How to use this program:
Run the program with the following command in terminal:
1) g++ subtitle_modifier.cpp -o subtitle_modifier
2) ./subtitle_modifier subtitle.srt 3000

//Lets try to add 5000 milliseconds to the timestamps in the subtitle file.

*/

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <input_file.srt> <time_in_ms>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cout << "Error opening input file: " << argv[1] << std::endl;
        return 1;
    }

    std::string outputFileName = std::string(argv[1]) + ".modified";
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        std::cout << "Error opening output file: " << outputFileName << std::endl;
        return 1;
    }

    int timeInMs = std::atoi(argv[2]);
    std::string line;
    while (std::getline(inputFile, line)) {
        // Check if the line contains a timestamp
        size_t pos1 = line.find(" --> ");
        if (pos1 != std::string::npos) {
            // Split the line into two timestamps
            std::string timestamp1 = line.substr(0, pos1);
            std::string timestamp2 = line.substr(pos1 + 5);

            // Split the timestamps into hours, minutes, seconds, and milliseconds
            std::stringstream timestamp1Stream(timestamp1);
            std::string hour1, minute1, second1, milliseconds1;
            std::getline(timestamp1Stream, hour1, ':');
            std::getline(timestamp1Stream, minute1, ':');
            std::getline(timestamp1Stream, second1, ',');
            std::getline(timestamp1Stream, milliseconds1);

            std::stringstream timestamp2Stream(timestamp2);
            std::string hour2, minute2, second2, milliseconds2;
            std::getline(timestamp2Stream, hour2, ':');
            std::getline(timestamp2Stream, minute2, ':');
            std::getline(timestamp2Stream, second2, ',');
            std::getline(timestamp2Stream, milliseconds2);

            // Convert the timestamps to milliseconds
            int ms1 = std::atoi(hour1.c_str()) * 3600000 + std::atoi(minute1.c_str()) * 60000 + std::atoi(second1.c_str()) * 1000 + std::atoi(milliseconds1.c_str());
            int ms2 = std::atoi(hour2.c_str()) * 3600000 + std::atoi(minute2.c_str()) * 60000 + std::atoi(second2.c_str()) * 1000 + std::atoi(milliseconds2.c_str());

                    // Add or subtract the time specified by the user
            ms1 += timeInMs;
            ms2 += timeInMs;

            // Convert the timestamps back to hours, minutes, seconds, and milliseconds
            int newHour1 = ms1 / 3600000;
            int newMinute1 = (ms1 % 3600000) / 60000;
            int newSecond1 = (ms1 % 60000) / 1000;
            int newMilliseconds1 = ms1 % 1000;

            int newHour2 = ms2 / 3600000;
            int newMinute2 = (ms2 % 3600000) / 60000;
            int newSecond2 = (ms2 % 60000) / 1000;
            int newMilliseconds2 = ms2 % 1000;

            // Output the modified timestamps
            outputFile << newHour1 << ':' << newMinute1 << ':' << newSecond1 << ',' << newMilliseconds1 << " --> ";
            outputFile << newHour2 << ':' << newMinute2 << ':' << newSecond2 << ',' << newMilliseconds2 << std::endl;
        } else {
            // Output the line as is
            outputFile << line << std::endl;
        }
}

inputFile.close();
outputFile.close();

return 0;
}