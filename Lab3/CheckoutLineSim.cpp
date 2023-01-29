/*
 * File: CheckoutLine.cpp
 * ----------------------
 * This program simulates a checkout line, such as one you
 * might encounter in a grocery store.  Customers arrive at
 * the checkout stand and get in line.  Those customers wait
 * in the line until the cashier is free, at which point
 * they are served and occupy the cashier for some period
 * of time.  After the service time is complete, the cashier
 * is free to serve the next customer in the line.
 *
 * In each unit of time, up to the constant SIMULATION_TIME,
 * the following operations are performed:
 *
 * 1. Determine whether a new customer has arrived.
 *    New customers arrive randomly, with a probability
 *    determined by the constant ARRIVAL_RATE, taken from the
 *    input file.
 *
 * 2. If the cashier is busy, note that the cashier has
 *    spent another minute with that customer.  Eventually,
 *    the customer's time request is satisfied, which frees
 *    the cashier.
 *
 * 3. If the cashier is free, serve the next customer in line.
 *    Each customer is given the same amount of time at the
 *    register (SERVICE_TIME), which is taken from the file.
 *
 * At the end of the simulation, the program displays the
 * simulation constants and the following computed results:
 *
 * o  The number of customers served
 * o  The average time spent in waiting line
 * o  The average number of people in line
 * o  The number of people who left because the line was full.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <cctype>
using namespace std;
// Number of parameters in each simulation
const int PARAMS_MAX = 5;
//
// Returns 'true' if a customer arrived during this minute, using
// a random number.
//
bool customerArrived(double prob) {
        double rv = rand() / (double(RAND_MAX) + 1);
        return (rv < prob);
}
//
// Runs the actual simulation.  This function returns the results
// of the simulation through the reference parameters, which record
// the number of customers served, the total number of minutes that
// customers were waiting in a queue, and the sum of the queue length
// in each time step.
//
void runSimulation(int simTime, double arrivalRate,
        int serviceTime, int maxLine,
        int &nServed, int &totalWait,
        int &totalLength, int &totalDropped) {
    queue<int> customerQueue;
    int curCustomerTime = 0;
    int curSize;
    // Main simulation loop
    for (int curTime = 0; curTime < simTime; curTime++) {
        // At the top of this loop, we're starting a new minute
        // of the simulation.
        // GENERAL STEPS:
        //
        // 1) First, add the current length of the line to an accumulator
        //    variable (like totalLineSize) of the queue to
        //    compute the average after the sim completes.
        curSize = customerQueue.size();
        totalLength += curSize;

        // 2) See if a customer is arriving this minute.
        if (customerArrived(arrivalRate)) {
            // 2a) See if the line is at max size.  If it is, this
            //     customer turns away and leaves (is a "dropped" customer).
            if(customerQueue.size() == maxLine){
                totalDropped ++;
            }
            else{
                customerQueue.push(curTime);
            }
        }
        // 3) See if a customer is currently being serviced.
        //    One way to do this is to keep a counter such as
        //    'curCustomerTime', which is first set to serviceTime,
        //    then decremented each time through the loop at this point.
        if(curCustomerTime > 0) {
            curCustomerTime --;
            }
        //
        // 4) If a customer is NOT being serviced, it's time to get
        //    the next customer from the line.  See if the line is
        //    non-empty.
        else{
            if (customerQueue.size() != 0) {
            // 4a) See how long they waited and record it
            // In order to compute the total wait time we have to know the individual people's wait time and sum up the all individual waiting time.
                totalWait += curTime - customerQueue.front();
            // 4b) Get the next customer from the line, and keep a counter
            //     for how many were serviced.
                customerQueue.pop();
                nServed++;
                curCustomerTime = serviceTime;

            }
        }
    }
}
// Read one simulation from the file.
//
// Each simulation is specified by 5 values, each on a single line:
// - Name (a string)
// - Simulation time - the overall number of minutes for the simulation
// - Arrival rate - per-minute arrival rate of customers
// - Service time - the time each customer takes at the register
// - Max. line size - the maximum number of people in line
//
bool readNextSimulation(ifstream &f, string &name, int &simulationTime,
        double &arrivalRate, int &serviceTime, int &lineSize) {
    string buf;
    string fileValues[5];
    int i = 0;
    while (getline(f, buf)) {
        // We've reached the end of the file, indicate to caller
        // there are no more simulations.
        if (f.eof())
            break;
        fileValues[i++] = buf;
        if (i == PARAMS_MAX) {
            // Fill in the values, converting to the right type
            name = fileValues[0];
            // Remove linefeed if necessary
            if (name.size() != 0 && name[name.size() - 1] == '\r')
                name.erase(name.size() - 1);
            simulationTime = atoi(fileValues[1].c_str());
            arrivalRate = atof(fileValues[2].c_str());
            serviceTime = atoi(fileValues[3].c_str());
            lineSize = atoi(fileValues[4].c_str());
            return (true);
        }
    }
    return (false);
}
//
// Reports the results of the simulation in tabular format.
//
void printReport(string name, int simTime, double arrivalRate,
        int serviceTime, int maxLine, int nServed, int totalWait,
        int totalLength, int totalDropped) {
    // Left-justify everything
    cout << left;
    // Print a table
    cout << endl;
    cout << setw(25) << "Simulation name: " << setw(12) << name << endl;
    cout << "--------------------------------------" << endl;
    cout << setw(25) << "Simulation time: " << setw(12) << simTime << endl;
    cout << setw(25) << "Arrival rate: " << setw(12) << arrivalRate << endl;
    cout << setw(25) << "Service time: " << setw(12) << serviceTime << endl;
    cout << setw(25) << "Max line size: " << setw(12) << maxLine << endl;
    cout << endl;
    cout << setw(25) << "Customers served:" << setw(12) << nServed << endl;
    cout << setw(25) << "Average wait time:" << double(totalWait) / nServed <<
endl;
    cout << setw(25) << "Average line length:" << setw(12)
         << double(totalLength) / simTime << endl;
   cout << setw(25) << "Total dropped customers:" << setw(12)
         << totalDropped << endl;
}
/* Main program */
int main() {
    // Sim results
    int nServed=0;
    int totalWait=0;
    int totalLength=0;
    int totalDropped=0;
    // Sim parameters
    string name;
    int simTime;
    double arrivalRate;
    int serviceTime;
    int maxLine;
    string buf;
    ifstream f("simtest1.txt");
    // initialize the random number generator
    srand(int(time(NULL)));
    if (!f.good()) {
       cerr << "Invalid file, exiting." << endl;
       return (-1);
    }
    while (readNextSimulation(f, name, simTime, arrivalRate, serviceTime, maxLine))
{
           runSimulation(simTime, arrivalRate, serviceTime, maxLine,
                nServed, totalWait, totalLength, totalDropped);
           printReport(name, simTime, arrivalRate,
                serviceTime, maxLine, nServed, totalWait, totalLength,
totalDropped);
    }
    return 0;
}
