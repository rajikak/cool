#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Lexer.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

using namespace std;

string read(const string file_name) {
  ifstream f(file_name);
  string str;

  if (f) {
    ostringstream ss;
    ss << f.rdbuf();
    str = ss.str();
  }

  return str;
}

int main() {

  string path =
      "/Users/kumarasiri/github/cool-llvm/suite"; // test suite for the compiler

  for (const auto &file : filesystem::directory_iterator(path)) {
    string content = read(file.path());
    cout << content.c_str();
    Lexer Lex(content.c_str());
    Token Tok;
    do {
      Lex.nextToken(Tok);
      Lex.printToken(Tok);
    } while (Tok.getType() != Token::END_OF_FILE);
  }
}
