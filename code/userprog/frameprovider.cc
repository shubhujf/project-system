// stackmgr.cc
//      Routines to manage user stacks
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "frameprovider.h"
#include "system.h"
#include "addrspace.h"

/**
 * data_end_at indicate where the data segment end.
 * Suppose code & segment contiguous and code start at 0x0
 **/
FrameProvider::FrameProvider(int allocation_strategy)
{
	alloc_strat = allocation_strategy;
    total_frame_number=NumPhysPages;
    number_of_free_frame = total_frame_number; // If we block the first page, we will need to add -1
    // Create bitmap
    bitmap = new BitMap(total_frame_number);
    
    // Can not bock the first page, at least for now... It contains the first lines of code,
    // so can not make it trigger page fault.

}

FrameProvider::~FrameProvider()
{
    // De-alocate bitmap
    delete bitmap;
}

/**
 * GetNewFrameProvider return address in user space corresponding to Physical Frame, NULL if
 * no more memory
 **/
int FrameProvider::GetEmptyFrame(unsigned int *page)
{
    int index;
    unsigned int frame_addr;
    // Find a clear bit according to the choosen strategy
	switch(alloc_strat)
	{
		case FIRST:
		{
			index = bitmap->FindFirst();
			break;
		}
		case LAST:
		{
			index = bitmap->FindLast();
			break;
		}
		case RANDOM:
		{
			index = bitmap->FindRandom();
			break;
		}
		default:
		{
			printf("Unexpected allocation strategy type %d\n", alloc_strat);
			ASSERT(FALSE);
			break;
		}
	}

    // If error, return -1
    if (index == -1)
        return -1;

    // Compute Physical addr
    frame_addr = index*PageSize;

    // Clear frame
    bzero(machine->mainMemory + frame_addr,PageSize);
    
     // we allocated a frame, so one less free now
    number_of_free_frame--;

	*page = frame_addr;
    return 0;
}

/**
 * FreeFrame
 * address : int corresponding to the frame freed
 * return -1 if invalid addr
 **/
int FrameProvider::ReleaseFrame(unsigned int addr)
{
    unsigned int frame_index;
   
    // Check if addr does not goes out memory
    if (addr > MemorySize-1)
        return -1;

    // Check if it is the begin of a frame
    if ((addr) % PageSize != 0)
        return -1;

    // Compute frame index
    frame_index = addr / PageSize;

    // Check if frame is used
    if (!bitmap->Test(frame_index))
        return -1;

    // Clean frame
    bitmap->Clear(frame_index);
    
    // We freed a frame, so one more now
    number_of_free_frame++; 
    
    return 0;
}

int FrameProvider::NumAvailFrame()
{
  return number_of_free_frame;
}

