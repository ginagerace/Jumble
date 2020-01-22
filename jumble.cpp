#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

void ssort(std::string &s) {
  std::sort(s.begin(), s.end());
}

//   usage:   ./jumble <filename>
//   example:  ./jumble words.txt

int main(int argc, char *argv[]){

// the variable wordList is an unordered_map from strings to integers.

  std::unordered_map<std::string, std::vector<std::string>> wordList;
  std::ifstream file;
  std::string word, key, largestKey;
  int largestSize = 0;
  int counter = 0;

  if(argc != 2) {
    std::cout << "usage:  ./jumble <filename>\n";
    std::cout << "goodbye\n";
    return 1;
  }

//argv[1] is a C-string which is the filname specified by the user.
//Let's try to open it.

  file.open(argv[1], std::ios::in);

  if(!file.is_open()){
    std::cout << "Error: could not open file '" <<
                     argv[1] << "'\n";
    std::cout << "goodbye\n";
    return 1;
  }

  std::cout << "reading input file...\n";

  while(file >> word) {
    key = word;
    ssort(key);

    wordList[key].push_back(word);

    if(wordList[key].size() > largestSize){
        largestSize = wordList[key].size();
        largestKey = key;
    }
    counter++;
  }

  std::cout <<
    "  start entering jumbled words (ctrl-d to terminate)\n\n";
  std::cout << "> ";

  while(std::cin >> word) {
    key = word;
    ssort(key);

    if(wordList.count(key)==0) {
       std::cout << "no anagrams found...try again"<< "'\n";
    }
    else {
       std::cout << "English Anagrams Found:" << "\n";
       for(int i=0; i<wordList[key].size(); i++)
            std::cout << "     " << wordList[key].at(i) << "\n";
    }
    std::cout << "> ";
  }
  // user has quit.  Let's dump the map contents

  std::cout << "REPORT:" << "\n";

  //EDIT below
  printf("\n   num_words             : %d", counter);
  printf("\n   num_classes           : %d", (int)wordList.size());
  printf("\n   size-of-largest-class : %d", largestSize);
  std::cout << "\n   largest-class key     : '" << largestKey << "'";
  printf("\n   members of largest class:\n");
  for(int i=0; i<wordList[largestKey].size(); i++)
            std::cout << "     '" << wordList[largestKey].at(i) << "'\n";

  return 0;
}
