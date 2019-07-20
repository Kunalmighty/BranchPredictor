/*

Name: Kunal Baran Maiti, JHED ID: kmaiti1, CSF Spring 2019, Prog Assignment 5 (Branch Predictor Simulator)

branch.cpp - Branch Predictor Simulator for a file containing an abbreviated trace file.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <map> 
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define SIZE 1024

static unsigned long long int hashedforbah[SIZE][2]; 

static unsigned long long int hashedfortah[SIZE][2]; 

static unsigned long long int hashedforbta[SIZE][2]; 

static unsigned long long int hashedforcol[SIZE][2]; 

static unsigned long long int hashedforsat[SIZE][2]; 

static unsigned long long int hashedfortwo[SIZE][2]; 
static unsigned long long int predictorfortwo[32];

static unsigned long long int output[7][3];



static void simSTA(unsigned long long int branch, unsigned long long int target, char flag) {

    //correctly predicted
    if ((branch < target) && flag == 'N') {
        output[0][0]++; 
    }
    
    //incorrectly predicted
    if ((branch < target) && flag == 'T') {
        output[0][1]++; 
    }

    //correctly predicted
    if ((branch > target) && flag == 'N') {
        output[0][1]++; 
    }

    //incorrectly predicted
    if ((branch > target) && flag == 'T') {
        output[0][0]++; 
    }

}


static void simBAH(unsigned long long int branch, char flag) {

    unsigned short hash = branch & 0x3FF; 

    if (hashedforbah[hash][1] != branch) {
            output[1][2]++;             
    }

    //predictions    
    if (hashedforbah[hash][1] == branch) {

        //correctly predicted
        if ((hashedforbah[hash][0] == 0) && (flag == 'N')) { //if history bit is 0 and input flag is N
            output[1][0]++;                    
        }
    
        //correctly predicted
        else if ((hashedforbah[hash][0] == 1) && (flag == 'T')) { //if history bit is 1 and input flag is T
            output[1][0]++;            
        }

        //incorrectly predicted
        else if ((hashedforbah[hash][0] == 1) && (flag == 'N')) { //if history bit is 1 and input flag is N
            output[1][1]++;                  
        }

        //incorrectly predicted
        else if ((hashedforbah[hash][0] == 0) && (flag == 'T')) { //if history bit is 0 and input flag is T
            output[1][1]++;             
        }       

    }

    //update hashed branch
    hashedforbah[hash][1] = branch; 

    //record history bit
    //remember that target will always be the same for the given branch address
    if (flag == 'T') {
        hashedforbah[hash][0] = 1; 
    }
    if (flag == 'N') {
        hashedforbah[hash][0] = 0; 
    }  

}



static void simTAH(unsigned long long int branch, unsigned long long int target, char flag) {

    unsigned short hash = target & 0x3FF; 

    if (hashedfortah[hash][1] != branch) {
            output[2][2]++;             
    }

    //predictions    
    if (hashedfortah[hash][1] == branch) {

        //correctly predicted
        if ((hashedfortah[hash][0] == 0) && (flag == 'N')) { //if history bit is 0 and input flag is N
            output[2][0]++;                    
        }
    
        //correctly predicted
        else if ((hashedfortah[hash][0] == 1) && (flag == 'T')) { //if history bit is 1 and input flag is T
            output[2][0]++;            
        }

        //incorrectly predicted
        else if ((hashedfortah[hash][0] == 1) && (flag == 'N')) { //if history bit is 1 and input flag is N
            output[2][1]++;                  
        }

        //incorrectly predicted
        else if ((hashedfortah[hash][0] == 0) && (flag == 'T')) { //if history bit is 0 and input flag is T
            output[2][1]++;             
        }       

    }

    //update hashed branch
    hashedfortah[hash][1] = branch; 

    //record history bit
    //remember that target will always be the same for the given branch address
    if (flag == 'T') {
        hashedfortah[hash][0] = 1; 
    } 
    if (flag == 'N') {
        hashedfortah[hash][0] = 0; 
    } 

}


static void simBTA(unsigned long long int branch, unsigned long long int target, char flag) {

    unsigned short hash = ((branch & 0x1F) << 5) | (target & 0x1F);  

    if (hashedforbta[hash][1] != branch) {
            output[3][2]++;             
    }

    //predictions    
    if (hashedforbta[hash][1] == branch) {

        //correctly predicted
        if ((hashedforbta[hash][0] == 0) && (flag == 'N')) { //if history bit is 0 and input flag is N
            output[3][0]++;                    
        }
    
        //correctly predicted
        else if ((hashedforbta[hash][0] == 1) && (flag == 'T')) { //if history bit is 1 and input flag is T
            output[3][0]++;            
        }

        //incorrectly predicted
        else if ((hashedforbta[hash][0] == 1) && (flag == 'N')) { //if history bit is 1 and input flag is N
            output[3][1]++;                  
        }

        //incorrectly predicted
        else if ((hashedforbta[hash][0] == 0) && (flag == 'T')) { //if history bit is 0 and input flag is T
            output[3][1]++;             
        }       

    }

    //update hashed branch
    hashedforbta[hash][1] = branch; 

    //record history bit
    //remember that target will always be the same for the given branch address
    if (flag == 'T') {
        hashedforbta[hash][0] = 1; 
    } 
    if (flag == 'N') {
        hashedforbta[hash][0] = 0; 
    } 

}



static void simCOL(unsigned long long int branch, unsigned long long int target, char flag) {

    unsigned short hash = branch & 0x3FF;   

    //predictions    
    if (hashedforcol[hash][1] == branch) {

        //correctly predicted
        if ((hashedforcol[hash][0] == 0) && (flag == 'N')) { //if history bit is 0 and input flag is N
            output[4][0]++;                    
        }
    
        //correctly predicted
        else if ((hashedforcol[hash][0] == 1) && (flag == 'T')) { //if history bit is 1 and input flag is T
            output[4][0]++;            
        }

        //incorrectly predicted
        else if ((hashedforcol[hash][0] == 1) && (flag == 'N')) { //if history bit is 1 and input flag is N
            output[4][1]++;                  
        }

        //incorrectly predicted
        else if ((hashedforcol[hash][0] == 0) && (flag == 'T')) { //if history bit is 0 and input flag is T
            output[4][1]++;             
        }       

    }

    else { //collision

        //correctly predicted
        if ((branch < target) && flag == 'N') {
            output[4][0]++; 
        }
        
        //incorrectly predicted
        if ((branch < target) && flag == 'T') {
            output[4][1]++; 
        }

        //correctly predicted
        if ((branch > target) && flag == 'N') {
            output[4][1]++; 
        }

        //incorrectly predicted
        if ((branch > target) && flag == 'T') {
            output[4][0]++; 
        }

    }

    //update hashed branch
    hashedforcol[hash][1] = branch; 

    //record history bit
    //remember that target will always be the same for the given branch address
    if (flag == 'T') {
        hashedforcol[hash][0] = 1; 
    }
    if (flag == 'N') {
        hashedforcol[hash][0] = 0; 
    } 

}


static void simSAT(unsigned long long int branch, char flag) {

    unsigned short hash = branch & 0x3FF;   

    if (hashedforsat[hash][1] != branch) {
            output[5][2]++;             
    }

    //predictions    
    if (hashedforsat[hash][1] == branch) {    
        
        //collision detection
        if (hashedforsat[hash][1] != branch) {
            output[5][2]++; 
        }         

        //correctly predicted
        if ((hashedforsat[hash][0] <= 1) && (flag == 'N')) { //if history bit is 0 and input flag is N
            output[5][0]++;         
        }
    
        //correctly predicted
        if ((hashedforsat[hash][0] >= 2) && (flag == 'T')) { //if history bit is 1 and input flag is T
            output[5][0]++;             
        }

        //incorrectly predicted
        if ((hashedforsat[hash][0] >= 2) && (flag == 'N')) { //if history bit is 1 and input flag is N
            output[5][1]++;             
        }

        //incorrectly predicted
        if ((hashedforsat[hash][0] <= 1) && (flag == 'T')) { //if history bit is 0 and input flag is T
            output[5][1]++;             
        }   

    }    

    hashedforsat[hash][1] = branch; 

    //update history bit
    //target will always be the same for the given branch address
    if (flag == 'T') {        
        if (hashedforsat[hash][0] < 3) {       
            hashedforsat[hash][0]++;
        }
    }   
    if (flag == 'N') {
        if (hashedforsat[hash][0] > 0) {       
            hashedforsat[hash][0]--;
        }
    }

}


static void simTWO(unsigned long long int branch, char flag) {

    unsigned short hash = branch & 0x3FF;  
    unsigned char hash2 = hashedfortwo[hash][0]; 
      
    //collision detection
    if (hashedfortwo[hash][1] != branch) {
        output[6][2]++; 
    }  

    if (hashedfortwo[hash][1] == branch) { 

        //predictions    
        //correctly predicted
        if ((predictorfortwo[hash2] == 0) && (flag == 'N')) { //if history bit is 0 and input flag is N
            output[6][0]++;           
        }
    
        //correctly predicted
        if ((predictorfortwo[hash2] == 1) && (flag == 'T')) { //if history bit is 1 and input flag is T
            output[6][0]++;    
        }

        //incorrectly predicted
        if ((predictorfortwo[hash2] == 1) && (flag == 'N')) { //if history bit is 1 and input flag is N
            output[6][1]++;             
        }

        //incorrectly predicted
        if ((predictorfortwo[hash2] == 0) && (flag == 'T')) { //if history bit is 0 and input flag is T
            output[6][1]++;           
        }   

    }

    hashedfortwo[hash][1] = branch; 

    if (flag == 'T') {
        predictorfortwo[hash2] = 1;
        hash2 = ((hash2 & 0x0F) << 1) | 1;
        hashedfortwo[hash][0] = hash2;
    } 
    if (flag == 'N') {
        predictorfortwo[hash2] = 0; 
        hash2 = ((hash2 & 0x0F) << 1) | 0;
        hashedfortwo[hash][0] = hash2;
    }

}


int main() {	

    //initialize output array
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            output[i][j] = 0;
        }
    }

    //initialize BAH array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 2; j++) {
            hashedforbah[i][j] = 0;              
        }
    }

    //initialize TAH array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 2; j++) {
            hashedfortah[i][j] = 0;              
        }
    }

    //initialize BTA array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 2; j++) {
            hashedforbta[i][j] = 0;              
        }
    }

    //initialize COL array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 2; j++) {
            hashedforcol[i][j] = 0;              
        }
    }

    //initialize SAT array
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 2; j++) {
            hashedforsat[i][j] = 0;              
        }
    }

    //initialize TWO arrays
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 2; j++) {
            hashedfortwo[i][j] = 0;              
        }
    }
    for (int i = 0; i < 32; i++) {
        predictorfortwo[i] = 0;
    }

    unsigned long long int branch_address, target_address = 0;
    char flag;

    while (scanf("%llx %llx %c", &branch_address, &target_address, &flag) == 3) {

        simSTA(branch_address, target_address, flag);
        simBAH(branch_address, flag);  
        simTAH(branch_address, target_address, flag);
        simBTA(branch_address, target_address, flag);
        simCOL(branch_address, target_address, flag);
        simSAT(branch_address, flag);     
        simTWO(branch_address, flag);        

    }                

    printf("STA: %20llu %20llu %20llu\n", output[0][0], output[0][1], output[0][2]);
    printf("BAH: %20llu %20llu %20llu\n", output[1][0], output[1][1], output[1][2]);
    printf("TAH: %20llu %20llu %20llu\n", output[2][0], output[2][1], output[2][2]);
    printf("BTA: %20llu %20llu %20llu\n", output[3][0], output[3][1], output[3][2]);
    printf("COL: %20llu %20llu %20llu\n", output[4][0], output[4][1], output[4][2]);
    printf("SAT: %20llu %20llu %20llu\n", output[5][0], output[5][1], output[5][2]);
    printf("TWO: %20llu %20llu %20llu\n", output[6][0], output[6][1], output[6][2]);

	return 0;

}