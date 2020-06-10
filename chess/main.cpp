#include <iostream>
#include <fstream>
#include <sstream>
#include "chess.h"
using namespace std;

Figure *** load_figures(string filename) {
    Figure *** field = new Figure**[9];
    for (int i = 0; i < 8; i++) {
        field[i] = new Figure*[9];
        for (int j = 0; j < 8; j++) {
            field[i][j] = nullptr;
        }
    }
    ifstream in(filename);
    bool color = 0;
    while (!in.eof()) {
        string line;
        getline(in, line);
        stringstream ssin(line);
        int n;
        ssin >> line >> n;
        for (int i = 0; i < n; i++) {
            getline(in, line);
            stringstream ssin(line);
            string figure;
            ssin >> figure;
            Figure * fig = Figure::figure_from_code(figure, color);
            field[fig->y][fig->x] = fig;
        }
        color = !color;
    }
    return field;
}

int main() {
  Figure *** field = load_figures("input.txt");
  ofstream out("output.txt");
  for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
          Figure * fig = field[i][j];
          if (fig) {
              auto points = fig->beats();
              for (auto point : points) {
                  Figure * beaten = field[point.second][point.first];
                  if (beaten && beaten->color != fig->color) {
                      out << *fig << "->" << *beaten << endl;
                  }
              }
          }
      }
  }
  return 0;
}
