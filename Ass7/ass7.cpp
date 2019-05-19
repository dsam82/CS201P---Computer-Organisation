#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

void filln(int array[][4], int rows, int value)
{
	for(int i=0; i < rows ; i++)
		for(int j=0 ; j < 4 ; j++)
			array[i][j] = value;
}

// Function to convert hexadecimal to decimal
unsigned int hexadecimalToDecimal(string hexVal)
{
    int len = hexVal.length();

    // Initializing base value to 1, i.e 16^0
    unsigned int base = 1;

    unsigned int dec_val = 0;

    // Extracting characters as digits from last character
    for (int i=len-1; i>=0; i--)
    {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value.
        if (hexVal[i]>='0' && hexVal[i]<='9')
        {
            dec_val += (hexVal[i] - 48)*base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i]>='A' && hexVal[i]<='F')
        {
            dec_val += (hexVal[i] - 55)*base;

            // incrementing base by power
            base = base*16;
        }
    }

    return dec_val;
}

void shift(int array[][4], int row, int block, int index=2)
{
	for(int i=index ; i>=0 ; i--)
		array[row][i+1] = array[row][i];
	array[row][0] = block;
}

void way4SetAssoLRU(int block, int cache[][4], int size, int hit[])
{
	int cacheLine = block % size;

	for(int i=0 ; i<4 ; i++)
	{
		if(cache[cacheLine][i] == block)
		{
			hit[1]++;
			shift(cache, cacheLine, block, i-1);
			return;
		}
	}

	hit[0]++;
	if(cache[cacheLine][0] == -1)
	{
		int index = 0;
		for(int i=1 ; i<4 ; i++)
			if(cache[cacheLine][i] == -1)
				index = i;
		cache[cacheLine][index] = block;
	}
	else
		shift(cache, cacheLine, block);
}

void way4SetAssoFIFO(int block, int cache[][4], int size, int hit[])
{
	int cacheLine = block % size;

	for(int i=0 ; i<4 ; i++)
	{
		if(cache[cacheLine][i] == block)
		{
			hit[1]++;
			return;
		}
	}

	hit[0]++;
	if(cache[cacheLine][0] == -1)
	{
		int index = 0;
		for(int i=1 ; i<4 ; i++)
			if(cache[cacheLine][i] == -1)
				index = i;
		cache[cacheLine][index] = block;
	}
	else
		shift(cache, cacheLine, block);
}

void directMapping(int block, int cache[], int size, int hit[])
{
	int cacheLine = block % size;
	if (cache[cacheLine] == block)
	{
		hit[1]++;
		return;
	}
	hit[0]++;
	if (cache[cacheLine] == -1)
		cache[cacheLine] = block;
	else
		cache[cacheLine] = block;
}

