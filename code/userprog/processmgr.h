// processmgr.h
//      Routines to manage user process
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef PROCESSMGR_H
#define PROCESSMGR_H
#include "copyright.h"
class AddrSpace;
#include "synch.h"

#include <map>
#include <set>
#include <string>

enum ProcessStatusEnum
{
    PROCESS_RUNNING,
    PROCESS_WAITING,	//after waitpid
    PROCESS_ENDED
};

struct ProcessInfo
{
    enum ProcessStatusEnum status;
    AddrSpace *space;
    Semaphore *wait;  //for waitpid
    int returnCode;
};

class ProcessMgr
{
public:

    ProcessMgr();
    ~ProcessMgr(); //destroy the map
    void KillAllProcess();
    unsigned int CreateProcess(AddrSpace *space);
    void EndProcess(AddrSpace *proc);
    int ProcessWaitP(unsigned int pid);
    void ProcessWaitV(unsigned int pid);
    AddrSpace *GetProcessById(unsigned int pid);
    bool ProcessEnded(unsigned int pid);
    int GetReturn(unsigned int pid);
    void SetReturn(unsigned int pid, int code);

    std::map<unsigned int, ProcessInfo> getProcess();

    //number of processes currently running
    unsigned int nbProcess;
private:
    //keep tracks of the processes
    std::map<unsigned int, ProcessInfo> Processes;
    //max pid that was given
    unsigned int max_pid;
};
#endif
