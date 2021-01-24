//MFQS Made by Sam Strecker 1/16/21

#include<stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Job {
public:
    int PID;
    int burst;
    int arrival;
    Job *nextJob;

    Job *getNextJob() const;

    void setNextJob(Job *nextJob);

    int age;
    int startTime;
    int workRemaining;

    int getAge() const;

    void setAge(int age);

    int getStartTime() const;

    void setStartTime(int startTime);

    int getWorkRemaining() const;

    void setWorkRemaining(int workRemaining);


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
        age = 0;
    };

    Job(string line) {
        nextJob = NULL;
        age = 0;
        char *tok;
        char char_array[99];
        setStartTime(-1);
        setWorkRemaining(-1);
        setAge(-1);

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
}

int Job::getAge() const {
    return age;
}

void Job::setAge(int age) {
    Job::age = age;
}

int Job::getStartTime() const {
    return startTime;
}

void Job::setStartTime(int startTime) {
    Job::startTime = startTime;
}

int Job::getWorkRemaining() const {
    return workRemaining;
}

void Job::setWorkRemaining(int workRemaining) {
    Job::workRemaining = workRemaining;
}

Job *Job::getNextJob() const {
    return nextJob;
}

void Job::setNextJob(Job *nextJob) {
    Job::nextJob = nextJob;
};

string getJob(ifstream &, int);

Job *jobFill(string);

Job *dispatcher(Job *, Job *);

int checkActiveJobs(Job *, int);

void demote(Job *&, Job *&, int);

void deleteJob(Job *&, int, int &, int &, int &);

void promoteJob(Job *&, Job *&, int, int &, int &);

