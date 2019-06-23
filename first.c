#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//variables for no prefetcher
int reads;
int writes;
int hits;
int misses;
int count =0;

//prefetch variables
int preads;
int pwrites;
int phits;
int pmisses;
int pcount =0;

int count1 =0;

struct cacheLine ** cache;

void printerNoPrefetch (int reads, int writes, int hits, int misses){
printf("no-prefetch\n");
 printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",reads,writes,hits,misses);

}

void printerPrefetch (int reads, int writes, int hits, int misses){
printf("prefetch\n");
 printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",reads,writes,hits,misses);

}


unsigned long int tagDexBits;
unsigned long int setDexBits;
unsigned long int setDexBits2;
unsigned long int tagDexBits2;




typedef struct cacheLine{
    unsigned long int tag;
    int valid;
    int count;
int pf;
   
}cacheLine;

cacheLine** cacheMaker(int setNum, int assoc){
int i;
cache = (cacheLine**)malloc(setNum*sizeof(cacheLine*));
for (i=0; i<setNum; i++){
cache[i]=(cacheLine*)malloc(assoc*sizeof(cacheLine));
}
int x;
int y;
for(x=0;x<setNum; x++){
for(y=0;y<assoc;y++){
cache[x][y].valid=0;
}
}
return cache;
}

bool isPowerOfTwo(int checker){
    if(checker==0){  
   return false; }
   return (ceil(log2(checker)) == floor(log2(checker)));
}

unsigned long int addressCalc(unsigned long int addy, int blockSize){
int count = 0;
unsigned long int buf;
int remainder;
int dec=0;
while(blockSize>0){
remainder = blockSize % 10;
dec = dec + remainder * pow(16, count);
blockSize=blockSize/10;
count++;
}

buf = addy+dec;
return buf;
}
/*
void readW(unsigned long int tag, unsigned long int set, int assoc, unsigned long int addy, int blockSize, int setNum, int init){
count1++;

unsigned long int setMasker;
unsigned long int address = addy;
unsigned long int newAddress =address;
int bitmask = log2(setNum);
int blockOffset = log2(blockSize);

int i;
int x=0;
for(i =0; i<assoc; i++){

//cache hit
if(cache[set][i].valid == 1 && cache[set][i].tag ==tag){

//if init ==0 then that means this is the value that is trying to be prefetched into the cache
if(init ==0){
return;
}
//if the prefetched block hits in the cache, line replacment policy should not be updated
phits++;
x++;
pcount++;
cache[set][i].count= pcount;
return;
}

//first case of cache miss
if(cache[set][i].valid==0){
pmisses++;
preads++;
pcount++;
x++;
//if (init ==1)
cache[set][i].count = pcount;
cache[set][i].tag = tag;
cache[set][i].valid = 1;


//implement prefetcher here
if (init ==1){
newAddress = addressCalc(address, blockSize);

tagDexBits=newAddress>>(blockOffset+bitmask);
setMasker = ((1<<bitmask)-1);
setDexBits = (newAddress>>(blockOffset))&setMasker;


readW(tagDexBits, set, assoc, newAddress,blockSize ,setNum,0);}

return;
}

//miss case 2: valid data but different tag
//if(x==0){
if (i==assoc-1){
pmisses++;
preads++;
pcount++;


int in;
int minLoc=0;
int min = cache[set][0].count;

//find out where to read in the new data
for(in=0; in<assoc;in++){

if(cache[set][in].count<=min){
min = cache[set][in].count;
minLoc=in;
}
}

//minLoc is where we read in the new data
cache[set][minLoc].tag=tag;
cache[set][minLoc].count=pcount;
cache[set][minLoc].valid=1;

//implement prefetcher here
if (init==1){
newAddress = addressCalc(address, blockSize);

tagDexBits=newAddress>>(blockOffset+bitmask);
setMasker = ((1<<bitmask)-1);
setDexBits = (newAddress>>(blockOffset))&setMasker;


readW(tagDexBits, set, assoc, newAddress,blockSize ,setNum , 0);
}
}

}

}

void readWD(unsigned long int tag, unsigned long int set, int assoc, unsigned long int addy, int blockSize, int setNum, int init){
count1++;

unsigned long int setMasker;
unsigned long int address = addy;
unsigned long int newAddress =address;
int bitmask = log2(setNum);
int blockOffset = log2(blockSize);

int i;
int x=0;
for(i =0; i<assoc; i++){

//cache hit
if(cache[set][i].valid == 1 && cache[set][i].tag ==tag){
phits++;
x++;
pcount++;
cache[set][i].count= pcount;
return;
}

//first case of cache miss
if(cache[set][i].valid==0){
pmisses++;
preads++;
pcount++;
x++;
cache[set][i].count = pcount;
cache[set][i].tag = tag;
cache[set][i].valid = 1;


return;
}

//miss case 2: valid data but different tag
if(x==0){
pmisses++;
preads++;
pcount++;


int in;
int minLoc=0;
int min = cache[set][0].count;

//find out where to read in the new data
for(in=0; in<assoc;in++){

if(cache[set][in].count<=min){
min = cache[set][in].count;
minLoc=in;
}
}

//minLoc is where we read in the new data
cache[set][minLoc].tag=tag;
cache[set][minLoc].count=pcount;
cache[set][minLoc].valid=1;


}
}

}

*/

