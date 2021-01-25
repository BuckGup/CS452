//MFQS Made by Sam Strecker 1/25/21

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
        char *tok;
        char char_array[99];
        setStartTime(-1);
        setWorkRemaining(-1);
        setAge(0);

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

string getJob(ifstream &, int);

Job *dispatcher(Job *, Job *);

int checkActiveJobs(Job *, int);

void demote(Job *&, Job *&, int);

void deleteJob(Job *&, int, int &, int &, int &);

Job *promoteJob(Job *&, Job *&, int, int);

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
    char tempArray[99];
    int clockCycle = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int totalProcess = 0;
    int workToDo = 0;
    int quantumClock = 0;
    int myAge = 0;

    printf("\nEnter the test file directory:\t");
    scanf("%s", fileDirectory);
    
    printf("Enter the number of queues:\t");
    scanf("%d", &numQ);

    printf("Enter time quantum for top queue:\t");
    scanf("%d", &timeQuantum);

    printf("Enter ageing interval:\t");
    scanf("%d", &myAge);

    sprintf(tempArray, "sort -g -k 3,3 %s > 1M.sorted", fileDirectory);

    system(tempArray); // execute the UNIX command "sort"
    string line;
    ifstream myfile("1M.sorted");

    quantumClock = timeQuantum;
    while (true) {

        string tempJob;
        Job *currentJob;

        tempJob = getJob(myfile, clockCycle);
        //Read in scheduled jobs from file
        while (!tempJob.empty()) {
            myJob = new Job(tempJob);
            Q1 = dispatcher(Q1, myJob);

            if (!myfile.eof()) {
                tempJob = getJob(myfile, clockCycle);
            }
        }

        if (QF != NULL || QF != nullptr) {
            //Call the function to check if the age is past the interval and traverse across all elements in FCFS
            if (numQ == 2) {
                currentJob = Q1;
                currentJob = promoteJob(QF, currentJob, clockCycle, myAge);

            } else if (numQ == 3) {
                currentJob = Q2;
                currentJob = promoteJob(QF, currentJob, clockCycle, myAge);

            } else if (numQ == 4) {
                currentJob = Q3;
                currentJob = promoteJob(QF, currentJob, clockCycle, myAge);

            } else if (numQ == 5) {
                currentJob = Q4;
                currentJob = promoteJob(QF, currentJob, clockCycle, myAge);

            } else {
                cerr << "Queue out of bounds" << endl;
            }
        }

        //Check status of jobs
        if (Q1 != nullptr || Q1 != NULL) {
            workToDo = checkActiveJobs(Q1, clockCycle);
            quantumClock--;

            if (workToDo == 0) {
                deleteJob(Q1, clockCycle, totalProcess, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum;

            } else {
                if (quantumClock == 0) {
                    if (numQ == 2) {
                        demote(Q1, QF, clockCycle);

                    } else {
                        demote(Q1, Q2, clockCycle);
                    }
                    quantumClock = timeQuantum;
                }
            }


        } else if (Q2 != nullptr || Q2 != NULL) {
            workToDo = checkActiveJobs(Q2, clockCycle);
            quantumClock--;
            if (workToDo == 0) {
                deleteJob(Q2, clockCycle, totalProcess, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum * 2;

            } else {
                if (quantumClock == 0) {
                    if (numQ == 3) {
                        demote(Q2, QF, clockCycle);

                    } else {
                        demote(Q2, Q3, clockCycle);
                    }
                    quantumClock = timeQuantum;
                }
            }


        } else if (Q3 != nullptr || Q3 != NULL) {
            workToDo = checkActiveJobs(Q3, clockCycle);
            quantumClock--;
            if (workToDo == 0) {
                deleteJob(Q3, clockCycle, totalProcess, totalWaitTime, totalTurnaroundTime);
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
            workToDo = checkActiveJobs(Q4, clockCycle);
            quantumClock--;
            if (workToDo == 0) {
                deleteJob(Q4, clockCycle, totalProcess, totalWaitTime, totalTurnaroundTime);
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
            workToDo = checkActiveJobs(QF, clockCycle);
            quantumClock = timeQuantum;
            if (workToDo == 0) {
                deleteJob(QF, clockCycle, totalProcess, totalWaitTime, totalTurnaroundTime);
            }

        } else {
            double aveWaitTime = totalWaitTime / totalProcess;
            double aveTurnaroundTime = totalTurnaroundTime / totalProcess;

            cout << "Ave. wait time= " << aveWaitTime << " Ave. turnaround time = " << aveTurnaroundTime
                 << " Total processes scheduled = " << totalProcess << endl;

            myfile.close();
            remove("1M.sorted");
            exit(0);
        }
        clockCycle++;
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
    if (myQ == nullptr) {
        myQ = myJob;

        myQ->nextJob = nullptr;
        cout << "Process " << myJob->getPid() << ":" << " arrives @ " << myJob->getArrival() << endl;

    } else {

        while (tempPointer->nextJob != nullptr) {
            tempPointer = tempPointer->nextJob;
        }

        tempPointer->nextJob = myJob;
        myJob->nextJob = nullptr;
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

    while (tempPtrQa->nextJob != nullptr) {
        tempPtrQa = tempPtrQa->nextJob;
    }
    if (Qb == nullptr || Qb == NULL) {
        Qb = Qa;
        Qa = Qa->nextJob;
        Qb->nextJob = nullptr;
        cout << Qb->getPid() << " switched @ " << clockCycle << endl;

    } else {
        while (tempPtrQb->nextJob != nullptr) {

            tempPtrQb = tempPtrQb->nextJob;
        }

        tempPtrQb->nextJob = Qa;
        Qa = Qa->nextJob;
        cout << tempPtrQb->nextJob->getPid() << " switched @ " << clockCycle << endl;
        tempPtrQb->nextJob->nextJob = nullptr;

    }

}

void deleteJob(Job *&Qa, int clockCycle, int &totalProcess, int &totalWaitTime, int &totalTurnaroundTime) {
    Job *tempPtr = nullptr;
    tempPtr = Qa;

    totalTurnaroundTime += (clockCycle - Qa->getStartTime());
    totalWaitTime += (Qa->getStartTime() - Qa->getArrival());
    totalProcess++;
    cout << Qa->getPid() << " finished @ " << clockCycle << endl;

    Qa = Qa->nextJob;


}

Job *promoteJob(Job *&QF, Job *&Qb, int clockCycle, int ageInterval) {

    Job *ptrQF = nullptr;
    ptrQF = QF;

    Job *ptrEndQb = nullptr;
    ptrEndQb = Qb;

    //finds the end of the Q above QF
    while (ptrEndQb != nullptr) {
        ptrEndQb = ptrEndQb->nextJob;
    }

    //Walks across the QF for each element
    while (ptrQF->nextJob != nullptr) {
        //checks each element to see if it's aged out
        if (ptrQF->getAge() > ageInterval) {
            ptrEndQb->nextJob = ptrQF;
            return Qb;
        }
        ptrQF = ptrQF->nextJob;
    }
    return Qb;

}


