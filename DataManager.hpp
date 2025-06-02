#ifndef DATA_MANAGER_HPP
#define DATA_MANAGER_HPP

#include <fstream>
#include <string>
#include <sstream>

#define DATA_PATH "./getPM25/PM25_Tainan.csv" 

enum class Difficulty {easy, midium, hard, very_hard};

class DataManager {
      private:

      std::ifstream fs;
      std::string date;
      float pm25;
      Difficulty difficulty;

      void loadData ();
      Difficulty determineDifficulty ();

      public:

      DataManager ();

      Difficulty getDifficulty () const { return difficulty; }
};

#endif // DATA_MANAGER_HPP