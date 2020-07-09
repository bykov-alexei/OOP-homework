//
// Created by alexei on 07.07.2020.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <sys/io.h>
#include <fcntl.h>
#include "Figure.h"
#include "Field.h"
using namespace std;

auto load_figures(string filename) {
    auto * v = new vector<Figure*>();
    ifstream in(filename);
    bool color = true;
    while (!in.eof()) {
        string line;
        int n;
        in >> line >> n;
        for (int i = 0; i < n; i++) {
            Figure * fig = Figure::from_stream(in);
            fig->change_color(color);
            v->push_back(fig);
        }
        color = !color;
    }
    return v;
}

int main() {
    auto v = *load_figures("fields/test2.txt");
    Field * f = new Field(v);
    f->turn = !f->turn;
    f->print();
    
    // f->turn = !f->turn;
    // f->print();

//    f->turn = !f->turn;
//    for (auto step : f->steps()) {
//        cout << step.first << " " << step.second.second << endl;
//    }
//    cout << f->check() << endl;
//    cout << f->mate() << endl;
//    for (auto step : f->steps()) {
//        auto figure = step.first;
//        auto to = step.second.first;
//        auto beats = step.second.second;
//        if (beats) {
//            cout << *figure << " " << to.first << " " << to.second << " " << (*beats) << endl;
//        } else {
//            cout << *figure << " " << to.first << " " << to.second << " " << 0 << endl;
//        }
//    }
//    for (auto fig : v) {
//        cout << *fig << endl;
//        auto res = fig->step(*f);
//        for (auto step : res) {
//            if (step.second) {
//                cout << step.first.first << step.first.second << " " << *step.second << endl;
//            } else {
//                cout << step.first.first << step.first.second << " " << step.second << endl;
//            }
//        }
//        cout << res.size() << endl;
//    }
}