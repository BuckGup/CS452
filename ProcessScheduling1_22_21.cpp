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

int main() {

    char *tok;
    Job *prevJob = nullptr;
    Job *currentJob = nullptr;
    Job *topJob = nullptr;
    Job *myJob = nullptr;

    char fileDirectory[99];
    int numQ;
    int timeQuantum;
    int ageInterval;
    char char_array[99];
    char tempArray[40];
    int clockCycle = 0;
    int totalJobCount = 0;


    printf("\nEnter the test file directory:\t");
    scanf("%s", &fileDirectory);

    printf("Enter the number of queues:\t");
    scanf("%d", numQ);

    printf("Enter time quantum for top queue:\t");
    scanf("%d", timeQuantum);

    printf("Enter ageing interval:\t");
    scanf("%d", ageInterval);

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
    streampos oldpos;


    //Check top newJob.next pointer = current
    //Previous job = new job if current job is greater than previous
    //If current is smaller than newJob and next job is NULL then add on end

    // std::string str;
    // const char * c = str.c_str();


    if (myfile.is_open()) {
        getline(myfile, line);

        oldpos = myfile.tellg();   // get back to the position
        while (getline(myfile, line) && !line.empty()) {

            strcpy(char_array, line.c_str());
            if (strchr(char_array, '-') != NULL) {
                continue;
            }

            myJob = new Job();

            tok = strtok(char_array, "\t");
            myJob->setPid(stoi(tok));
            //cout << myJob->getPid() << " ";

            tok = strtok(NULL, "\t");
            myJob->setBurst(stoi(tok));
            //cout << myJob->getBurst() << " ";

            tok = strtok(NULL, "\t");
            myJob->setArrival(stoi(tok));
            //cout << myJob->getArrival() << " ";

            tok = strtok(NULL, "\t");
            myJob->setPriority(stoi(tok));
            //cout << myJob->getPriority() << " " << endl;



            //@todo THIS
            while (myJob->nextJob != NULL) {
                //goes until the end of the file

                if (currentJob->getArrival() == myJob->nextJob->getArrival()) {

                    if (currentJob->getPriority() > myJob->nextJob->getPriority()) {

                        //Check if Q1 is full and Qs afterwards
                        //point current Job to end of open Q

                    } else {

                        //Check if Q1 is full and Qs afterwards
                        //point nextJob to end of open Q

                    }


                } else {


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

            oldpos = myfile.tellg();   // get back to the position
        }

        myfile.close();

        remove("1M.sorted");


        /* currentJob = topJob;
        while (currentJob != NULL) {
            cout << currentJob->getArrival() << "-";
            currentJob = currentJob->nextJob;
        }

         */

    } else {
        cout << "Wrong file";
    }

    return 0;
}
