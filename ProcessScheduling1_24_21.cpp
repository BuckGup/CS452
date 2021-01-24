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

void demote(Job **, Job **, int);

void deleteJob(Job **, int, int &, int &, int &);

void demote2(Job **, Job **, Job **, Job **, Job **, Job **, int, int);


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

    quantumClock = timeQuantum;
    while (true) {

        string tempJob;

        tempJob = getJob(myfile, clockCycle);
        //Read in scheduled jobs from file
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
        //Check status of jobs

        if (Q1 != nullptr || Q1 != NULL) {
            workToDo = checkActiveJobs(Q1, clockCycle);

            if (workToDo == 0) {
                deleteJob(&Q1, clockCycle, totalProcesses, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum;

            } else {
                if (quantumClock == 0) {
                    demote(&Q1, &Q2, clockCycle);
                    //demote2(&Q1, &Q1, &Q2, &Q3, &Q4, &QF, clockCycle, numQ);
                    quantumClock = timeQuantum;

                }
            }
        } else if (Q2 != nullptr || Q2 != NULL) {
            workToDo = checkActiveJobs(Q1, clockCycle);

            if (workToDo == 0) {
                deleteJob(&Q1, clockCycle, totalProcesses, totalWaitTime, totalTurnaroundTime);
                quantumClock = timeQuantum;

            } else {
                if (quantumClock == 0) {
                    //demote(&Q1, &Q2, clockCycle);
                    demote2(&Q2, &Q1, &Q2, &Q3, &Q4, &QF, clockCycle, numQ);
                    quantumClock = timeQuantum;
                }
            }

        }

        if (clockCycle == 10000) {
            Job *tempPtr = Q1;
//            while (tempPtr->nextJob != Q1) {
//                cout << tempPtr->getArrival() << " ";
//               cout << tempPtr->getPid() << " ";
//              cout << tempPtr->getPriority() << endl;
//                tempPtr = tempPtr->nextJob;
//            }
//            cout << tempPtr->getArrival() << " ";
//            cout << tempPtr->getPid() << " ";
//            cout << tempPtr->getPriority() << endl;
//            tempPtr = tempPtr->nextJob;
            // remove("1M.sorted");
            exit(0);
        }

        // cout << clockCycle << " quantum " << quantumClock << endl;
        clockCycle++;
        quantumClock--;
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
            cout << "PID: " << Qa->getPid() << " Work Remaining: " << Qa->getWorkRemaining() << endl;
            return Qa->getWorkRemaining();

        }

    }

    return 0;
}

void demote(Job **Qa, Job **Qb, int clockCycle) {
    Job *tempPtrQa = nullptr;
    tempPtrQa = *Qa;
    Job *tempPtrQb = nullptr;
    tempPtrQb = *Qb;

    while (tempPtrQa->nextJob != *Qa) {
        *tempPtrQa = *tempPtrQa->nextJob;
    }
    if (tempPtrQb == nullptr || tempPtrQb == NULL) {
        tempPtrQb = tempPtrQa;
        *tempPtrQb->nextJob = *tempPtrQb;

        *tempPtrQa = *tempPtrQa->nextJob;
        //^^^^^^?????
    } else {
        while (tempPtrQb->nextJob != tempPtrQb) {
            *tempPtrQb = *tempPtrQb->nextJob;
        }
        *tempPtrQa->nextJob = *tempPtrQa->nextJob;

        *tempPtrQb->nextJob = *tempPtrQa;
        *tempPtrQa = *tempPtrQa->nextJob;
    }

    *tempPtrQa->nextJob = *tempPtrQb;
    *tempPtrQa = *tempPtrQa;

    cout << tempPtrQa->getPid() << " switched @ " << clockCycle << " " << tempPtrQa->getWorkRemaining() << endl;

}

void deleteJob(Job **Qa, int clockCycle, int &totalProcess, int &totalWaitTime, int &totalTurnaroundTime) {
    Job *tempPtr = nullptr;
    Job *tempPtr2 = nullptr;
    Job *tempPtr3 = nullptr;


    tempPtr = *Qa;
    tempPtr2 = *Qa;
    tempPtr3 = *Qa;

    while (tempPtr->nextJob != *Qa) {
        *tempPtr = *tempPtr->nextJob;
    }

    //checks if last element and delete itself
    if (tempPtr->nextJob == tempPtr) {
        *Qa = nullptr;
    } else {
        *tempPtr->nextJob = *tempPtr2->nextJob;
        *tempPtr2 = *tempPtr2->nextJob;
    }

    cout << tempPtr3->getPid() << " finished @ " << clockCycle << " " << tempPtr3->getWorkRemaining() << endl;

    // delete tempPtr;
}

