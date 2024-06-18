#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <array>
#include <thread>
#include <chrono>
using std::cerr;
using std::endl;
using std::exit;


int readIntFromFile(const std::string& filePath){
    std::ifstream file(filePath);
    if(!file.is_open()){
        cerr<<"ERROR: Unsuccesful reading voltage file"<<endl;
        exit(-1);
    }
    // reads file to a2dreading
    int a2dreading = -1;
    file >> a2dreading;
    if(a2dreading != 0 && a2dreading != 1){
        cerr<<"ERROR: Obtained unexpected values from the file"<<endl;
        exit(-1);
    }
    file.close();
    return a2dreading;
}

void writeToFile(const std::string& filePath, std::string toWrite){
    std::ofstream file(filePath);
    if(!file.is_open()){
        cerr<<"ERROR: Failed to open file"<<endl;
        exit(-1);
    }
    // writes the string to file
    file << toWrite;
    if(file.fail()){
        cerr<<"ERROR: Failed to write to file"<<endl;
        exit(-1);
    }
    file.close();
}

void runCommand(const std::string& command) {
    try {
        // Execute the shell command (output into pipe)
        std::array<char, 128> buffer;
        std::string result;
        
        // Create a unique_ptr with a custom deleter (pclose)
        auto pipe = std::unique_ptr<FILE, decltype(&pclose)>(popen(command.c_str(), "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");

        // Ignore output of the command; but consume it
        // so we don't get an error when closing the pipe.
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
            // std::cout << "--> " << buffer.data(); // Uncomment for debugging
        }

        // Get the exit code from the pipe; non-zero is an error:
        int exitCode = WEXITSTATUS(pclose(pipe.release()));  // Release before calling pclose
        if (exitCode != 0) {
            cerr << "Unable to execute command: " << command << endl;
            cerr << "Exit code: " << exitCode << endl;
        }
    } catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

void sleepThread(unsigned int ms){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}