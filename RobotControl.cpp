#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;

int main()
{
    //declare and initialize variables
    int inputTRIES = 1;
    int outputTRIES = 1;
    char inputfileNAME[80] = {'\0'};
    char outputfileNAME[80] = {'\0'};
    ifstream inputFILE;
    ofstream outputFILE;

    int numberofPAIRS = 0;
    int numberofpairsUSED = 0;

    int weightNUMBER[10001] = {'\0'}, colorNUMBER[10001] = {'\0'};
    int inc = 1;

    int clearBOTTLE = 0;
    int greenBOTTLE = 0;
    int brownBOTTLE = 0;

    double lengthINCREASE[10001] = {'\0'};
    double weightCALCULATED[10001] = {'\0'};
    double sumofWEIGHT = 0.0;
    double sumofWEIGHTPRIME = 0.0;
    int numberofSUMS = 0;
    bool beltSTOP = false;

    //declare and intitialize constants
    const int MAX_TRIES = 6;
    const int MAX_NUMBER_OF_PAIRS = 10000;
    const int MAX_SENSOR_VALUE = 255;
    const int COLOR_SENSOR_VALUE_1 = 240.0000;
    const int COLOR_SENSOR_VALUE_2 = 175.0000;
    const int COLOR_SENSOR_VALUE_3 = 150.0000;
    const int COLOR_SENSOR_VALUE_4 = 90.0000;
    const int COLOR_SENSOR_VALUE_5 = 20.0000;
    const int WEIGHT_SENSOR_VALUE_1 = 15.00000;
    const int WEIGHT_SENSOR_VALUE_2 = 21.00000;
    const int WEIGHT_SENSOR_VALUE_3 = 35.00000;
    const int WEIGHT_SENSOR_VALUE_4 = 41.00000;
    const int WEIGHT_SENSOR_VALUE_5 = 53.00000;
    const int WEIGHT_SENSOR_VALUE_6 = 59.00000;
    const double WEIGHT_REINITIALIZER = 499.99999;
    const int CONVERSION_FACTOR_1 = 5;
    const double CONVERSION_FACTOR_2 = 12.0;
    const int CONVERSION_FACTOR_3 = 255;

    //prompt the user:
    cout << "Please enter the name of the input file containing sensor readings: " << endl;
    cin >>  inputfileNAME;
    inputFILE.open(inputfileNAME);
    for ( inputTRIES = 1 ; ( ( inputTRIES <= MAX_TRIES) && ( inputFILE.fail() ) ); inputTRIES++ )
    {
        cerr << "The input file " << inputfileNAME << " could not be opened" << endl;
        cout << "Please enter the name of the input file containing sensor readings: " << endl;
        cin >>  inputfileNAME;
        inputFILE.open(inputfileNAME);
        if ( inputTRIES >= 5 && inputFILE.fail() )
        {
            cerr << "The input file " << inputfileNAME << " could not be opened" << endl;
            cerr << "You exceeded maximum number of tries allowed for entering the input fileName";
            return 1;
        }
    }
    cout << "Please enter the name of the output file containing simulation results: " << endl;
    cin >>  outputfileNAME;
    outputFILE.open(outputfileNAME);
    for ( outputTRIES = 1 ; ( ( outputTRIES <= MAX_TRIES) && ( outputFILE.fail() ) ); outputTRIES++ )
    {
        cerr << "The output file " << outputfileNAME << " could not be opened" << endl;
        cout << "Please enter the name of the output file containing simulation results: " << endl;
        cin >>  outputfileNAME;
        outputFILE.open(outputfileNAME);

        if ( outputTRIES >= 5 && outputFILE.fail() )
        {
            cerr << "The output file " << outputfileNAME << " could not be opened" << endl;
            cerr << "You exceeded maximum number of tries allowed for entering the output fileName";
            return 2;
        }
    }
    if(!(inputFILE >> numberofPAIRS))
    {
        if (inputFILE.eof() ) //when the input file is empty
        {
            cerr << "Data file is empty";
            inputFILE.close();
            outputFILE.close();
            return 3;
        }
        else   //for when the first character in the file cannot be part of an integer
        {
            cerr << "Unable to read the number of sensor readings";
            inputFILE.close();
            outputFILE.close();
            return 4;
        }
    }
    if ( numberofPAIRS <=0 || numberofPAIRS > MAX_NUMBER_OF_PAIRS )   //for when the number of sensor readings in the inputfile is out of range (<=0 or > 10,000)
    {
        cerr << "The number of sensor readings is out of range";
        inputFILE.close();
        outputFILE.close();
        return 5;
    }
    for ( inc = 1 ; (inc <= numberofPAIRS) ; inc++)
    {
        if ( (!(inputFILE >> weightNUMBER[inc] )))
        {
            if (inputFILE.eof() ) // If no value is read we are at the end of the data in the file
            {
                cerr << "No more data, simulation completed early on line " << (inc + 1) << " of input" << endl;
                break;
            }
        
            else //This is for when incorrect data that is not part of an integer is found.
            {
                cerr << "The number read on line " << (inc+1) << " of your input file is not an integer" << endl;    //not an integer
                cerr << "Please correct your data file and then rerun";
                inputFILE.close();
                outputFILE.close();
                return 6;
            }
        }
        if( (!(inputFILE >> colorNUMBER[inc])))// its when No light sensor measurement to match final weight measurement
        {
            if (inputFILE.eof() ) // If no value is read we are at the end of the data in the file
            {
                cerr << "No light sensor measurement to match final weight measurement" << endl;
                break;
            }
            else //This is for when incorrect data that is not part of an integer is found.
            {
                cerr << "The number read on line " << (inc+1) << " of your input file is not an integer" << endl;   //not an interger
                cerr << "Please correct your data file and then rerun";
                inputFILE.close();
                outputFILE.close();
                return 6;
                }
        }
        if(( (weightNUMBER[inc] >= 0) && (weightNUMBER[inc] <=MAX_SENSOR_VALUE) && (colorNUMBER[inc] >= 0) && (colorNUMBER[inc] <= MAX_SENSOR_VALUE)) )
        {
            lengthINCREASE[inc] = ((CONVERSION_FACTOR_1) * weightNUMBER[inc]);// conversion relationship from weightsensornumber(integer) to lenght of sprringincrease(double)
            weightCALCULATED[inc] = (CONVERSION_FACTOR_2) * ((lengthINCREASE[inc])/(CONVERSION_FACTOR_3));// conversion from springincrease (double) to actual wight value(double)
            
           if((colorNUMBER[inc] <= MAX_SENSOR_VALUE) && (colorNUMBER[inc] >= COLOR_SENSOR_VALUE_1) && (weightCALCULATED[inc] <= WEIGHT_SENSOR_VALUE_2 ) && (weightCALCULATED[inc] >= WEIGHT_SENSOR_VALUE_1 ))
            {
                clearBOTTLE++;
                cout << "The robot has rotated 90 degrees to face the clear glass conveyor belt"<< endl;
                cout << "The robot has placed " << clearBOTTLE << " clear bottles on the conveyor belt"<< endl;
                cout << "The robot rotates -90 degrees" << endl;
                outputFILE << "The robot has rotated 90 degrees to face the clear glass conveyor belt"<< endl;
                outputFILE << "The robot has placed " << clearBOTTLE << " clear bottles on the conveyor belt"<< endl;
                outputFILE << "The robot rotates -90 degrees" << endl;
            }
            else if((colorNUMBER[inc] <= COLOR_SENSOR_VALUE_2) && (colorNUMBER[inc] >= COLOR_SENSOR_VALUE_3) && (weightCALCULATED[inc] <= WEIGHT_SENSOR_VALUE_4 ) && (weightCALCULATED[inc] >=WEIGHT_SENSOR_VALUE_3 ))
            {
                greenBOTTLE++;
                cout << "The robot has rotated 150 degrees to face the green glass conveyor belt"<< endl;
                cout << "The robot has placed " << greenBOTTLE << " green bottles on the conveyor belt"<< endl;
                cout << "The robot rotates -150 degrees" << endl;
                outputFILE << "The robot has rotated 150 degrees to face the green glass conveyor belt"<< endl;
                outputFILE << "The robot has placed " << greenBOTTLE << " green bottles on the conveyor belt"<< endl;
                outputFILE << "The robot rotates -150 degrees" << endl;
            }
            else if((colorNUMBER[inc] <= COLOR_SENSOR_VALUE_4) && (colorNUMBER[inc] >= COLOR_SENSOR_VALUE_5) && (weightCALCULATED[inc] <= WEIGHT_SENSOR_VALUE_6) && (weightCALCULATED[inc] >= WEIGHT_SENSOR_VALUE_5 ))
            {
                brownBOTTLE++;
                cout << "The robot has rotated 210 degrees to face the brown glass conveyor belt"<< endl;
                cout << "The robot has placed " << brownBOTTLE << " brown bottles on the conveyor belt"<< endl;
                cout << "The robot rotates -210 degrees" << endl;
                outputFILE << "The robot has rotated 210 degrees to face the brown glass conveyor belt"<< endl;
                outputFILE << "The robot has placed " << brownBOTTLE << " brown bottles on the conveyor belt"<< endl;
                outputFILE << "The robot rotates -210 degrees" << endl;
            }
            else
            {
                sumofWEIGHT += weightCALCULATED[inc];
                sumofWEIGHTPRIME += weightCALCULATED[inc];
                cout << "The robot has rotated 270 degrees to face the waste container"<< endl;
                outputFILE << "The robot has rotated 270 degrees to face the waste container"<< endl;

                if ((sumofWEIGHTPRIME) >= WEIGHT_REINITIALIZER)
                {
                    sumofWEIGHTPRIME = 0.00;// reinitialize the wight number if it was more than 500grams
                    sumofWEIGHTPRIME += weightCALCULATED[inc];
                    beltSTOP = true;// make the belt stop when it reaches 500gramees

                    cout << "A new waste container is needed"<< endl;
                    cout << "Stop the incoming conveyor belt"<< endl;
                    cout << "A new waste container is ready for use"<< endl;
                    outputFILE << "A new waste container is needed"<< endl;
                    outputFILE << "Stop the incoming conveyor belt"<< endl;
                    outputFILE << "A new waste container is ready for use"<< endl;
                }
                cout << "The waste container now contains " << setw(8) << fixed << setprecision(3) << right << sumofWEIGHTPRIME << " grams of glass" << endl;
                outputFILE << "The waste container now contains " << setw(8) << fixed << setprecision(3) << right << sumofWEIGHTPRIME << " grams of glass" << endl;

                cout << "The robot rotates -270 degrees" << endl;
                outputFILE << "The robot rotates -270 degrees" << endl;
                if(beltSTOP == true)// in case the belt was stopped
                {
                    cout << "Start the conveyor belt" << endl;
                    outputFILE << "Start the conveyor belt"<< endl;
                    beltSTOP = false;
                }
            }

            numberofpairsUSED++;
        }
        else  // This is an error message for the measurements that were not used
        {
            cerr << "Sensor reading out of range, ignoring line " << (inc+1) << " of input" << endl;
        }
    }
    inputFILE.close();
    if ( numberofpairsUSED > 0 ) //Get a summary
    {
        cout << endl << endl << endl << endl;
        cout << left << "SUMMARY" << endl;
        cout << fixed << "The robot processed " << clearBOTTLE << " clear bottles" << endl;
        cout << fixed << "The robot processed " << greenBOTTLE << " green bottles" << endl;
        cout << fixed << "The robot processed " << brownBOTTLE << " brown bottles" << endl;
        cout << fixed << setprecision(4) << right << "The robot processed " << setw(12) << (sumofWEIGHT / 1000) << " kg  of waste glass";
        outputFILE << endl << endl << endl << endl;
        outputFILE << left << "SUMMARY" << endl;
        outputFILE << fixed << "The robot processed " << clearBOTTLE << " clear bottles" << endl;
        outputFILE << fixed << "The robot processed " << greenBOTTLE << " green bottles" << endl;
        outputFILE << fixed << "The robot processed " << brownBOTTLE << " brown bottles" << endl;
        outputFILE << fixed << setprecision(4) << right << "The robot processed " << setw(12) << (sumofWEIGHT / 1000) << " kg  of waste glass";
    }
    outputFILE.close();
    return 0;
}
