#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define EXTRACT_MIN -1 //an invalid or non-occurring integer

int main(void) {

   int input[] = {5, 3, 6, EXTRACT_MIN, 1, 7, EXTRACT_MIN, EXTRACT_MIN, 4, 2};
   int inLen = sizeof(input) / sizeof(input[0]);

   vector<int> extract;
   vector<int> elementsForThisExtractCall;

   int i;
   for(i = 0; i < inLen; i++) {
      if(input[i] != EXTRACT_MIN) {
        elementsForThisExtractCall.push_back(input[i]);
     } else {
        sort(elementsForThisExtractCall.begin(), elementsForThisExtractCall.end());
        extract.push_back(elementsForThisExtractCall[0]);
        elementsForThisExtractCall.erase(elementsForThisExtractCall.begin());
     }
   }

   int noOfExtractCalls = extract.size();
   for(i = 0; i < noOfExtractCalls; i++)
        cout << extract[i] << " ";
   cout << endl;
   return 0;
}
