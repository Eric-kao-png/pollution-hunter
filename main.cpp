#include "Game.hpp"

int main (void) {
      int successfullyLoadData = system("/opt/homebrew/bin/python3.11 getPM25/getPM25.py");

      if (successfullyLoadData != 0) {
            std::cerr << "❌ 執行 Python 腳本失敗，錯誤碼：" << successfullyLoadData << std::endl;
      } else {
            std::cout << "✅ 成功執行 Python 腳本！" << std::endl;
      }

      Game game;
      game.run();

      return 0;
}     