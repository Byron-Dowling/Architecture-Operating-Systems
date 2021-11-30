/*
    Name:       Byron Dowling, Paxton Proctor, Fowzy Alsaud
    Course:     4103 Operating Systems
    Date:       11/29/2021

    Assignment: Mini Project #4
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


typedef vector<unsigned int> VUI;       // Typedef for a vector of unsigned ints


struct BitMap
{
    unsigned int x;         // Decimal value
    unsigned int BT[32];    // Temp array to hold the binary values
    vector<VUI> LE;         // Matrix to split the binary string into the 4 groups of 8 bit strings
    VUI File_System;        // Container for the actual BitMap
    int Skips;              // Skip Counter
    int Block_Size;         // Value for how big a file we are working with


    /*
        Default constructor will initilaize a random value in the specified range of
        70,000 to 2,000,000. Also will initialize block size to 4 since the assignment
        states that a file of 4 blocks of storage will be written.
    */

    BitMap()
    {
        x = rand();
        x = x % 1300000;
        x = x + 70000;

        Skips = 0;
        Block_Size = 4;
    }


    /*
        Converting unsigned int value x into Binary via u-int array. The code
        woll shift the number by i to get the value and perform an AND to determine
        if the binary bit should be a zero or a one.
    */

    void load_Bitmap()
    {
        for (int i = 0; i < 32; i++)
        {
            if (x >> i & 0x1)
            {
                BT[i] = 1;
            }

            else
            {
                BT[i] = 0;
            }
        }


        // Since BT holds the binary string backwards, this puts it in correct order
        for (int j = 31; j >= 0; j--)
        {
            File_System.push_back(BT[j]);
        }


        /* 
            Splitting the binary string into 4 strings to be used for the little endian format.
            The for loop takes the current index and uses some math to make sure that it will
            only copy over 8 bits at a time. Values are hard coded as we know we are working
            with 32 bits.

            The actual values that are coped are put in a temp vector of unsigned ints and
            those are then pushed to a matrix with is a vector of vector of unsigned ints.
        */

        for (int k = 0; k < 4; k++)
        {
            VUI temp;

            for (int l = (k * 32) / 4; l < (k + 1) * (32 / 4); l++)
            {
                temp.push_back(File_System[l]);
            }

            LE.push_back(temp);
        }
    }


    /*
        This method will tally up the binary values of the 4 substrings and determine what
        order they need to be "assembled" in to construct the little endian bit map string.
        The result of each string is calculated and placed in a temp vector Assembly. We 
        then loop through the results and search in order of highest to lowest and construct
        the Bit Map string called File_System.
    */

    void little_endian()
    {
        vector<unsigned int> Assembly;


        for (int i = 0; i < LE.size(); i++)
        {
            unsigned int RT = 0;
            unsigned int BPT = 128;

            for (int j = 0; j < LE[i].size(); j++)
            {
                unsigned int temp = LE[i][j];
                RT += (temp * BPT);
                BPT = BPT / 2;
            }

            Assembly.push_back(RT);
        }

        File_System.clear();

        for (int k = 0; k < Assembly.size(); k++)
        {
            unsigned int highest = 0;
            int index = 0;

            for (int l = 0; l < Assembly.size(); l++)
            {
                if (Assembly[l] > highest)
                {
                    highest = Assembly[l];
                    index = l;
                }
            }

            Assembly[index] = 0;

            for (int m = 0; m < LE[index].size(); m++)
            {
                File_System.push_back(LE[index][m]);
            }
        }
    }


    /*
        With our File System constructed in proper Little Endian form, we just need to
        loop through the results and determine if the empty blocks have enough room to
        write our file or if we need to skip. A skip counter keeps track of this only
        counting the free blocks that aren't big enough for our file as a skip. Once
        we have a contiguous block big enough for our file, we break.
    */

    void Skip_Counter()
    {
        int consec_zero_count = 0;
        bool Free_Space = false;

        for (int i = 0; i < File_System.size(); i++)
        {
            if (File_System[i] == 1 && Free_Space == true)
            {
                Free_Space = false;
                consec_zero_count = 0;
                Skips++;
            }

            if (File_System[i] == 0)
            {
                Free_Space = true;
                consec_zero_count++;
            }

            if(consec_zero_count >= Block_Size)
            {
                break;
            }
        }
    }
};


int main()
{
    ofstream outfile;

    double RT = 0;
    double average = 0.0;

    outfile.open("Results.txt");


    /*
        Since we are doing 10 experiments, we will loop 10 times and at each loop
        execution, we create a temp struct of our Bit Map schematic which should
        initialize it with a random number in the desired range. Then we call the
        necessary methods to build the Bit Map and count the skips and then write
        the result to the outfile destination. 
    */


    for (int i = 0; i < 10; i++)
    {
        BitMap temp;
        
        temp.load_Bitmap();
        temp.little_endian();
        temp.Skip_Counter();

        outfile << "Decimal Number: " << temp.x << endl;
        outfile << "Little Endian Bit Map: ";

        for (int z = 0; z < temp.File_System.size(); z++)
        {
            outfile << temp.File_System[z] << " ";
        }

        outfile << endl;

        outfile << "Skips: " << temp.Skips << endl << endl;
        RT += temp.Skips;
    }

    average = RT / 10;

    outfile << "The average number of skips for this experiment is: " << average << endl;

    outfile.close();

    return 0;
}