void readWO(unsigned long int tag, unsigned long int set, int assoc){
//count1++;
int i;
int x=0;
for(i =0; i<assoc; i++){

//cache hit
if(cache[set][i].valid == 1 && cache[set][i].tag ==tag){
hits++;
x++;
count++;
cache[set][i].count= count;
return;
}

//first case of cache miss
if(cache[set][i].valid==0){
misses++;
reads++;
count++;
x++;
cache[set][i].count = count;
cache[set][i].tag = tag;
cache[set][i].valid = 1;
return;
}

//miss case 2: valid data but different tag
if(x==0){
misses++;
reads++;
count++;


int in;
int minLoc=0;
int min = cache[set][0].count;

//find out where to read in the new data
for(in=0; in<assoc;in++){

if(cache[set][in].count<=min){
min = cache[set][in].count;
minLoc=in;
}
}

//minLoc is where we read in the new data
cache[set][minLoc].tag=tag;
cache[set][minLoc].count=count;
cache[set][minLoc].valid=1;

}

}
}



void writeWO(unsigned long int tag, unsigned long int set, int assoc){
//count1++;
int i;
int x = 0;
for(i=0; i<assoc; i++){

//cache hit
if(cache[set][i].valid==1 && cache[set][i].tag==tag){
hits++;
writes++;
x++;
return;
}

//cache miss first case
if(cache[set][i].valid==0){
writes++;
x++;

//read into cache
readWO(tag,set,assoc);
return;
}

//cache miss second case
if(x==0){

writes++;
readWO(tag,set,assoc);

}

}

}
/*

void writeW(unsigned long int tag, unsigned long int set, int assoc, unsigned long int addy, int blockSize, int setNum, int init){

unsigned long int setMasker;
unsigned long int address = addy;
unsigned long int newAddress;
int bitmask = log2(setNum);
int blockOffset = log2(blockSize);
int i;
int x = 0;
for(i=0; i<assoc; i++){

//cache hit
if(cache[set][i].valid==1 && cache[set][i].tag==tag){
if (init == 0){return;}
phits++;
pwrites++;
x++;
return;
}

//cache miss first case
if(cache[set][i].valid==0){
pwrites++;
x++;

//read into cache
readWD(tag,set,1,address, blockSize, setNum,1);

//implement prefetcher here
//if (init == 1){

newAddress = addressCalc(address, blockSize);

tagDexBits=newAddress>>(blockOffset+bitmask);
setMasker = ((1<<bitmask)-1);
setDexBits = (newAddress>>(blockOffset))&setMasker;

if (init ==1){
writeW(tagDexBits, set, assoc, newAddress,blockSize ,setNum ,0);
}
return;
}

//cache miss second case
if(x==0){

pwrites++;
//read into cache
readWD(tag,set,1,address, blockSize, setNum,1);
//implement prefetcher here

newAddress = addressCalc(address, blockSize);

tagDexBits=newAddress>>(blockOffset+bitmask);
setMasker = ((1<<bitmask)-1);
setDexBits = (newAddress>>(blockOffset))&setMasker;

if (init ==1){
writeW(tagDexBits, set, assoc, newAddress,blockSize ,setNum ,0);
}

}

}}
*/

void clearer(int setnum, int assoc){
int out;
int in =0;
for(out=0;out<setnum;out++){
for(in=0;in<assoc;in++){

cache[out][in].valid=0;
cache[out][in].tag=0;
cache[out][in].count=0;
}
}
}
void fetchRead1(unsigned long int firstTagDex,unsigned long int setDex1,int assoc){
int inn,jlooper,lo;
for(inn=0;inn<assoc;inn++){

switch(cache[setDex1][inn].valid){

case 0 : preads++;
pcount++;
cache[setDex1][inn].valid=1;
cache[setDex1][inn].count=pcount;
cache[setDex1][inn].tag=firstTagDex;
return;
break;

default:
if(cache[setDex1][inn].tag==firstTagDex){
return;
break;}

if(inn==assoc-1){
preads++;
lo=0;
jlooper=0;
while(jlooper<assoc){

if(cache[setDex1][jlooper].count<=cache[setDex1][lo].count){
lo=jlooper;}
jlooper++;

}
cache[setDex1][lo].valid=1;
       cache[setDex1][lo].tag=firstTagDex;
pcount++;
       cache[setDex1][lo].count=pcount;
       return;
}
}
}
}