int main()
{
	ifstream inFile;
	inFile.open("address.txt");
	ofstream myfile ("result.txt");

	string str;

	int hit16_64[2], hit16_128[2], hit16_256[2], hit16_512[2], hit32_32[2], hit32_64[2], hit32_128[2], hit32_256[2];
	int cache16_64[64], cache16_128[128], cache16_256[256], cache16_512[512];
	int cache32_32[32], cache32_64[64], cache32_128[128], cache32_256[256];
	fill_n(cache16_64, 64, -1);
	fill_n(cache16_128, 128, -1);
	fill_n(cache16_256, 256, -1);
	fill_n(cache16_512, 512, -1);
	fill_n(cache32_32, 32, -1);
	fill_n(cache32_64, 64, -1);
	fill_n(cache32_128, 128, -1);
	fill_n(cache32_256, 256, -1);

	int cachef16_16[16][4], cachef16_32[32][4], cachef16_64[64][4], cachef16_128[128][4];
	int cachef32_8[8][4], cachef32_16[16][4], cachef32_32[32][4], cachef32_64[64][4];
	int hitfi16_16[2], hitfi16_32[2], hitfi16_64[2], hitfi16_128[2], hitfi32_8[2], hitfi32_16[2], hitfi32_32[2], hitfi32_64[2];
	filln(cachef16_16, 16, -1);
	filln(cachef16_32, 32, -1);
	filln(cachef16_64, 64, -1);
	filln(cachef16_128, 128, -1);
	filln(cachef32_8, 8, -1);
	filln(cachef32_16, 16, -1);
	filln(cachef32_32, 32, -1);
	filln(cachef32_64, 64, -1);

	int cachel16_16[16][4], cachel16_32[32][4], cachel16_64[64][4], cachel16_128[128][4];
	int cachel32_8[8][4], cachel32_16[16][4], cachel32_32[32][4], cachel32_64[64][4];
	int hitlru16_16[2], hitlru16_32[2], hitlru16_64[2], hitlru16_128[2], hitlru32_8[2], hitlru32_16[2], hitlru32_32[2], hitlru32_64[2];
	filln(cachel16_16, 16, -1);
	filln(cachel16_32, 32, -1);
	filln(cachel16_64, 64, -1);
	filln(cachel16_128, 128, -1);
	filln(cachel32_8, 8, -1);
	filln(cachel32_16, 16, -1);
	filln(cachel32_32, 32, -1);
	filln(cachel32_64, 64, -1);

	if (!inFile)
	{
    	cerr << "Unable to open file datafile.txt";
    	exit(1);   // call system to stop
	}

	while(getline(inFile, str))
	{
		unsigned int addr = hexadecimalToDecimal(str);
		directMapping(addr/16, cache16_64, 64, hit16_64);
		directMapping(addr/16, cache16_128, 128, hit16_128);
		directMapping(addr/16, cache16_256, 256, hit16_256);
		directMapping(addr/16, cache16_512, 512, hit16_512);
		directMapping(addr/32, cache32_32, 32, hit32_32);
		directMapping(addr/32, cache32_64, 64, hit32_64);
		directMapping(addr/32, cache32_128, 128, hit32_128);
		directMapping(addr/32, cache32_256, 256, hit32_256);
		way4SetAssoFIFO(addr/16, cachef16_16, 16, hitfi16_16);
		way4SetAssoFIFO(addr/16, cachef16_32, 32, hitfi16_32);
		way4SetAssoFIFO(addr/16, cachef16_64, 64, hitfi16_64);
		way4SetAssoFIFO(addr/16, cachef16_128, 128, hitfi16_128);
		way4SetAssoFIFO(addr/32, cachef32_8, 8, hitfi32_8);
		way4SetAssoFIFO(addr/32, cachef32_16, 16, hitfi32_16);
		way4SetAssoFIFO(addr/32, cachef32_32, 32, hitfi32_32);
		way4SetAssoFIFO(addr/32, cachef32_64, 64, hitfi32_64);
		way4SetAssoLRU(addr/16, cachel16_16, 16, hitlru16_16);
		way4SetAssoLRU(addr/16, cachel16_32, 32, hitlru16_32);
		way4SetAssoLRU(addr/16, cachel16_64, 64, hitlru16_64);
		way4SetAssoLRU(addr/16, cachel16_128, 128, hitlru16_128);
		way4SetAssoLRU(addr/32, cachel32_8, 8, hitlru32_8);
		way4SetAssoLRU(addr/32, cachel32_16, 16, hitlru32_16);
		way4SetAssoLRU(addr/32, cachel32_32, 32, hitlru32_32);
		way4SetAssoLRU(addr/32, cachel32_64, 64, hitlru32_64);
	}

	cout << "Mapping Function : Direct Mapping" << endl;
	cout << "Block Size = 16 bytes" << endl;
	cout << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
	cout << "\t" << 1024 << "\t\t" << hit16_64[1] << "\t" << hit16_64[0] << "\t  " << (float)hit16_64[0]/(hit16_64[0] + hit16_64[1]) << endl;
	cout << "\t" << 2048 << "\t\t" << hit16_128[1] << "\t" << hit16_128[0] << "\t  " << (float)hit16_128[0]/(hit16_128[0] + hit16_128[1]) << endl;
	cout << "\t" << 4096 << "\t\t" << hit16_256[1] << "\t" << hit16_256[0] << "\t  " << (float)hit16_256[0]/(hit16_256[0] + hit16_256[1]) << endl;
	cout << "\t" << 8192 << "\t\t" << hit16_512[1] << "\t" << hit16_512[0] << "\t  " << (float)hit16_512[0]/(hit16_512[0] + hit16_512[1]) << endl;
	cout << endl;
	cout << "Block Size = 32 bytes" << endl;
	cout << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
	cout << "\t" << 1024 << "\t\t" << hit32_32[1] << "\t" << hit32_32[0] << "\t  " << (float)hit32_32[0]/(hit32_32[0] + hit32_32[1]) << endl;
	cout << "\t" << 2048 << "\t\t" << hit32_64[1] << "\t" << hit32_64[0] << "\t  " << (float)hit32_64[0]/(hit32_64[0] + hit32_64[1]) << endl;
	cout << "\t" << 4096 << "\t\t" << hit32_128[1] << "\t" << hit32_128[0] << "\t  " << (float)hit32_128[0]/(hit32_128[0] + hit32_128[1]) << endl;
	cout << "\t" << 8192 << "\t\t" << hit32_256[1] << "\t" << hit32_256[0] << "\t  " << (float)hit32_256[0]/(hit32_256[0] + hit32_256[1]) << endl;

	cout << endl;
	cout << "Mapping Function : 4-way Set Assosciative" << endl;
	cout << "Replacement Algorithm : FIFO" << endl << endl;
	cout << "Block Size = 16 bytes" << endl;
	cout << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
	cout << "\t" << 1024 << "\t\t" << hitfi16_16[1] << "\t" << hitfi16_16[0] << "\t  " << (float)hitfi16_16[0]/(hitfi16_16[0] + hitfi16_16[1]) << endl;
	cout << "\t" << 2048 << "\t\t" << hitfi16_32[1] << "\t" << hitfi16_32[0] << "\t  " << (float)hitfi16_32[0]/(hitfi16_32[0] + hitfi16_32[1]) << endl;
	cout << "\t" << 4096 << "\t\t" << hitfi16_64[1] << "\t" << hitfi16_64[0] << "\t  " << (float)hitfi16_64[0]/(hitfi16_64[0] + hitfi16_64[1]) << endl;
	cout << "\t" << 8192 << "\t\t" << hitfi16_128[1] << "\t" << hitfi16_128[0] << "\t  " << (float)hitfi16_128[0]/(hitfi16_128[0] + hitfi16_128[1]) << endl;
	cout << endl;
	cout << "Block Size = 32 bytes" << endl;
	cout << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
	cout << "\t" << 1024 << "\t\t" << hitfi32_8[1] << "\t" << hitfi32_8[0] << "\t  " << (float)hitfi32_8[0]/(hitfi32_8[0] + hitfi32_8[1]) << endl;
	cout << "\t" << 2048 << "\t\t" << hitfi32_16[1] << "\t" << hitfi32_16[0] << "\t  " << (float)hitfi32_16[0]/(hitfi32_16[0] + hitfi32_16[1]) << endl;
	cout << "\t" << 4096 << "\t\t" << hitfi32_32[1] << "\t" << hitfi32_32[0] << "\t  " << (float)hitfi32_32[0]/(hitfi32_32[0] + hitfi32_32[1]) << endl;
	cout << "\t" << 8192 << "\t\t" << hitfi32_64[1] << "\t" << hitfi32_64[0] << "\t  " << (float)hitfi32_64[0]/(hitfi32_64[0] + hitfi32_64[1]) << endl;

	cout << endl;
	cout << "Mapping Function : 4-way Set Assosciative" << endl;
	cout << "Replacement Algorithm : LRU" << endl << endl;
	cout << "Block Size = 16 bytes" << endl;
	cout << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
	cout << "\t" << 1024 << "\t\t" << hitlru16_16[1] << "\t" << hitlru16_16[0] << "\t  " << (float)hitlru16_16[0]/(hitlru16_16[0] + hitlru16_16[1]) << endl;
	cout << "\t" << 2048 << "\t\t" << hitlru16_32[1] << "\t" << hitlru16_32[0] << "\t  " << (float)hitlru16_32[0]/(hitlru16_32[0] + hitlru16_32[1]) << endl;
	cout << "\t" << 4096 << "\t\t" << hitlru16_64[1] << "\t" << hitlru16_64[0] << "\t  " << (float)hitlru16_64[0]/(hitlru16_64[0] + hitlru16_64[1]) << endl;
	cout << "\t" << 8192 << "\t\t" << hitlru16_128[1] << "\t" << hitlru16_128[0] << "\t  " << (float)hitlru16_128[0]/(hitlru16_128[0] + hitlru16_128[1]) << endl;
	cout << endl;
	cout << "Block Size = 32 bytes" << endl;
	cout << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
	cout << "\t" << 1024 << "\t\t" << hitlru32_8[1] << "\t" << hitlru32_8[0] << "\t  " << (float)hitlru32_8[0]/(hitlru32_8[0] + hitlru32_8[1]) << endl;
	cout << "\t" << 2048 << "\t\t" << hitlru32_16[1] << "\t" << hitlru32_16[0] << "\t  " << (float)hitlru32_16[0]/(hitlru32_16[0] + hitlru32_16[1]) << endl;
	cout << "\t" << 4096 << "\t\t" << hitlru32_32[1] << "\t" << hitlru32_32[0] << "\t  " << (float)hitlru32_32[0]/(hitlru32_32[0] + hitlru32_32[1]) << endl;
	cout << "\t" << 8192 << "\t\t" << hitlru32_64[1] << "\t" << hitlru32_64[0] << "\t  " << (float)hitlru32_64[0]/(hitlru32_64[0] + hitlru32_64[1]) << endl;

	if(myfile.is_open())
	{
		myfile << "Mapping Function : Direct Mapping" << endl;
		myfile << "Block Size = 16 bytes" << endl;
		myfile << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
		myfile << "\t" << 1024 << "\t\t" << hit16_64[1] << "\t" << hit16_64[0] << "\t  " << (float)hit16_64[0]/(hit16_64[0] + hit16_64[1]) << endl;
		myfile << "\t" << 2048 << "\t\t" << hit16_128[1] << "\t" << hit16_128[0] << "\t  " << (float)hit16_128[0]/(hit16_128[0] + hit16_128[1]) << endl;
		myfile << "\t" << 4096 << "\t\t" << hit16_256[1] << "\t" << hit16_256[0] << "\t  " << (float)hit16_256[0]/(hit16_256[0] + hit16_256[1]) << endl;
		myfile << "\t" << 8192 << "\t\t" << hit16_512[1] << "\t" << hit16_512[0] << "\t  " << (float)hit16_512[0]/(hit16_512[0] + hit16_512[1]) << endl;
		myfile << endl;
		myfile << "Block Size = 32 bytes" << endl;
		myfile << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
		myfile << "\t" << 1024 << "\t\t" << hit32_32[1] << "\t" << hit32_32[0] << "\t  " << (float)hit32_32[0]/(hit32_32[0] + hit32_32[1]) << endl;
		myfile << "\t" << 2048 << "\t\t" << hit32_64[1] << "\t" << hit32_64[0] << "\t  " << (float)hit32_64[0]/(hit32_64[0] + hit32_64[1]) << endl;
		myfile << "\t" << 4096 << "\t\t" << hit32_128[1] << "\t" << hit32_128[0] << "\t  " << (float)hit32_128[0]/(hit32_128[0] + hit32_128[1]) << endl;
		myfile << "\t" << 8192 << "\t\t" << hit32_256[1] << "\t" << hit32_256[0] << "\t  " << (float)hit32_256[0]/(hit32_256[0] + hit32_256[1]) << endl;

		myfile << endl;
		myfile << "Mapping Function : 4-way Set Assosciative" << endl;
		myfile << "Replacement Algorithm : FIFO" << endl << endl;
		myfile << "Block Size = 16 bytes" << endl;
		myfile << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
		myfile << "\t" << 1024 << "\t\t" << hitfi16_16[1] << "\t" << hitfi16_16[0] << "\t  " << (float)hitfi16_16[0]/(hitfi16_16[0] + hitfi16_16[1]) << endl;
		myfile << "\t" << 2048 << "\t\t" << hitfi16_32[1] << "\t" << hitfi16_32[0] << "\t  " << (float)hitfi16_32[0]/(hitfi16_32[0] + hitfi16_32[1]) << endl;
		myfile << "\t" << 4096 << "\t\t" << hitfi16_64[1] << "\t" << hitfi16_64[0] << "\t  " << (float)hitfi16_64[0]/(hitfi16_64[0] + hitfi16_64[1]) << endl;
		myfile << "\t" << 8192 << "\t\t" << hitfi16_128[1] << "\t" << hitfi16_128[0] << "\t  " << (float)hitfi16_128[0]/(hitfi16_128[0] + hitfi16_128[1]) << endl;
		myfile << endl;
		myfile << "Block Size = 32 bytes" << endl;
		myfile << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
		myfile << "\t" << 1024 << "\t\t" << hitfi32_8[1] << "\t" << hitfi32_8[0] << "\t  " << (float)hitfi32_8[0]/(hitfi32_8[0] + hitfi32_8[1]) << endl;
		myfile << "\t" << 2048 << "\t\t" << hitfi32_16[1] << "\t" << hitfi32_16[0] << "\t  " << (float)hitfi32_16[0]/(hitfi32_16[0] + hitfi32_16[1]) << endl;
		myfile << "\t" << 4096 << "\t\t" << hitfi32_32[1] << "\t" << hitfi32_32[0] << "\t  " << (float)hitfi32_32[0]/(hitfi32_32[0] + hitfi32_32[1]) << endl;
		myfile << "\t" << 8192 << "\t\t" << hitfi32_64[1] << "\t" << hitfi32_64[0] << "\t  " << (float)hitfi32_64[0]/(hitfi32_64[0] + hitfi32_64[1]) << endl;

		myfile << endl;
		myfile << "Mapping Function : 4-way Set Assosciative" << endl;
		myfile << "Replacement Algorithm : LRU" << endl << endl;
		myfile << "Block Size = 16 bytes" << endl;
		myfile << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
		myfile << "\t" << 1024 << "\t\t" << hitlru16_16[1] << "\t" << hitlru16_16[0] << "\t  " << (float)hitlru16_16[0]/(hitlru16_16[0] + hitlru16_16[1]) << endl;
		myfile << "\t" << 2048 << "\t\t" << hitlru16_32[1] << "\t" << hitlru16_32[0] << "\t  " << (float)hitlru16_32[0]/(hitlru16_32[0] + hitlru16_32[1]) << endl;
		myfile << "\t" << 4096 << "\t\t" << hitlru16_64[1] << "\t" << hitlru16_64[0] << "\t  " << (float)hitlru16_64[0]/(hitlru16_64[0] + hitlru16_64[1]) << endl;
		myfile << "\t" << 8192 << "\t\t" << hitlru16_128[1] << "\t" << hitlru16_128[0] << "\t  " << (float)hitlru16_128[0]/(hitlru16_128[0] + hitlru16_128[1]) << endl;
		myfile << endl;
		myfile << "Block Size = 32 bytes" << endl;
		myfile << "   Cache Size(Bytes)\tHits\tMisses\tMiss Ratio" << endl;
		myfile << "\t" << 1024 << "\t\t" << hitlru32_8[1] << "\t" << hitlru32_8[0] << "\t  " << (float)hitlru32_8[0]/(hitlru32_8[0] + hitlru32_8[1]) << endl;
		myfile << "\t" << 2048 << "\t\t" << hitlru32_16[1] << "\t" << hitlru32_16[0] << "\t  " << (float)hitlru32_16[0]/(hitlru32_16[0] + hitlru32_16[1]) << endl;
		myfile << "\t" << 4096 << "\t\t" << hitlru32_32[1] << "\t" << hitlru32_32[0] << "\t  " << (float)hitlru32_32[0]/(hitlru32_32[0] + hitlru32_32[1]) << endl;
		myfile << "\t" << 8192 << "\t\t" << hitlru32_64[1] << "\t" << hitlru32_64[0] << "\t  " << (float)hitlru32_64[0]/(hitlru32_64[0] + hitlru32_64[1]) << endl;

		myfile.close();
	}
	else
		myfile << "Unable to open file";
	inFile.close();
	return 0;
}