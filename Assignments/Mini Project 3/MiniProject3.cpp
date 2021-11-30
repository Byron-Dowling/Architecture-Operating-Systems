/*
    Name:       Byron Dowling, Paxton Proctor, Timothy Lockhart
    Course:     4103 Operating Systems
    Date:       11/12/2021

    Assignment: Mini Project #3
*/

#include <iostream>
#include <fstream>
#include <deque>


using namespace std;


/*
    Struct Object to hold our data in a convienent way

    - Hex_Address is read as an unsigned int using >> hex

    - command is read but not used mainly so it will not interfere
      with reading the rest of the data and in case we want to exapnd
      on the functionality of this program later, we already have it.
    
    - Page_Num is derived from doing a >> of 12 of the Hex_Address

*/

struct Entry
{
    unsigned int Hex_Address;
    int command;
    int Page_Num;
};


int main()
{
    int TLB_Size = 12;              // Pre-defined TLB size given in program instructions
    unsigned int Hits = 0;          // Hit counter
    unsigned int Misses = 0;        // Miss counter

    deque<Entry> TLB;               // Deque container representing the TLB

    ifstream Fin;                   // Input file source variable

    Fin.open("spice.txt");          // Input file
    //Fin.open("spicy.txt");

    while(!Fin.eof())               // While not EOF, we continue to read lines
    {
        Entry temp;                 // Declaring temp struct variable


        /*
            After declaring the temp struct, we read in the command (despite not used)
            and then we read in the Hex_Address using the >> hex command specified. Then
            we use that Hex_address and shift >> by 12 to get the Page Num
        */

        Fin >> temp.command;
        Fin >> hex >> temp.Hex_Address;
        temp.Page_Num = (temp.Hex_Address >>12);


        /*
            If the TLB is not full, we need to insert into the table.
            However, if the TLB is not full but also not empty, we need to make sure that
            the page number of the next address isn't already inserted into the TLB. Therefore
            if the TLB is not full but also not empty we need to loop through the reduced table.
            Assuming the table is not full and the page num is not in the TLB, we will insert.
        */

        if (TLB.size() < TLB_Size)
        {
            if (TLB.empty())
            {
                TLB.push_back(temp);
                Misses++;
            }

            else
            {
                bool found = false;

                for (int i = 0; i < TLB.size(); i++)
                {
                    if (temp.Page_Num == TLB[i].Page_Num)
                    {
                        Hits++;
                        found = true;
                    }
                }

                if (!found)
                {
                    TLB.push_back(temp);
                    Misses++;
                }
            }
        }


        /*
            If the TLB is full, we need to traverse it to see if the page num is already
            in the TLB, if it is it increments the HIT counter, if it isn't it is a MISS.

            If we get a MISS we have more work to do. Since we're doing a FIFO, a queue or
            in this case a Deque is uniquely structured to fulfill this algorithm. When a
            MISS occurs, we will pop_front the deque which will evict the oldest item in the
            deque and then we will take the current entry that we're reading from the file 
            and we will push that to the back of the queue. We will also update the MISS
            counter to keep track.
        */

        else
        {
            bool found2 = false;

            for (int i = 0; i < TLB.size(); i++)
            {
                if (temp.Page_Num == TLB[i].Page_Num)
                {
                    found2 = true;
                    Hits++;
                }
            }

            if (!found2)
            {
                TLB.pop_front();
                TLB.push_back(temp);
                Misses++;
            }
        }

    }


    cout << "Hits: " << Hits << endl;
    cout << "Misses: " << Misses << endl;

    return 0;
}
