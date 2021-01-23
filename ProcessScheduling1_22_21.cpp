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

            cout << tempJob << endl;
            cout << myJob->getArrival() << " " << clockCycle << endl;

            if (clockCycle == 100) {
                exit(0);
            }

            tempJob = getJob(myfile, clockCycle);

        }
        clockCycle++;

    }



    /*     if (topJob == NULL) {
             //first element in list
             topJob = myJob;
             currentJob = myJob;
             prevJob = myJob;

         } else {
             currentJob = topJob;
             prevJob = topJob;

             while (currentJob->getArrival() < myJob->getArrival() && currentJob->nextJob != NULL) {
                 prevJob = currentJob;
                 currentJob = currentJob->nextJob;
             }

             if (currentJob == topJob) {
                 //end
                 if (currentJob->nextJob == NULL) {
                     currentJob->nextJob = myJob;
                 } else {
                     //front
                     topJob = myJob;
                     myJob->nextJob = currentJob;
                     // cout << "if " << myJob->getArrival() << endl;
                 }

             } else if (currentJob->nextJob == NULL) {
                 //if last element
                 currentJob->nextJob = myJob;
                 //  cout << "else if " << myJob->getArrival() << endl;

             } else {
                 //handles case for NULL
                 prevJob->nextJob = myJob;
                 myJob->nextJob = currentJob;
                 // cout << "Prev Job:" << prevJob->getArrival() << " ";
                 // cout << "Current Job: " << currentJob->getArrival() << " ";
                 // cout << "Top Job: " << topJob->getArrival() << " ";
                 // cout << "My Job: " << myJob->getArrival() << " " << endl;
             }

         }

         */


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


        } while (!line.empty());


        /*while (getline(myfile, line) && !line.empty()) {
            strcpy(char_array, line.c_str());
            if (strchr(char_array, '-') != NULL || strchr(char_array, 'i')) {
                oldpos = myfile.tellg();
                continue;
            }


            PID = strtok(char_array, "\t");
            Burst = strtok(NULL, "\t");
            Arrival = strtok(NULL, "\t");

            if(stoi(Arrival) == currentTime){
                return line;
            }

            else{
                myfile.seekg (oldpos);
                return NULL;
            }

        }*/


        //compare it to clockCycle
        //if clockCycle = arrivalTime

        //then return the string of the line

        //else go back one job

        //return NULL

    }
}