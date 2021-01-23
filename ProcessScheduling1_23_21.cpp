//MFQS Made by Sam Strecker 1/16/21

#include<stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

class Job {
public:
    int PID;
    int burst;
    int arrival;
    Job *nextJob;
    Job *prevJob;
    int age;

    void setPid(int pid);

    void setBurst(int burst);

    void setArrival(int arrival);

    void setPriority(int priority);

    int priority;

    int getPid() const {
        return PID;
    }

    int getBurst() const {
        return burst;
    }

    int getArrival() const {
        return arrival;
    }

    int getPriority() const {
        return priority;
    }

    Job() {
        nextJob = NULL;
        prevJob = NULL;
        age = 0;
    };

    Job(string line) {
        nextJob = NULL;
        prevJob = NULL;
        age = 0;
        char *tok;
        char char_array[99];
        strcpy(char_array, line.c_str());

        tok = strtok(char_array, "\t");
        setPid(stoi(tok));

        tok = strtok(NULL, "\t");
        setBurst(stoi(tok));

        tok = strtok(NULL, "\t");
        setArrival(stoi(tok));

        tok = strtok(NULL, "\t");
        setPriority(stoi(tok));
    }

    void printJob();
};

void Job::printJob() {
    cout << "This is the PID";
    cout << this->PID;
    cout << endl;
}

void Job::setPid(int pid) {
    PID = pid;
}

void Job::setBurst(int burst) {
    Job::burst = burst;
}

void Job::setArrival(int arrival) {
    Job::arrival = arrival;
}

void Job::setPriority(int priority) {
    Job::priority = priority;
};

string getJob(ifstream &, int);

Job *jobFill(string);

Job *dispatcher(Job *, Job *);

int main() {
    char *tok;
    Job *prevJob = nullptr;
    Job *currentJob = nullptr;
    Job *topJob = nullptr;
    Job *myJob = nullptr;

    char fileDirectory[99];
    int numQ = 0;
    int timeQuantum = 0;
    int ageInterval = 0;
    char tempArray[40];
    int clockCycle = 0;
    int totalJobCount = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int totalProcesses = 0;
    Job *Q1 = nullptr;
    Job *Q2, *Q3, *Q4, *F = nullptr;


    printf("\nEnter the test file directory:\t");
    scanf("%s", &fileDirectory);

    printf("Enter the number of queues:\t");
    scanf("%d", &numQ);

    printf("Enter time quantum for top queue:\t");
    scanf("%d", &timeQuantum);

    printf("Enter ageing interval:\t");
    scanf("%d", &ageInterval);

    int q1Time = timeQuantum;
    int q2Time = q1Time * 2;
    int q3Time = q2Time * 2;
    int q4Time = q3Time * 2;

    sprintf(tempArray, "sort -g -k 3,3 %s > 1M.sorted", fileDirectory);

    //cout << tempArray;
    //"sort -g -k 3,3 + /Users/buckgup/Downloads/1M > 1M.sorted"

    system(tempArray); // execute the UNIX command "sort"

    string line;
    ifstream myfile("1M.sorted");


    //Check top newJob.next pointer = current
    //Previous job = new job if current job is greater than previous
    //If current is smaller than newJob and next job is NULL then add on end

    // std::string str;
    // const char * c = str.c_str();


    while (true) {

        string tempJob;

        tempJob = getJob(myfile, clockCycle);

        while (!tempJob.empty()) {
            // cout << tempJob.c_str() << " ";
            //cout << clockCycle << endl;
            myJob = new Job(tempJob);

            //cout << tempJob << endl;
            //cout << myJob->getArrival() << " " << clockCycle << endl;

            Q1 = dispatcher(Q1, myJob);

            if (!myfile.eof()) {
                tempJob = getJob(myfile, clockCycle);
            }

            //cout << clockCycle << " " << endl;

        }

        if (clockCycle == 20) {
            Job *tempPtr = Q1;
            while (tempPtr->nextJob != Q1) {
//                cout << tempPtr->getArrival() << " ";
//                cout << tempPtr->getPid() << " ";
//                cout << tempPtr->getPriority() << endl;
//                tempPtr = tempPtr->nextJob;
            }
//            cout << tempPtr->getArrival() << " ";
//            cout << tempPtr->getPid() << " ";
//            cout << tempPtr->getPriority() << endl;
//            tempPtr = tempPtr->nextJob;
            remove("1M.sorted");
            exit(0);
        }

        clockCycle++;
    }

    myfile.close();

    remove("1M.sorted");

    return 0;
}

string getJob(ifstream &myfile, int currentTime) {
    char char_array[99];
    char *PID;
    char *Burst;
    char *Arrival;
    string line;
    streampos oldpos;


    if (myfile.is_open()) {

        do {
            oldpos = myfile.tellg();   // get back to the position
            getline(myfile, line);

            if (myfile.eof() || line.empty()) {
                // myfile.seekg(oldpos);
                return "";
            }

            strcpy(char_array, line.c_str());


            if (strchr(char_array, '-') != NULL || strchr(char_array, 'i')) {
                continue;
            }

            PID = strtok(char_array, "\t");
            Burst = strtok(NULL, "\t");
            Arrival = strtok(NULL, "\t");

            if (stoi(Arrival) == currentTime) {
                return line;
            } else {
                myfile.seekg(oldpos);
                return "";
            }

        } while (!myfile.eof() && !line.empty());

    }
}


Job* dispatcher(Job *myQ, Job *myJob) {
    Job *tempPointer = myQ;

    //Check for if Que is empty
    if (myQ == NULL) {
        myQ = myJob;
        myQ->nextJob = myQ;

    } else {
        while (tempPointer->nextJob != myQ) {
            tempPointer = tempPointer->nextJob;
        }
        tempPointer->nextJob = myJob;
        myJob->nextJob = myQ;

    }
    return myQ;

}