void demote2(Job **Qa, Job **QP1, Job **QP2, Job **QP3, Job **QP4, Job **QPF, int clockCycle, int numQ) {

    //@TODO assumption 5 is inclusive of F and Multi level means always 2 or more
    //Qa is where you are currently

    Job *tempPtrQa = nullptr;
    tempPtrQa = *Qa;
    Job *tempPtrQb = nullptr;
    Job *ptrQa = nullptr;
    ptrQa = *Qa;

    Job *ptrF = nullptr;
    ptrF = *QPF;



    Job *tempPtrQ1 = nullptr;

    if (*Qa == *QP1) {

        if (numQ >= 2) {
            tempPtrQb = *QP2;
        } else {
            tempPtrQb = ptrF;
        }
    } else if (*Qa == *QP2) {
        if (numQ >= 3) {
            tempPtrQb = *QP3;
        } else {
            tempPtrQb = *QPF;
        }
    } else if (*Qa == *QP3) {
        if (numQ >= 4) {
            tempPtrQb = *QP4;
        } else {
            tempPtrQb = *QPF;
        }

    } else if (*Qa == *QP4) {
        if (numQ == 5) {
            tempPtrQb = *QPF;
        } else {
            cerr << "Number of Queues grater than 5" << endl;
        }

    }
    //find end of Q you are demoting from
    while (tempPtrQa->nextJob != *Qa) {
        *tempPtrQa = *tempPtrQa->nextJob;
    }
    if (tempPtrQb == nullptr || tempPtrQb == NULL) {
        tempPtrQb = tempPtrQa;
        //^^^^^ Astrik?????
        *tempPtrQb->nextJob = *tempPtrQb;

        tempPtrQa = tempPtrQa->nextJob;
        //^^^^^^?????
    } else {
        while (tempPtrQb->nextJob != tempPtrQb) {
            *tempPtrQb = *tempPtrQb->nextJob;
        }
        //*tempPtrQa->nextJob = *tempPtrQa->nextJob;
        *tempPtrQa->nextJob = *ptrQa->nextJob;

        //*tempPtrQa = *tempPtrQa->nextJob;
        *ptrQa->nextJob = *tempPtrQb->nextJob;

        //*tempPtrQb->nextJob = *tempPtrQa;
        *tempPtrQb->nextJob = *ptrQa;


    }

//    *tempPtrQa->nextJob = *tempPtrQb;
//    *tempPtrQa = *tempPtrQa;

    cout << tempPtrQa->getPid() << " switched @ " << clockCycle << " " << tempPtrQa->getWorkRemaining() << endl;

}

//} else if (Q2 != nullptr) {
//            workToDo = checkActiveJobs(Q2, clockCycle);
//
//            if (workToDo == 0) {
//                //delete job()
//                quantumClock = timeQuantum;
//            } else {
//                //check time quantum if at Quantum edge then demote the job
//
//            }
//
//        } else if (Q3 != nullptr) {
//            workToDo = checkActiveJobs(Q3, clockCycle);
//
//            if (workToDo == 0) {
//                //delete job()
//                quantumClock = timeQuantum;
//            } else {
//                //check time quantum if at Quantum edge then demote the job
//
//            }
//
//        } else if (Q4 != nullptr) {
//            workToDo = checkActiveJobs(Q4, clockCycle);
//
//            if (workToDo == 0) {
//                //delete job()
//                quantumClock = timeQuantum;
//            } else {
//                //check time quantum if at Quantum edge then demote the job
//
//            }
//
//        } else if (F != nullptr) {
//            workToDo = checkActiveJobs(F, clockCycle);
//
//            if (workToDo == 0) {
//                //delete job()
//                quantumClock = timeQuantum;
//            } else {
//                //check time quantum if at Quantum edge then demote the job
//
//            }
