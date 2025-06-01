#ifndef DATA_MANAGERAGER_HPP
#define DATA_MANAGERAGER_HPP

#include <fstream>
#include <string>

#define DATA_PATH "./getPM25/PM25_Tainan.csv" 

enum class Difficulity {easy, midium, hard, very_hard};

class DataManager {
      private:

      std::ifstream fs;
      std::string date;
      float pm25;
      Difficulity difficulity;

      void loadData ();
      Difficulity determineDifficulity ();

      public:

      DataManager ();

      Difficulity getDifficulity () const { return difficulity; }
};

#endif // DATA_MANAGERAGER_HPP