void fetchRead2(unsigned long int firstTagDex,unsigned long int setDex1,int assoc,unsigned long int secondTagDex,unsigned long int setDex2){

int i,j,lo;

for(i=0;i<assoc;i++){

switch(cache[setDex1][i].valid) {
case 0:
pmisses++;
preads++;
pcount++;
cache[setDex1][i].valid=1;
cache[setDex1][i].tag=firstTagDex;
cache[setDex1][i].count=pcount;
fetchRead1(secondTagDex,setDex2,assoc);
return;
break;
default:
if(cache[setDex1][i].tag=firstTagDex){
phits++;
pcount++;
cache[setDex1][i].count=pcount;
return;
}if(i==assoc-1){
pmisses++;
preads++;
lo=0;
j=0;

while(j<assoc) {

if(cache[setDex1][j].count<=cache[setDex1][lo].count){
lo=j;
}
j++;}
cache[setDex1][lo].valid=1;
cache[setDex1][lo].tag=firstTagDex;
pcount++;
cache[setDex1][lo].count=pcount;
   fetchRead1(secondTagDex,setDex2,assoc);
       return;
       break;
}
}
}
return;}
void fetchWrite1(unsigned long int firstTagDex,unsigned long int setDex1,int assoc){
int ou,j,lo;
for(ou=0;ou<assoc;ou++){
switch(cache[setDex1][ou].valid) {
case 0:
preads++;
pcount++;
cache[setDex1][ou].valid=1;
cache[setDex1][ou].tag=firstTagDex;
cache[setDex1][ou].count=pcount;
return;
break;
default:
if(cache[setDex1][ou].tag==firstTagDex){
return;}
if(ou==(assoc-1)){lo=0;
preads++;
j=0;
while(j<assoc){
if(cache[setDex1][j].count<=cache[setDex1][lo].count){
lo=j;}
j++;}
cache[setDex1][lo].valid=1;
       cache[setDex1][lo].tag=firstTagDex;
pcount++;
       cache[setDex1][lo].count=pcount;
       return;
}}}
return;
}
void writer2Fetch(unsigned long int firstTagDex,unsigned long int setDex1,int assoc,unsigned long int secondTagDex,unsigned long int setDex2){

int outter,j,lo;

for(outter=0;outter<assoc;outter++){
switch(cache[setDex1][outter].valid) {
case 0:
pcount++;
cache[setDex1][outter].valid=1;
cache[setDex1][outter].tag=firstTagDex;
cache[setDex1][outter].count=pcount;
pmisses++;
preads++;
pwrites++;
fetchWrite1(secondTagDex,setDex2,assoc);
return;
break;
default:
if(cache[setDex1][outter].tag==firstTagDex){phits++;
pwrites++;
pcount++;
cache[setDex1][outter].count=pcount;
return;
break;}

if(outter==assoc-1){
pmisses++;
preads++;
pwrites++;
lo=0;
j=0;
while(j<assoc){
if(cache[setDex1][j].count<=cache[setDex1][lo].count)
{
lo=j;
}j++;}
cache[setDex1][lo].valid=1;
cache[setDex1][lo].tag=firstTagDex;
pcount++;
       cache[setDex1][lo].count=pcount;
       fetchWrite1(secondTagDex, setDex2,assoc);
       return;}}}
//memoryClearer(setnum)        
       return;}

