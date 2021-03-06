#pragma once

#include "MyoPluginPrivatePCH.h"
#include "MyoLambdaRunnable.h"

uint64 FMyoLambdaRunnable::ThreadNumber = 0;

FMyoLambdaRunnable::FMyoLambdaRunnable(TFunction< void()> InFunction)
{
	FunctionPointer = InFunction;
	Finished = false;
	Number = ThreadNumber;

	FString threadStatGroup = FString::Printf(TEXT("FMyoLambdaRunnable%d"), ThreadNumber);
	Thread = NULL;
	Thread = FRunnableThread::Create(this, *threadStatGroup, 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
	ThreadNumber++;

	//Runnables.Add(this);
}

FMyoLambdaRunnable::~FMyoLambdaRunnable()
{
	if (Thread == NULL)
	{
		delete Thread;
		Thread = NULL;
	}

	//Runnables.Remove(this);
}

//Init
bool FMyoLambdaRunnable::Init()
{
	//UE_LOG(LogClass, Log, TEXT("FLambdaRunnable %d Init"), Number);
	return true;
}

//Run
uint32 FMyoLambdaRunnable::Run()
{
	if (FunctionPointer)
	{
		FunctionPointer();
	}

	//UE_LOG(LogClass, Log, TEXT("FLambdaRunnable %d Run complete"), Number);
	return 0;
}

//stop
void FMyoLambdaRunnable::Stop()
{
	Finished = true;
}

void FMyoLambdaRunnable::Exit()
{
	Finished = true;
	//UE_LOG(LogClass, Log, TEXT("FLambdaRunnable %d Exit"), Number);

	//delete ourselves when we're done
	delete this;
}

void FMyoLambdaRunnable::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

FMyoLambdaRunnable* FMyoLambdaRunnable::RunLambdaOnBackGroundThread(TFunction< void()> InFunction)
{
	FMyoLambdaRunnable* Runnable;
	if (FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FMyoLambdaRunnable(InFunction);
		//UE_LOG(LogClass, Log, TEXT("FLambdaRunnable RunLambdaBackGroundThread"));
		return Runnable;
	}
	else
	{
		return nullptr;
	}
}

FGraphEventRef FMyoLambdaRunnable::RunShortLambdaOnGameThread(TFunction< void()> InFunction)
{
	return FFunctionGraphTask::CreateAndDispatchWhenReady(InFunction, TStatId(), nullptr, ENamedThreads::GameThread);
}

void FMyoLambdaRunnable::ShutdownThreads()
{
	/*for (auto Runnable : Runnables)
	{
	if (Runnable != nullptr)
	{
	delete Runnable;
	}
	Runnable = nullptr;
	}*/
}