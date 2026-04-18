// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <cctype>
#include <sstream>

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> operators;
  std::string postfix = "";
  std::map<char, int> priority;

  priority['+'] = priority['-'] = 1;
  priority['*'] = priority['/'] = 2;

  size_t pos = 0;
  while (pos < inf.size()) {
    char symbol = inf[pos];

    if (std::isspace(static_cast<unsigned char>(symbol))) {
      ++pos;
      continue;
    }

    if (std::isdigit(static_cast<unsigned char>(symbol))) {
      std::string number = "";
      while (pos < inf.size() && std::isdigit(static_cast<unsigned char>(inf[pos]))) {
        number += inf[pos];
        ++pos;
      }
      postfix += number + " ";
      continue;
    }

    if (symbol == '(') {
      operators.Push(symbol);
      ++pos;
      continue;
    }

    if (symbol == ')') {
      while (!operators.IsEmpty() && operators.Top() != '(') {
        postfix += operators.Pop();
        postfix += " ";
      }
      if (!operators.IsEmpty()) {
        operators.Pop();
      }
      ++pos;
      continue;
    }

    if (priority.find(symbol) != priority.end()) {
      while (!operators.IsEmpty() && operators.Top() != '(' &&
             priority[operators.Top()] >= priority[symbol]) {
        postfix += operators.Pop();
        postfix += " ";
      }
      operators.Push(symbol);
      ++pos;
      continue;
    }

    ++pos;
  }

  while (!operators.IsEmpty()) {
    postfix += operators.Pop();
    postfix += " ";
  }

  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }

  return postfix;
}

int eval(const std::string& pref) {
  TStack<int, 100> numbers;
  std::istringstream iss(pref);
  std::string token;

  while (iss >> token) {
    if (!token.empty() && std::isdigit(static_cast<unsigned char>(token[0]))) {
      numbers.Push(std::stoi(token));
    } else if (!token.empty()) {
      int right = numbers.Pop();
      int left  = numbers.Pop();
      char op   = token[0];

      if (op == '+')      numbers.Push(left + right);
      else if (op == '-') numbers.Push(left - right);
      else if (op == '*') numbers.Push(left * right);
      else if (op == '/') numbers.Push(left / right);
    }
  }

  return numbers.Pop();
}