int main(int argc, char** argv){

char op;
    int bitmask;
    int assoc;
    int setNum;
    int blockOffset;
    unsigned long int address;
    unsigned long int setMasker;
   
   
    //save the arguments
    int cacheSize = atoi(argv[1]);
    int blockSize = atoi(argv[4]);
   
    //number of block offset bits
    blockOffset = log2(blockSize);
   
    //cacheSize and blockSize must be a power of 2
    if(!(isPowerOfTwo(cacheSize))||!(isPowerOfTwo(blockSize))){
        printf("%s", "error1");
        return 0;
    }
   
    //file open
    FILE* traceFile;
    traceFile = fopen(argv[5],"r");
   
    //if file is not found
    if (traceFile == NULL){
        printf("%s","error2");
        return 0;}
   
    //check for LRU
    if(argv[3][0]!='l' || argv[3][1]!='r' || argv[3][2]!='u'){
            printf("%s", "error3");
            return 0;
        }
 
   
   //direct mapped cache
 if (argv[2][0]=='d'){
    if(argv[2][1]=='i' && argv[2][2]=='r' && argv[2][3]=='e' &&
       argv[2][4]=='c' && argv [2][5]=='t'){
       
       
        fseek(traceFile,0,SEEK_SET);
        //direct mapped cache (one block per set)
        setNum = cacheSize/blockSize;
        assoc =1;
       
        //number of set index bits
 bitmask = log2(setNum);
 
 cacheMaker(setNum,assoc);        
       
        //while loop without prefetch
        while(fscanf(traceFile, "%*x: %c %lx", &op, &address)==2) {
count1++;

//calculate bits
tagDexBits=address>>(blockOffset+bitmask);
setMasker = ((1<<bitmask)-1);
setDexBits = (address>>(blockOffset))&setMasker;



//read
if(op=='R'){

//count1++;
readWO(tagDexBits,setDexBits,1);
}

//write
else if(op=='W'){
count1++;
writeWO(tagDexBits,setDexBits,assoc);

}
     
               
}
   
    printerNoPrefetch(reads, writes, hits, misses);
   
    //sets the pointer to the top of the file
    fseek(traceFile,0,SEEK_SET);
   
   
clearer(setNum,assoc);    
unsigned long int add;
unsigned long int newAddress;

unsigned long int addy;
  int n;
  unsigned long int nAddy;
  //int setnum;
  //int assoc;
  unsigned long int bitMaskerSet;
  unsigned long int setDex1;
  int s;
  //int y =0;
  unsigned long int secondTagDex;
  int b;
  unsigned long int setDex2;
  unsigned long int longA;
   
b = log2(blockSize);
s = log2(setNum);
bitMaskerSet=((1<<s)-1);

    //prefetch while loop
while(fscanf(traceFile, "%*x: %c %lx", &op, &address)==2) {

/*
//calculate bits
tagDexBits=address>>(blockOffset+bitmask);
setMasker = ((1<<bitmask)-1);
setDexBits = (address>>(blockOffset))&setMasker;

newAddress=address+blockSize;
setDexBits2= (newAddress>>(blockOffset))&setMasker;
tagDexBits2= newAddress>>(blockOffset+bitmask);
*/

setDex1=(addy>>b)&bitMaskerSet;
longA=addy>>(b+s);
nAddy=addy+blockSize;
setDex2=(nAddy>>b)&bitMaskerSet;
secondTagDex=nAddy>>(b+s);


//read
if(op=='R'){
//readW(tagDexBits,setDexBits,1,address, blockSize, setNum,1);

//fetchRead2(tagDexBits,setDexBits,assoc,tagDexBits2,setDexBits2);
fetchRead2(longA,setDex1,assoc,secondTagDex,setDex2);
}

//write
else if(op=='W'){

//writeW(tagDexBits,setDexBits,1,address,blockSize, setNum, 1);

//writer2Fetch(tagDexBits,setDexBits,assoc,tagDexBits2,setDexBits2);
writer2Fetch(longA,setDex1,assoc,secondTagDex,setDex2);
}
     
               
    }


 
 }


 }
 
 if (argv[2][0]=='a'){
    // have to make the cache!!!!!!!!!!!!!!!!!










    //set associative
    if(argv[2][5]==':'){
        assoc = argv[2][6] -'0';

printf("%d\n", assoc);
   
   //assoc must be power of 2
   if(!(isPowerOfTwo(assoc))){
    printf("%s", "error6.1");
    return 0;
 
   }
        printf("%s\n", "works");
    }
   
    else{
        //fully associative

        setNum=1;
        assoc = cacheSize/blockSize;
bitmask=log2(setNum);

  while(fscanf(traceFile, "%*x: %c %lx", &op, &address)==2){
 

  tagDexBits=address>>(blockOffset+bitmask);
setMasker = ((1<<bitmask)-1);
setDexBits = (address>>(blockOffset))&setMasker;


  if(op=='R'){
printf("%s\n", "works");
readWO(tagDexBits, setDexBits,assoc);

}
 
  else if (op =='W'){
printf("%s\n", "works");
writeWO(tagDexBits, setDexBits, assoc);
}
 
  else{
printf("%s", "error6");
return 0;
  }
 
 
  }    
       
       
       
    }

   
 }
 
 
 
 printf("%lu\n", setDexBits2);
 printf("%lu\n", tagDexBits2);
 printf("%lu\n", tagDexBits);
 printf("%lu\n", setDexBits);
 printf("%lu\n", assoc);
 //printerNoPrefetch(reads, writes, hits, misses);
 printerPrefetch(preads,pwrites,phits,pmisses);
 //clearer(setNum,assoc);
 return 0;
}
