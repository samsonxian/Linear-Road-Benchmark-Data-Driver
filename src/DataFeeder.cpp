// DataFeeder.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <string>
#include <iostream>

#include <time.h>
#include <unistd.h>

#include "LRDataProvider.h"

using namespace std;

void ErrorHandler(int nErrorCode)
{
	switch(nErrorCode)
	{
		case END_OF_FILE:
			{
				cout << "End of data file" << endl;
			}
			break;
		case ERROR_FILE_NOT_FOUND:
			{	
				cout << "Data file not found. Check data file path name." << endl;
			}
			break;
		case ERROR_INVALID_FILE:
			{
				cout << "Invalid file handler. Restart the system." << endl;
			}
			break;
		case ERROR_BUFFER_OVERFLOW:
			{
				cout << "Buffer over flow. Increase the buffer size." << endl;
			}
			break;
		default:
			{
				cout << "Programming error." << endl;
			}
			break;
	}
}

int main(int argc, char* argv[])
{
	pthread_mutex_t  mutex_lock = PTHREAD_MUTEX_INITIALIZER;

	// Check parameter
	if (argc < 2)
	{
	  cout << "You have to provider input data file name as a parameter." << endl;
	  return 0;

	}

	char* dataFile = argv[1];

	//CLRDataProvider
	CLRDataProvider* provider = new CLRDataProvider();
	
	//Initialize the provider
	cout << "Initializing..." << endl;
	int ret = provider->Initialize(dataFile, 10000, &mutex_lock);
	
	//Allocate caller's buffer
	if ( ret != SUCCESS )
	  {	
	    ErrorHandler(ret);
	    return 0;

	  }
	else
	{
		//Using the provider
		if( provider->PrepareData(provider) == SUCCESS )
		{
			int		nTuplesRead = 0;
			int		nMaxTuples  = 100;
			LPTuple lpTuples = new Tuple[nMaxTuples ];
			
			int seconds = 0;

			for(;;)
			{
			  
     
			  // Get a random number between 5 and 15
			  srand(time(NULL));			  
			  int s =  (int) ((((double) rand())/ RAND_MAX) * 10) + 5;

			  // Sleep s seconds
			       sleep(s);

			       int ret;
				for(;;)
				{
					//Gets available data
					ret = provider->GetData(lpTuples, nMaxTuples, nTuplesRead);

					if ( ret < 0 )
					{
						//Handle erros including eof
						ErrorHandler(ret);
						break;
					}

					if ( nTuplesRead == 0 )
					{
						//No tuple available
						break;
					}
					
					//Using the return data
					for(int i = 0; i < nTuplesRead; i++ )
					{
					        char* str =  lpTuples[i].ToString();
						cout << str;
						delete str;
					}

					if ( nTuplesRead < nMaxTuples ) 
					{
						//Last tuple has been read
						break;
					}
				}

				if ( ret < SUCCESS )
				{				
					break;
				}

			}
		}
		
		//Uninitialize the provider
		cout << "Uninitialize..." << endl;
		provider->Uninitialize();
	}

	delete provider;
	
	return 0;
}

