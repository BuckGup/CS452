//MFQS Made by Sam Strecker 1/16/21

#include<stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


class Job {
public:
    int PID;
    int burst;
    int arrival;
    Job *nextJob;

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
    char char_array[99];

    printf("\nEnter the test file directory:\t");
    scanf("%s", &fileDirectory);

    string line;
    ifstream myfile(fileDirectory);

    // @todo add input validation for tokens

    //Check top newJob.next pointer = current
    //Previous job = new job if current job is greater than previous
    //If current is smaller than newJob and next job is NULL then add on end

    // std::string str;
    // const char * c = str.c_str();


    if (myfile.is_open()) {
        getline(myfile, line);

        while (getline(myfile, line) && !line.empty()) {
            strcpy(char_array, line.c_str());

            if (strchr(char_array, '-') != NULL) {
                continue;
            }

            myJob = new Job();

            tok = strtok(char_array, "\t");
            myJob->setPid(stoi(tok));
            // cout << myJob->getPid() << " ";

            tok = strtok(NULL, "\t");
            myJob->setBurst(stoi(tok));

            //cout << myJob->getBurst() << " ";

            tok = strtok(NULL, "\t");
            myJob->setArrival(stoi(tok));

            //cout << myJob.getArrival() << " ";

            tok = strtok(NULL, "\t");
            myJob->setPriority(stoi(tok));

            //cout << myJob.getPriority() << " ";

            if (topJob == NULL) {
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


        }
        myfile.close();

        currentJob = topJob;
        while (currentJob != NULL) {
            cout << currentJob->getArrival() << "-";
            currentJob = currentJob->nextJob;
        }


    } else {
        cout << "Wrong file";
    }

    return 0;
}