int main() {
    char *tok;
    Job *currentJob = nullptr;
    Job *topJob = nullptr;
    Job *myJob = nullptr;
    Job *Q1 = nullptr;
    Job *Q2 = nullptr;
    Job *Q3 = nullptr;
    Job *Q4 = nullptr;
    Job *QF = nullptr;
    char fileDirectory[99];
    int numQ = 0;
    int timeQuantum = 0;
    int ageInterval = 0;
    char tempArray[40];
    int clockCycle = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int totalProcesses = 0;
    int workToDo = 0;
    int quantumClock = 0;

    printf("\nEnter the test file directory:\t");
    scanf("%s", &fileDirectory);

    printf("Enter the number of queues:\t");
    scanf("%d", &numQ);

    printf("Enter time quantum for top queue:\t");
    scanf("%d", &timeQuantum);

    printf("Enter ageing interval:\t");
    scanf("%d", &ageInterval);


    sprintf(tempArray, "sort -g -k 3,3 %s > 1M.sorted", fileDirectory);

    system(tempArray); // execute the UNIX command "sort"

    string line;
    ifstream myfile("1M.sorted");

    //Check top newJob.next pointer = current
    //Previous job = new job if current job is greater than previous
    //If current is smaller than newJob and next job is NULL then add on end


    quantumClock = timeQuantum;
    while (true) {

        string tempJob;

        tempJob = getJob(myfile, clockCycle);
        //Read in scheduled jobs from file
        while (!tempJob.empty()) {
            myJob = new Job(tempJob);
            Q1 = dispatcher(Q1, myJob);
            if (!myfile.eof()) {
                tempJob = getJob(myfile, clockCycle);
            }
        }
        //Check status of jobs
        if (Q1 != nullptr || Q1 != NULL) {
            workToDo = checkActiveJobs(Q1, clockCycle);

            if (workToDo == 0) {
                deleteJob(Q1, clockCycle, totalProcesses, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum;

            } else {
                if (quantumClock == 0) {
                    if (numQ == 2) {
                        demote(Q1, QF, clockCycle);
                    } else {
                        demote(Q1, Q2, clockCycle);
                    }
                    //demote2(Q1, Q1, Q2, Q3, Q4, QF, clockCycle, numQ);
                    quantumClock = timeQuantum;

                }
            }
        } else if (Q2 != nullptr || Q2 != NULL) {
            workToDo = checkActiveJobs(Q1, clockCycle);

            if (workToDo == 0) {
                deleteJob(Q2, clockCycle, totalProcesses, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum * 2;

            } else {
                if (quantumClock == 0) {
                    if (numQ == 3) {
                        demote(Q2, QF, clockCycle);
                    } else {
                        demote(Q2, Q3, clockCycle);
                    }
                    // demote(Q1, Q2, clockCycle);
                    // demote2(Q2, Q1, Q2, Q3, Q4, QF, clockCycle, numQ);
                    quantumClock = timeQuantum;
                }
            }

        } else if (Q3 != nullptr || Q3 != NULL) {
            workToDo = checkActiveJobs(Q1, clockCycle);

            if (workToDo == 0) {
                deleteJob(Q3, clockCycle, totalProcesses, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum * 4;

            } else {
                if (quantumClock == 0) {
                    if (numQ == 3) {
                        demote(Q3, QF, clockCycle);
                    } else {
                        demote(Q3, Q4, clockCycle);
                    }
                    quantumClock = timeQuantum;
                }
            }

        } else if (Q4 != nullptr || Q4 != NULL) {
            workToDo = checkActiveJobs(Q1, clockCycle);

            if (workToDo == 0) {
                deleteJob(Q4, clockCycle, totalProcesses, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum * 8;

            } else {
                if (quantumClock == 0) {
                    if (numQ == 4) {
                        demote(Q4, QF, clockCycle);
                    }

                    quantumClock = timeQuantum;
                }
            }

        } else if (QF != nullptr || QF != NULL) {
            workToDo = checkActiveJobs(Q1, clockCycle);

            if (workToDo == 0) {
                deleteJob(QF, clockCycle, totalProcesses, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum;

            } else {

                //Call the function to check if the age is past the interval and traverse across all elements in FCFS
                if (quantumClock == 0) {
                    cout << " In FCFS: " << timeQuantum << endl;
                    quantumClock = timeQuantum;
                }
            }

        } else {

            cout << "Ave. wait time= " << totalWaitTime/totalProcesses << " Ave. turnaround time = " << totalTurnaroundTime
                 << " Total processes scheduled = " << totalProcesses << endl;

            myfile.close();
            remove("1M.sorted");
            exit(0);
        }
        clockCycle++;
        quantumClock--;
    }
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
    return "";
}


Job *dispatcher(Job *myQ, Job *myJob) {
    Job *tempPointer = myQ;

    //Check for if Que is empty
    if (myQ == NULL) {
        myQ = myJob;
        myQ->nextJob = myQ;
        cout << "Process " << myJob->getPid() << ":" << " arrives @ " << myJob->getArrival() << endl;

    } else {
        while (tempPointer->nextJob != myQ) {
            tempPointer = tempPointer->nextJob;
        }
        tempPointer->nextJob = myJob;
        myJob->nextJob = myQ;
        cout << "Process " << myJob->getPid() << ":" << " arrives @ " << myJob->getArrival() << endl;

    }
    return myQ;

}

int checkActiveJobs(Job *Qa, int clockCycle) {

    if (Qa == nullptr || Qa == NULL) {
        return 0;
    } else {
        if (Qa->getStartTime() == -1) {
            Qa->setWorkRemaining(Qa->getBurst());
            //start job
            Qa->setStartTime(clockCycle);
            return Qa->getBurst();
        } else {
//            if(Qa->getWorkRemaining() == 0){
//
//            }
            Qa->setWorkRemaining(Qa->getWorkRemaining() - 1);
            return Qa->getWorkRemaining();
        }
    }

    return 0;
}

void demote(Job *&Qa, Job *&Qb, int clockCycle) {
    Job *tempPtrQa = nullptr;
    tempPtrQa = Qa;
    Job *tempPtrQb = nullptr;
    tempPtrQb = Qb;

    while (tempPtrQa->nextJob != Qa) {
        tempPtrQa = tempPtrQa->nextJob;
    }
    if (Qb == nullptr || Qb == NULL) {
        Qb = Qa;
        Qb->nextJob = Qb;

        if (tempPtrQa->nextJob == Qa) {
            Qa = NULL;
        } else {
            Qa = Qa->nextJob;

        }

        //^^^^^^?????
    } else {
        //if last element in Q1
        while (tempPtrQb->nextJob != Qb) {
            tempPtrQb = tempPtrQb->nextJob;
        }
        tempPtrQa->nextJob = Qa->nextJob;
        tempPtrQb->nextJob = Qa;
        Qa->nextJob = Qb;

        if (tempPtrQa->nextJob == Qa) {
            Qa = NULL;
        } else {
            Qa = tempPtrQa->nextJob;
        }
        //  *tempPtrQb->nextJob = *tempPtrQa;
        Qb->nextJob = Qb->nextJob;

    }
    cout << tempPtrQa->getPid() << " switched @ " << clockCycle << endl;

}

void deleteJob(Job *&Qa, int clockCycle, int &totalProcess, int &totalWaitTime, int &totalTurnaroundTime) {
    Job *tempPtr = nullptr;

    tempPtr = Qa;


    while (tempPtr->nextJob != Qa) {
        tempPtr = tempPtr->nextJob;
    }

    totalTurnaroundTime += (clockCycle - Qa->getStartTime());
    totalWaitTime += (Qa->getStartTime() - Qa->getArrival());
    totalProcess++;
    cout << Qa->getPid() << " finished @ " << clockCycle << endl;

    //checks if last element and delete itself
    if (Qa->nextJob == Qa) {
        Qa = nullptr;
    } else {
        tempPtr->nextJob = Qa->nextJob;
        Qa = Qa->nextJob;
    }

}


void promoteJob(Job *&Qa, Job *&Qb, int clockCycle, int &ageInterval, int numQ) {



}

